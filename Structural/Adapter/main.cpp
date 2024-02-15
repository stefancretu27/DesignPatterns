#include <iostream>

#include "SquareToRectangleAdapter.hpp"

using namespace std;

/*
* Adapter is a structural design pattern that involves the developemnt of a new piece of code
* which perform conversions between an existing interface to required interfaces. It can be
* an interface per see, or a method's signature.
* 
* Often, this process entails conversions between data types, so they should be related.
* One example is converting a more concrete type to a general one, or to another one as derived as it is.
* Another example is conversion from type A back to the type B that A is composed from. 
*
* Implementtaion-wise, it involves creating a separate class, named Adapter, which inherits from the
* class/interface to adapt to. Next to that, it holds and Adapted class instance or interface ref/ptr,
* which is used when overriding the inherited behavior from the AdaptTo class, including afferent data 
* conversions and processing. Also, it candefines methods whose implementations perform further adaptations.
*
* This way, the newly created Adapter class/interface reuses the AdaptTo interface, eventually extending it, 
* to encapsulate and customize the Adapted interface calls to be used via the AdaptTo interface. Consequently,
* via the Adapter class, the Adapted class' interface is used as if it was AdaptedTo, with no need to be rewritten.
*
*     _________________________________
*     |    AdaptTo  - known interface |
*     | widely used in the program    |
*     |_______________________________|
*             /|\
*              |  Inherits/extends
*              |    
*     _________|______________________________________                   ______________________________________
*     |   Adapter - newly implemented interface      |   Aggregation     |    Adapted - existing interface    |
*     |   extends known interface. Inherited methods | /_________________| must be used as AdaptTo interface  |
*     | wrap calls to Adapted methods + conversions  | \                 |____________________________________|
*     |______________________________________________|
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
