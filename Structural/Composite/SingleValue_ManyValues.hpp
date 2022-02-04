#pragma once

#include <iostream>
#include <utility>
#include <tuple>
#include <vector>
#include <string>
using namespace std;

/*
* There are given 2 classes: SingleValue that wraps over an int value and ManyValues that encapsualtes a vector of int values.
* The ManyValues class also encapsulates an add method which takes an int as input.
* Also, it is given the signature of function sum, which takes a vector of pointers to a generic type "ContainsIntegers"
* and aims at computing the sum of all elements in this vector. That said, the input vector contains pointers to SingleValue
* and ManyValues elements simultaneously (as in vector of vectors).
*
* The implementation of composite pattern in this case entails defining the common interface "ContainsIntegers". Here, 2
* possible solutions are proposed. The first one defines a method getSum() which computes the sum of all elemnts in the 
* underlying vector, when it is overriden by ManyValues or returns the wrapped int value when overriden by SingleValue.
* Then, the sum function just iterates over the input vector of pointers and calls the virtual method getSum().
*
* The second approach overloads begin() and end() methods in the interface class. The each derived class overrides
* the implementation adequately. Then, the sum2 function iterates over the input vector of pointers, then treats
* each items as a possible collection, so it used range based for loop which, under the hood, calls the virtual methods
* begin() and end(), that are overriden.
*/

struct ContainsIntegers
{
    //1st solution
    virtual int getSum() = 0;
    
    //2nd solution
    virtual vector<int>::iterator begin() = 0;
    virtual vector<int>::iterator end() = 0;

    //not necessarily useful
    virtual size_t getSize() = 0;
};

struct SingleValue: public ContainsIntegers
{
    int mValue;
    
    explicit SingleValue(const int value):mValue{value}{};
    explicit SingleValue(int* const value):mValue{*value}{};
    
    int convertValue(SingleValue* const inst){return inst->mValue;};
    
    //1st solution
    int getSum() override{return mValue;};
    
    //2nd solution
    size_t getSize() override {return 1;};
    vector<int>::iterator begin() override {return static_cast<vector<int>::iterator>(&mValue);};
    vector<int>::iterator end() override 
    {
        auto it = static_cast<vector<int>::iterator>(&mValue); 
        return ++it;
    };
};

struct ManyValues: public ContainsIntegers
{
    vector<int> mValues;
    
    ManyValues() = default;
    ManyValues(const vector<int>& vi):mValues{vi}{};
    
    vector<int>* convertValue(ManyValues* const inst){return &inst->mValues;};
    
    void add(const int value)
    {
        mValues.emplace_back(value);
    }
    
    int getSum()  override
    {
        int sum{0};
        for(auto&& integer : mValues)
            sum+=integer;
        
        return sum;
    };
    size_t getSize() override {return mValues.size();};
    
    vector<int>::iterator begin() override {return mValues.begin();};
    vector<int>::iterator end() override {return mValues.end();};
};

int sum(const vector<ContainsIntegers*> items)
{
    int result{0};
    
    for(ContainsIntegers* item : items)
    {
        result += item->getSum();
    }
    
    return result;
}

int sum2(const vector<ContainsIntegers*> items)
{
    int result{0};
    
    //items can contain pointer to either SingleValue or ManyValues
    for(ContainsIntegers* item : items)
    {
        //*item is an instance of ManyValues. As it overloaded begin() and end(), it can be looped over
        for(int elem : *item)
        {
            result += elem;
        }
    }
    
    return result;
}
