#include "BrokerChain.hpp"

#include <iostream>

/*
* Chain of responsibility represents a chain of components that process a command or query, allowing for terminating 
* the processing with either a successful result or not. A common implementation example is linked list which uses
* pointer to self type to indicate to next/prev nodes. 
*
* A particular implementation is broker chain that makes use of a centralized list of pointers to the type it queries,
* that can be encapsulated in a separate structure (hence the idea of centralized list). Then, another structure can be
* used to model the query, as it defines the set of possible operations and yelds the result.
* The idea here is that in order to retrieve value afferent to an object, all objects in list are interogated and they
* contribute to producing the final result, as all are considered "responsible". Hence, the query object's result member
* acts as a global variable in this case. 
*
* The broker instance is kept as reference member in the queried class and used each time a value that depends on other
* instances is requested. Such requests, implemented as get operations, iterate over the centralzied list, accessed via 
* the broker instance and query each instance. 
*
* The query is implemented by the query class and encapsulates business logic. It can be a private method and oftentimes
* it differentiates between the caller object and callee object by taking as argument *this (which represents the callee)
* Then, its implementation uses syntax such as: if(source == this) or if(dest != this),where this represents the caller.
*
* That said, this pattern pays off when the existence of multiple objects of similar type (derived from the same interface,
* at least) influence each other's members values (eg: with each new goblin in game, every goblin gets +1 defense).
*/

int main()
{
    Game game{};
    Goblin goblin{game};

    game.creatures.push_back(&goblin);

    GoblinKing gk1{game};

    game.creatures.push_back(&gk1);

    cout<<gk1.get_attack()<<" "<<gk1.get_defense()<<endl;
    cout<<goblin.get_attack()<<" "<<goblin.get_defense()<<endl;

    return 0;
}