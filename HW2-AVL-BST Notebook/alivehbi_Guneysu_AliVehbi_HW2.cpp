#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#pragma comment(linker, "/STACK:2700000")

using namespace std;
/*For binary Tree I used Gulsen Hoca's code but I made some changes
* For AVL tree I again used Gulsen Hoca's code but I also get help from GeeksForGekks codes, and I made changes in AVL Tree
* but I did not Plagrize anything I just get help while creating some codes
* PLEASE READ!!! => sometimes it can overflow the stack so please try to increase pragma comment
*/
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
    void insertSubTree(const Comparable& x, BinaryNode<Comparable>* & t); 
    void updateInfo(const Comparable& y,const Comparable&x);
    const Comparable GetInfo(const Comparable& y);
    BinaryNode<Comparable>*& GetRoot();
    void SetRoot(BinaryNode<Comparable>*& t);
    BinaryNode<Comparable>* &GetSubTree(const Comparable&x);
    

    void makeEmpty();
   
    void insert(const Comparable& x,const Comparable& y);
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
template <class Comparable>BinaryNode<Comparable>*BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable>* t)const{
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
void BinarySearchTree<Comparable> ::insertSubTree(const Comparable& x, BinaryNode<Comparable>* &t) {
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
    return find(x,root)->subtree;
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
    insert(x,y, root);
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
void BinarySearchTree<Comparable>::updateInfo(const Comparable& x,const Comparable& y) {
    find(x, root)->item = y;
}

template <class Comparable>
void BinarySearchTree<Comparable>::
insert(const Comparable& x, const Comparable& y, BinaryNode<Comparable>*& t) const
{
    if (t == NULL) //  create a new node at the right place
        t = new BinaryNode<Comparable>(x,y, NULL, NULL,NULL);
    else if (x < t->element)
        insert(x,y, t->left);  // insert at the left or 
    else if (t->element < x)
        insert(x,y, t->right);  // right subtree
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
            cout << t->element + "-"+t->item << endl;
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
        (t->element,t->item,
            clone(t->left),
            clone(t->right),clone(t->subtree));
}




template <class Comparable>
class AvlTree;

template <class Comparable>
class AvlNode
{
    Comparable 	element;
    Comparable info;
    AvlNode* subtree;
    AvlNode* left;
    AvlNode* right;
    int    height;

    AvlNode(const Comparable& theElement, const Comparable& theInfo,
        AvlNode* lt, AvlNode* rt, AvlNode* sbt, int h = 0)
        : element(theElement), info(theInfo), left(lt), right(rt), subtree(sbt), height(h) { }

    friend class AvlTree<Comparable>;
};

template <class Comparable>
class AvlTree
{
public:
    explicit AvlTree(const Comparable& notFound);
    AvlTree(const AvlTree& rhs);
    ~AvlTree();

    const Comparable& findMin() const;
    const Comparable& findMax() const;
    const Comparable& find(const Comparable& x) const;
    bool isEmpty() const;
    void printTree() const;

    void makeEmpty();
    void insert(const Comparable& x, const Comparable& y);
    void updateInfo(const Comparable& y, const Comparable& x);
    const Comparable GetInfo(const Comparable& y);
    AvlNode<Comparable>*& GetRoot();
    void SetRoot(AvlNode<Comparable>*& t);
    AvlNode<Comparable>*& GetSubTree(const Comparable& x);
    void insertSubTree(const Comparable& x, AvlNode<Comparable>*& t);
    void remove(const Comparable& x);

    //const AvlTree& operator=(const AvlTree& rhs);
private:
    AvlNode<Comparable>* root;
    const Comparable ITEM_NOT_FOUND;

    const Comparable& elementAt(AvlNode<Comparable>* t) const;

    void insert(const Comparable& x, const Comparable& y, AvlNode<Comparable>*& t) const;
    AvlNode<Comparable>* remove(AvlNode<Comparable>*& t, const Comparable& x) const;

    AvlNode<Comparable>* findMin(AvlNode<Comparable>* t) const;
    AvlNode<Comparable>* findMax(AvlNode<Comparable>* t) const;
    AvlNode<Comparable>* find(const Comparable& x, AvlNode<Comparable>* t)
        const;
    void makeEmpty(AvlNode<Comparable>*& t) const;
    void printTree(AvlNode<Comparable>* t) const;
    //AvlNode<Comparable>* clone(AvlNode<Comparable>* t) const;

    // Avl manipulations
    int getBalance(AvlNode<Comparable>* N) const;
    int height(AvlNode<Comparable>* t) const;
    int max(int lhs, int rhs) const;
    void rotateWithLeftChild(AvlNode<Comparable>*& k2) const;
    void rotateWithRightChild(AvlNode<Comparable>*& k1) const;
    void doubleWithLeftChild(AvlNode<Comparable>*& k3) const;
    void doubleWithRightChild(AvlNode<Comparable>*& k1) const;
};
template <class Comparable>
AvlTree<Comparable>::AvlTree(const Comparable& notFound) :
    ITEM_NOT_FOUND(notFound), root(NULL)
{
}
template <class Comparable>
AvlTree<Comparable>::
AvlTree(const AvlTree<Comparable>& rhs) :
    root(NULL), ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND)
{
    *this = rhs;
}
template <class Comparable>
AvlTree<Comparable>::~AvlTree()
{
    makeEmpty();
}
template <class Comparable>
int AvlTree<Comparable>::height(AvlNode<Comparable>* t)const
{
    if (t == NULL)
        return -1;

    return t->height;
}
template <class Comparable>
int AvlTree<Comparable>::max(int lhs, int rhs)
const
{
    if (lhs > rhs)
        return lhs;

    return rhs;
}
template <class Comparable>
void AvlTree<Comparable>::insert(const Comparable& x, const Comparable& y)
{
    insert(x, y, root);
}
template <class Comparable>
int AvlTree<Comparable>::getBalance(AvlNode<Comparable>* N) const
{
    if (N == NULL)
        return -1;
    return (height(N->left) - height(N->right));
}
template <class Comparable>
void AvlTree<Comparable>::insert(const Comparable& x, const Comparable& y, AvlNode<Comparable>*& t) const
{
    if (t == NULL)
        t = new AvlNode<Comparable>(x,y,NULL, NULL, NULL);

    else if (x < t->element) {
        // X should be inserted to the left tree!
        insert(x,y, t->left);

        // Check if the left tree is out of balance (left subtree grew in height!)
        if (height(t->left) - height(t->right) == 2)
            if (x < t->left->element)  // X was inserted to the left-left subtree!
                rotateWithLeftChild(t);
            else			     // X was inserted to the left-right subtree!
                doubleWithLeftChild(t);
    }
    else if (t->element < x)
    {    // Otherwise X is inserted to the right subtree
        insert(x,y, t->right);
        if (height(t->right) - height(t->left) == 2)
            // height of the right subtree increased
            if (t->right->element < x)
                // X was inserted to right-right subtree
                rotateWithRightChild(t);
            else // X was inserted to right-left subtree
                doubleWithRightChild(t);
    }
    else
        ;  // Duplicate; do nothing

  // update the height the node
    t->height = max(height(t->left), height(t->right)) + 1;
}
template <class Comparable>
const Comparable AvlTree<Comparable> ::GetInfo(const Comparable& x) {
    return find(x, root)->info;
}

template <class Comparable>
void AvlTree<Comparable>::updateInfo(const Comparable& x, const Comparable& y) {
    find(x, root)->info = y;
}
template <class Comparable>
void AvlTree<Comparable> ::insertSubTree(const Comparable& x, AvlNode<Comparable>*& t) {
    find(x, root)->subtree = t;
}
template <class Comparable>
AvlNode<Comparable>*& AvlTree<Comparable> ::GetRoot() {
    return root;
}
template <class Comparable>
void AvlTree<Comparable> ::SetRoot(AvlNode<Comparable>*& t) {
    root = NULL;
    root = t;
}

template <class Comparable>
AvlNode<Comparable>*& AvlTree<Comparable> ::GetSubTree(const Comparable& x) {
    return find(x, root)->subtree;
}

template <class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild(
    AvlNode<Comparable>*& k2) const
{
    AvlNode<Comparable>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}
template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild
(AvlNode<Comparable>*& k1) const
{
    AvlNode<Comparable>* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}
template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild
(AvlNode<Comparable>*& k3) const
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}
template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild
(AvlNode<Comparable>*& k1) const
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}
template <class Comparable>
const Comparable& AvlTree<Comparable>::elementAt(AvlNode<Comparable>* t) const
{
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}
template <class Comparable>
const Comparable& AvlTree<Comparable>::
find(const Comparable& x) const
{
    return elementAt(find(x, root));
}
template <class Comparable>
AvlNode<Comparable>*
AvlTree<Comparable>::
find(const Comparable& x, AvlNode<Comparable>* t) const
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
AvlNode<Comparable>*
AvlTree<Comparable>::findMax(AvlNode<Comparable>* t)
const
{
    if (t != NULL)
        while (t->right != NULL)
            t = t->right;
    return t;
}
template <class Comparable>
const Comparable& AvlTree<Comparable>::findMax() const
{
    return elementAt(findMax(root));
}
template <class Comparable>
const Comparable& AvlTree<Comparable>::findMin() const
{
    return elementAt(findMin(root));
}
template <class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::findMin(AvlNode<Comparable>* t)const {
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return findMin(t->left);
}

