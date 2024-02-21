#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <memory>

//observer headers
#include "Observer.hpp"

//Observed interface is a template whose type parameetrs include the Implementation class of this interface and the data type it works with
//Exposes the required methods for add observer, remove observer, notify all observers, notify one observer, as wrappers of the private virtual methods
template<class Impl, class DataType>
class ObservableInterface
{
    public:
    void NotifyAll()
    {
        DoNotifyAll();
    };
    
    void NotifyOne(const std::shared_ptr<ObserverInterface<Impl>>& observerObj)
    {
        DoNotifyOne(observerObj);
    };
    
    void Subscribe(const std::shared_ptr<ObserverInterface<Impl>>& observerObj)
    {
        DoSubscribe(observerObj);
    };
    
    void Unsubscribe(const std::shared_ptr<ObserverInterface<Impl>>& observerObj)
    {
        DoUnsubscribe(observerObj);
    };
    
    virtual DataType GetData() const = 0;
    
    virtual ~ObservableInterface() = default;
    
    private:
    virtual void DoNotifyAll() = 0;
    virtual void DoNotifyOne(const std::shared_ptr<ObserverInterface<Impl>>& observerObj) = 0;
    virtual void DoSubscribe(const std::shared_ptr<ObserverInterface<Impl>>& observerObj) = 0;
    virtual void DoUnsubscribe(const std::shared_ptr<ObserverInterface<Impl>>& observerObj) = 0;
};

//The implementation of the above Observable interface, pivately implementing the inherited virtual methods 
//Keeps a list of observers, as shared_ptr due to copies required by std::algorithms, whilst envisaging to keep the outside created instances
class ObservableClass : public ObservableInterface<ObservableClass, std::string>
{
    public:
    void SetData(const std::string& str){mData = str;};
    std::string GetData() const {return mData;};
    
    private:
    void DoNotifyAll() override
    {
        for(auto&& observer : mObserversList) 
        {
            observer->ProcessChange(*this);
        }
    }
    
    void DoNotifyOne(const std::shared_ptr<ObserverInterface<ObservableClass>>& observerObj) override
    {
        observerObj->ProcessChange(*this);
    }
    
    void DoSubscribe(const std::shared_ptr<ObserverInterface<ObservableClass>>& observerObj) override
    {
        auto it = std::find(mObserversList.begin(), mObserversList.end(), observerObj);
        
        if(it == mObserversList.end())
        {
            mObserversList.push_back(std::move(observerObj));
        }
    }
    
    void DoUnsubscribe(const std::shared_ptr<ObserverInterface<ObservableClass>>& observerObj) override
    {
        mObserversList.erase(std::remove(mObserversList.begin(), mObserversList.end(), observerObj), mObserversList.end());
    }
    
    std::string mData;
    std::vector<std::shared_ptr<ObserverInterface<ObservableClass>>> mObserversList;
};
