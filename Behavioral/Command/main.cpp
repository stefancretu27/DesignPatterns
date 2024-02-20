#include "Command.hpp"

/*
* Command is a behavioral design pattern that implies the creation os a class which represents a model for certain operations
* that can be done on other objects (instances of another class or more classes). The reason for using a command is that it 
* keeps track of the performed operations on some given objects, such that each operations can be undone afterwords. On the 
* other hand, there is no common way to record if usual C++ statements took place or not.
*
* Implementation-wise, the command class encapsulates definition of the operations it is able to do (as enum) and, eventually,
* a flag that marks whther the operation succeeded or not. Additionally, it can hold state, as some data required by each
* operation can be stored internally (as in amount of money involved in a transaction). Then, other classes can use this class
* to process commands, taking appropriate decision for each command code, eventually storing state and using the value associated
* with a certain command. Eventually, the command class/struct can be use via composition.
*            ________________________________                        _____________________________________________
*            |        struct Command -       |                       |             User class                    |
*            |                               |                       |                                           |  
*            | enum class CommandsCodes      |    Uses               | void ProcessCommand(Command& cmd)         |
*            | { CMD1,                       |<----------------------| {                                         |
*            |   CMD2,                       |                       |   switch(cmd)                             |
*            |   CMD3} cmdsCodes;            |                       |   { case CommandsCodes::CMD1:             |  
*            | bool flagOperationSuccessful; |                       |      cmd.flagOperationSuccessful==true;   |  
*            | S valueUsedByOperation;       |                       |       break; }                            |   
*            | T state;                      |                       |___________________________________________| 
*            |_______________________________|
*
*
* In some cases, the command class can store a reference member to class it operates on. As an alternative, a command instance
* can be used by the class it operates on, either as a member or as method argument. It depends how it is desired to design
* the business logic's control flow.
*
* There should be distinguished between a command and a query:
*  - command: it causes the change of the object, but does not have a return value (much like a set operation), causing a 
* change in the system
*  - query: represents an interogation which has a return value, but which does not change the system (like a get operation) 
*/
int main()
{
    vector<Command> commands {Command(Command::deposit, 100), Command(Command::withdraw, 102), Command(Command::withdraw, 2), Command(Command::deposit, 15)};
    Account account{};
    
    for(auto& cmd : commands)
        account.process(cmd);
        
    cout << account;

    //rollBack should happens in reverse order. Avoid reverseing tyhe first operation
    for(auto it = commands.rbegin(), end = commands.rend()-1; it!=end; ++it)
        account.rollBack(*it);

    cout <<account;

    return 0;
}
