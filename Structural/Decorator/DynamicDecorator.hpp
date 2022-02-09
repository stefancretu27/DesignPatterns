# pragma once

#include <string>
#include <sstream>

using namespace std;

/*
* Given the common interface Flower and its standard implementation Rose
* it is required to implement dynamic decorators RedFlower and BlueFlower
* such that it add a color one time, regardless of how many time a decorators is composed of itself:
* RedFlower(Rose).str() -> A rose that is red
* RedFlower(RedFlower(Rose)).str() -> A rose that is red 
* BlueFlower(RedFlower(Rose)).str() -> A rose that is red and blue
* RedFlower(BlueFlower((Rose)).str() -> A rose that is blue and red
* RedFlower(RedFlower(BlueFlower((Rose))).str() -> A rose that is blue and red
*/
//common interface for decorated class and its decorators
struct Flower
{
    virtual string str() = 0;
};

//decorated class
struct Rose : public Flower
{
    string str() override 
    {
        return "A rose";
    }
};

/*
* Decorator class: implements the same interface as the decorated class + 
* holds a reference to decorated class, set via c-tor => alows creation
* of Decorator(Decorator)
*/
struct RedFlower : public Flower
{
    string color{"red"};
    Flower& mFlower;
    
    RedFlower(Flower& flower):mFlower{flower}{};
    
    string str() override 
    {
        //build a stream of strings from the decorated member
        istringstream iss(mFlower.str());
        //the object that is decorated
        string result{mFlower.str()};
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
            result += " that is " + color;
        }
        
        return result;
    }

};

/*
* Decorator class: implements the same interface as the decorated class + 
* holds a reference to decorated class, set via c-tor => alows creation
* of Decorator(Decorator)
*/
struct BlueFlower : public Flower
{
    string color{"blue"};
    Flower& mFlower;
    
    BlueFlower(Flower& flower):mFlower{flower}{};
    
    string str() override 
    {
        //build a stream of strings from the decorated member
        istringstream iss(mFlower.str());
        //the object that is decorated
        string result{mFlower.str()};
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

