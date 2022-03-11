#pragma once

#include <variant>
#include <string>
/*
* c++17 introduced std::variant which implements an union. Likewise an union, at a given time, the variant
* hold the value of one of its alternative types. Also, its allocated size equals the length of its biggest
* alternative type.
* Variant cannot hold references, void and arrays. It can hold pointers to any type.
*
* Additionally, c++17 introduced visit which implements the visditor pattern. It takes 2 inputs: the 1st one 
* is a visitor, which is a callable. Convetionally, it can eb a lambda or a functor. The second argument is
* a variant, or an object on which the visitor is applied
*/

#include <iostream>

using namespace std;

struct Functor
{
    void operator()(int arg)
    {
        cout<<arg*arg<<" ";
    }
    void operator()(double arg)
    {
        cout<<arg+arg<<" ";
    }
    void operator()(float arg)
    {
        cout<<arg+arg<<" ";
    }
    void operator()(char arg)
    {
        cout<<arg<<" ";
    }
    void operator()(string arg)
    {
        cout<<arg + " " + arg<<" ";
    }
};

