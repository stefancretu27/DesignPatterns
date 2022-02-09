#pragma once

#include <string>
#include <sstream>
#include <type_traits>
using namespace std;

//Interface  implemented only by decorated class
struct FlowerInterface
{
    virtual string str() = 0;
};

//decorated class
struct RoseImpl : public FlowerInterface
{
    unsigned int mRoseCount{};

    RoseImpl(unsigned count):mRoseCount{count}{};
    RoseImpl(const RoseImpl& obj):mRoseCount{obj.mRoseCount}{};

    string str() override 
    {
        return to_string(mRoseCount) + " roses";
    }

    string methodOfRoseImpl()
    {
        return "This method is proper to RoseImpl and is not accessible via FlowerInterface";
    }
};

//decorated class
struct WaterLilyImpl : public FlowerInterface
{
    unsigned int mWaterLilyCount{};

    WaterLilyImpl(unsigned count):mWaterLilyCount{count}{};
    WaterLilyImpl(const WaterLilyImpl& obj):mWaterLilyCount{obj.mWaterLilyCount}{};

    string str() override 
    {
        return to_string(mWaterLilyCount) + " water lilies";
    }

    string methodOfWaterLilyImpl()
    {
        return "This method is proper to WaterLilyImpl and is not accessible via FlowerInterface";
    }
};

/*
* Decorator class: template class that inherits from its template type 
* such that it can call methods that are proper to T, not only those
* virtual methods defined by the interface. Nonetheless, T should be a
* implementation of the interface.
*/
template<class T>
struct RedFlowerDecorator : public T
{
    static_assert(is_base_of<FlowerInterface, T>::value, "TYpe T should be an implementation of Flower interface");

    string color{"red"};
    
    //use perfect forwarding to pass the args from the decorator's ctor to the decorated class ctor
    template<class...Args>
    RedFlowerDecorator(Args...args):T{forward<Args>(args)...}{};
    
    string str() override 
    {
        //build a stream of strings from the decorated member, by accessing the methods of the class
        // that is inherited from
        istringstream iss(T::str());
        //the object that is decorated
        string result{T::str()};
        //data used to parse the input
        string word{};
        bool hasAlreadyThisColor{false};
        bool hasAlreadyAColor{false};
        
        while(iss >> word)
        {
            //if this color already exists
            if(word == color)
            {
                hasAlreadyThisColor = true;
                continue;
            }
            
            //if any color exists
            if( word == "that")
            {
                hasAlreadyAColor = true;
                continue;
            }
        }
        
        if(hasAlreadyAColor && !hasAlreadyThisColor)
            result += " and " + color;
            
        if(!hasAlreadyAColor && !hasAlreadyThisColor)
        {
            result += " that are " + color;
        }
        
        return result;
    }

};

/*
* Decorator class: template class that inherits from its template type 
* such that it can call methods that are proper to T, not only those
* virtual methods defined by the interface. Nonetheless, T should be a
* implementation of the interface.
*/
template<class T>
struct BlueFlowerDecorator : public T
{

    static_assert(is_base_of<FlowerInterface, T>::value, "TYpe T should be an implementation of Flower interface");

    string color{"blue"};
    
    //use perfect forwarding to pass the args from the decorator's ctor to the decorated class ctor
    template<class...Args>
    BlueFlowerDecorator(Args...args):T{forward<Args>(args)...}{};
    
    string str() override 
    {
        //build a stream of strings from the decorated member, by accessing the methods of the class
        // that is inherited from
        istringstream iss(T::str());
        //the object that is decorated
        string result{T::str()};
        //data used to parse the input
        string word{};
        bool hasAlreadyThisColor{false};
        bool hasAlreadyAColor{false};
        
        while(iss >> word)
        {
            //if thsi color already exists
            if(word == color)
            {
                hasAlreadyThisColor = true;
                continue;
            }
            
            if( word == "that")
            {
                hasAlreadyAColor = true;
                continue;
            }
        }
        
        if(hasAlreadyAColor && !hasAlreadyThisColor)
            result += " and " + color;
            
        if(!hasAlreadyAColor && !hasAlreadyThisColor)
        {
            result += " that is " + color;
        }
        
        return result;
    }

};