template <class Comparable>
void AvlTree<Comparable>::printTree() const
{
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root);
}
template <class Comparable>
void AvlTree<Comparable>::printTree(AvlNode<Comparable>* t) const
{
    if (t != NULL)
    {
        printTree(t->left);
        cout << t->element << endl;
        printTree(t->right);
    }
}

template <class Comparable>
void AvlTree<Comparable>::makeEmpty()
{
    makeEmpty(root);
}
template <class Comparable>
void AvlTree<Comparable>::makeEmpty(AvlNode<Comparable>*& t) const
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
bool AvlTree<Comparable>::isEmpty() const
{
    if (root == NULL) {
        return true;
    }
    else {
        return false;
    }
}
template <class Comparable>
void AvlTree<Comparable>:: remove(const Comparable& x) {
    root = remove(root, x);
}
template <class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::remove(AvlNode<Comparable>*& root,const Comparable & item) const{

    
    if (root == NULL)
        return root;

    
    if (item < root->element)
        root->left = remove(root->left, item);

    
    else if (item > root->element)
        root->right = remove(root->right, item);

   
    else
    {
        
        if ((root->left == NULL) ||
            (root->right == NULL))
        {
            AvlNode<Comparable>* temp = root->left ?
                root->left :
                root->right;

            
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else 
                *root = *temp; 

            free(temp);
        }
        else
        {
            
            AvlNode<Comparable>* temp = findMin(root->right);

            
            root->element = temp->element;

            
            root->right = remove(root->right,temp->element);
        }
    }

    
    if (root == NULL)
        return root;

   
    root->height = 1 + max(height(root->left),height(root->right));

    
    int balance = getBalance(root);

  

    if (balance > 1 && getBalance(root->left) >= 0) {
        rotateWithRightChild(root);
        return root;
       
    }
        

        

    
    if (balance > 1 && getBalance(root->left) < 0)
    {
        
        rotateWithLeftChild(root->left);
        rotateWithRightChild(root);
        return root;
        
    }

    
    if (balance < -1 && getBalance(root->right) <= 0) {
        rotateWithLeftChild(root);
        return root;
        
    }

    if (balance < -1 && getBalance(root->right) > 0)
    {
       
        rotateWithRightChild(root->right);
        rotateWithLeftChild(root);
        return root;
        
    }

    return root;
}






