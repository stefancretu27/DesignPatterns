#include "Mediator.hpp"

/*
* Mediator is a design pattern that facilitates communication between components which are not
* aware of each other's presence/absence (such as participants in a chat room).
*
*    ________________________________________________                 __________________________________________
*    |  template<class T>  class Mediator            |   Uses         | template<class T> MediatedInterface    |             
*    |                                               |--------------->|                                        |
*    | vector<Interface*> mediatedObjs;              |                | virtual void DoWork(const T& msg) = 0; | 
*    |                                               |                | virtual void ValueUpdate(int val = 0); |
*    |void Broadcast(Interface* source, const T& msg)|                |________________________________________|
*    | {                                             |                                     ^
*    |    for(Interface* ptr : mediatedObjs)         |                                     |   
*    |    {    if(ptr!=source)                       |                                     |   Inherits    
*    |           ptr.DoWork(msg);                    |                                     |    
*    |    }                                          |                 ____________________|___________________________
*    | }                                             |   Composition  |            MediatedClass                       |
*    | void Unicast(Interface* src, Interface* dst)  |<---------------|                                                |
*    | {    if(ptr!=source)                          |                | Mediator<int> mediatorInst;                    |
*    |            ptr.DoWork(); }                    |                |                                                |
*    |_______________________________________________|                | MediatedClass()                                |
*                                                                     | { mediatorInst.mediatedObjs.push_back(*this);} |
*                                                                     |                                                |
*                                                                     | void ValueUpdate(int val)                      |
*                                                                     | { mediatorInst.Broadcast(*this, val);}         |
*                                                                     |                                                |
*                                                                     | void DoWork(const T& msg)                      |
*                                                                     | {  cout<<msg;}                                 |         
*                                                                     |________________________________________________|
*
* Implementation wise it is a class or component that encapsulates some business logic which
* is used by other classes/components when communicating. That said, other component call
* the mediator's methods. Moroever, the mediator can call methods from the components that use it.
*
* A mediator is aggregated as ptr/ref by a class willing to use it. This way, that component can call
* mediator's methods when implementing its communication logic. In its turn, the mediator can use interface
* or pointers to classes that need to communicate, usually being kept in a container were all participants
* in the communication are centralized. Via this interface/pointer, the mediator can invoke the methods 
* of the classes that need to communicate.
*/

int main()
{
    Mediator mediator{};

    Participant p1{mediator};
    Participant p2{mediator};
    Participant p3{mediator};
    Participant p4{mediator};
    Participant p5{mediator};

    p1.say(5);
    p4.say(1);
    p3.say(-1);

    mediator.printMessageLog();

    return 0;
}
