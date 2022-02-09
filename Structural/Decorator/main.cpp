
#include <iostream>

#include "DynamicDecorator.hpp"
#include "StaticDecorator.hpp"
/*
* Decoratror is a design pattern that allows for adding new functionalities (decorate) to existing classes,
* without modifying the current implementation of these classes. The decoration happens by implementing a
* new class, that decorates th existing one.
*
* There are 2 types of decorators:
* 1) Dynamic decorator: implemented via aggregation, as an instance of the existing class is encapsulated 
* as a reference in the decorator class. In addition, the decorator and the decorated class must implement
* the same (common) interface. The inheritance from the same interface is necessary as the decorators
* implement new functionalities for the considered virtual methods. The aggregated reference is used
* as a starting point for the decoration that occurs in the methods overriden by decorators.
*
* This allows the decorator class to accept as ctor argument other decorator instances
* (either of the same type or other decorator types), which leads to a sort of composition, as each time,
* but last, the decorated object is another decorator instance.
* eg: Decorator1(Decorator1(Decorator2(InitialObject))) inst;
*
* 2) Static decorator: the decorator classes are template and they inherit from the template parameter type T
* (as in public T). Here, T should be an implementation of the interface that should have been common, but
* that is not implemented anymore by the decorator classes. This is referred to as mixing inheritance.
* This way, a decorator objects has the decorated object as its sub object, so it can access all its members,
* including methods particular to T, but which are not available via the interface. This thing is not possible
* with dynamic decorator.
* Additionally, perfect forwarding is used for decorator ctor, such that its ctor arguments are passed along
* to the decorated object's ctor
*
* Similarily, this approach allows for decorators compositions, as follows
* Decorator2<Decorator1<Decorator2<InitialObject>>>(args) inst;
*/
int main()
{
    //Dynamic decorator
    Rose rose{};
    RedFlower red_rose{rose};
    RedFlower red_red_rose{red_rose};
    BlueFlower blue_red_rose{red_rose};
    BlueFlower blue_rose{rose};
    BlueFlower blue_blue_rose{blue_rose};
    RedFlower red_blue_rose{blue_rose};
    RedFlower redRose{red_rose};
    RedFlower redredRose{redRose};
    BlueFlower blueredredRose{redredRose};
    
    cout<<rose.str()<<endl;
    cout<<blue_rose.str()<<endl;
    cout<<red_rose.str()<<endl;
    cout<<red_red_rose.str()<<endl;
    cout<<blue_red_rose.str()<<endl;
    cout<<blue_blue_rose.str()<<endl;
    cout<<red_blue_rose.str()<<endl;
    cout<<redredRose.str()<<endl;
    cout<<blueredredRose.str()<<endl<<endl;
    
    //static decorator
    unsigned noOfFlowers{5};
    RedFlowerDecorator<RoseImpl> decorateRedRose(noOfFlowers);
    BlueFlowerDecorator<RedFlowerDecorator<RoseImpl>> decorateRedBlueRose{decorateRedRose};

    cout<<decorateRedRose.str()<<endl;
    cout<<decorateRedBlueRose.str()<<endl;
    cout<<RedFlowerDecorator<BlueFlowerDecorator<BlueFlowerDecorator<RedFlowerDecorator<WaterLilyImpl>>>>(noOfFlowers+2).str()<<endl;

    return 0;
}