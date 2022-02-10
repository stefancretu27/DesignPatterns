#include "InnerFactory.hpp"
#include "AbstractFactory/AbstractFactoryBuilder.hpp"

#include <vector>

/*
* Factory design pattern provides a mechanism that allows for an easier construction of objects
* whose ctor do not provide an explicit enough API or which require customization upon creation.
* Thus, the customization togetehr with class instantiation are delegated to a factory class,
* which aims at providing a simple API for opbject"s creation while hiding customization>
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

//explicitly instantiate static const member
const unique_ptr<Person::PersonFactory> Person::factory {make_unique<Person::PersonFactory>()};

int main()
{
    Person::factory->createPerson("Bill");
    Person::factory->createPerson("Oana");


    //--------------------------------------------------

    AbstractFactoryBuilder factoryBuilder{};
    factoryBuilder.addItemToBasket("fruit", 1.1, 2.73)
                    .addItemToBasket("veggie", 0.95, 1.7)
                    .addItemToBasket("dairy", 1.5, 2.7);

    cout << factoryBuilder;

    for(auto& elem : factoryBuilder.getMarketBasket())
    {
        cout<<elem.first<<" "<<elem.second->getPrice()<<endl;
    }

    return 0;
};
