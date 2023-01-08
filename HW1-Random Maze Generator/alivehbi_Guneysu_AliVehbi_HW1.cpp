#include<iostream>
#include<string>
#include <fstream>
#include"strutils.h"
#include<array>
#include"randgen.h"


using namespace std;

/* PLEASE READ THIS PART: Both of the two parts are exactly working (Maze Generator and the Path).However; when the maze becomes bigger like 30x20,
sometimes it takes time to find a path like(3-4 minutes); therefore, please wait for it because I tried several times the code always working true sorry for taking time.

I used the lecture's stack code but I made some changes in it.
The Maze and the path created by using template Stack.
The maze stocked in linked list not vector or array
* 
*/
template <class Object>
class Stack
{
public:
    Stack();
    Stack(const Stack& rhs);
    ~Stack();

    bool isEmpty() const;
    bool isFull() const;
    void pop();
    void push(const Object& x, const Object& y);
    const Object& top_x() const;
    const Object& top_y() const;
 
    void makeEmpty();
    const Stack& operator=(const Stack& rhs);


private:
    struct ListNode
    {
        Object   x;
        Object   y;
        ListNode* next;

        ListNode(const Object& thex, const Object& they, ListNode* n = NULL)
            : x(thex), y(they),next(n) { }
    };

    ListNode* topOfStack;

};
template <class Object>
Stack<Object>::Stack()
{
    topOfStack = NULL;
}
template <class Object>
bool Stack<Object>::isFull() const
{
    return false;
}
template <class Object>
bool Stack<Object>::isEmpty() const
{
    return topOfStack == NULL;
}

template <class Object>
void Stack<Object>::pop()
{
    if (isEmpty())
        cout << "the stack is empty" << endl;
    ListNode* oldTop = topOfStack;
    topOfStack = topOfStack->next;
    delete oldTop;
}
template <class Object>
void Stack<Object>::push(const Object& x, const Object& y)
{
    topOfStack = new ListNode(x,y, topOfStack);
}
template <class Object>
const Object& Stack<Object>::top_x() const
{
    if (isEmpty())
        cout << "the stack is empty" << endl;
    return topOfStack->x;
}
template <class Object>
const Object& Stack<Object>::top_y() const
{
    if (isEmpty())
        cout << "the stack is empty" << endl;
    return topOfStack->y;
}


template <class Object>
void Stack<Object>::makeEmpty()
{
    while (!isEmpty())
        pop();
}
template <class Object>
const Stack<Object>& Stack<Object>::
operator=(const Stack<Object>& rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        if (rhs.isEmpty())
            return *this;

        ListNode* rptr = rhs.topOfStack;
        ListNode* ptr = new ListNode(rptr->x,rptr->y);
        topOfStack = ptr;

        for (rptr = rptr->next; rptr != NULL; rptr = rptr->next)
            ptr = ptr->next = new ListNode(rptr->x,rptr->y);
    }
    return *this;
}
template <class Object>
Stack<Object>::Stack(const Stack<Object>& rhs)
{
    topOfStack = NULL;
    *this = rhs; // deep copy 
}
template <class Object>
Stack<Object>::~Stack()
{
    makeEmpty();
}

struct Maze {
    int x;
    int y;
    bool cellvisit;
    int left;
    int right;
    int up;
    int down;
    Maze* next;
    Maze(int & thex, int & they, int l = 1, int r = 1, int u = 1, int d = 1, int cv = 1, Maze* n = NULL)
        : x(thex), y(they),left(l), right(r), up(u), down(d), cellvisit(cv),next(n) { }
    Maze() : left(1),right(1), up(1), down(1),cellvisit(false),next(NULL),x(0),y(0) {

    }
    
};


