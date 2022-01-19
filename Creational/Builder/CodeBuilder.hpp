#include "ClassStruct.hpp"


class CodeBuilder
{
    private:
        ClassStruct root;

    public:
    ClassStruct getRoot() const {return root;};
    /*
    * One alternative to the above is to overload operator ()
    */
    ClassStruct operator() () const {return root;}

    /*
    * When construction starts with a CodeBuilder instance, the root node for ClassStruct is built internally
    * Then, the Codebuilder instance can be used to call 'add_node' and <<, or other builder methods
    * */
    CodeBuilder(const string& class_name):root{class_name}
    {
    }

    /* Method that builds in phases. It returns a reference to self so to allow chain construction.
    * Here, the preference was to hide how the implementation details of the building, so 
    * built's class method appendField was preferred (it uses a vector with an emplace_back)
    */
    CodeBuilder& add_field(const string& name, const string& type)
    {
        root.appendField(name, type);
        return *this;
    }

    //example of usage of the builder
    friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
    {
        os << "class " << obj.getRoot().getClassName() << endl;
        os<<'{'<<endl;
        
        for(auto& class_field : obj().getClassFields())
        {
            //use 2 space identation with "  "
            os << "  " << class_field.getType() << ' ' << class_field.getName() << ';' << endl;
        }
        
        os << '}' << ';'<< endl;
        return os;
    }
};