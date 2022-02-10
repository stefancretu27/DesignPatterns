

#include "Singleton.hpp"
#include "SingletonTester.hpp"
#include "SingletonDataAccess.hpp"
#include "CheckTypes.hpp"

/*
* Singleton is a class that is instantiated only once in the process' lifetime.
* This unique instance is returned via a public static method after it is created locally, in the same method,
* as a static local variable => ensuring thread safety wih magic statics since c++11.
* Copy semantics of the Singleton class must be deleted.
* The instance can be returned as a reference to self or as a const reference to unique_ptr to self
*
* In order to solve the testability issues, the methods from the Singleton class that must be tested
* can be included in an interface. From this interface, the Singleton class then derived. Also, a singleton dummy
* class also derives, implementing the same behavior for its emthods, but on mocked data. Otherwise, it
* would be tested the behavior on the actual data (eg: prod DB), which is undesirable.
*/

template<class T> 
T* factoryRef()
{
    auto& inst = T::getInstance();
    static_assert(check_type<decltype(inst)>::is_ref(), "getInstance should return by ref");

    return &inst;
}

template<class T> 
T* factoryUPtr()
{
    auto& inst = T::getInstance();
    static_assert(check_type<decltype(inst)>::is_uptr(), "getInstance should return by unique_ptr");

    return inst.get();
}

template<class T> 
T* factoryPtr()
{
    T* inst= new T{};

    return inst;
}

class NonSingleton
{

};

map<unsigned, string>  SingletonDataAccess::mData;
const string SingletonDataAccess::mFilename{"C:\\Users\\scretu\\VisualCodeProjects\\DesignPatterns\\Creational\\Singleton\\data.txt"};

int main()
{
    SingletonRef* singletonref = factoryRef<SingletonRef>();

    SingletonUPtr* singletonUptr = factoryUPtr<SingletonUPtr>();

    //auto dummyInst = factoryUPtr<SingletonRef>();

    cout<<"is SingletonRef class a singleton: "<<SingletonTester::is_singleton<SingletonRef>(factoryRef<SingletonRef>)<<endl;
    cout<<"is SingletonUPtr class a singleton: "<<SingletonTester::is_singleton<SingletonUPtr>(factoryUPtr<SingletonUPtr>)<<endl;
    cout<<"is NonSingleton class a singleton: "<<SingletonTester::is_singleton<NonSingleton>(factoryPtr<NonSingleton>)<<endl;

    SingletonDataAccess::getInstance().parseFile();
    SingletonDataAccess::getInstance().printData();

    DummyDataAccess::getInstance().parseFile();
    DummyDataAccess::getInstance().printData();

    return 0;
}

