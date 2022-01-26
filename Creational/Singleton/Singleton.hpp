#pragma once

#include <memory>

/*
* Singleton is a class that is instantiated only once in the process' lifetime.
* This unique instance is returned via a public static method after is created locally, in the same method,
* as a static local variable => thread safe wih magic statics since c++11.
* Copy semantics should be deleted.
*
* In order to solve the testability issues, the methods from the Singleton class that must be tested
* can be included in an interface. From this interface, the Singleton class then derived. Also, a singleton dummy
* class also derives, implementing the same behavior for its emthods, but on mocked data. Otherwise, it
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

