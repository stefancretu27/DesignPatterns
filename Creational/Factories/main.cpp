#include "InnerFactory.hpp"
#include "AbstractFactory/AbstractFactoryBuilder.hpp"
#include "InheritanceHierarchy.hpp"

#include <vector>

/*
* Brief description:
* Factory is a design pattern used to deletegate the construction of instances of a class to
* another class, named Factory, for example. Implementation-wise, the latter encapsulates a 
* Create() method which can take the required arguments for constructing the instance, whilst 
* can perform further processing/customization before calling the ctor of the factroied class. 
* The constructed instance is returned from the Factory class.If it is not envisaged to 
* allow direct calls to ctor, it can be made private in the factoried class.
*
*
* Description:
* Factory design pattern provides a mechanism that allows for an easier construction of objects
* whose ctors do not provide an explicit enough API or which require customization upon creation.
* Thus, the customization together with class instantiation are delegated to a factory class,
* which aims at providing a simple API for opbjects' creation while hiding customization.
* It differs from builder as it does not entail piece wise creation of the object, as no
* container of objects is involved in construction phase.
*
* A simple example is when a class requires to hold unique ids, it can delegate the responsibility
* to another classto hold a static id incremented each time a new instance is created.
*
* Implementation wise it involves creating a separate factory class in the private section of the
* constructed class, and having it forward declared. Alternatively, the factory  can be externalized
* and can become a friend class of the constructed class. Then, the factory provides a static method
* which performs creation and customization required upon creation, returning an instance to the
* built class.
*
* Implementation is changed when dealing with polymorphic types. In this scenario, each class in the
* inheritance chain has a corresponding factory class, leading to another inheritance chain of factory
* classes. Then, another class, called abstract factory, aggregates these factories, as it creates them
* manually in its ctor, eventually keeping them in a map, for an inttutive access to them. Furthermore, the
* abstract class access the created to be objects by pointers/references to their interface. That said,
* the abstract factory only deals with abstract classes/interfaces of the created-to-be objects and
* of the factories, whilst remaining agnostic of their implementations.
*
* Thereafter, the abstract factory can have a create method that retruns an instance to the corresponding 
* object, which is created via the afferent factory. The factory is identified via some input to the create 
* method. Alternatively, the abstract factory class can be designed a s abuilder, with the create method
* being replaced by an add_item method, as the abstarct factory builder can encapsulate a container of
* pointers/references to the abstract class/interface of the constructed-to-be objects.
*/

int main()
{
    cout<<"---Inner factory example: factory class implemented as private of the created class with its instance retrieved as Singleton---"<<endl;
    Person p1 = Person::GetFactory().CreatePerson("Bill");
    Person p2 = Person::GetFcatory().CreatePerson("Oana");

    p1.GetDetails();

    //--------------------------------------------------
    cout<<"---Abstract factory with builder: an interface implemented by multiple classes has a corresponding factory abstract class that is implemented in its turn";
    cout<<" by factory classes corresponding to each implementing class. Then, a multiton GetFactory() method of the abstract factory builder handles and returns the needed factory from the map";
    cout<<"constrcucting the collection of objects in phases, as with builder, using the such retrieved factory.---"<<endl;
    
    AbstractFactoryBuilder factoryBuilder{};
    factoryBuilder.addItemToBasket("fruit", 1.1, 2.73)
                    .addItemToBasket("veggie", 0.95, 1.7)
                    .addItemToBasket("dairy", 1.5, 2.7);

    cout << factoryBuilder;

    for(auto& elem : factoryBuilder.getMarketBasket())
    {
        cout<<elem.first<<" "<<elem.second->getPrice()<<endl;
    }

    //--------------------------------------------------
    cout<<"---inheritance hierarchy with factory singleton integrated in interface"<<endl;
    CreatedClass obj1 = CreatedClass::GetFactory().CreateInstance(1, 2.7182, "aha");
    obj1.Display();
    
    CreatedClass obj2 = CreatedClass::GetFactory().CreateInstance(2, 3.14159, "2nd inst");
    obj2.Display();
    
    
    auto interfaceInstance = Interface::GetFactory().CreateInstance(55, -273.7);
    interfaceInstance->DisplayContents();
    
    auto interfaceInstance2 = Interface::GetFactory().CreateInstance(16);
    interfaceInstance2->DisplayContents();
    
    auto interfaceInstance3 = Interface::GetFactory().CreateInstance(-9, 1.01, string("qaz"));
    interfaceInstance3->DisplayContents();

    return 0;
};
