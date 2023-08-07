#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

class Interface
{
    private:
    class Factory;
    
    public:
    virtual void DisplayContents() = 0;
    
    static Factory& GetFactory()
    {
        static Factory factory;
        
        return factory;
    }
    
    private:
    class Factory
    {
        public:
        Factory() = default;
        
        template<class ... Args>
        std::unique_ptr<Interface> CreateInstance(Args&& ... args);
    };
};

class TopClass : public Interface
{
    public:
    TopClass() = default;
    TopClass(const int i) : m_i{i}{}; 
    
    void DisplayContents() override
    {
        std::cout<<m_i<<std::endl;
    }
    
    private:
    int m_i;
};

class MidClass : public TopClass
{
    public:
    MidClass() = default;
    MidClass(const int i, const double d) : TopClass{i},
                                            m_d{d}
    {}; 
    
    void DisplayContents() override
    {
        TopClass::DisplayContents();
        std::cout<<m_d<<std::endl;
    }
    
    private:
    double m_d;
};

class BottomClass : public MidClass
{
    public:
    BottomClass() = default;
    BottomClass(const int i, const double d, const std::string& str) : MidClass{i, d},
                                                                       m_str{str}
    {}; 
    
    void DisplayContents() override
    {
        MidClass::DisplayContents();
        std::cout<<m_str<<std::endl;
    }
    
    private:
    std::string m_str;
};

template<class ... Args>
std::unique_ptr<Interface> Interface::Factory::CreateInstance(Args&& ... args)
{
    std::unique_ptr<Interface> instance;
    
    const std::size_t args_number = sizeof...(Args);
    std::tuple<Args...> argsTuple = std::make_tuple(args...);
    
    if constexpr (args_number == 1)
    {
        instance = std::make_unique<TopClass>(args...);
    }
    else if constexpr (args_number == 2)
    {
        instance = std::make_unique<MidClass>(args...);
    }
    else if constexpr (args_number == 3)
    {
        instance = std::make_unique<BottomClass>(args...);
    }
    
    return instance;
}
