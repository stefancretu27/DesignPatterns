#include "CodeBuilder.hpp"

int main()
{
    // If the CodeBuilder is meant to be instantiated, then its implementation should have an instance to the class it builds, 
    // Thus, its ctor creates a root node of the built class' type where is starts the construction from
    auto cb1 = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
    cout<<cb1<<endl;

    cout << ClassStruct::createBuilder("Foo")->add_field("mUPtrSomeClass", "unique_ptr<SomeClass>")<<endl;

    return 0;
}