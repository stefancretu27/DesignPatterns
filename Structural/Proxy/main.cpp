#include "VirtualProxy.hpp"
#include "PropertyProxy.hpp"


/*
* Brief description:
* Provides a placeholder (proxy object) for accessing another object (resource).
*
* Use Case: Control access to another object
*        Remote proxy (acts as an intermediary for a remote service)
*        Virtual proxy (creates an object lazily on request)
*        Security proxy (adds security to a request)
*        Caching proxy (delivers cached requests)
*
* Description:
* Proxy is a design pattern that offers a mechanism to access a resource, which can be remote.
* It acts as a wrapper over the proxied object and offers exactly the same interface as the
* proxied object, such that the object is used the same way it was used before the proxy existed.
* Additionaly, proxy controls lifetime of the proxied object. However, proxy methods can add further 
* functionality in its interface methods. Smart pointers, lock wrappers are examples of proxies and,
* in general, ani class implementing the RAII idiom acts as a proxy (as it controls access and the
* lifetime of the wrapped objects).
*
* 1) Virtual proxy
* Implementation wise, it involves creating an interface class that encapsulates as pure virtual methods
* all the public methods, but c-tors and d-tor, of the proxy class. The interface is implemented then,
* by both proxied and proxy class. Furthermore, the proxy class encapsulates an instance, or a pointer
* to the proxied class, which is used to retrieve data from the proxy object, by calling its methods,
* when overriding. During overriding, the proxy class adds new functionality into the overrides.
* It acts merely as a Dynamic Decorator, only that it keeps an instance/ref/pr to Proxied class, not
* to the interface.
*
*                                    ____________________________________
*                                    |           Interface -             |
*                                    | implemented by both the Proxied   |
*                                    | class, and newly created Proxy    |
*                                    | class. Exposes methods to the     |
*                                    | clients of Proxied class.         |
*                                    |                                   |
*                                    | virtual void Method() = 0;        |
*                                    |___________________________________|
*                                       /                          \
*                                      /  inheritance               \    inheritance
*                  ___________________/________               ________\______________________________
*                  |   Proxied  class  -      |              |            Proxy class -             |
*                  | initial implementation of|              | implementing the common interface.   |  
*                  | the exposed interface.   |              | Provides access to Proxied instance, |         
*                  | Provides manipulation    |              | that can be stored remotely          |
*                  | of a resource.           |              |                                      |  
*                  |                          |              |void Method() override                |
*                  |  void Method() override  |              |    { doOtheWork();                   | 
*                  |    {doWork();}           |              |      doMoreWork();                   |  
*                  |__________________________|              |          mRef.doWork();}             |
*                                                            |                                      |
*                                                            | Proxy(Proxied& inst):mref{inst}      |
*                                                            |  Proxied& mref;                      |  
*                                                            |______________________________________|
*
* 2) Property proxy
* It entails implementing a template class that offers an interface for data members of other classes.
* That said, the proxy wraps a data member for which it overloads assignment operator, provides conversion 
* c-tor and conversion operator overloading. This way, it is not necessary to write setters and getters for 
* public data members. It acts a wrapper for data members in a class.
*
**                                    ____________________________________
*                                    |  template<class T> PropertyProxy -|
*                                    |                                   |    
*                                    | offers interface to the member of |
*                                    | Type T that it encapsulates. Thus |
*                                    | the access and lifetime of its T  |
*                                    | member is controlled              |
*                                    |                                   |
*                                    | T member;                         |
*                                    |___________________________________|
*                                       /                      
*                                      /  uses             
*                  ___________________/____________________              
*                  |             User class  -             |             
*                  | uses the template PropertyProxy class |              
*                  | that wraps all the data members of    |                      
*                  | the User class.                       |             
*                  |                                       |              
*                  |  PropertyProxy<std::string> mStr;     |             
*                  |  PropertyProxy<MyClass> mMyClass;     |             
*                  |_______________________________________|              
*/

int main()
{
    MyClass inst1 (0, "this");
    
    cout<<inst1.mId<<" "<<inst1.mName<<endl;
    
    Property<string> pstr {inst1.mName};
    cout<<pstr<<endl;

    //virtual proxy
    Person p{};
    ResponsiblePerson rp{p};

    rp.set_age(17);
    cout<<rp.drink()<<" "<<rp.drive()<<" "<<rp.drink_and_drive()<<endl;

    rp.set_age(37);
    cout<<rp.drink()<<" "<<rp.drive()<<" "<<rp.drink_and_drive()<<endl;

    rp.set_age(7);
    cout<<rp.drink()<<" "<<rp.drive()<<" "<<rp.drink_and_drive()<<endl;
    
    return 0;
}
