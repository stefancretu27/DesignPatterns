#include "MarketBasketItem.hpp"

#include <memory>

//create abstract factory class hierarchy

//double cannot be non template parameter as it is non const expresion
class MarketBasketItemFactory
{
    public:
        virtual ~MarketBasketItemFactory() = default;
        virtual unique_ptr<MarketBasketItem> createItem(double weight, double price) = 0;
};

class FruitFactory: public MarketBasketItemFactory
{
    public:
        unique_ptr<MarketBasketItem> createItem(double weight, double price)
        {

            return make_unique<Fruit>(weight, price);
        }
};

class VegetableFactory: public MarketBasketItemFactory
{
    public:
        unique_ptr<MarketBasketItem> createItem(double weight, double price)
        {

            return make_unique<Vegetable>(weight, price);
        }
};

class DairyFactory: public MarketBasketItemFactory
{
    public:
        unique_ptr<MarketBasketItem> createItem(double weight, double price)
        {
            return make_unique<Dairy>(weight, price);
        }
};