int main() {
    const string ITEM_NOT_FOUND = "errror404";
    BinarySearchTree<string> BST(ITEM_NOT_FOUND); //Sections BST
    BinarySearchTree<string> items(ITEM_NOT_FOUND); // Sections -> items (they are connected with Sections)
    AvlTree<string> AVL(ITEM_NOT_FOUND);// Sections AVL
    AvlTree<string> AVL_items(ITEM_NOT_FOUND);
   
   
    string section_title = "";
    string titles = "";
    ifstream datafile("data.txt");
    cout << "Welcome to the Notebook!" << endl;

    while (getline(datafile, titles)) {
        int dashcounter = 0;
        int tree_count = 0;
        
        string item_title = "";
        string info = "";
        
        if (titles[0] != '-') {
            /*if (section_title != "") {
                auto start_2 = std::chrono::high_resolution_clock::now();
                AVL.insertSubTree(section_title, AVL_items.GetRoot());
                auto end_2 = std::chrono::high_resolution_clock::now();
                long long timer_3 = (end_2 - start_2).count() / 1000.0;
                cout << "Section '" << section_title << "' has been inserted into the AVL notebook." << endl;
                std::cout << "[AVL] Elapsed time:" << timer_3 << " microseconds" << std::endl;

                auto start_3 = std::chrono::high_resolution_clock::now();
                BST.insertSubTree(section_title, items.GetRoot());
                auto end_3 = std::chrono::high_resolution_clock::now();
                timer_3 = (end_3 - start_3).count() / 1000.0;
                cout << "Section '" << section_title << "' has been inserted into the BST notebook." << endl;
                std::cout << "[BST] Elapsed time:" << timer_3 << " microseconds" << std::endl;

              
                
                
                

            }*/
            section_title = "";
            cout << endl;
            for (int i = 0; i < titles.length(); i++) {
                section_title = section_title + titles[i];
            }
            auto start_2 = std::chrono::high_resolution_clock::now();
            AVL.insert(section_title, "");
            auto end_2 = std::chrono::high_resolution_clock::now();
            long long timer_3 = (end_2 - start_2).count() / 1000.0;
            cout << "Section '" << section_title << "' has been inserted into the AVL notebook." << endl;
            std::cout << "[AVL] Elapsed time:" << timer_3 << " microseconds" << std::endl;

            auto start_3 = std::chrono::high_resolution_clock::now();
            BST.insert(section_title, "");
            auto end_3 = std::chrono::high_resolution_clock::now();
            timer_3 = (end_3 - start_3).count() / 1000.0;
            cout << "Section '" << section_title << "' has been inserted into the BST notebook." << endl;
            std::cout << "[BST] Elapsed time:" << timer_3 << " microseconds" << std::endl; 
            
            AvlTree<string>AVL_temp(ITEM_NOT_FOUND);
            BinarySearchTree<string>temp(ITEM_NOT_FOUND);
            AVL_items.SetRoot(AVL_temp.GetRoot());
            items.SetRoot(temp.GetRoot());
            
            
            
            
        }
        else {
            for (int i = 0; i < titles.length(); i++) {
                if (titles[i] == '-') {
                    dashcounter++;
                }
                else if (dashcounter == 1) {
                    item_title = item_title + titles[i];

                }
                else if (dashcounter == 2) {
                    info = info + titles[i];
                    
                }

            }
            AVL_items.insert(item_title, info);
            items.insert(item_title, info);
            AVL.insertSubTree(section_title, AVL_items.GetRoot());
            BST.insertSubTree(section_title, items.GetRoot());
            
        }
        /*if (titles[titles.length()-1] == '\eof') {
            auto start_2 = std::chrono::high_resolution_clock::now();
            AVL.insertSubTree(section_title, AVL_items.GetRoot());
            auto end_2 = std::chrono::high_resolution_clock::now();
            long long timer = (end_2 - start_2).count() / 1000.0;
            cout << "Section '" << section_title << "' has been inserted into the AVL notebook." << endl;
            std::cout << "[AVL] Elapsed time:" << timer << " microseconds" << std::endl;
            auto start_3 = std::chrono::high_resolution_clock::now();
            BST.insertSubTree(section_title, items.GetRoot());
            auto end_3 = std::chrono::high_resolution_clock::now();
            timer = (end_3 - start_3).count() / 1000.0;
            cout << "Section '" << section_title << "' has been inserted into the BST notebook." << endl;
            std::cout << "[BST] Elapsed time:" << timer << " microseconds" << std::endl;
            
        }*/
        
       
    }
   
    
    bool menu_1 = true;
    bool show_menu = true;
    while (menu_1) {
        if (show_menu) {
            cout << "MENU" << endl;
            cout << "Please enter an input between [1 - 6]:" << endl;
            cout << "1- Display the sections [AVL]" << endl;
            cout << "2- Display the sections [BST]" << endl;
            cout << "3- Select a section" << endl;
            cout << "4- Add new section" << endl;
            cout << "5- Delete a section" << endl;
            cout << "6- Exit" << endl;
            show_menu = false;
        }
        int input;
        cout << "Input: ";
        cin >> input;
        if (input == 1) {

            cout << "\n******" << endl;
            AVL.printTree();
            cout << "******\n" << endl;
        }
        else if (input == 2) {
            
            cout << "\n******" << endl;
            BST.printTree();
            cout << "******\n" << endl;
            

        }
        else if (input == 3) {
           
            string section;
            cout << "Enter the title of the section: ";
            cin.ignore();
            getline(cin, section);
          

            if (BST.find(section) == ITEM_NOT_FOUND) {
                cout << "Invalid title!" << endl;
            }
            else {
                bool menu_2 = true;
                bool show_menu2 = true;
                show_menu = true; // to show first menu options again after this part
                while (menu_2) {
                    if (BST.GetSubTree(section) == NULL) {

                        AvlTree<string>AVL_temp(ITEM_NOT_FOUND);
                        AVL_items.SetRoot(AVL_temp.GetRoot());
                        AVL.insertSubTree(section, AVL_items.GetRoot());

                        BinarySearchTree<string>temp(ITEM_NOT_FOUND);
                        items.SetRoot(temp.GetRoot());
                        BST.insertSubTree(section, items.GetRoot());
                    }
                    AVL_items.SetRoot(AVL.GetSubTree(section));
                    items.SetRoot(BST.GetSubTree(section));
                    if (show_menu2) {
                        cout << endl << endl;
                        cout << "Selected section -> " << section << endl;
                        cout << "Please enter an input between [1 - 7]:" << endl;
                        cout << "1- Display the items [AVL]" << endl;
                        cout << "2- Display the items [BST]" << endl;
                        cout << "3- Display the information of a item" << endl;
                        cout << "4- Add new item" << endl;
                        cout << "5- Update the information of a item" << endl;
                        cout << "6- Delete a item" << endl;
                        cout << "7- Return to Main Menu" << endl;
                        show_menu2 = false;

                    }
                    int input2;
                    cout << endl;
                    cout << "Input: ";
                    cin >> input2;
                    if (input2 == 1) {
                        cout << endl;
                        cout << "*****" << endl;
                        AVL_items.printTree();
                        cout << "*****" << endl;

                    }
                    else if (input2 == 2) {
              
                        cout << endl;
                        cout << "*****" << endl;
                        items.printTree();
                        cout << "*****" << endl;

                    }
                    else if (input2 == 3) {
                        string the_item = "";
                        cout << "Enter the title of the item: ";
                        cin.ignore();
                        getline(cin, the_item);
                        auto start = std::chrono::high_resolution_clock::now();
                        AVL_items.find(section);
                        auto end = std::chrono::high_resolution_clock::now();
                        long long timer = (end - start).count() / 1000.0;
                        std::cout << "[AVL] Elapsed time:" << timer << " microseconds" << std::endl;
                        auto start_1 = std::chrono::high_resolution_clock::now();
                        items.find(section);
                        auto end_1 = std::chrono::high_resolution_clock::now();
                        timer = (end_1 - start_1).count() / 1000.0;
                        std::cout << "[BST] Elapsed time:" << timer << " microseconds" << std::endl;

                        if (items.find(the_item) == ITEM_NOT_FOUND) {
                            cout << "Invalid title." << endl;
                        }
                        else {
                            cout << items.GetInfo(the_item) << endl;

                        }

                    }
                    else if (input2 == 4) {
                        string the_item;
                        cout << "Enter the title of the item: ";
                        cin.ignore();
                        getline(cin, the_item);
                        if (items.find(the_item) != ITEM_NOT_FOUND) {
                            cout << "Item '"<<the_item<<"' already exists in the '"<< section << "'." << endl;
                        }
                        else {
                            string des;
                            cout << "Enter a description for the item: ";
                            getline(cin, des);
                            auto start = std::chrono::high_resolution_clock::now();
                            AVL_items.insert(the_item, des);
                            auto end = std::chrono::high_resolution_clock::now();
                            long long timer = (end - start).count() / 1000.0;
                            std::cout << "[AVL] Elapsed time:" << timer << " microseconds" << std::endl;
                            auto start_1 = std::chrono::high_resolution_clock::now();
                            items.insert(the_item, des);
                            auto end_1 = std::chrono::high_resolution_clock::now();
                            timer = (end_1 - start_1).count() / 1000.0;
                            std::cout << "[BST] Elapsed time:" << timer << " microseconds" << std::endl;
                            
                           
                            
                            AVL.insertSubTree(section, AVL_items.GetRoot());
                           
                            BST.insertSubTree(section, items.GetRoot());
                            cout << "The new item '" << the_item << "' has been inserted." << endl;

                        }


                    }
                    else if (input2 == 5) {
                        string the_item;
                        cout << "Enter the title of the item: ";
                        cin.ignore();
                        getline(cin, the_item);
                        auto start = std::chrono::high_resolution_clock::now();
                        AVL_items.find(section);
                        auto end = std::chrono::high_resolution_clock::now();
                        long long timer = (end - start).count() / 1000.0;
                        std::cout << "[AVL] Elapsed time:" << timer << " microseconds" << std::endl;
                        auto start_1 = std::chrono::high_resolution_clock::now();
                        items.find(section);
                        auto end_1 = std::chrono::high_resolution_clock::now();
                        timer = (end_1 - start_1).count() / 1000.0;
                        std::cout << "[BST] Elapsed time:" << timer << " microseconds" << std::endl;

                        if (items.find(the_item) == ITEM_NOT_FOUND) {
                            cout << "Item '" << the_item << "' does not exists in the '" << section << "'." << endl;
                        }
                        else {
                            string new_info;
                            cout << "Enter the new information: ";
                            
                            getline(cin, new_info);
                            
                            AVL_items.updateInfo(the_item, new_info);
                            items.updateInfo(the_item, new_info);
                            cout << "The content " << the_item << " has been updated." << endl;
                        }
                    }
                    else if (input2 == 6) {
                        string the_item = "";
                        cout << "Enter the title of the item: ";
                        cin.ignore();
                        getline(cin, the_item);
                        if (items.find(the_item) == ITEM_NOT_FOUND) {
                            cout << "Item '" << the_item << "' does not exists in the '" << section << "'." << endl;
                        }
                        else {
                            auto start = std::chrono::high_resolution_clock::now();
                            AVL_items.remove(the_item);
                            auto end = std::chrono::high_resolution_clock::now();
                            long long timer = (end - start).count() / 1000.0;
                            std::cout << "[AVL] Elapsed time:" << timer << " microseconds" << std::endl;
                            auto start_1 = std::chrono::high_resolution_clock::now();
                            items.remove(the_item);
                            auto end_1 = std::chrono::high_resolution_clock::now();
                            timer = (end_1 - start_1).count() / 1000.0;
                            std::cout << "[BST] Elapsed time:" << timer << " microseconds" << std::endl;

                           
                            AVL.insertSubTree(section, AVL_items.GetRoot());
                            BST.insertSubTree(section,items.GetRoot());
                            cout << "The item '" << the_item << "' has been deleted." << endl;
                        }

                    }
                    else if (input2 == 7) {
                        menu_2 = false;

                    }
                    

                }
            }
          

        }
        else if (input == 4) {
            string section;
            cout << "Enter a title for the section: ";
            cin.ignore();
            getline(cin, section);
            if (BST.find(section) != ITEM_NOT_FOUND) {
                cout << "Section '" << section << "' already exists." << endl;
            }
            else {
                AVL.insert(section, "");
                BST.insert(section, "");
                cout << "The new section '" << section << "'has been inserted." << endl;
            }
        }
        else if (input == 5) {
            string section;
            cout << "Enter a title for the section: ";
            cin.ignore();
            getline(cin, section);
            if (BST.find(section) == ITEM_NOT_FOUND) {
                cout << "Section '" << section << "' does not exists." << endl;
            }
            else {
                BST.remove(section);
                AVL.remove(section);
                cout << "The section has been deleted." << endl;
            }


        }
        else if (input == 6) {
            menu_1 = false;

        }

    }
    /*BST.printTree();
    items.SetRoot(BST.GetSubTree("Phonebook"));
    items.printTreeInfo();
    items.SetRoot(BST.GetSubTree("Courseworks"));
    items.printTreeInfo();*/
    


    datafile.close();
    
    
   






	return 0;
}
