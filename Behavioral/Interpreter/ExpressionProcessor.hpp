#pragma once


#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#include <cctype>
#include <memory>
#include <limits>

#include "LexingToken.hpp"

/*
* Parsing: turn tokens into OOP elements => define classes/struct to model them
*/

/*
* 2.1 Define a struct that models an element in an expression. 
* The element can be an integer, variable that evaluates to integer or an operation. both evaluating to an integer
*/
struct Element
{
    virtual ~Element() = default;
    virtual double eval() const = 0;
};

/* 
* An operation deals with operands. In this case, operands are considered to be floating point type
* but this includes integers as well. Thus, this class is the model for variables and for numbers
*/
struct FloatingPointNumber: public Element
{
    double value{};
    
    FloatingPointNumber() = default;
    explicit FloatingPointNumber(const double val):value{val}{};
    
    double eval() const override {return value;};
};

/* 
* The operands are involved in operations. Thus an operation has 2 operands and one operator.
*
* The operator's type defines the type of the operation. Hence, as the vector of tokens obtained
* after lexing is iterated over, when an operator is encountered, the operation's type is set
* to the corresponding type, defined by the encapsulated enumeration.
*
* This class models the ides of operators, acting as model for operations they define, together
* with the associated operands.
*/
struct Operation: public Element
{
    FloatingPointNumber lhs, rhs;
    
    enum OperationType
    {
        none,
        add, 
        sub,
        mul,
        div
    } operationType;
    
    Operation():operationType{none}{};
    
    double eval() const override
    {
        double result{};

        if(operationType == add)
        {
            result = lhs.eval() + rhs.eval();
        }
        if(operationType == sub)
        {
            result = lhs.eval() - rhs.eval();
        }
        if(operationType == mul)
        {
            result = lhs.eval() * rhs.eval();
        }
        if(operationType == div)
        {
            if(abs(rhs.eval() - 0.0f) >= 0.000001f)
            {
                result = lhs.eval() / rhs.eval();
            }
            else
            {
                result = numeric_limits<double>::min();
            }
        }

        return result;
    }
    
};

class ExpressionProcessor
{
    private:
    double getValueFromNumericToken(Token tk);
    vector<Token> computeParenthesis(vector<Token>& tokens);
    vector<Token> computeMultiplicationsAndDivisions(const vector<Token>& tokens);
    double computeAdditionsAndSubstractions(const vector<Token>& tokens);

    public:
    map<char, double> variables;                         
    double Calculate(const string& expression);
};