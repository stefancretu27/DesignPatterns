#include "VirtualProxy.hpp"
#include "PropertyProxy.hpp"


/*
* Proxy is a design pattern that offers a mechanism to access a resource, which can be remote,
* It acts as a wrapper over the proxied object and offers exactly the same interface as the
* proxied object, such that the object is used the same way it was used before the proxy existed,
* However, proxy methods can add further functionality in its interface methods.
*
* 1) Virtual proxy
* Implementation wise, it involves creating an interface class that encapsulates as pure virtual methods
* all the public methods, but c-tors and d-tor, of the proxy class. The interface is implemented then,
* by both proxied and proxy class. Furthermore, the proxy class encapsulates an instance, or a pointer
* to the proxied class, which is used to retrieve data from the proxy object, by calling its methods,
* when overriding. During overriding, the proxy class adds new functionality into the overrides.
*
* 2) Property proxy
* It entails implementinga  template class that offers an interface for data members of other classes.
* That said, the proxy wraps a data member for which it overloads assignment operator, provides conversion 
* c-tor and conversion operator overloading. This way, it is not necessary to write stter and getters for \
* public data members.
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