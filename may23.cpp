//May 23
#include <iostream>
#include <ifstream>
using namespace std;

//Constants

const int x = 10;   //must be initialized right away & cannot be changed

struct Node {
    int data;
    Node *next;
};

Node n1 {5, nullptr};

const Node n2 = n1; //copy n1 to n2 and n2 is immutable
n2.data = 10;   //compile time error

//--------------------------------------------------------------------------------

//Parameter Passing

/*Recall from c: 
    pass by value gives a copy of the value and does not change the original value.
    pass a pointer of the value and any changes reflect on the actual value.*/

int x {5};
inc (x);
cout << x << endl;  //6

void inc (int &nr) {    //nr is a reference to x
    nr = nr + 1;
    ++nr;
}

//references
int x = 10;
int &z = x; //z behaves exactly like x; it is an alias for x
//the & here means reference

z = 12; //this updates x to 12

&z <-> &x
//the & here means address

/*References allow us to declare a new name to an object.
They are kind of like const pointers with automatic referencing.

int &z; //not valid because z must be a reference of something; cannot assign it later*/

int intArray[5] = {1, 2, 3, 4, 5};
int &i2 = intArray[2]; //points to 3
i2 = 30;
cout << i2 << endl;
cout << intArray[2] << endl;    //both 30

struct ReallyBig {...};

int f(ReallyBig rb) {...}   //copies caller's rb to f's rb; potentially slow
int g(ReallyBig &rb) {...}  //rb as a alias to the caller's rb; no copying of the data; fast

int h(const ReallyBig &rb) {    //guaranteed the rb won't change by h
    rb.data = "...";    //compile error

    ReallyBig rb2 = rb;
    rb2.data = "...";   //okay to change now
}

/*Prefer pass by const reference for anything larger than a pointer,
unless the function need to make a copy anyway.*/

//What cannot do with reference?
    //-cannot leave them uninitialized
    //-cannot create a ptr to a reference -> different from a pointer
        int i = 5
        int &ir = i;
        &ir <-> &i  //ir and i refer to the same int object so they have the same address
    //-cannot create a reference to a reference
        int &&r;    //not okay
    //-cannot create an array of references

//One more detail:
int f(int &n); 
f(5);   //not okay, because f could change n but n as a literal cannot be changed
f(i);   //okay

int g(const int &n);
g(5);   //okay - g cannot change the literal
g(i);   //okay
//Declaring the parameter const allows us to use the function in more ways.

//--------------------------------------------------------------------------------

//Dynamic Memory Allocation

//c:
int *p = (int *)malloc(10 *sizeof(int));    //malloc allocates 40 bytes &
                                            //returns a ptr to that memory
                                            //(int *) changes a void ptr to an int ptr
//p is a local memory stored on the stack,
//and it points to a block of memory allocated from the heap.

free(p);
p = nullptr;
free(p);    //harmless - calling free with a null pointer doesn't do anything

//c++:
int *p = new int[10];   //new allocates memory from the heap and returns a ptr to that memory
                        //no casting required. Pointer points to an obj with a specific type.

delete[] p; //free the memory

Node *np = new Node;    //allocates a single Node object and returns a pointer to that obj
delete np;

/*physical memory layout
code        -programs loaded and running


-------------------------------------
static data -global variables

-------------------------------------
heap        -free store
Node <---
        |
        |
        |
        |
--------|----------------------------
stack   |   -local variables, function call stack, function parameters
np ------


-------------------------------------*/

//don't free all allocated memory -> memory leak
//Programs may eventually failed and this is regraded as an incorrect program.
Memory allocated with new musted be deallocated with delete.
//Mixing these is an undefined behaviour.

Node *np = new Node;
delete np;
delete np;  //not good, undefined behaviours may happen

np = nullptr;
delete np;  //does nothing

/*Aside:
    -pointers don't know how many elements they point to (huge problem causer in c and c++)*/

int *p; //a pointer to an int array with length 7; first element is p[0]
p++;    //this increments p by 4 bytes, so it is pointing to the next element now
//p[-1] now points to the first element
//p += 5 now points to the last element