void MazePrint(Maze* header) {
    Maze* ptr = header;
    while (ptr != NULL) {
        cout << "x: " << ptr->x << " y: " << ptr->y << " u:" << ptr->up << " d:" << ptr->down << " l:" << ptr->left << " r:" << ptr->right << " cellvisit: " << ptr->cellvisit << endl;
        ptr = ptr->next;
    }
}
void MazePrint_txt(Maze* header) {
    Maze* ptr = header;
    while (ptr != NULL) {
        cout << "x=" << ptr->x << " y=" << ptr->y << " l=" << ptr->left << " r=" << ptr->right << " u=" << ptr->up << " d=" << ptr->down << endl;
        ptr = ptr->next;
    }
}
Maze * return_cell(Maze* header,int x,int y) { // working
    Maze* ptr = header;
    bool check = true;
    while (check == true) {
        if (ptr->x == x && ptr->y == y) {
            check = false;
        }
        else {
            ptr = ptr->next;
        }
    }
    return ptr;

}
void rebuild_maze(Maze*& header, int x, int y, int l, int r, int u, int d) {
    Maze* currentcell = return_cell(header, x, y);
    currentcell->left = l;
    currentcell->right = r;
    currentcell->up = u;
    currentcell->down = d;
    
}

bool up(Maze*& header, int x, int y) { // working
    y = y + 1;
    Maze* nextcell = return_cell(header, x, y);
    Maze* currentcell = return_cell(header, x, y - 1);

    if (nextcell->cellvisit == false && nextcell->down == 1) {
        nextcell->cellvisit = true;
        nextcell->down = 0;
        currentcell->up = 0;
        return true;
        

    }
    else {
        return false;
    }

}
bool right(Maze*& header, int x, int y) { //working
    x = x + 1;
    Maze* nextcell = return_cell(header, x, y);
    Maze* currentcell = return_cell(header, x-1, y);

    if (nextcell->cellvisit == false && nextcell->left == 1) {
        nextcell->cellvisit = true;
        nextcell->left = 0;
        currentcell->right = 0;
        return true;


    }
    else {
        return false;
    }

}
bool down(Maze*& header, int x, int y) {
    y = y - 1;
    Maze* nextcell = return_cell(header, x, y);
    Maze* currentcell = return_cell(header, x, y + 1);

    if (nextcell->cellvisit == false && nextcell->up == 1) {
        nextcell->cellvisit = true;
        nextcell->up = 0;
        currentcell->down = 0;
        return true;


    }
    else {
        return false;
    }

}
bool left(Maze*& header, int x, int y) {
    x = x - 1;
    Maze* nextcell = return_cell(header, x, y);
    Maze* currentcell = return_cell(header, x + 1, y);

    if (nextcell->cellvisit == false && nextcell->right == 1) {
        nextcell->cellvisit = true;
        nextcell->right = 0;
        currentcell->left = 0;
        return true;


    }
    else {
        return false;
    }

}
bool up_check(Maze* header, int x, int y) {
    Maze* currentcell = return_cell(header, x, y);
    
    
    if (currentcell->up == 0) {
        return true;
       
        
    }
    else {
        return false;
    }

}
bool down_check(Maze* header, int x, int y) {
    Maze* currentcell = return_cell(header, x, y);
   
    if (currentcell->down == 0) {
        return true;
    }
    else {
        return false;
    }

}
bool right_check(Maze* header, int x, int y) {
    Maze* currentcell = return_cell(header, x, y);
   
    if (currentcell->right == 0) {
        return true;
     
       
    }
    else {
        return false;
    }

}
bool left_check(Maze* header, int x, int y) {
    Maze* currentcell = return_cell(header, x, y);
    if (currentcell->left == 0 ) {
        return true;
   

    }
    else {
        return false;
    }

}
void build_wall(Maze* header, int x, int y,char way) {
    Maze* currentcell = return_cell(header, x, y);
    if (way == 'l') {
     
        currentcell->left = 1;
        

    }
    else if(way == 'r')
    {
        
        currentcell->right = 1;
        

    }
    else if (way == 'u')
    {
        
        currentcell->up = 1;
     

    }
    else if (way == 'd')
    {
        
        currentcell->down = 1;
        

    }

}






