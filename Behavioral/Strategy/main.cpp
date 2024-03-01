#include "Strategy.hpp"

/*
* An algorithm can be implemented in phases: the generic, high-level part which is encapsulated in an interface,
* and the specific, low level part that is encapsulated in classes implementing the interface. There can be
* more implementations, as the algorithm can come in several flavours
*
* Then, a business logic class that uses the algorithm, encapsulates a ptr/ref to the interface, which can be 
* set at runtime to the desired implementation type. This is called dynamic strategy (or policy). Basically, it
* is an interface whith at least one implementation, which is used by another (business logic) class.
*
*            _____________________________________                          _____________________________________  
*            |          StrategyInterface         |                         |            User class              |   
*            |                                    |<------------------------|                                    |    
*            | virtual void CoreAlgorithm() = 0;  |                         | StrategyInterface& strategyAlgo;   |
*            |____________________________________|                         |                                    |
*                    ^                           ^                          | strategyAlgo.CoreAlgorithm();      |     
*                    |                           |                          |____________________________________|   
*                    |                           |
*            ________|_______________      ______|________________
*            |  Implementation 1    |      | Implementation 2     |
*            |                      |      |                      |  
*            | void CoreAlgorithm() |      | void CoreAlgorithm() |     
*            | { Impl1(); }         |      | { Impl2();}          |   
*            |______________________|      |______________________|  
*
* On the other hand, static strategy means the business class does not have the ability to customize which behavior
* it uses. That said, it is tied to one of the implementation, either being composed of such an instance or by being
* implementated as a template class whose template type parameter is an instance of specific algorithm implementation.
*
* Then, once the strategy is set in one of the 2 manners, its behavior becomes callable within the business logic class.
*/

int main()
{
    OrdinaryDiscriminantStrategy ordinary{};
    RealDiscriminantStrategy real{};
    
    QuadraticEquationSolver qsolver{ordinary};
    
    auto result = qsolver.solve(1 , 1 , 2);
    
    cout<<get<0>(result)<<get<1>(result)<<endl;
    
    QuadraticEquationSolver qsolver2{real};
    result = qsolver2.solve(1 , 1 , 2);
    
    cout<<get<0>(result)<<get<1>(result)<<endl;

    return 0;
}
