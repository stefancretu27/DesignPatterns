#pragma once

/*
* Template builder pattenr implementation can eb reused to build multiple complex classes, as long as they provide a AppendItem method that returns void.
* Also, this implementation can be used in multiple ways. Firstly, it uses the variadic template c-tor to take required arguments used to construct the 
* built object internally, via dynamic allocation. In this case, is bookmarked with a boolean for deallocating the memory in d-tor.
* It was chosen to use a pointer to the built object for the second usage case, when the object is already created, such that the builder class reuses
* that instance. hence, the non variadic template c-tor which take a non-const reference parameter.
* The object is always returned by value, to hide the internally used raw pointer.
* */
template<class T>
class Builder
{
    public:
    Builder() = default;
    ~Builder()
    {
        if(isBuiltObjectInternallyConstructed)
        {
            delete mBuiltObject;
        }
    }

    //c-tor used when built object instance already exists, as it is created outside the scope of the builder
    Builder(T& objectToBuild) : mBuiltObject{&objectToBuild}
    {};
    
    //c-tor used when built object instance doesn't exist, as it is allocated in the scope of the builder
    template<class ... Args>
    Builder(Args&& ... args)
    {
        if(!mBuiltObject)
        {
            isBuiltObjectInternallyConstructed = true;
            
            mBuiltObject = new T(std::forward<Args>(args)...);
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
