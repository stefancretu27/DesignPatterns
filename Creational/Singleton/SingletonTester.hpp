#pragma once

/*
* is_singleton takes as input a factory that creates instance of a generic class T.
* It is supposed to test if the class T is singleton or not.
*/

#include <functional>
using namespace std;

struct SingletonTester
{
  template <typename T>
  static bool is_singleton(function<T*()> factory)
  {
    T* inst1 = factory();
    T* inst2 = factory();
    
    if(inst1==inst2)
        return true;
        
    return false;
  }
};