#pragma once

/*
* Template builder pattern implementation can be reused to build multiple complex classes, as long as they provide a AppendItem method that returns void.
* Also, this implementation can be used in multiple ways:
*     1. firstly, it uses the variadic template c-tor to take required arguments used to construct the built object internally, in the TemplateBuilder class, 
*        via dynamic allocation. This case it is bookmarked with a boolean used for deallocating the memory in d-tor. In this case, the built class is hidden
*        from the external world as operations are done via the TemplateBuilder class: variadic template c-tor, AddItem, GetBuiltObject. As the Builder pattern
*        requires the Builder class to hold an instance/pointer/reference to to built object, it is a classical implementation of the pattern
*     2. It was chosen to use a pointer to the built object for the second usage case, when the object is already created, such that the builder class reuses
*        that instance. Hence, the non variadic template c-tor which take a non-const reference parameter. It exposes both Builder and Built classes, as both have to be
*        explicitly instantiated. As the Builder pattern requires the Builder class to hold an instance/pointer/reference to to built object, it is a classical 
*        implementation of the pattern.
*     3. The TemplateBuilder can be exposed by the Built class, via a getter method. Thus, both c-tors of the TemplateBuilder class call a SetTemplateBuilder method
*        of the built class, for injecting *this pointer as dependency. It leads to a circular dependency between ther Built and TemplateBuilder classes, but it hides the 
*        TemplateBuilder class from the external world and operations are handled via the built class. This approach is is less desirable. Conversely,  it is better for 
*        the Built class to use a privately implemented Builder class, if it is desired to hide it. Implicitly, it will have an implementation dedicated to that Built class
*        and even though it does not avoid the circular dependency, the code can be better maintained, as a change of the nested Builder class only impacts that Built class.
* 
* The object is always returned by value, to hide the internally used raw pointer.
* */
template<class T>
class TemplateBuilder
{
    public:
    TemplateBuilder() = default;
    TemplateBuilder& operator=(const TemplateBuilder&) = default;
    TemplateBuilder& operator=(TemplateBuilder&&) = default;
    ~TemplateBuilder()
    {
        if(isBuiltObjectInternallyConstructed)
        {
            delete mBuiltObject;
        }
    }

    //c-tor used when built object instance already exists, as it is created outside the scope of the builder
    TemplateBuilder(T& objectToBuild) : mBuiltObject{&objectToBuild}
    {
        //inject dependency into built class
        mBuiltObject->SetTemplateBuilder(this);
    };
    
    //c-tor used when built object instance doesn't exist, as it is allocated in the scope of the builder
    template<class ... Args>
    TemplateBuilder(Args&& ... args)
    {
        if(!mBuiltObject)
        {
            isBuiltObjectInternallyConstructed = true;
            
            mBuiltObject = new T(std::forward<Args>(args)...);
            
            //inject dependency into built class
            mBuiltObject->SetTemplateBuilder(this);
        }
    }
    
    template<class ... Args>
    void AddItem(Args&& ... args)
    {
        mBuiltObject->AppendItem(args...);
    }
    
    T GetBuiltObject() const {return *mBuiltObject;};
    
    private:
    T* mBuiltObject{nullptr};
    bool isBuiltObjectInternallyConstructed{false};
};
