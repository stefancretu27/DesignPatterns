#pragma once

#include <iostream>
#include <string>

using namespace std;

template<class T>
class Property
{
    public:
    Property(const T& val)
    {
        mValue = val;
    }
    
    operator T()
    {
        return mValue;
    }
    
    T& operator=(const T& val)
    {
        mValue = val;
        return *this;
    }
    
    friend ostream& operator<<(ostream& os, const Property<T>& p)
    {
        os << p.mValue;
        
        return os;
    }
    
    private:
    T mValue;
};

struct MyClass
{
    public:
    MyClass(unsigned id, const string& name): mId{id}, mName{name}{};
    

    Property<string> mName;
    Property<unsigned> mId;
};
