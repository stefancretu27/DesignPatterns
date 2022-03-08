#pragma once

#include <string>
#include <vector>
#include <algorithm>

template<class T>
class Observer;

template <class ObservableClass>
class ObservableBase
{
    private:
    vector<Observer<ObservableClass>*> observers; 

    public:
    void notify(ObservableClass& sourceObject, const string& fieldName)
    {
        for(Observer<ObservableClass>* obs : observers)
        {
            obs->fieldChanged(sourceObject, fieldName);
        }
    }

    void subscribe(Observer<ObservableClass>& obs)
    {
        observers.push_back(&obs);
    }

    void unsubscribe(Observer<ObservableClass>& obs)
    {
        observers.erase( remove(observers.begin(),
                                observers.end(),
                                &obs),
                         observers.end()
                       );
    }
};

// Observable class inherit from template Base class using CRTP idiom
class MyObservableClass: public ObservableBase<MyObservableClass>
{
    private:
    int value;

    public:
    MyObservableClass(const int val):value{val}{};

    void setValue(const int val)
    {
        value = val;
        notify(*this, "value");
    }

    int getValue() const {return value;};
};