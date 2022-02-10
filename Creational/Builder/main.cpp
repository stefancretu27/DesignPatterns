#include "CodeBuilder.hpp"

/*
* The builder design pattern provides a mechanism that allows the creation of a class to take place in steps.
*
* The reason behind is that some classes are complex and require lots of input upon creation. Having a ctor
* with lots of parameters makes it difficult to use and follow. Additionally, some classes may encapsulate
* containers of objects (even of pointers to self type) which can be built incrementally (node by node).
*
* Implementation-wise, it entails developing a separate class, called builder, which encapsulates a member
* instance to the class meant to be built. This member represents the root node in the class construction
* and is set by Builder's ctor (as it calls the appropriate ctor for its members ). Then the builder class 
* defines an add_node/add_item methods that provides a simple interface for adding a new node. The method
* returns reference to self (*this) to allow for chaining operations:
* builder_inst.add_item(data1).add_item(data2).add_item(data3)
* 
* The new nodes are added to the root, so a get method for it is also implemented by the builder. When it is
* called, the entire nodes are retrieved. The builder class should eb forwared declared to the built class
* such that it can be set a sfriend class of the built class, allowing for an easier access to the private data.
*
* Another implementation approach, reuses the forward declaration and friendship with the built class, but does
* not expose the builder class to the end user. Instead, the built class encapsulates a method that returns an
* instance to the builder,eventually as singleton method, as only one builder instance is required.
*
*/

int main()
{
    // If the CodeBuilder is meant to be instantiated, then its implementation should have an instance to the class it builds, 
    // Thus, its ctor creates a root node of the built class' type where is starts the construction from
    auto cb1 = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
    cout<<cb1<<endl;

    cout << ClassStruct::createBuilder("Foo")->add_field("mUPtrSomeClass", "unique_ptr<SomeClass>")<<endl;

    return 0;
}
