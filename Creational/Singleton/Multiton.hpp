#pragma once

#include <string>
#include <map>

/*
* Unlinke singleton that creates a unique instance of a class in the entire's project's lifetime,
* the multiton allowas for creation of multiple instances, each insatnce being uniquely identified using a key.
* The keys and instances are bookkept in a map. The map can be statically created by the getInstance method or
* can be a member of the class, which would allow for more customization.
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

//customizable multiton, working with different built types and different key types.
template<class Key, class T>
class CustomizableMultiton
{
    public:
    static CustomizableMultiton* GetInstance(const Key& key)
    {
        auto&& it = mInstances.find(key);
        if( it == mInstances.end())
        {
            T* instance = new T{};
            mInstances[key] = instance;
        }
        
        return mInstances[key];
    }
    
    static void DeleteInstance(const Key& key)
    {
        auto&& it = mInstances.find(key);
        if( it != mInstances.end())
        {
            mInstances.erase(key);
        }
        
    }
    
    static void DeleteAllInstances()
    {
        mInstances.clear();
    }
      
    private:
    CustomizableMultiton() = default;
    static std::map<Key, T*> mInstances;
};

template<class Key, class T>
std::map<Key, T*> CustomizableMultiton<Key, T>::mInstances{};
