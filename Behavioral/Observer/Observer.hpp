#pragma once

#include <iostream>
#include <map>

//The Observer exposes an interface, aiming for decoupling, which uses a template type parameter for the type it observes 
template<class ObservedInterface>
class ObserverInterface
{
    public:
    //process change form the observed instance where it occurred
    virtual void ProcessChange(const ObservedInterface& observedObj) = 0;
    virtual ~ObserverInterface() = default;
};

//The Observer interface implementation, also a template, implements the above interface
template<class ObservedInterface>
class ObserverImplementation : public ObserverInterface<ObservedInterface>
{
    public:
    ObserverImplementation()
    {
        static size_t idx{};
        observersIds[this] = idx++;
    }
    
    virtual void ProcessChange(const ObservedInterface& observedObj)
    {
        std::cout<<"Subscriber: "<<observersIds[this]<<" processed notification "<<observedObj.GetData()<<std::endl;
    }
    
    private:
    static std::map<ObserverImplementation<ObservedInterface>*, size_t> observersIds;
};

template<class ObservedInterface>
std::map<ObserverImplementation<ObservedInterface>*, size_t> ObserverImplementation<ObservedInterface>::observersIds;
