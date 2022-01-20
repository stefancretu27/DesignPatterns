#include "MarketBasketItemFactory.hpp"
#include <map>
#include <string>

/*
* Why using builder?
* This class brings together builder and abstract factory patterns.
* It is essentially a Builder composed of a collection of objects which are constructed via their factory.
* The collection is a map that is built in phases (object by object) => necessity for builder. 
* 
* MarketBasketItem abstract class usefulness for hidding implementation details:
* When AbstractFactoryBuilder is used by the outside world, implementation details of MarketBasket are hidden.
* So, the user does not know about the existence of the classes in MarketBasket inheritance chain. 
* Neither does AbstractFactoryBuilder. Thus, such implementation details are hidden from builder as well. 
*
* Why using abstract factories?
* The outside world deals with a market basket, which is a collection of MarketBasketItem instances. 
* As it is abstract class, its creation leads to creation of one of its derived implementations. That
* said, to the outside world it appears that the creation of MarketBasketItem requires customization.
* That said, based on a item type givern as input, MarketBasketItem is constructed in a certain way =>
* => necessity for abstract factory
*
* So, leveraging factory pattern, AbstractFactoryBuilder deals with factories in order not to be concerned 
* with each type's constructor. Concretely, the factory interface (MarketbasketItemFactory) provides an  
* uniform API to build each type from MarketBasketItem inheritance chain, that is createItem().
*
* As each type has its own factory, AbstractFactoryBuilder has to create all of them. This step is
* necessary only once, so it is performed by the AbstractFactoryBuilder c-tor.
* 
* To be noted that AbstractFactoryBuilder is aware of all the types in the inheritance chain, but only
* privately, as its public interface does not expose the types' creation mechanism used by factories,
* in order to properly access their interface for outputting information.
*/
class AbstractFactoryBuilder
{
    private:
        map<string, unique_ptr<MarketBasketItem>> mMarketBasket;
        map<string, unique_ptr<MarketBasketItemFactory>> mItemsFactories;

        /*
        * the factories have to be created by hand, in correspondence with the string identifying the item type
        */
        MarketBasketItemFactory& getFactory(const string& item_type)
        {
            MarketBasketItemFactory* ptrFactory;

            if(item_type == "fruit" || item_type == "Fruit")
            {
                ptrFactory = mItemsFactories["fruit"].get();
            }
            if(item_type == "veggie" || item_type == "vegetable" | item_type == "Veggie" || item_type == "Vegetable")
            {
                ptrFactory = mItemsFactories["vegetable"].get();
            }
            if(item_type == "dairy" || item_type == "Dairy")
            {
                ptrFactory =  mItemsFactories["dairy"].get();
            }

            return *ptrFactory;
        }

    public:
        AbstractFactoryBuilder()
        {
            //construct factories
            mItemsFactories["fruit"] = make_unique<FruitFactory>();
            mItemsFactories["vegetable"] = make_unique<VegetableFactory>();
            mItemsFactories["dairy"] = make_unique<DairyFactory>();
        }

        AbstractFactoryBuilder& addItemToBasket(const string& item_type, double weight, double price)
        {
            //Step 1: create factory
            auto&& factory = getFactory(item_type);

            //Step 2: use factory to create item
            mMarketBasket[item_type] = factory.createItem(weight, price);
            return *this;
        }

        const map<string, unique_ptr<MarketBasketItem>>& getMarketBasket() const {return mMarketBasket;};

        friend ostream& operator<<(ostream& os, const AbstractFactoryBuilder& factoryBuilder)
        {
            os << "My market basket: "<<endl;
            os << '{' <<endl;
            for(const auto& mapElement : factoryBuilder.mMarketBasket)
            {   
                os << "  {" <<endl;
                os << "    [item type:] " << mapElement.first <<endl;
                os << "    [properties:] " << endl;
                 os << "   {" << endl;
                os << "      [weight:] " << mapElement.second->getWeight() <<endl;
                os << "      [price:] " << mapElement.second->getPrice() <<endl;
                os << "      [instructions:] " << mapElement.second->howToConsumeItem()<<endl;
                os << "    } "<<endl;
                os << "  }" <<endl;
            }
            os << '}' <<endl;

            return os;
        }
};