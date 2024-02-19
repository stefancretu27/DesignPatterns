#include <iostream>

#include "RendererBridge.hpp"
#include "ShrinkWrappedPimpl/PimplClass.hpp"

using namespace std;

/*
* Brief description: 
* Bridge is a structural pattern that decouples interface users from the interface implementation(s).
* The interface users can be other interfaces or their implementation classes, thus complex inheritance
* hierarchies, that aggregate refs to the used interface. The used interface can gave multiple implementations:
* either long inheritance chain, or more derivates at the same inheritance level, with any changes in them
* being opaque to th user classes.
*
*        ______________________________                                    ___________________________________ 
*        |       UserInterface        |                                  / |         UsedInterface           |
*        |                            |                                 /  |                                 |
*        | virtual void Method() = 0; |                                /   |  virtual void UsedMethod() = 0; | 
*        |____________________________|                               /    |_________________________________|
*                   ^                /\                              /                 ^                     \    
*                   |                 \               Aggregation   /                  |                      \         
*                   | inheritance      \                           /                   |                       \    
*         __________|_______________    \_________________________/                    |                        \   
*         |        UserImpl1       |     |       UserImpl2        |            ________|___________      ________\___________       
*         |                        |     |                        |            |     UsedImpl1     |     |     UsedImpl2     | 
*         | virtual void Method()  |     | virtual void Method()  |            |                   |     |                   |   
*         |  { mRef.Usedmethod();} |     |  { mRef.Usedmethod();} |            | void UsedMethod() |     | void UsedMethod() |
*         |                        |     |                        |            |    {Impl1;}       |     |   {Impl1;}        |  
*         | UsedInterface& mRef;   |     | UsedInterface& mRef;   |            |___________________|     |___________________|
*         |________________________|     |________________________|                    ^
*                                                                                      |          
*                                                                                      |  
*                                                                               _______|____________
*                                                                               |  UsedImpl1_1      |   
*                                                                               |                   |
*                                                                               | void UsedMethod() |
*                                                                               |    {Impl1_1;}     |
*                                                                               |___________________| 
*
* Long derivation hierarchies, involving at least 2 classes per each derived level, when relatively
* similar specializations are done for the first derived level, as the 2nd level being merely users of their
* base classes, with each class in the first derivation level getting a relatively similar specialization:
*   Root->{Derived1_1, Derived1_2}->{Derived1_1_Logic1, Derived1_1_Logic2, Derived1_2_Logic1, Derived1_2_Logic2}
* Such combinations of the derived types can lead to Cartesian product complexity explosion, between used (base) 
* classes and users (derived ) classes.
* Briefly, it involves creating a separate interface, implemented by the classes that used to be at the lowest
* inheritance level (that used the behavior of their bases), with the bases using that interface to call the
* appropriate behavior, created via constructor of the used class
*
* Procedure:
*   1. Thus, such combinations are decoupled  by implementing an interface that exposes the behavior removed from
* the inheritance chain.
*   2. The newly added interface will be used in the inheritance chain it was removed from (in the leaf nodes
* that used to be its parents).
*   3. The root abstract class aggregates a ref to the new interface, that is created via ctor. Then,
* the corresponding implementation's instance is passed along upon construction.
*
* In particular, PImpl is a typical technique to reduce the compilation dependency.It aims to have a stable ABI 
* and to reduce the compilation time. Separating interface from implementation, the private members of the bridged
* class are moved to a newly constructed class, Impl. The latter is encapsulated by the bridged class, as it hold
* a member ptr to it. Thus, any changes to the implementation, that is Impl class, or any of its dependecies (Class1,
* Class2) require recompilation of the .cpp file containing Impl class definition, but not of the .cpp files using 
* the Bridged class' interface (which can be main.cpp or other source code files).
* This way, it decouples a class/interface user, from its implementation, by trading off composition in favor 
* of aggregation, with the composition being deferred to the Impl class. 
* Implementation-wise, the Bridged class must explicitly delcare c-tor and d-tor and define them in the source 
* code file, after the Impl class is defined. This wsay, the Impl class would appear as a complete type when the 
* c-tor and d-tor of the Bridged class will call the c-tor and d-tor of the member unique_ptr to Impl class.
*
*        __________________________            _____________________________            ______________________
*        |     Bridged.hpp        |            |        Bridged.cpp        |   includes |    Class1.hpp      |
*        |{                       |            |                           | ---------->|                    |
*        | private:               |            |class Bridged::Impl        |            |____________________|
*        | class Impl;            |            |{                          |
*        | unique_ptr<Impl> impl; |            | private:                  |            _____________________
*        |}                       |            | Class1 instClass1;        | includes   |    Class2.hpp      |
*        |________________________|            | Class2 instClass2;        | ---------->|                    |        
*                                              |}                          |            |____________________|
*                                              |                           | 
*                                              | Bridged implementation    |
*                                              |___________________________|
*/

void renderingUsingBridge(const Shape& shape)
{
    cout<<shape.str()<<endl;
}

int main()
{
    //declare renderer instances
    VectorRenderer vr{};
    RasterRenderer rr{};

    Triangle t1{vr};
    renderingUsingBridge(t1);

    Triangle t2{rr};
    renderingUsingBridge(t2);

    Square s1{vr};
    renderingUsingBridge(s1);

    Square s2{rr};
    renderingUsingBridge(s2);

    PimplClass pimplObj{8};

    pimplObj.addData("one");
    pimplObj.addData("string");
    pimplObj.addData("and");
    pimplObj.addData("another");
    pimplObj.addData("STRING");

    pimplObj.printData();
    return 0;
}
