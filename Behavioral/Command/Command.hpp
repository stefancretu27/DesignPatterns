#pragma once

#include <iostream>
#include <vector>
using namespace std;

/*
* There are given the struct Command which models a command for a bank account with 2 possible operations: deposit and withdraw.
* Additionally, it has a status flag that corresponds to each command signaling the operation occured successfully or not.
* Also, the struct Account has a balance initialized to 0 an an empty process method.
*
* It is asked to implement the process method such that it allows to withdraw money only if the balance suffices.
*
* In addition to this requirement, a rollBack methods was added that reverses the operations without changing the status flag.
*/

struct Command
{
    enum Action { deposit, withdraw } action;
    int amount{0};
    bool success{false};
    
    Command(Action act, int sum):action{act}, amount{sum}{};
};

struct Account
{
  int balance{0};
  
  Account() = default;
  Account(int sum):balance(sum){};

  void process(Command& cmd)
  {
    switch(cmd.action)
    {
        case Command::deposit:
        {
            balance += cmd.amount;
            cmd.success = true;
            break;
        }
        case Command::withdraw:
        {
            if(cmd.amount <= balance)
            {
                balance -= cmd.amount;
                cmd.success = true;
            }
            else
            {
                cmd.success = false;
            }
            break;
        }
    }
  };

  void rollBack(Command& cmd)
  {
    switch(cmd.action)
    {
        case Command::deposit:
        {
            balance -= cmd.amount;
            break;
        }
        case Command::withdraw:
        {
            if(cmd.success)
            {
                balance += cmd.amount;
            }
            break;
        }
    }
  };
  
  friend ostream& operator<<(ostream& os, const Account& acc)
  {
      os<< acc.balance <<endl;
      
      return os;
  }
};