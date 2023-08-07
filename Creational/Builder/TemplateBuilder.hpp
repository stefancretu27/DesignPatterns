#pragma once

/*
* Template builder pattern implementation can be reused to build multiple complex classes, as long as they provide a AppendItem method that returns void.
* Also, this implementation can be used in multiple ways:
*     1. firstly, it uses the variadic template c-tor to take required arguments used to construct the built object internally, in the TemplateBuilder class, 
*        via dynamic allocation. In this case, the built class is hidden from the external world as operations are done via the TemplateBuilder class: 
*        variadic template c-tor, AddItem, GetBuiltObject. The AddItem method returns the instance of the TemplateBuilder, for reusability in chain construction
*     2. It was chosen to use a pointer to the built object for the second usage case, when the object is already created, such that the builder class reuses
*        that instance. So, to the raw pointer being it can be assigned the address of the statically allocated Built instance, as smart pointers work only with 
*        dynamically allocated objects.This design exposes both Builder and Built classes, as both have to be explicitly instantiated.
*     3. It internally creates an empty object, eventually when the default TemplateBuilder c-tor is called via Built's GetBuilder() method, reusing the
*       such created templateBuilder instance for chained construction.
*
* For the first use case, there are 2 c-tors overloads: without parameters and with variadic template arguments. The 2nd use case only requires the address
* of the existing instance, as argument.
* The object is always returned by value, to hide the internally used raw pointer.
* */
template<class T>
class TemplateBuilder
{
    public:
    TemplateBuilder& operator=(const TemplateBuilder&) = default;
    TemplateBuilder& operator=(TemplateBuilder&&) = default;
    ~TemplateBuilder() = default;
    
    //c-tors used for internally built object
    template<class ... Args>
    TemplateBuilder(Args&& ... args)
    {
        if(!mBuiltObject)
        {
            mBuiltObject = new T(std::forward<Args>(args)...);
        }
    }
    
    TemplateBuilder()
    {
        if(!mBuiltObject)
        {
            mBuiltObject = new T{};
        }
    }
    
    //c-tor used for when the Built object is instantiated outside the TemplateBuilder class
    TemplateBuilder(T* objectToBuild)
    {
        if(!mBuiltObject)
        {
            mBuiltObject = objectToBuild;
        }
    }
    
    template<class ... Args>
    TemplateBuilder<T>& AddItem(Args&& ... args)
    {
        mBuiltObject->AppendItem(args...);
        
        return *this;
    }
    
    inline T GetBuiltObject() const 
    {
        return *mBuiltObject;
    };
    
    inline T operator()()
    {
        return *mBuiltObject;
    }
    
    private:
    T* mBuiltObject{nullptr};
};
