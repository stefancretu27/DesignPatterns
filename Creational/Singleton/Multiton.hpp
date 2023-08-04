#pragma once

#include <string>
#include <map>

/*
* Unlinke singleton that creates a unique instance of a class in the entire's project's lifetime,
* the multiton allowas for creation of multiple instances, each insatnce being uniquely identified using a key.
* The keys and instances are bookkept in a map. The map can be statically created by the getInstance method or
* can be a member of the class, which would allow for more customization, as it serves as base class, with CRTP, for
* classes requiring controlled multiple instances
*/

//Multiton class working with multiple types of keys, but using string as default
template<class Key = std::string>
class Multiton
{
    public:
    static Multiton* GetInstance(const Key& key)
    {
        static std::map<Key, Multiton*> mInstances;
        
        auto&& it = mInstances.find(key);
        if( it == mInstances.end())
        {
            Multiton* instance = new Multiton{};
            mInstances[key] = instance;
        }
        
        return mInstances[key];
    }
      
    private:
    Multiton() = default;
};

/*
* The Multiton pattern is an extension of the singleton pattern, allowing a class
* to have more instances, but in a controlled fashion, as each instance is connected to
* a key, hence bookkept in a map. Consequently, for a specific key (word/value/identifier)
* only one instance of the class is created. 
* The Multiton can be implemented as a template class, acting as a stencil used to instantiate
* other classes in the above-described controlled fashion. Internally, it associates the Key
* with a (unique) pointer that is allocated when the instances is requested but doesan't exist.
* For being compliant with multiple classes, the getInstance method is implemented as variadic
* template which perfect forwards the variadic template arguments to the class' c-tor.
*
* Works with c++17.
*/

template<class T, class Key = std::string>
class Multiton
{
    public:
    template<class ... Args>
    static T& GetMultitonInstance(const Key& key, Args&& ... args)
    {
        const std::size_t args_number = sizeof...(Args);
        
        auto&& it = mInstances.find(key);
        
        if (it == mInstances.end())
        {
            if constexpr (args_number > 0)
            {
                mInstances[key] = std::make_unique<T>(std::forward<Args>(args)...);
                std::cout<<"Key "<<key<<" associated with instance created with parameters"<<std::endl;
            }
            else if constexpr (args_number == 0)
            {
                mInstances[key] = std::make_unique<T>();
                std::cout<<"Key "<<key<<" associated with no params instance"<<std::endl;
            }
        }
        
        std::cout<<"Map size: "<<mInstances.size()<<std::endl;
        
        return *mInstances[key];
    }
    
    static void DeleteSpecificInstance(const Key& key)
    {
        auto&& it = mInstances.find(key);
        
        if(it != mInstances.end())
        {
            mInstances.erase(it); //or mInstances.erase(key);
        }
    }
    
    static void DeleteAllInstance()
    {
        mInstances.clear();
    }
    
    private:
    Multiton() = default;
    static std::map<Key, std::unique_ptr<T>> mInstances;
};

template<class T, class Key>
std::map<Key, std::unique_ptr<T>> Multiton<T, Key>::mInstances;
