#include "CodeBuilder.hpp"
#include "JsonFileStructure.hpp"
#include "PrivateBuilderClass.hpp"
/*
* Brief description: 
* Builder is used when the class instance requires construction in multiple steps, either because it 
* encapsulates a data structure that is populated in phases, or because it is so complex such that requires
* multiple parameters upon construction, also provided in phases. 
* Implementation-wise, it entails delegating the construction of the Built object to a separate class, named Builder.
* The latter encapsulates a member, called root object, that can be instance or pointer to the class meant to be built, and whose  
* creation is managed by builder's ctor. Furthermore, it encapsulates a AddItem method, that returns the builder's instance, such 
* that AddItem can be called in chain and manipulates the built's members requiring construction in phases. 
* The Builder instance is retrieved via Built's interface, via a getter, constructing it every time the getter is called. 
* Additionally, the Builder can keep track of the created instances, mapping them to a key received as argument to Built.
* The Builder class can be friend of the Built class, or implemented in the scope of the Built class, such that
* it gets access to private members to be constructed. 
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
* called, the entire nodes are retrieved. The builder class should be forwared declared to the built class
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

     //use builder as template class examples
    cout<<"---1. use template  builder as instance built within a static method of the built class---"<<endl;
    JsonFileStructure jsonFileInstance = JsonFileStructure::GetStaticBuilder().AddItem(make_pair("template builder", "add item"))
                                                                               .AddItem(make_pair("same template builder", to_string(27.91))).GetBuiltObject();
    
    jsonFileInstance.DisplayContents();
    
    //use builder and built class with explicitly created instances
    cout<<"---use template builder and built class with explicitly created instances---"<<endl;
    JsonFileStructure objToBuild{make_pair("built object", "instantiated outside the template builder")};
    TemplateBuilder<JsonFileStructure> builder{&objToBuild};
    builder.AddItem(make_pair("item", "value")).AddItem(make_pair("new_item", to_string(-3.14159)));
    
    for(auto&& keyVal : objToBuild.GetJsonFileStructure())
    {
        cout<<keyVal.first<<" "<<keyVal.second<<endl;
    }
    
    //use built class as internally created by the builder
    cout<<"---use built class as internally created by the builder with variadic template---"<<endl;
    TemplateBuilder<JsonFileStructure> builderInternallyBuiltObj{make_pair("internally", "built obj")};
    builderInternallyBuiltObj.AddItem(make_pair("new", "item"));
    
    for(auto&& keyVal : builderInternallyBuiltObj().GetJsonFileStructure())
    {
        cout<<keyVal.first<<" "<<keyVal.second<<endl;
    }

    cout<<"---use Builder class as private class to the Builder, with dependences on each other, enforcing adding new item via the Builder instance---"<<endl;
    
    Built builtObject = Built::GetStaticPrivateBuilder().AddItem(make_pair("private builder", "locally constructed in static getter"))
                                                        .AddItem(make_pair("add item using private builder", "-271.3"))
                                                        .AddItem(make_pair("another object", "added in chained fashion"))();
    builtObject.DisplayContents();
    
    Built anotherBuiltObject = Built::GetStaticPrivateBuilder(make_pair(" newly built object", "using Builder's variadic template c-tor"))
                                                               .AddItem(make_pair("another", "built object")).ConstructObject();
    anotherBuiltObject.DisplayContents();

    return 0;
}
