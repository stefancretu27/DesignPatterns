#pragma once

#include <memory>

/*
* Brief description: Singleton is used when it is required to instntiate a class only once in process lifetime.
* Implementation-wise, it creates a static instance inside a static method, which is a thread safe approach, whilst
* the c-tor is private.
*
* Description:
* Singleton is a class that is instantiated only once in the process' lifetime.
* This unique instance is returned via a public static method after it is created locally, in the same method,
* as a static local variable => thread safe with magic statics since c++11.
* Copy semantics should be publicly deleted.
*
* In order to solve the testability issues, the methods from the Singleton class that must be tested
* can be included in an interface. From this interface, the Singleton class then derives. Also, a singleton dummy
* class derives from it, implementing the same behavior for its methods, but on mocked data. Otherwise, it
* would be tested the behavior on the actual data (eg: prod DB), which is undesirable.
*/

class SingletonRef
{
    public:
    static SingletonRef& getInstance();

    ~SingletonRef() = default;
    SingletonRef(const SingletonRef&) = delete;
    SingletonRef& operator=(const SingletonRef&) = delete;

    protected:
    SingletonRef() = default;    
};

SingletonRef& SingletonRef::getInstance()
{
    static SingletonRef uniqueInstance{};

    return uniqueInstance;
}

class SingletonUPtr
{
    public:
    static const std::unique_ptr<SingletonUPtr>& getInstance();

    ~SingletonUPtr() = default;
    SingletonUPtr(const SingletonUPtr&) = delete;
    SingletonUPtr& operator=(const SingletonUPtr&) = delete;

    protected:
    SingletonUPtr() = default;

};

const std::unique_ptr<SingletonUPtr>& SingletonUPtr::getInstance()
{
    static std::unique_ptr<SingletonUPtr> uniqueInstance {new SingletonUPtr()};

    return uniqueInstance;
}

