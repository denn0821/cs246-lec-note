//Tue May 16
#include <iostream>
#include <ifstream>
using namespace std;

//Defaults Function Parameters

int f(int a, int b, int c) {...}

f(1, 3, 5);
f(7, 10, 24);

int f(int a, int b = 0, int c = 0) {...}  //we call the value for b and c is default values

f(1);
f(1, 3);

cin.ignore();
cin.ignore(5);
cin.ignore(80, '\n');  //contain two, first is the length and second is the stop value
//default values create more flexible functions

//default value must be at the end of the parameters
int f(int a = 0, int b, int c) {...}  // this is not valid

//the compiler generates the default values
f(1);   //compiler turns this into f(1, 0, 0)

int f(int a, int b = 0, int c = 0); //the declaration of func f
/*  .
    .
    .*/
int f(int a, int b = 0, int c = 0) {...}   //the definition of func f
the definition cannot repeat the default values, or u get a compiler error
f(1, 2);    //compiler adds missing values automatically

//-----------------------------------------------------------------

//Streams
//reading or writing datas

/*Data Sources: input device -> device driver -> input library -> our program
Data Destinations: -> output library ->device driver -> output device*/

/*our job as programmers:
    1) set up I/O streams to the appropriate data sources and destinations
    2) read from and write to the streams
    << >>*/

//to create ostringstream/istringstream, we declare a variable

//The C++ standard library provides the type istream to deal with streams of input,
//and the type ostream ...streams of output.

//istreams: cin, ifstream, istringstream
//ostreams: cout, cerr, ofstream, ostringstream

/*An ostream can be represented like this:
    c       ->
    123     ->
    "hello" ->  ostream -> buffer -> somewhere
    (2, 9)  ->

    -turns various data types to bytes sequences
    -sends them somewhere
    -a buffer is an internal data structure to store data while communicating to the os*/

/*An istream:
'c'     <- 
123     <-      istream <- buffer <- somewhere
"hello" <-

-reads from somewhere
-turns bytes to various type*/

Generally, an istream provides features for reading kinds of output produces by ostreams

//-----------------------------------------------------------------

//Overloading

//c:
    int negint(int n) {return -n;}
    bool negbool(bool b) {return !b;}

//c++:
    int neg(int n) {return -n;}
    bool neg(bool b) {return !b;}

    neg(5); //calling the first func
    neg(false); //calling the second func
    neg(5.0);   //double, not gonna work
    neg("Hello");   //this is c-style string(char *), not gonna work

//Overloading is functions with the same names but different parameter lists
//Functions must differ in numbers of parameters and/or types of parameters

bool f(int a);
int f(int a);   //not valid because only return types are different

int f(int a, int b = 0);
int f(int a, string s = " ");
f(5);   //invalid, compiler doesn't know which function to use
f(5, 0);
f(5, "Hello");  //both works

//-----------------------------------------------------------------

//User-Defined Types

//built-in types:
    int, float, double, char, char *...

//user-defined types, anything is not a built-in type:
    node, vector, point //programmers created
    string, ostringstream, istream  //from system libraries

//how to create a user-defined type:
struct Node{
    int data;
    Node *next;
};

struct Node{
    int data;
    Node next;
};  //won't compile. It's self-referential - cannot determine the size
    //compiler error: node incomplete

struct Node{
    int data;
    Node *next;
}   //compiler gonna assume u define the type node and immediately using it

struct Node{
    int data;
    Node *next;
} n1, n2;
Node n3;    //valid - n1 and n2 used right away and n3 used for later

//-----------------------------------------------------------------

//Constants

const int maxGrade = 100;   //const makes macGrade immutable (cannot be changed)

//to deal with magic numbers:
    const int JUNE = 6;
    if(month == JUNE)...
//for readability and clarity

const int maxGrade;
maxGrade = 100; //this is not valid, const must be initialized when declared

for (int i = 0; i < 10; i++) {
    //n is not declared up here at this point
    const int n = i * 10 * random();    //from here forward, n is immutable
    n += 1; //compiler error
}

Advice: declare as many consts as u can to catch errors
        compiler catches the errors - better at run time

//-----------------------------------------------------------------

//Revisiting Node

struct Node{
    int data;
    Node *next;
};

Node n1;
//to avoid junk values:
n1.data = 10;
n1.next = nullptr;  //nullptr is the NULL in c++, used for a pointer pointing to nothing

Node n2 {10, nullptr};  //{} is the universial initialization syntax

Node n3 = n2;   /*n2    n3
                  10 -> 10
                  /  -> /
                  
                  n2    n3  shallow copy
                  10 -> 10
                  ptr-> ptr
                   |    /
                  n4

                  n2    n3  deep copy
                  10 -> 10
                  ptr-> ptr
                   |    |
                  n4    new ptr*/
