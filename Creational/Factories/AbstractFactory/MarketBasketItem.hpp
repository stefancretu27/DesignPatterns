#include <iostream>
using namespace std;

//create class hierarchy to be used with abstract factory

class MarketBasketItem
{
    public:
        virtual ~MarketBasketItem() = default;
        virtual string howToConsumeItem() = 0;

        double getWeight() const {return mWeight;};
        double getPrice() const {return mPrice;};

    //below attributes are common to all items => make this clas abstract
    protected:
        MarketBasketItem(double weight, double price):mWeight{weight}, mPrice{price}{};
        double mWeight;
        double mPrice;
};

class Fruit: public MarketBasketItem
{
    public:
        enum class Sweetness
        {
            SWEETLESS,
            LOW_SWEETNESS,
            AVERAGE_SWEETNESS,
            VERY_SWEET
        };

        Fruit(double weight, double price, Sweetness sweet_level = Sweetness::AVERAGE_SWEETNESS):MarketBasketItem{weight, price}, mSweetness{sweet_level}{};
        Fruit() = default;
        Fruit(const Fruit&) = default;
        Fruit& operator=(const Fruit&) = default;
        Fruit(Fruit&&) = default;
        Fruit& operator=(Fruit&&) = default;
        
        string howToConsumeItem() override
        {
            return move("wash it or peel it before eating. Cutting into pieces and mix with other fruit with make a delicious salad.");
        }

    private:
        Sweetness mSweetness;

};

class Vegetable: public MarketBasketItem
{
    public:
        explicit Vegetable(double weight, double price):MarketBasketItem{weight, price}{};
        Vegetable() = default;
        Vegetable(const Vegetable&) = default;
        Vegetable& operator=(const Vegetable&) = default;
        Vegetable(Vegetable&&) = default;
        Vegetable& operator=(Vegetable&&) = default;
        
        string howToConsumeItem() override
        {
            return move("wash it or peel it before eating. Preferably bake it in the oven or boil it together with your soup.");
        }
};

class Dairy: public MarketBasketItem
{
    public:
        enum class LactoseLevel
        {
            LACTOSELESS,
            LOW_LACTOSE,
            MEDIUM_LACTOSE_LEVEL,
            HIGH_LACTOSE_LEVEL
        };

        Dairy(double weight, double price, LactoseLevel lactose_level = LactoseLevel::MEDIUM_LACTOSE_LEVEL):MarketBasketItem{weight, price}, mLactoseLevel{lactose_level}{};
        Dairy() = default;
        Dairy(const Dairy&) = default;
        Dairy& operator=(const Dairy&) = default;
        Dairy(Dairy&&) = default;
        Dairy& operator=(Dairy&&) = default;
        
        string howToConsumeItem() override
        {
            return move("if its milk or yoghurt, drink it, but not too cold. For any cheese type, it goes well with pasta.");
        }

    private:
        LactoseLevel mLactoseLevel;
}; 