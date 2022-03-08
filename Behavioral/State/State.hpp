#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
using namespace std;

/*
* Given the class CombinationLock which has a privat vector member, that is initialized in c-tor with the
* correct passphrase(digits sequence) for unlocking. The inital state is LOCKED. When a digits is entered, 
* the status is updated to show that digit. If the digits sequence does not match the combination, status
* shows ERROR, otherwise, status is changed to OPEN.
*/

class CombinationLock
{
    vector<int> combination;
public:
    string status;

    CombinationLock(const vector<int> &combination) : combination(combination) 
    {
        status = "LOCKED";  
    }

    void enter_digit(int digit)
    {
        static vector<int> enteredDigits;
        
        if(enteredDigits.size() < combination.size())
        {
            enteredDigits.push_back(digit);
            
            stringstream ss;
            copy( enteredDigits.begin(), enteredDigits.end(), ostream_iterator<int>(ss, ""));
            status = ss.str();
        }
        
        if(enteredDigits.size() == combination.size())
        {
            if(enteredDigits == combination)
            {
                status = "OPEN";
                enteredDigits.clear();
            }
            else
            {
                status = "ERROR";
                enteredDigits.clear();
            }
        }
    }
};