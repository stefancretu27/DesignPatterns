#include <string>
#include <memory>
#include <iostream>
using namespace std;


struct Address
{
    string town;
    string street;
    int streetNo;

    Address() = default;
    Address(const string& t, const string& str, int strNo):town{t}, street{str}, streetNo{strNo}{};
    Address(const Address& addr):town{addr.town}, street{addr.street}, streetNo{addr.streetNo}{};

    friend ostream& operator<<(ostream& os, const Address& addr )
    {
        os << "Town: "<<addr.town << " Street: " <<addr.street << " StreetNo: " <<addr.streetNo <<endl;
        return os;
    }
};

/*
* Implement non static Personfactory that creates Person instances
* with the id starting from 0 and incremented with each newly created instance =>customization upon creation
*/
class Person
{
    private:
        //forward declaration of factory class
        class PersonFactory;

    public:
        //class interface: rule of zero
        Person() = default;
        ~Person() = default;
        Person(const Person&) = default;
        Person& operator=(const Person&) = default;
        Person(Person&&) = default;
        Person& operator=(Person&&) = default;

        static const unique_ptr<PersonFactory>& getFactory() 
        {
            //let the user know a factory is used and make it accessible
            static const unique_ptr<PersonFactory> mFactory;

            return mFactory;
        };

        friend ostream& operator<<(ostream& os, const Person& pers)
        {
            os << "ID: " << pers.mId << " name: " << pers.mName << " address: "<< pers.mAddress<<endl;

            return os;
        }

    private:
        int mId;
        string mName;
        Address mAddress;

        //instances are to be created exclusively via factory
        Person(int id, const string& name, const Address& address):mId{id}, mName{name}, mAddress{address}{};

        //don't let the outside world know what kind of factory is used
        class PersonFactory
        {
            public:
                //class interface
                PersonFactory() = default;
                ~PersonFactory() = default;
                PersonFactory(const PersonFactory&) = delete;
                PersonFactory& operator=(const PersonFactory&) = delete;
                PersonFactory(PersonFactory&&) = delete;
                PersonFactory& operator=(PersonFactory&&) = delete;

                /*
                * This method is aimed at being called when creating the first person living at a given address
                * Thus, the id is zero and the address is specified
                */
                Person createPersonWithAddress(const string& name, const string& t, const string& str, int strNo)
                {
                    person_id = 0;
                    //let's suppose each newly crated person lives at the same address, as in enummerate all persons living in the house
                    prototype = Address{t, str, strNo};
                    
                    return Person{person_id++, name, prototype};
                }

                /*
                * This method is aimed at being called when creating the other persons living at the same address
                * Thus, the address is reused and the counter is further incremented
                */
                Person createPersonUsingPrototype(const string& name)
                {
                    return Person{person_id++, name, prototype};
                }

            private:
                static Address prototype;
                static int person_id;
        };
};
