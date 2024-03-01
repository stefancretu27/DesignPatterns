#include "TemplateMethod.hpp"

/*
* Likwise strategy, template method entails that an algorithm's implementation can be structured in 2 parts:
* a generic, high-level one, and a specific, low-level one.
*
* The difference lies in the fact that the business logic class is the high level part of the algorithm. It has
* some generic logic implemented which invokes specific logic. This specific logic is a pure virtual method of the
* abstract class, which is inherited and overriden by specific implementation classes. Lastly, these implementations
* are instantiated in order to be used for invoking the encapsulated behaviors.
*
*             _________________________________________________                    
*            |    TemplateMethodInterface                     |                         
*            |                                                |
*            | void GenericAlgorithm(){SpecificAlgorithm();}  |  
*            | virtual void SpecificAlgorithm() = 0;          |                        
*            |________________________________________________|                        
*                    ^                           ^                                 
*                    |                           |                              
*                    |                           |
*            ________|___________________      ______|_____________________
*            |  Implementation 1        |      | Implementation 2         |
*            |                          |      |                          |  
*            | void SpecificAlgorithm() |      | void SpecificAlgorithm() |     
*            | { Impl1(); }             |      | { Impl2();}              |   
*            |__________________________|      |__________________________| 
*
* Basically, it is an abstract class encapsulating a part of the behavior envisaged by the algorithm. Then, it can have
* several implementation classes, that inherit the generic behavior and implement the remaining specific logic.
*/

int main()
{
    return 0;
}
