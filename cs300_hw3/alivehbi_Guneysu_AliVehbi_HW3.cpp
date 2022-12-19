#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<list>
#include<chrono>
#include"strutils.h"

using namespace std;

/* I used the same Binary Tree class that used in hw2, I added some extra functions and structs to it,
* for the hash table I used Gulsen hoca's code but I changed it,
* BST time refers to binary search tree's time and HSH time refers to hash table's time, 
* Hash table is always faster than BST, (But only one time it was slower then bst when the query is not found in documents (I tried 5-6 times it only happens once)).
* The times can be look extremely big because I divide them by the length of the given query by user 

*/

struct DocumentItem {
    string documentName;
    int count;
};
struct Documents {
    string name;
    vector<DocumentItem> items;
};


template <class HashedObj>
class HashTable
{
public:
    explicit HashTable(const HashedObj& notFound, int size = 101);
    HashTable(const HashTable& rhs) : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),array(rhs.array), currentSize(rhs.currentSize) { }

    const HashedObj& find(const HashedObj& x) const;

    void makeEmpty();
    int getCurrentUnique();
    double getCurrentLoad();
    void insert(const HashedObj& x);
    void updateDocInfo(const HashedObj& x, const HashedObj& y);
    vector<DocumentItem> GetDocInfo(const HashedObj& x);
    void remove(const HashedObj& x);
    int hash(const HashedObj & key, int tableSize) const;
    

    const HashTable& operator=(const HashTable& rhs);

    enum EntryType { ACTIVE, EMPTY, DELETED };
private:
    struct HashEntry
    {
        HashedObj element;
        vector<DocumentItem> docs;
        EntryType info;

        HashEntry(vector<DocumentItem> d,const HashedObj& e = HashedObj(), EntryType i = EMPTY): element(e), info(i), docs(d) { }
        HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY) : element(e), info(i) { }
    };

    vector<HashEntry> array;
    int currentSize;
    const HashedObj ITEM_NOT_FOUND;

    bool isActive(int currentPos) const;
    int findPos(const HashedObj& x) const;
    void insert(const HashedObj& x, vector<DocumentItem> & d);
    void rehash();
};

bool isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}
template <class HashedObj>
int HashTable<HashedObj>::getCurrentUnique() {
    return currentSize;
}
template <class HashedObj>
double HashTable<HashedObj>::getCurrentLoad() {
    double c = currentSize;
    double as = array.size();
    double loadfac = c / as;
    return loadfac;
}
template <class HashedObj>
int HashTable<HashedObj>:: hash(const HashedObj & key, int tableSize) const
{
    int sum = 0;
    for (int i = 0; i < key.length(); i++) { // add all bytes in a loop
        sum = sum + key[i];
    }
    return (sum % tableSize);
}
template <class HashedObj>
void HashTable<HashedObj>::updateDocInfo(const HashedObj& x, const HashedObj& y) {
    int currentPos = findPos(x);
    
    if (isActive(currentPos)) {
        
        DocumentItem the_doc;
        for (int a = 0; a < array[currentPos].docs.size(); a++) {
            if (array[currentPos].docs[a].documentName == y) {
                
                array[currentPos].docs[a].count++;
                return;
            }
        }

        the_doc.count = 1;
        the_doc.documentName = y;
        array[currentPos].docs.push_back(the_doc);
    }


}
template <class HashedObj>
vector<DocumentItem> HashTable<HashedObj>::GetDocInfo(const HashedObj& x) {
    int currentPos = findPos(x);
    if (isActive(currentPos)) {
        return  array[currentPos].docs;
    }


}






int nextPrime(int n)
{
    if (n % 2 == 0)
        n++;

    for (; !isPrime(n); n += 2)
        ;

    return n;
}

template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj& notFound, int size): ITEM_NOT_FOUND(notFound), array(nextPrime(size))
{
    makeEmpty();
}
template <class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj& x) const
{
    int collisionNum = 0;
    int currentPos = hash(x, array.size());

    while (array[currentPos].info != EMPTY && array[currentPos].element != x)
    {
        currentPos += pow(++collisionNum, 2);  
        if (currentPos >= array.size()) {             
            currentPos -= array.size();
        }
    }
    return currentPos;
}
template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}
template <class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj& x)
{
    int currentPos = findPos(x);
    if (isActive(currentPos))
        array[currentPos].info = DELETED;
}
template <class HashedObj>
const HashedObj& HashTable<HashedObj>::find(const HashedObj& x)
const
{
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return array[currentPos].element;

    return   ITEM_NOT_FOUND;
}
template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj& x,vector<DocumentItem>&d)
{
    
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return;
    array[currentPos] = HashEntry(d,x, ACTIVE);

 
    if (++currentSize >= array.size() * 0.6)
        rehash();
}
template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj& x)
{

    int currentPos = findPos(x);
    if (isActive(currentPos))
        return;
    array[currentPos] = HashEntry(x, ACTIVE);


    if (++currentSize >= array.size() * 0.6)
        rehash();
}

