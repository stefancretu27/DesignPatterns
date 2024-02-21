#include "RatGameObserver.hpp"

#include "Observer.hpp"

/*
* Observer is a behavioral design pattern which involves 2 entities:
*   - one which generates a signal or launches an event, called observable
*   - one which wishes to be informed when a certain event occured in the other entity, or when the other entity triggers a signal
*
* Implementation-wise, observer is a class which subsribes to get notification from the observable class. The observer
* tipically executes a routine, a callback called sometimes, when it receives the notification/signal. 
*
*    ______________________________________________________                        _________________________________________________
*    |  template<class ObservedType>                       |      Uses             | class Observed/Notifier/Publisher/Signal       |
*    |  class Observer/Notified/Subscriber/Slot            |---------------------->|                                                |  
*    |  {                                                  |                       | vector<Observer*> observersList;               |
*    |    void ProcessNotification(ObservedType& notifier) |                       |                                                |  
*    |    {                                                |                       | void NotifyOne(Observer* notifiedObserver)     |
*    |        notifier.GetChange();                        |   Aggregates          |   { notifiedObserver->ProcessChange(*this);}   |
*    |    }                                                |<----------------------|                                                |   
*    |  }                                                  |                       | void Subscribe(Observer* subscriber)           |   
*    |_____________________________________________________|                       |   { observersList.push_back(subscriber);}      |
*                                                                                  |                                                |
*                                                                                  | void Unsubscribe(Observer* unsubscriber)       |  
*                                                                                  |   {  remove_it = remove(unsubscriber);         |
*                                                                                  |      observersList.erase(remove_it, end());}   |
*                                                                                  |                                                |
*                                                                                  | void NotifyAll()                               |
*                                                                                  |   { for(auto observer* : observersList)        |
*                                                                                  |        observer->ProcessChange(*this); }}      |
*                                                                                  |________________________________________________|  
*
* This callback's signature is being made accessible via an interface, which can be template, such that when the Observer class 
* implements it, it can explicitly state which observable class it whishes to observe. In addition, the template type parameter 
* is used as a placeholder for the data type of the source object, which launched the signal/event. This object would be an instance
* of a generic observable class. This way, the object's attributes are being made accessible in the Observer class.
*           ObserverInterface <T>
*            { virtual void callbackRoutine(T& sourceObject) = 0;} 
*                   ^
*                   |       -->inherits from 
*           ObserverClass: public  ObserverInterface<Observable>    -->specifies which observable class it observes, which is forward declared
*           { virtual void callbackRoutine(Observable& sourceObject) override;}      --> the source object data type is known
*                                                                                        so its attributes can be accessed here
*                                                                                        via public methods
*
* On the other hand, the observable class uses the observer template interface, that is forward declared, as well, such that
* it keeps inside a list of observers, that are pointers/refs to the ObserverInterface, whose template parameter is the observable 
* class type. When performing a notification, the observer iterates over this list and invokes the callbackRoutine, that is
* accessible via the used interface. In addition, it provides subscribe and unsubscribe methods which add/remove an ObserverInterface
* to the list of pointers/refs. 
*
* Eventually, the observable can inherit from a template class, as the notify, subscribe and unsubscribe methods
* have a generic implementation which can be reused by multiple observer classes. The template class is not an interface per se,
* a sit implements the 3 methods, which are then used by the classes inheriting from it, following the CRTP approach.
*           Observable <T>
*            { void notify(T& sourceObject) { for(auto&& observer : observers){observer->callbackRoutine(sourceObject)};}
*              void subscribe(Observer<T>&);
*              void unsubscribe(Observer<T>&); 
*            } 
*                   ^
*                   |       -->inherits from 
*           ObservableImpl: public Observable<ObservableImpl>    -->CRTP
*           calls notify(*this), subscribe(Observer<ObservableImpl>&), unsubscribe(Observer<ObservableImpl>&)
*
* Using template interface for ObserverClass it allows for a decoupling between the 2 components. Moroever, there can be 
* multiple implementations of the observer interface (more observer classes with distinct implementation of the same
* interface) which would allow different components to implement specific behavior for an observable's notification.
*/

int main()
{
    ObservableClass observed;
	//ObserverImplementation<ObservableClass> observer;
	auto observer = make_shared<ObserverImplementation<ObservableClass>>();
	observed.Subscribe(observer);
	observed.SetData("data change");
	observed.NotifyOne(observer);
	
	observed.Subscribe(make_shared<ObserverImplementation<ObservableClass>>());
	observed.SetData("update data change");
	observed.NotifyAll();
    
    return 0;
}
