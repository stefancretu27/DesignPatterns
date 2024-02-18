
#include <iostream>

#include "DynamicDecorator.hpp"
#include "StaticDecorator.hpp"
#include "AnotherStaticDecorator.hpp"
/*
* Decoratror is a design pattern that allows for adding new functionalities (decorate) to existing classes,
* without modifying the current implementation of these classes. The decoration happens by implementing a
* new class, that decorates th existing one.
*
* There are 2 types of decorators:
* 1) Dynamic decorator: implemented via aggregation, as a reference of the Decorated class is encapsulated 
* as by the Decorator class. In addition, the Decorator and the Decorated class must implement
* the same (common) interface. Thus, if the Decorated class does not have a separate interface class that
* it extends, it must provide one, which will also be implemented by the newly created Decorator class.
* The inheritance from the same interface is necessary as the Decorator implements new functionalities for 
* the existing virtual methods, thus respecting the open-closed principle. 
* Nonetheless, this approach does not allow to decorate methods proper to Decorated class, but only the
* virtual methods exposed via the interface class.
*
* The aggregated reference is used as a starting point for the decoration that occurs in the methods overriden
* by Decorator. This allows the decorator class to accept as ctor argument other decorator instances
* (either of the same type or other decorator types), which leads to a sort of composition, as each time,
* but last, the decorated object is another decorator instance.
* eg: Decorator1(Decorator1(Decorator2(InitialObject))) inst;
*
*                                    ____________________________________
*                                    |           Interface -             |
*                                    | implemented by both the Decorated |
*                                    | class, and newly created Decorator|
*                                    | class. Exposes methods to the     |
*                                    | clients of Decorated.             |
*                                    |                                   |
*                                    | virtual void Method() = 0;        |
*                                    |___________________________________|
*                                       /                          \
*                                      /  inheritance               \    inheritance
*                  ___________________/________               ________\______________________________
*                  |   Decorated  class  -    |              |          Decorator class             |
*                  | initial implementation of|              |  implementing the common interface   |  
*                  | the exposed interface    |              |                                      |         
*                  |                          |              |   void Method() override             |
*                  |  void Method() override  |              |    { doOtheWork();                   | 
*                  |    {doWork();}           |              |      doMoreWork();                   |  
*                  |__________________________|              |          doWork();}                  |
*                                                            |                                      |
*                                                            | Decorator(Interface& inst):mref{inst}|
*                                                            |  Interface& mref;                    |  
*                                                            |______________________________________|
*
* 2) Static decorator: it also involves the creation of a new decorator class. In this case, it is a template
* class that inherits from the template parameter type T (as in public T). The common interface is still used
* as T should implement it, but it is not necessary for the Decorator to implement it, which inherits from
* the interface implementation that is also its template type parameetr T. This approach is referred 
* to as mixing inheritance.
* This way, a Decorator object has the Decorated object as its sub object, so it can access all its members,
* including methods particular to T, but which are not available via the interface. This thing is not possible
* with dynamic decorator. Surely, it involves having access to implementations of the interface.
* Additionally, perfect forwarding is used for decorator ctor, such that its ctor arguments are passed along
* to the decorated object's ctor.
*
* Similarily, this approach allows for decorators compositions, as follows
* Decorator2<Decorator1<Decorator2<InitialObject>>>(args) inst;
*
*                                    ____________________________________
*                                    |           Interface -             |
*                                    | implemented by the Decorated      |
*                                    | class only. Exposes methods to    |
*                                    | the clients of Decorated.         |
*                                    |                                   |
*                                    | virtual void Method() = 0;        |
*                                    |___________________________________|
*                                       /                       
*                                      /  inheritance               
*                  ___________________/________               ______________________________________
*                  |   Decorated  class  -    |              |          Decorator class             |
*                  | initial implementation of|              |  template<class T>                   |  
*                  | the exposed interface    | inheritance  |  class decorator : public T          |         
*                  |                          |<-------------|   void Method() override             |
*                  |  void Method() override  |              |    { doOtheWork();                   | 
*                  |    {doWork();}           |              |      doMoreWork();                   |  
*                  |__________________________|              |          doWork();}                  |
*                                                            |                                      |
*                                                            | Decorator(T& inst):mref{inst}        |
*                                                            |  T& mref;                            |  
*                                                            |______________________________________|
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

    Decorated decoratedInst{"decorated instance"};
    DecoratorFloat<Decorated> decoratorFloat{3.14159, decoratedInst};
    DecoratorFloat<DecoratorFloat<Decorated>> decoratorFloatDecoratorFloat{2.7182, decoratorFloat};
    
    DecoratorInt<Decorated> decoratorInt{1, decoratedInst};
    DecoratorInt<DecoratorInt<Decorated>> decoratorIntDecoratorInt{2, decoratorInt};
    
    std::cout<<decoratedInst.GetData()<<" "<<decoratorInt.GetData()<<" "<<decoratorIntDecoratorInt.GetData()<<endl;
    std::cout<<decoratedInst.GetData()<<" "<<decoratorFloat.GetData()<<" "<<decoratorFloatDecoratorFloat.GetData()<<endl;

    return 0;
}
