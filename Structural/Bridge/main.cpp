#include <iostream>

#include "RendererBridge.hpp"
#include "ShrinkWrappedPimpl/PimplClass.hpp"

using namespace std;

/*
* Bridge is a structural pattern that  decouples interface users from the interface implementation(s).
* The interface users and interface implementation(s) can exists as hierarchies, as in the interface can
* have multiple implementations, and the users of the interfaces can have further specializations
* (derived classes)
*
* In long derivation hierarchies, involving at least 2 classes per each derived level, when relatively
* similar specializations are done for the first derived level: 
*   Root->{Derived1_1, Derived1_2}->{Derived1_1_Logic1, Derived1_1_Logic2, Derived1_2_Logic1, Derived1_2_Logic2}
* Such combinations of the derived types can lead to Cartesian product complexity explosion. 
*
* Procedure:
*   1. Thus, such combinations are decoupled  by implementing an interface that exposes the behavior removed from
* the inheritance chain.
*   2. The newly added interface will be used in the inheritance chain it was removed from (in the leaf nodes
* that used to be its parents).
*   3. The root abstarct class aggregates a ref to the new interface, that is created via ctor. Then,
* the corresponding implementation's instance is passed along upon construction.
*
* A particular example of Bridge is Pimpl idiom, which uses an internal pointer to implementation in order
* to decouple a class interface from the methods' implementations. The class uses a privately defined Impl
* class, which is entirely defined in the source code file and only forward declared in the header. 
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