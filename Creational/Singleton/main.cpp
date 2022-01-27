
#include "Singleton.hpp"
#include "SingletonTester.hpp"
#include "SingletonDataAccess.hpp"

template<class T>
struct check_type
{
    static constexpr bool is_ref(){return false;};
    static constexpr bool is_ptr(){return false;};
    static constexpr bool is_uptr(){return false;};
};

template<class T>
struct check_type<T&>
{
    static  constexpr bool is_ref(){return true;};
    static constexpr  bool is_ptr(){return false;};
    static  constexpr bool is_uptr(){return false;};
};

template<class T>
struct check_type<T*>
{
    static constexpr bool is_ref(){return false;};
    static constexpr bool is_ptr(){return true;};
    static constexpr bool is_uptr(){return false;};
};

template<class T>
struct check_type<const unique_ptr<T>&>
{
    static  constexpr bool is_ref(){return false;};
    static constexpr  bool is_ptr(){return false;};
    static  constexpr bool is_uptr(){return true;};
};

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

class NonSingleton
{

};

template<class T> 
T* factoryPtr()
{
    T* inst= new T{};

    return inst;
}

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
