#pragma once

#include <string>

using namespace std;

/*
* The task is to create a ResposniblePerson class that acts a s aproxy for Person
* such that a person is allowed to drink if the age is at least 18, otherwise return
* "too young". Similarily, it is done for driving, but age treshold is 16. If drinking
* and driving, then return "dead".
*
* In order to do that, an interface must be implemented. The requirements of proxy state
* the proxied class and the proxy class must have identic interface. Therefore, all public
* methods, but ctor, of person are made virtual methods of the interface. The proxy class
* adds functionality when overriding the virtual methods and uses the encapsulated instance
* of proxied class to retrieve data from it.
*/

class PersonInterface
{
    public:
        virtual string drink() const  = 0;
        virtual string drive() const = 0;
        virtual string drink_and_drive() const  = 0;
        
        virtual int get_age() const  = 0;
        virtual void set_age(int age) = 0;
};

class Person: public PersonInterface
{
    private:
        friend class ResponsiblePerson;
        int age;
        
    public:
        Person() = default;
        Person(int age) : age(age) {};
        
        int get_age() const { return age; };
        void set_age(int age) { this->age=age; };
        
        string drink() const { return "drinking"; };
        string drive() const { return "driving"; };
        string drink_and_drive() const { return "driving while drunk"; };
};

class ResponsiblePerson : public PersonInterface
{
    public:
        ResponsiblePerson(const Person &person) : person(person) {}
        string drink() const override
        { 
            string result{"drinking"};
            
            if(person.get_age() < 18)
            {
                result = "too young";
            }
            
            return result; 
        };

        string drive() const override
        { 
            string result{"driving"};
            
            if(person.get_age() < 16)
            {
                result = "too young";
            }
            
            return result; 
        };

        string drink_and_drive() const override
        { 
            string result{"driving while drunk"};
            return "dead"; 
        };
        
        int get_age() const override { return person.age; };
        void set_age(int age) override { person.age=age; };

    private:
        Person person;
};