template <class HashedObj>
void HashTable<HashedObj>::rehash()
{
    vector<HashEntry> oldArray = array;
    cout << "rehashed..." << endl;
    

    
    array.resize(nextPrime(2 * oldArray.size()));
    for (int j = 0; j < array.size(); j++)
        array[j].info = EMPTY;

    
    currentSize = 0;
    for (int i = 0; i < oldArray.size(); i++)
        if (oldArray[i].info == ACTIVE)
            insert(oldArray[i].element, oldArray[i].docs);

    double c = currentSize;
    double as = array.size();
    double load = c / as;
    cout << "previous size:" << oldArray.size() << ", new table size: " << array.size() << ", current unique word count " << currentSize << ",current load factor: "<< load << endl;
    
}

template <class HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
    
    for (int i = 0; i < array.size(); i++)
        array[i].info = EMPTY;
   
}
template <class Comparable>
class BinarySearchTree;



template <class Comparable>
class BinaryNode
{
    BinaryNode* subtree; //to add trees to sections
    Comparable item;
    Comparable element;
    BinaryNode* left;
    BinaryNode* right;
    vector<DocumentItem> docs;


    BinaryNode(const Comparable& theElement, const Comparable& theItem,
        BinaryNode* lt, BinaryNode* rt, BinaryNode* sbt)
        : element(theElement), item(theItem), left(lt), right(rt), subtree(sbt) { }


    friend class BinarySearchTree<Comparable>;
};


template <class Comparable>
class BinarySearchTree
{
public:
    explicit BinarySearchTree(const Comparable& notFound);
    BinarySearchTree(const BinarySearchTree& rhs);
    ~BinarySearchTree();

    const Comparable& findMin() const;
    const Comparable& findMax() const;
    const Comparable& find(const Comparable& x) const;
    bool isEmpty() const;
    void printTree() const;
    void printTreeInfo() const;
    void insertSubTree(const Comparable& x, BinaryNode<Comparable>*& t);
    void updateInfo(const Comparable& y, const Comparable& x);
    void updateDocInfo(const Comparable& x, const Comparable& y);
    const Comparable GetInfo(const Comparable& y);
    BinaryNode<Comparable>*& GetRoot();
    void SetRoot(BinaryNode<Comparable>*& t);
    BinaryNode<Comparable>*& GetSubTree(const Comparable& x);
    vector<DocumentItem> GetDocInfo(const Comparable& x);


    void makeEmpty();

    void insert(const Comparable& x, const Comparable& y);
    void remove(const Comparable& x);

    //const BinarySearchTree& operator=(const BinarySearchTree& rhs);
private:
    BinaryNode<Comparable>* root;
    const Comparable ITEM_NOT_FOUND;

    const Comparable& elementAt(BinaryNode<Comparable>* t) const;

    void insert(const Comparable& x, const Comparable& y, BinaryNode<Comparable>*& t) const;
    void remove(const Comparable& x, BinaryNode<Comparable>*& t) const;
    BinaryNode<Comparable>* findMin(BinaryNode<Comparable>* t) const;
    BinaryNode<Comparable>* findMax(BinaryNode<Comparable>* t) const;
    BinaryNode<Comparable>* find(const Comparable& x, BinaryNode<Comparable>* t) const;
    void makeEmpty(BinaryNode<Comparable>*& t) const;
    void printTree(BinaryNode<Comparable>* t) const;
    void printTreeInfo(BinaryNode<Comparable>* t) const;
    BinaryNode<Comparable>* clone(BinaryNode<Comparable>* t) const;
};
template <class Comparable>
BinarySearchTree<Comparable>::
BinarySearchTree(const Comparable& notFound) :
    ITEM_NOT_FOUND(notFound), root(NULL)
{
}
template <class Comparable>
const Comparable& BinarySearchTree<Comparable>::
elementAt(BinaryNode<Comparable>* t) const
{
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}
template <class Comparable>
const Comparable& BinarySearchTree<Comparable>::
find(const Comparable& x) const
{
    return elementAt(find(x, root));
}
template <class Comparable>
BinaryNode<Comparable>*
BinarySearchTree<Comparable>::
find(const Comparable& x, BinaryNode<Comparable>* t) const
{
    if (t == NULL)
        return NULL;
    else if (x < t->element)
        return find(x, t->left);
    else if (t->element < x)
        return find(x, t->right);
    else
        return t;    // Match
}
template <class Comparable>
const Comparable& BinarySearchTree<Comparable>::findMin() const
{
    return elementAt(findMin(root));
}
template <class Comparable>BinaryNode<Comparable>* BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable>* t)const {
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return findMin(t->left);
}
template <class Comparable>
const Comparable& BinarySearchTree<Comparable>::findMax() const
{
    return elementAt(findMax(root));
}
template <class Comparable>
void BinarySearchTree<Comparable> ::insertSubTree(const Comparable& x, BinaryNode<Comparable>*& t) {
    find(x, root)->subtree = t;
}
template <class Comparable>
BinaryNode<Comparable>*& BinarySearchTree<Comparable> ::GetRoot() {
    return root;
}
template <class Comparable>
void BinarySearchTree<Comparable> ::SetRoot(BinaryNode<Comparable>*& t) {
    root = NULL;
    root = t;
}

