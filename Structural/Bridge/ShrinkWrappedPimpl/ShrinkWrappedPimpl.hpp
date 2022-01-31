#pragma once

#include <memory>
#include <utility>
#include <tuple>

template<class T>
class ShrinkWrappedPimpl
{
    public:
    ~ShrinkWrappedPimpl() = default;

    ShrinkWrappedPimpl();
    //c-tor with template parameter pack
    template<class...Args>
    ShrinkWrappedPimpl(Args&&...args);

    T& operator*();
    T* operator->();

    private:
        std::unique_ptr<T> impl;
};

template<class T>
ShrinkWrappedPimpl<T>::ShrinkWrappedPimpl():impl{new T{}}
{

}

template<class T>
template<class...Args>
ShrinkWrappedPimpl<T>::ShrinkWrappedPimpl(Args&&...args):impl{ new T{std::make_tuple<Args...>(std::forward<Args>(args)...) } }
{
    //make_unique does not work if it does not know at compile time the ctor => use new
    //forward args as ref to r-values (deduced from Args&&) to the c-tor of T class
    
}

template<class T>
T& ShrinkWrappedPimpl<T>::operator*()
{
    return *impl.get();
}

template<class T>
T* ShrinkWrappedPimpl<T>::operator->()
{
    return impl.get();
}