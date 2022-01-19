#include <string>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

/*
* Forward decvlare the builder class, so a conversion method to it can be implemented
*/
class CodeBuilder;

/*
* Helper class to better structure the code. Not necessarily relevant for pattern's implementation
*/

class ClassStructField
{
    public:
        explicit ClassStructField(const string& name, const string& type):mName{name}, mType{type}{};

        const string& getName() const {return mName;};
        const string& getType() const {return mType;};

    private:
        string mName;
        string mType;
};

/*
* Class to be built in phases
*/
class ClassStruct
{
    public:
        explicit ClassStruct(const string& className):mClassName{className}{};
        
        const string& getClassName() const {return mClassName;};
        void setClassName(const string& name){mClassName = name;};
        
        vector<ClassStructField> getClassFields() {return move(mClassFields);};
        void appendField(const string& name, const string& type)
        {
            mClassFields.emplace_back(name, type);
        }

        /*
        * To be used when the construction is initiated from ClassStruct.
        * Return by pointer so to mitigate incomplete type error caused by incomplete definition of CodeBuilder, which is later defined
        * */
        static unique_ptr<CodeBuilder> createBuilder(const string& className)
        {
            return make_unique<CodeBuilder>(className);
        }

        //alternative impl for the above
        // static CodeBuilder* createBuilder(const string& className)
        // {
        //     return new CodeBuilder(className);
        // }

    private:
        string mClassName;
        /*
        * collection of items to self (or subtype of self) where the building in phases will append to
        */
        vector<ClassStructField> mClassFields;
        
        /*
        * the builder class is friend of the built class, so the builder class can access the built's class private members
        */
        friend class CodeBuilder;
};