template <class Comparable>
BinaryNode<Comparable>*& BinarySearchTree<Comparable> ::GetSubTree(const Comparable& x) {
    return find(x, root)->subtree;
}


template <class Comparable>
BinaryNode<Comparable>*
BinarySearchTree<Comparable>::findMax(BinaryNode<Comparable>* t)
const
{
    if (t != NULL)
        while (t->right != NULL)
            t = t->right;
    return t;
}
template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x, const Comparable& y)
{
    insert(x, y, root);
}
template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const
{
    if (root == NULL) {
        return true;
    }
    else {
        return false;
    }
}

template <class Comparable>
const Comparable BinarySearchTree<Comparable> ::GetInfo(const Comparable& x) {
    return find(x, root)->item;
}

template <class Comparable>
void BinarySearchTree<Comparable>::updateInfo(const Comparable& x, const Comparable& y) {
    find(x, root)->item = y;
}
template <class Comparable>
void BinarySearchTree<Comparable>::updateDocInfo(const Comparable& x, const Comparable& y) {
    DocumentItem the_doc;
    for (int a = 0; a < find(x, root)->docs.size(); a++) {
        if (find(x, root)->docs[a].documentName == y) {
            find(x, root)->docs[a].count++;
            return;
        }
    }
    
    the_doc.count = 1;
    the_doc.documentName = y;
    find(x, root)->docs.push_back(the_doc);
}
template <class Comparable>
vector<DocumentItem> BinarySearchTree<Comparable>::GetDocInfo(const Comparable& x) {
    return find(x, root)->docs;
    
}
template <class Comparable>
void BinarySearchTree<Comparable>::
insert(const Comparable& x, const Comparable& y, BinaryNode<Comparable>*& t) const
{
    if (t == NULL) //  create a new node at the right place
        t = new BinaryNode<Comparable>(x, y, NULL, NULL, NULL);
    else if (x < t->element)
        insert(x, y, t->left);  // insert at the left or 
    else if (t->element < x)
        insert(x, y, t->right);  // right subtree
    else
        ;  // Duplicate; do nothing
}
template <class Comparable>
void BinarySearchTree<Comparable>::remove
(const Comparable& x)
{
    remove(x, root);
}
template <class Comparable>
void BinarySearchTree<Comparable>::
remove(const Comparable& x, BinaryNode<Comparable>*& t)const
{
    if (t == NULL)
        return;   // Item not found; do nothing
    if (x < t->element)
        remove(x, t->left);
    else if (t->element < x)
        remove(x, t->right);
    else if (t->left != NULL && t->right != NULL) // Two children
    {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else // one or no children
    {
        BinaryNode<Comparable>* oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }
}
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty()
{
    makeEmpty(root);
}
template <class Comparable>
void BinarySearchTree<Comparable>::
makeEmpty(BinaryNode<Comparable>*& t) const
{
    if (t != NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = NULL;
}
template <class Comparable>
void BinarySearchTree<Comparable>::printTree() const
{
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root);
}
template <class Comparable>
void BinarySearchTree<Comparable>::printTreeInfo() const
{
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTreeInfo(root);
}
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
    makeEmpty();
}
template <class Comparable>
BinarySearchTree<Comparable>::
BinarySearchTree(const BinarySearchTree<Comparable>& rhs) :
    root(NULL), ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND)
{
    *this = rhs;
}
template <class Comparable>
void BinarySearchTree<Comparable>::
printTreeInfo(BinaryNode<Comparable>* t) const
{
    if (t != NULL)
    {
        printTreeInfo(t->left);
        if (t->item == "") {
            cout << t->element << endl;
        }
        else {
            cout << t->element + "-" + t->item << endl;
        }
        printTreeInfo(t->right);
    }
}
template <class Comparable>
void BinarySearchTree<Comparable>::
printTree(BinaryNode<Comparable>* t) const
{
    if (t != NULL)
    {
        printTree(t->left);
        cout << t->element << endl;
        printTree(t->right);
    }
}
template <class Comparable>
BinaryNode<Comparable>*
BinarySearchTree<Comparable>::
clone(BinaryNode<Comparable>* t) const
{
    if (t == NULL)
        return NULL;
    else
        return new BinaryNode<Comparable>
        (t->element, t->item,
            clone(t->left),
            clone(t->right), clone(t->subtree));
}


