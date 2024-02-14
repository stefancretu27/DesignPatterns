#include "PrototypeInnerFactory.hpp"

/*
* Prototype is used to build complex objects from existing objects, by copying data from them, either fully or partially.
* The fully data copy can be done via copy constructors that use deep copy approach.
* The partial copy can leverage prototype data that is resued from an existing object and replicated for the newly created ones.
*
* Implementation-wise, in its simplest form, involves using a CreatWithPrototype method, which reuses the complex object
* constructed for previous instances, or in previous operations, stored as member, and which can take additional input arguments.
* 
* After the creation of the new objects, they can be further customized, either by chaning some of the fully copied data, or
* by adding values to the fields not set during partial copy process. Thus, this customization leads to the need to use
* a factory prototype.
*/


int Person::PersonFactory::person_id{};
Address Person::PersonFactory::prototype{};

int main()
{
    auto bill = Person::getFactory()->createPersonWithAddress("Bill", "Bacau", "Tudor Vladimirescu", 256);
    auto oana = Person::getFactory()->createPersonUsingPrototype("Oana");

    cout <<oana<<endl;;

    auto gogu = Person::getFactory()->createPersonWithAddress("Gogu", "Gherla", "Odaia", 14);
    auto ela = Person::getFactory()->createPersonUsingPrototype("Ela");
    cout << gogu <<endl<<ela<<endl;

    return 0;
};