int main() {
    int M;
    int N ;
    int K;
    cout << "Enter the number of mazes: ";
    cin >> K;
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> M >> N;
 
    int k_counter = 0;
    while (k_counter < K) {
        Maze* header = NULL;
        Maze* ptr = NULL;

        for (int y = 0; y < M; y++) {
            for (int x = 0; x < N; x++) {
                if (header == NULL) {
                    Maze* temp = new Maze();
                    temp->x = x;
                    temp->y = y;
                    temp->next = NULL;
                    header = temp;
                    ptr = header;



                }
                else {
                    Maze* temp = new Maze();
                    temp->x = x;
                    temp->y = y;
                    temp->next = NULL;
                    ptr->next = temp;
                    ptr = temp;
                }

            }

        }
        Stack<int> MazeGenerator;



        int broken_wall = 0; // brokenwall number
        MazeGenerator.push(0, 0);
        header->cellvisit = true;
        RandGen random;
        int x = 0;
        int y = 0;
        int a1 = 0; // for up backtrack
        int a2 = 0;
        int a3 = 0;
        int a4 = 0;

        while (broken_wall < (M * N) - 1) { 



            if (MazeGenerator.top_x() == 0) {

                if (MazeGenerator.top_y() == 0) {

                    int a = random.RandInt(0, 1);

                    if (a == 0) { // up
                        a1 = 1;
                        if (up(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x(), MazeGenerator.top_y() + 1);
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }
                        else if (a1 == 1 && a2 == 1) {
                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }



                    }
                    else if (a == 1) { // right

                        a2 = 1;
                        if (right(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x() + 1, MazeGenerator.top_y());
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }
                        else if (a1 == 1 && a2 == 1) {
                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }

                    }

                }
                else if (MazeGenerator.top_y() == M - 1) {
                    int a = random.RandInt(0, 1);

                    if (a == 0) { // down
                        a1 = 1;
                        if (down(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x(), MazeGenerator.top_y() - 1);
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }
                        else if (a1 == 1 && a2 == 1) {
                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }



                    }
                    else if (a == 1) { // right

                        a2 = 1;
                        if (right(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x() + 1, MazeGenerator.top_y());
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }
                        else if (a1 == 1 && a2 == 1) {
                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }

                    }

                }
                else {
                    int a = random.RandInt(0, 2);

                    if (a == 0) { // up
                        a1 = 1;
                        if (up(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x(), MazeGenerator.top_y() + 1);
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }
                        else if (a1 == 1 && a2 == 1 && a3 == 1) {
                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }



                    }
                    else if (a == 1) { // right

                        a2 = 1;
                        if (right(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x() + 1, MazeGenerator.top_y());
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }
                        else if (a1 == 1 && a2 == 1 && a3 == 1) {
                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }

                    }
                    else if (a == 2) { //down
                        a3 = 1;
                        if (down(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x(), MazeGenerator.top_y() - 1);
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }
                        else if (a1 == 1 && a2 == 1 && a3 == 1) {

                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }

                    }

                }

            }
            else if (MazeGenerator.top_x() == N - 1) {

                if (MazeGenerator.top_y() == 0) {

                    int a = random.RandInt(0, 1);

                    if (a == 0) { // up
                        a1 = 1;
                        if (up(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x(), MazeGenerator.top_y() + 1);
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }
                        else if (a1 == 1 && a2 == 1) {
                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }



                    }
                    else if (a == 1) { // left

                        a2 = 1;
                        if (left(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x() - 1, MazeGenerator.top_y());
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }
                        else if (a1 == 1 && a2 == 1) {
                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }

                    }

                }
                else if (MazeGenerator.top_y() == M - 1) {
                    int a = random.RandInt(0, 1);

                    if (a == 0) { // down
                        a1 = 1;
                        if (down(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x(), MazeGenerator.top_y() - 1);
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }
                        else if (a1 == 1 && a2 == 1) {
                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }



                    }
                    else if (a == 1) { // left

                        a2 = 1;
                        if (left(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x() - 1, MazeGenerator.top_y());
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }
                        else if (a1 == 1 && a2 == 1) {
                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }

                    }

                }
                else {
                    int a = random.RandInt(0, 2);

                    if (a == 0) { // up
                        a1 = 1;
                        if (up(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x(), MazeGenerator.top_y() + 1);
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }
                        else if (a1 == 1 && a2 == 1 && a3 == 1) {
                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }



                    }
                    else if (a == 1) { // left

                        a2 = 1;
                        if (left(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x() - 1, MazeGenerator.top_y());
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }
                        else if (a1 == 1 && a2 == 1 && a3 == 1) {
                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }

                    }
                    else if (a == 2) { //down
                        a3 = 1;
                        if (down(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                            MazeGenerator.push(MazeGenerator.top_x(), MazeGenerator.top_y() - 1);
                            broken_wall++;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;
                        }
                        else if (a1 == 1 && a2 == 1 && a3 == 1) {

                            MazeGenerator.pop();
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            a4 = 0;

                        }

                    }

                }


            }
            else if (MazeGenerator.top_y() == 0) {

                int a = random.RandInt(0, 2);
                if (a == 0) { // up
                    a1 = 1;
                    if (up(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                        MazeGenerator.push(MazeGenerator.top_x(), MazeGenerator.top_y() + 1);
                        broken_wall++;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                    }
                    else if (a1 == 1 && a2 == 1 && a3 == 1) {
                        MazeGenerator.pop();
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;

                    }

                }
                else if (a == 1) { // right
                    a2 = 1;
                    if (right(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                        MazeGenerator.push(MazeGenerator.top_x() + 1, MazeGenerator.top_y());
                        broken_wall++;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;

                    }
                    else if (a1 == 1 && a2 == 1 && a3 == 1) {
                        MazeGenerator.pop();
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                    }

                }
                else if (a == 2) { //left
                    a3 = 1;
                    if (left(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                        MazeGenerator.push(MazeGenerator.top_x() - 1, MazeGenerator.top_y());
                        broken_wall++;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;

                    }
                    else if (a1 == 1 && a2 == 1 && a3 == 1) {
                        MazeGenerator.pop();
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                    }

                }


            }
            else if (MazeGenerator.top_y() == M - 1) {
                int a = random.RandInt(0, 2);
                if (a == 0) { // down
                    a1 = 1;
                    if (down(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                        MazeGenerator.push(MazeGenerator.top_x(), MazeGenerator.top_y() - 1);
                        broken_wall++;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                    }
                    else if (a1 == 1 && a2 == 1 && a3 == 1) {
                        MazeGenerator.pop();
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;

                    }

                }
                else if (a == 1) { // right
                    a2 = 1;
                    if (right(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                        MazeGenerator.push(MazeGenerator.top_x() + 1, MazeGenerator.top_y());
                        broken_wall++;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;

                    }
                    else if (a1 == 1 && a2 == 1 && a3 == 1) {
                        MazeGenerator.pop();
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                    }

                }
                else if (a == 2) { //left
                    a3 = 1;
                    if (left(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                        MazeGenerator.push(MazeGenerator.top_x() - 1, MazeGenerator.top_y());
                        broken_wall++;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;

                    }
                    else if (a1 == 1 && a2 == 1 && a3 == 1) {
                        MazeGenerator.pop();
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                    }

                }


            }
            else {
                int a = random.RandInt(0, 3);
                if (a == 0) { // down
                    a1 = 1;
                    if (down(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                        MazeGenerator.push(MazeGenerator.top_x(), MazeGenerator.top_y() - 1);
                        broken_wall++;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                    }
                    else if (a1 == 1 && a2 == 1 && a3 == 1 && a4 == 1) {
                        MazeGenerator.pop();
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;

                    }

                }
                else if (a == 1) { // right
                    a2 = 1;
                    if (right(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                        MazeGenerator.push(MazeGenerator.top_x() + 1, MazeGenerator.top_y());
                        broken_wall++;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;

                    }
                    else if (a1 == 1 && a2 == 1 && a3 == 1 && a4 == 1) {
                        MazeGenerator.pop();
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                    }

                }
                else if (a == 2) { //left
                    a3 = 1;
                    if (left(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                        MazeGenerator.push(MazeGenerator.top_x() - 1, MazeGenerator.top_y());
                        broken_wall++;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;

                    }
                    else if (a1 == 1 && a2 == 1 && a3 == 1 && a4 == 1) {
                        MazeGenerator.pop();
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                    }

                }
                else if (a == 3) { //up
                    a4 = 1;
                    if (up(header, MazeGenerator.top_x(), MazeGenerator.top_y()) == true) {
                        MazeGenerator.push(MazeGenerator.top_x(), MazeGenerator.top_y() + 1);
                        broken_wall++;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                    }
                    else if (a1 == 1 && a2 == 1 && a3 == 1 && a4 == 1) {
                        MazeGenerator.pop();
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;

                    }

                }


            }

        }

        ptr = header;
        
        ofstream output("maze_" + to_string(k_counter+1) + ".txt");
        output << to_string(M) + " " + to_string(N) + "\n";
        while(ptr != NULL){
            output << "x=" + to_string(ptr->x) + " y=" + to_string(ptr->y) + " l=" + to_string(ptr->left) + " r=" + to_string(ptr->right) + " u=" + to_string(ptr->up) + " d=" + to_string(ptr->down) + "\n";
            ptr = ptr->next;
        }
        output.close();

        k_counter++;
       
        
    }
    cout << "All mazes are generated." << endl << endl;
    int enterx;
    int entery;
    int exitx;
    int exity;
    int MazeID;
    cout << "Enter a maze ID between 1 to " << to_string(K) << " inclusive to find a path: ";
    cin >> MazeID;
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    cin >> enterx >> entery;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    cin >> exitx >> exity;

	cout << endl<<endl;
 
	cout << "Please wait 3-4 minutes, sometimes it can take time to find the path big mazes (30x30-40x40)"<<endl;
 
	cout << "So please do not close the consol until it finds the path (it always working)"<<endl;
 
	cout << "Thank you for your time"<<endl;

    Maze* header = NULL;
    Maze* ptr = NULL;


    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            if (header == NULL) {
                Maze* temp = new Maze();
                temp->x = x;
                temp->y = y;
                temp->next = NULL;
                header = temp;
                ptr = header;



            }
            else {
                Maze* temp = new Maze();
                temp->x = x;
                temp->y = y;
                temp->next = NULL;
                ptr->next = temp;
                ptr = temp;
            }

        }

    }
    string mazeline = "";
    ifstream mazefile("maze_" + to_string(MazeID) + ".txt");

    while (getline(mazefile, mazeline)) {
        int equalcount = 0;
        int x= -1;
        int y = -1;
        int l=-1;
        int r=-1;
        int u=-1;
        int d=-1;
        
      
        for (int i = 0; i < mazeline.length(); i++) {
            if (mazeline[i] == 'x') {
                
                int j = 2;
                int numlength = 0;
                string thenum = "";
                int thenumint = 0;
                while (mazeline[i + j] != ' ') {
                    numlength++;
                    thenum = thenum + mazeline[i + j];
                    j++;


                }
               
                for (int num = 0; num < numlength; num++) {
                    
                    int temp = thenum[numlength - num - 1] - 48;
                    for (int z = 0; z < num; z++) {
                        temp = temp * 10;
                    }
                    thenumint = thenumint + temp;
                }
               


                x = thenumint;
            }
            else if (mazeline[i] == 'y') {
                
                int j = 2;
                int numlength = 0;
                string thenum = "";
                int thenumint = 0;
                while (mazeline[i + j] != ' ') {
                    numlength++;
                    thenum = thenum + mazeline[i + j];
                    j++;


                }
               
                for (int num = 0; num < numlength; num++) {

                    int temp = thenum[numlength - num-1] - 48;
                    for (int z = 0; z < num; z++) {
                        temp = temp * 10;
                    }
                    thenumint = thenumint + temp;
                }
               


                y = thenumint;
                

            }
            else if (mazeline[i] == 'l') {
                l = mazeline[(i + 2)] - 48;

            }
            else if (mazeline[i] == 'r') {
                r = mazeline[(i + 2)] - 48;

            }
            else if (mazeline[i] == 'u') {
                u = mazeline[(i + 2)] - 48;

            }
            else if (mazeline[i] == 'd') {
                d = mazeline[(i + 2)] - 48;

            }
        }
        if (x != -1) {
            rebuild_maze(header, x, y, l, r, u, d);
        }
        
    }
    mazefile.close();



    

    Stack<int> Path;
    Stack<int> Control_Path;
    
    Path.push(enterx, entery);
    Control_Path.push(-1 , -1);
   
  
    int b1 = 0;
    int b2 = 0;
    int b3 = 0;
    int b4 = 0;
    int cellvisited = 0;

    RandGen random;
    while (Path.top_x() != exitx || Path.top_y() != exity) {
        int b = random.RandInt(0, 5);
        
        if (b == 0) { // left
            b1 = 1;
            if (left_check(header, Path.top_x(), Path.top_y()) == true) {
               if (Control_Path.top_x() != Path.top_x() - 1) {
                 

                
                 Control_Path.push(Path.top_x(), Path.top_y());
             

                Path.push(Path.top_x() - 1, Path.top_y());
                cellvisited++;
                b1 = 0;
                b2 = 0;
                b3 = 0;
                b4 = 0;



                
               }



            }
            else if (b1 == 1 && b2 == 1 && b3 == 1 && b4 == 1) {
                
                
                Control_Path.pop();
                Path.pop();
                

                b1 = 0;
                b2 = 0;
                b3 = 0;
                b4 = 0;
            }
            else if (cellvisited > M * N) { 
                Control_Path.pop();
                Path.pop();
                build_wall(header, Path.top_x(), Path.top_y(), 'l');
                cellvisited = 0;

            }
         
        

        }
        else if (b == 1) { // right
            b2 = 1;
            
            if (right_check(header, Path.top_x(), Path.top_y()) == true) {
                if (Control_Path.top_x() != Path.top_x() + 1) {
                
                Control_Path.push(Path.top_x(), Path.top_y());
              
                Path.push(Path.top_x() + 1, Path.top_y());
                cellvisited++;
                b1 = 0;
                b2 = 0;
                b3 = 0;
                b4 = 0;

                }


            }
            else if (b1 == 1 && b2 == 1 && b3 == 1 && b4 == 1) {
                
                Control_Path.pop();
               
                Path.pop();
               
                b1 = 0;
                b2 = 0;
                b3 = 0;
                b4 = 0;
               
            }
            else if (cellvisited > M * N) {
                Control_Path.pop();
                Path.pop();
                build_wall(header, Path.top_x(), Path.top_y(), 'r');
                cellvisited = 0;

            }
           

        }
        else if (b == 2) { // up
            b3 = 1;
            if (up_check(header, Path.top_x(), Path.top_y()) == true) {

                if (Control_Path.top_y() != Path.top_y() + 1) {
                
                Control_Path.push(Path.top_x(), Path.top_y());
               
                Path.push(Path.top_x(), Path.top_y() + 1);
                cellvisited++;
                b1 = 0;
                b2 = 0;
                b3 = 0;
                b4 = 0;



                }


            }
            else if (b1 == 1 && b2 == 1 && b3 == 1 && b4 == 1) {
               
                Control_Path.pop();
                
                Path.pop();
                
                b1 = 0;
                b2 = 0;
                b3 = 0;
                b4 = 0;
                
            }
            else if (cellvisited > M * N) {
                Control_Path.pop();
                Path.pop();
                build_wall(header, Path.top_x(), Path.top_y(), 'u');
                cellvisited = 0;

            }
            
          

        }
        else if (b == 3) { // down
            b4 = 1;
            if (down_check(header, Path.top_x(), Path.top_y()) == true) {
               if (Control_Path.top_y() != Path.top_y() - 1) {
                
                Control_Path.push(Path.top_x(), Path.top_y());
              
                Path.push(Path.top_x(), Path.top_y() - 1);
                cellvisited++;
                b1 = 0;
                b2 = 0;
                b3 = 0;
                b4 = 0;


               }



            }
            else if (b1 == 1 && b2 == 1 && b3 == 1 && b4 == 1) {
             
                Control_Path.pop();
               
                Path.pop();
                
                b1 = 0;
                b2 = 0;
                b3 = 0;
                b4 = 0;
                
            }
            else if (cellvisited > M * N) {
                Control_Path.pop();
                Path.pop();
                build_wall(header, Path.top_x(), Path.top_y(), 'd');
                cellvisited = 0;

            }
            

            

        }
        
        
        


    }
    
    Stack<int> Sorted_Path;
    while (!Path.isEmpty()) {
        Sorted_Path.push(Path.top_x(), Path.top_y());
        Path.pop();
    }
   
    ofstream path_file("maze_" + to_string(MazeID) + "_path_" + to_string(enterx) + "_" + to_string(entery) + "_" + to_string(exitx) + "_" + to_string(exity) + ".txt");
    while (!Sorted_Path.isEmpty()) {
        path_file << to_string(Sorted_Path.top_x())+" "+ to_string(Sorted_Path.top_y())+"\n";
        Sorted_Path.pop();
    }
    path_file.close();
    
    





    
    return 0;
}