void makeItStr(string& w) {
   
    string new_w = "";
    for (int j = 0; j < w.length(); j++) {
        if (w[j] >= 97 && w[j] <= 122) {
            new_w = new_w + w[j];
        }
        else if (w[j] >= 65 && w[j] <= 90) {
            char c = w[j] + 32;
            new_w = new_w + c;
        }
    }
    w = new_w;
 
}



int main() {
    int count = 0, num;
    string filename;
    ifstream input;
    string ITEM_NOT_FOUND = "Error404";
    cout << "Enter number of input files: ";
    cin >> num;
    vector<string> f_vector;
    vector<Documents> hsh_docs;
    vector<Documents> bst_docs;
   
    BinarySearchTree<string> BST(ITEM_NOT_FOUND);

    HashTable<string> HSH(ITEM_NOT_FOUND,53);

    
   
    


    while (count < num) {
        cout << "Enter " << count + 1 << ". file name: ";
        cin >> filename;
        f_vector.push_back(filename);
        Documents file_docs;
        file_docs.name = filename;
        hsh_docs.push_back(file_docs);
        bst_docs.push_back(file_docs);
        count++;
    }
    for (int i = 0; i < f_vector.size(); i++) {

        input.open(f_vector[i].c_str());
        char ch;
        string word = "";

        int counter = 0;
        while (input.get(ch)) {

            if (ch >= 97 && ch <= 122) {
                word = word + ch;
            }
            else if (ch >= 65 && ch <= 90) {
                char new_ch = ch + 32;
                word = word + new_ch;
            }
            else {
                if (word != "") {
                    
                    HSH.insert(word);
                    HSH.updateDocInfo(word, f_vector[i]);
                    BST.insert(word, "");
                    BST.updateDocInfo(word, f_vector[i]);
                    word = "";

                }

            }


        }
        if (word != "") {
            
            HSH.insert(word);
            HSH.updateDocInfo(word, f_vector[i]);
            BST.insert(word, "");
            BST.updateDocInfo(word, f_vector[i]);
            word = "";

        }
        
        input.clear();
        input.seekg(0);

        input.close();



    }
    cout << endl;
    cout << "After preprocessing, the unique word count is " << HSH.getCurrentUnique() << ". Current load ratio is " << HSH.getCurrentLoad() << endl;
    string search;
    cout << "Enter queried words in one line: ";
    cin.ignore();
    getline(cin, search);


   
    
    auto start = std::chrono::high_resolution_clock::now();
    vector<DocumentItem> info_doc;

    string part = "";
    int error_point = 0;

    
    for (int j = 0; j < search.length(); j++) {

        if (search[j] >= 97 && search[j] <= 122) {
            part = part + search[j];
            if (j == search.length() - 1) {
                if (BST.find(part) != ITEM_NOT_FOUND) {



                    info_doc = BST.GetDocInfo(part);
                    for (int z = 0; z < info_doc.size(); z++) {
                        for (int d = 0; d < bst_docs.size(); d++) {
                            if (info_doc[z].documentName == bst_docs[d].name) {
                                DocumentItem item;
                                item.documentName = part;
                                item.count = info_doc[z].count;
                                bst_docs[d].items.push_back(item);
                            }
                        }

                    }
                }
                else {
                    error_point++;
                }

            }
            

        }
        else if (search[j] >= 65 && search[j] <= 90) {
            char new_ch = search[j] + 32;
            part = part + new_ch;
            if (j == search.length() - 1) {
                if (BST.find(part) != ITEM_NOT_FOUND) {



                    info_doc = BST.GetDocInfo(part);
                    for (int z = 0; z < info_doc.size(); z++) {
                        for (int d = 0; d < bst_docs.size(); d++) {
                            if (info_doc[z].documentName == bst_docs[d].name) {
                                DocumentItem item;
                                item.documentName = part;
                                item.count = info_doc[z].count;
                                bst_docs[d].items.push_back(item);
                            }
                        }

                    }
                }
                else {
                    error_point++;
                }
               

            }
        }
        else {
            if (part != "") {
                if (BST.find(part) != ITEM_NOT_FOUND) {
                    
                    

                    info_doc = BST.GetDocInfo(part);
                    for (int z = 0; z < info_doc.size(); z++) {
                        for (int d = 0; d < bst_docs.size(); d++) {
                            if (info_doc[z].documentName == bst_docs[d].name) {
                                DocumentItem item;
                                item.documentName = part;
                                item.count = info_doc[z].count;
                                bst_docs[d].items.push_back(item);
                            }
                        }
                        
                    }
                    
                }
                else {
                    error_point++;
                }


                part = "";

            }

        }



    }
    if (error_point >= 1) {
        cout << "No document contains the given query" << endl;

    }
    else {
        for (int el = 0; el < bst_docs.size(); el++) {
            if (bst_docs[el].items.size() != 0) {
                cout << "in Document " << bst_docs[el].name;
                for (int e = 0; e < bst_docs[el].items.size(); e++) {
                    cout << ", " << bst_docs[el].items[e].documentName << " found " << bst_docs[el].items[e].count << " times";
                }
                cout << "." << endl;
            }
        }
    }

    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);


    start = std::chrono::high_resolution_clock::now();
    

    part = "";
    


    for (int j = 0; j < search.length(); j++) {

        if (search[j] >= 97 && search[j] <= 122) {
            part = part + search[j];
            if (j == search.length() - 1) {
                if (HSH.find(part) != ITEM_NOT_FOUND) {



                    info_doc = HSH.GetDocInfo(part);
                    for (int z = 0; z < info_doc.size(); z++) {
                        for (int d = 0; d < hsh_docs.size(); d++) {
                            if (info_doc[z].documentName == hsh_docs[d].name) {
                                DocumentItem item;
                                item.documentName = part;
                                item.count = info_doc[z].count;
                                hsh_docs[d].items.push_back(item);
                            }
                        }

                    }
                }
                else {
                    error_point++;
                }

            }


        }
        else if (search[j] >= 65 && search[j] <= 90) {
            char new_ch = search[j] + 32;
            part = part + new_ch;
            if (j == search.length() - 1) {
                if (HSH.find(part) != ITEM_NOT_FOUND) {



                    info_doc = HSH.GetDocInfo(part);
                    for (int z = 0; z < info_doc.size(); z++) {
                        for (int d = 0; d < hsh_docs.size(); d++) {
                            if (info_doc[z].documentName == hsh_docs[d].name) {
                                DocumentItem item;
                                item.documentName = part;
                                item.count = info_doc[z].count;
                                hsh_docs[d].items.push_back(item);
                            }
                        }

                    }
                }
                else {
                    error_point++;
                }


            }
        }
        else {
            if (part != "") {
                if (HSH.find(part) != ITEM_NOT_FOUND) {



                    info_doc = HSH.GetDocInfo(part);
                    for (int z = 0; z < info_doc.size(); z++) {
                        for (int d = 0; d < hsh_docs.size(); d++) {
                            if (info_doc[z].documentName == hsh_docs[d].name) {
                                DocumentItem item;
                                item.documentName = part;
                                item.count = info_doc[z].count;
                                hsh_docs[d].items.push_back(item);
                            }
                        }

                    }

                }
                else {
                    error_point++;
                }


                part = "";

            }

        }



    }
    if (error_point >= 1) {
        cout << "No document contains the given query" << endl;

    }
    else {
        for (int el = 0; el < hsh_docs.size(); el++) {
            if (hsh_docs[el].items.size() != 0) {
                cout << "in Document " << hsh_docs[el].name;
                for (int e = 0; e < hsh_docs[el].items.size(); e++) {
                    cout << ", " << hsh_docs[el].items[e].documentName << " found " << hsh_docs[el].items[e].count << " times";
                }
                cout << "." << endl;
            }
        }
    }

    auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

    
    cout << "\nBST Time: " << BSTTime.count() / search.length() << "\n";
    cout << endl;
    cout << "\nHSH Time: " << HTTime.count() / search.length() << "\n";
    double timebst = BSTTime.count() / search.length();
    double timehsh = HTTime.count() / search.length();
    cout << "Speed Up:" <<  timebst / timehsh << endl;







        return 0;
    
}