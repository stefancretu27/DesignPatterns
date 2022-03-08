#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "Observable.hpp"

template<class T>
class Observer
{
    public:
    virtual void fieldChanged(T& sourceObject, const string& name) = 0;
};

class MyObserver: public Observer<MyObservableClass>
{
    public:
    void fieldChanged(MyObservableClass& sourceObject, const string& name) override
    {
        cout<<name<<" has changed to "<<sourceObject.getValue()<<endl;
    };
};