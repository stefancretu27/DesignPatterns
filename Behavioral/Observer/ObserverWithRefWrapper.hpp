#pragma once

#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <functional>

template<class ObservableType>
class ObserverInterface
{
    public:
    void ProcessNotification(ObservableType& sender);
    virtual ~ObserverInterface() = default;
    
    friend bool operator==( const ObserverInterface& lhs,
                            const ObserverInterface& rhs)
    {
        return lhs==rhs;
    }
    
    //this overload makes use of the above
    friend bool operator==( const std::reference_wrapper<ObserverInterface> lhs,
                            const std::reference_wrapper<ObserverInterface> rhs)
    {
        return lhs.get()==rhs.get();
    }
    
    private:
    virtual void DoProcessNotification(ObservableType& sender) = 0;
};

template<class ObservableType>
void ObserverInterface<ObservableType>::ProcessNotification(ObservableType& sender)
{
    DoProcessNotification(sender);
}

//Implementation
template<class ObservableType>
class ObserverImpl : public ObserverInterface<ObservableType>
{
    public:
    ObserverImpl() = default;
    ~ObserverImpl() = default;
    ObserverImpl(const ObserverImpl& ) = default;
    ObserverImpl(ObserverImpl&& ) = default;
    ObserverImpl& operator=(const ObserverImpl& ) = default;
    ObserverImpl& operator=(ObserverImpl&& ) = default;
    
    
    private:
    void DoProcessNotification(ObservableType& sender) override;
};

template<class ObservableType>
void ObserverImpl<ObservableType>::DoProcessNotification(ObservableType& sender)
{
    std::cout<<" Sender: "<<sender.GetID()<<"sent message: "<<sender.GetMessage()<<std::endl;
}



//Apply CRTP by using the implementation of the below interface
template<class ObservableImpl, class MsgType>
class ObservableInterface
{
    public:
    void AddObserver(ObserverInterface<ObservableImpl>& observerObject);
    void RemoveObserver(ObserverInterface<ObservableImpl>& observerObject);
    void NotifyOne(ObserverInterface<ObservableImpl>& observerObject, MsgType& message);
    void NotifyAll(MsgType& message);
    MsgType GetMessage();
    size_t GetID();
    virtual ~ObservableInterface() = default;
    
    private:
    virtual void DoAddObserver(ObserverInterface<ObservableImpl>& observerObject) = 0;
    virtual void DoRemoveObserver(ObserverInterface<ObservableImpl>& observerObject) = 0;
    virtual void DoNotifyOne(ObserverInterface<ObservableImpl>& observerObject, MsgType& message) = 0;
    virtual void DoNotifyAll(MsgType& message) = 0;
    virtual size_t DoGetID() = 0;
    virtual MsgType DoGetMessage() = 0;
};

template<class ObservableImpl, class MsgType>
void ObservableInterface<ObservableImpl, MsgType>::AddObserver(ObserverInterface<ObservableImpl>& observerObject)
{
    DoAddObserver(std::forward(observerObject));
}

template<class ObservableImpl, class MsgType>
void ObservableInterface<ObservableImpl, MsgType>::RemoveObserver(ObserverInterface<ObservableImpl>& observerObject)
{
    DoRemoveObserver(std::forward(observerObject));
}

template<class ObservableImpl, class MsgType>
void ObservableInterface<ObservableImpl, MsgType>::NotifyOne(ObserverInterface<ObservableImpl>& observerObject, MsgType& message)
{
    DoNotifyOne(std::forward(observerObject));
}

template<class ObservableImpl, class MsgType>
void ObservableInterface<ObservableImpl, MsgType>::NotifyAll(MsgType& message)
{
    DoNotifyAll();
}

template<class ObservableImpl, class MsgType>
size_t ObservableInterface<ObservableImpl, MsgType>::GetID()
{
    return DoGetID();
}

template<class ObservableImpl, class MsgType>
MsgType ObservableInterface<ObservableImpl, MsgType>::GetMessage()
{
    return DoGetMessage();
}


//Implementation
template<class MsgType = std::string>
class ObservableImpl : public ObservableInterface<ObservableImpl<MsgType>, MsgType>
{
    public:
    ObservableImpl() = default;
    ~ObservableImpl() = default;
    ObservableImpl(const ObservableImpl<MsgType>& ) = default;
    ObservableImpl(ObservableImpl<MsgType>&& ) = default;
    ObservableImpl& operator=(const ObservableImpl<MsgType>& ) = default;
    ObservableImpl& operator=(ObservableImpl<MsgType>&& ) = default;
    
    
    private:
    MsgType mMessage;
    std::list<std::reference_wrapper<ObserverInterface<ObservableImpl<MsgType>>>> observersList;
    
    void DoAddObserver(ObserverInterface<ObservableImpl<MsgType>>& observerObject) override
    {
        auto it = /*std::find_if( observersList.cbegin(), 
                                observersList.cend(), 
                                [&observerObject](std::reference_wrapper<ObserverInterface<ObservableImpl<MsgType>>> rhs)
                                {
                                    return observerObject==rhs.get();
                                }
                                );*/
                    std::find( observersList.cbegin(), observersList.cend(), std::cref(observerObject));
                                
        if(it == observersList.end())
        {
            observersList.push_back(observerObject);
        }
    }
    
    void DoRemoveObserver(ObserverInterface<ObservableImpl<MsgType>>& observerObject) override
    {
        auto it = /*std::remove_if( observersList.begin(), 
                                  observersList.end(), 
                                  [&observerObject](std::reference_wrapper<ObserverInterface<ObservableImpl<MsgType>>> rhs)
                                    {
                                        return observerObject==rhs.get();
                                    });*/
                std::remove( observersList.begin(), observersList.end(), std::ref(observerObject));
                                    
        observersList.erase(it, observersList.end());
    }
    
    void DoNotifyOne(ObserverInterface<ObservableImpl<MsgType>>& observerObject, MsgType& message) override
    {
        observerObject.ProcessNotification(*this);
    }
    
    void DoNotifyAll(MsgType& message) override
    {
        for(auto&& observer : observersList)
        {
            observer.get().ProcessNotification(*this);
        }
    }
    
    size_t DoGetID() override
    {
        static size_t id{};
        
        return id++;
    }
    
    MsgType DoGetMessage() override
    {
        return mMessage;
    }
};
