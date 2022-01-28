#include <iostream>

#include "SquareToRectangleAdapter.hpp"

using namespace std;

/*
* Adapter is a structural design pattern that involves the developemnt of a new piece of code
* which perform conversions between an existing interface to a required interfaces. It can be
* an interface per see, or a method's signature.
* 
* Often, this process entails conversions between data types, so they should be related.
* One example is converting a more concrete type to a general one, or to another one as derived as it is.
* Another example is conversion from type A back to the type B that A is composed from. 
*
* Procedure: 
*   1. the adaptee is encapsulated in a Adapter class that inherits from the class it has to adapt to.
* That is because the prpocess logic requires an object of type Adapte to to work with, so such an object
* nneds to be constructed from an adaptee. So the Adapter class extends from the Adapted to class.
*   2. The adapter class c-tor takes as input the adaptee and uses it to build the class, or parts of the class
* it inherits from.
*
* This way, the structure of the Adaptee is changed to the Adapted To format.
*/

void printArea(const Rectangle& rectangle)
{
    cout<<"Area is: "<<rectangle.area()<<endl;
}

int main()
{
    //Step 1: Use the existing interface, that is of class Square, to create a square object.
    Square squareInst{4};

    //Step 2: the existing logic (printArea) uses a Rectangle, not a Square
    //Step 3: convert Square to Rectangle using adapter, which inherits from Rectangle and aggregates Square
    printArea(SquareToRectangleAdapter(squareInst));

    return 0;
}