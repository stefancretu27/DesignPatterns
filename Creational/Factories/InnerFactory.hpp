#include <string>
#include <memory>

/*
* Implement static PersonFactory, as a Singleton private class, that creates Person instances
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

        //let the user know a factory is used and make it accessible as a Singleton
        static PersonFactory& GetFactory()
        {
            static PersonFactory factory{};
            
            return factory;
        };

    private:
        int mId;
        std::string mName;

        //instances are to be created exclusively via factory
        Person(int id, const std::string& name):mId{id}, mName{name}{};

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

                //creator method
                Person CreatePerson(const std::string& name)
                {
                    static int person_id{0};
                    
                    return Person{person_id++, name};
                }
        };
};
