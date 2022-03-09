#pragma once

#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include <limits>
using namespace std;

/*
* Given virtual struct DiscriminantStrategy and its 2 implementations, it is asked to implement the virtual method
* such that it computes the discriminant of a quadratic equation (delta = b^2-4ac). For the Real implementation, if
* the discriminant is negative return NaN. Then, in the business logic class it is asked to compute the equation
* solutions.
*/

struct DiscriminantStrategy
{
    virtual double calculate_discriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) override
    {
        return b*b - 4*a*c;
    }
};

struct RealDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) override
    {
        double delta = b*b - 4*a*c;
        
        return (delta <0) ? std::numeric_limits<double>::quiet_NaN() : delta;
    }
};

class QuadraticEquationSolver
{
    DiscriminantStrategy& strategy;
public:
    QuadraticEquationSolver(DiscriminantStrategy &strategy) : strategy(strategy) {}

    tuple<complex<double>, complex<double>> solve(double a, double b, double c)
    {
        double delta = strategy.calculate_discriminant(a, b, c);
        tuple<complex<double>, complex<double>> result{{delta, delta}, {delta, delta}};
        
        if (delta < 0)
        {
            cout<<" if"<<endl;
            complex<double> x1{-b/(2*a), sqrt(abs(delta))/(2*a)};
            complex<double> x2{-b/(2*a), -sqrt(abs(delta))/(2*a)};
            
            result = make_tuple(x1, x2);
        }
        else if(delta >= 0)
        {
            cout<<"else if"<<endl;
            result = make_tuple((-b + sqrt(delta))/(2*a), (-b - sqrt(delta))/(2*a));
        }
        
        return result;
    }
};