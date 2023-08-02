#include "CodeBuilder.hpp"
#include "JsonFileStructure.hpp"
/*
* Brief description: 
* Builder is used when the class instance requires construction in multiple steps, either because it 
* encapsulates a data structure that is populated in phases, or because it is so complex such that requires
* multiple parameters upon construction, also provided in phases. Implementation-wise, it entails developing 
* a separate class, called builder, which encapsulates a member instance to the class meant to be built.
*
* Description:
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

    //use builder as singleton instance via the built class
    cout<<"---use builder as singleton instance via the built class---"<<endl;
    JsonFileStructure jsonFileInstance{};
    jsonFileInstance.GetUPtrBuilder().AddItem(make_pair("item_singleton", "value"));
    jsonFileInstance.GetUPtrBuilder().AddItem(make_pair("item2_singleton2", to_string(27.91)));
    
    jsonFileInstance.DisplayContents();
    
    //use builder and built class with explicitly created instances
    cout<<"---use builder and built class with explicitly created instances---"<<endl;
    JsonFileStructure objToBuild{};
    Builder<JsonFileStructure> builder{objToBuild};
    builder.AddItem(make_pair("item", "value"));
    builder.AddItem(make_pair("new_item", to_string(-3.14159)));
    
    for(auto&& keyVal : objToBuild.GetJsonFileStructure())
    {
        cout<<keyVal.first<<" "<<keyVal.second<<endl;
    }
    
    objToBuild = move(jsonFileInstance);
    objToBuild.DisplayContents();
    jsonFileInstance.DisplayContents();
    
    //use built class as internally created by the builder
    cout<<"---use built class as internally created by the builder---"<<endl;
    Builder<JsonFileStructure> builderInternallyBuiltObj{make_pair("internally", "built obj")};
    builderInternallyBuiltObj.AddItem(make_pair("new", "item"));
    
    for(auto&& keyVal : builderInternallyBuiltObj.GetBuiltObject().GetJsonFileStructure())
    {
        cout<<keyVal.first<<" "<<keyVal.second<<endl;
    }
    
    cout<<"=============="<<endl;
    
    Builder<JsonFileStructure> test{make_pair("2", "22")};
    test.AddItem(make_pair("55", "5"));
    
    for(auto&& keyVal : test.GetBuiltObject().GetJsonFileStructure())
    {
        cout<<keyVal.first<<" "<<keyVal.second<<endl;
    }

    return 0;
}
