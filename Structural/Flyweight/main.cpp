#include "TextFormating.hpp"
#include "Flyweight.hpp"
/*
* Flyweight is a design pattern tha aims at optimizing the structure of a class/program
* by avoiding redundancy. Concretely, it is a space optimization technique which aims at
* using less memory by storing externally (in a data base, or other class), the data
* associated with similar objects. 
*
* This is useful when it is expected that some objects can have similar values. Instead
* of storing th same value multiple times, it is encoded (in a map, for instance) and
* the value of the object is replaced with an index indicating to the initial value,
* that ends up being stored once.
*/


int main()
{
    Sentence sentence {"hello world"};
    sentence[1].capitalize = true;
    
    cout<<sentence[0].capitalize<<" "<<sentence[1].capitalize<<endl;
    cout<<sentence.str()<<endl;

    Sentence sentence2 {"What a wonderful world sang Louis Armstrong"};
    sentence2[2].capitalize = sentence2[5].capitalize = true;
    cout<<sentence2.str()<<endl;

    //
    NameStorage::getInstance().addName("Gogu");
    NameStorage::getInstance().addName("Doru");
    NameStorage::getInstance().addName("Iulia");
    NameStorage::getInstance().addName("Gogu");
    NameStorage::getInstance().addName("Doru");
    NameStorage::getInstance().addName("Iulia");
    cout << NameStorage::getInstance() <<endl;
    
    return 0;
}