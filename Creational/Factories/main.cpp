#include "InnerFactory.hpp"
#include "AbstractFactory/AbstractFactoryBuilder.hpp"

#include <vector>
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