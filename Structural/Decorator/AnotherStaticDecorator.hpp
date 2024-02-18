#pragma once
#include <string>
#include <type_traits>

class Decorated
{
    public:
    Decorated() = default;
    explicit Decorated(const std::string& str) noexcept : mStr{str} 
    {};
    Decorated(const Decorated& instance) : mStr{instance.mStr}{};
    
    std::string GetData() const
    {
        return mStr;
    }
    
    private:
    std::string mStr;
};

template<class T>
class DecoratorInt
{
    public:
    DecoratorInt() = default;
    template<class ... Args>
    explicit DecoratorInt(const int i, Args&& ... args) noexcept : mi{i}, 
                                                                mDecoratedObject{std::forward(args)...}
    {};
    
    explicit DecoratorInt(const int i, T& decoratedObject) noexcept : mi{i},
                                                                    mDecoratedObject{decoratedObject}
    {};
    
    DecoratorInt(const DecoratorInt& decoratedInt):mi{decoratedInt.mi},
                                                    mDecoratedObject{decoratedInt.mDecoratedObject}
    {};
    
    std::string GetData() const 
    {
        return  std::string(" ### ") + mDecoratedObject.GetData() + std::string(" ") + std::to_string(mi);
    }
    
    private:
    int mi;
    T mDecoratedObject;
};

template<class T, typename = std::enable_if_t< std::is_same<Decorated, T>::value || std::is_base_of<Decorated, T>::value>>
class DecoratorFloat : public T
{
    public:
    template<class ... Args>
    explicit DecoratorFloat(const float f, Args&& ... args) noexcept : T{std::forward(args)...}, mf{f}
                                                                
    {};
    
    explicit DecoratorFloat(const float f, T& decoratedObject) noexcept : T{decoratedObject}, mf{f}
                                                                        
    {};
    
    std::string GetData() const 
    {
        return  std::string(" ### ") + T::GetData() + std::string(" ") + std::to_string(mf);
    }
    
    private:
    float mf;
};
