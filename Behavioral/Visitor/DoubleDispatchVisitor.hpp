#pragma once

#include <string>
#include <sstream>
using namespace std;

/*
* Double dispatch visitor is the classical visitor implementation. It involves creating an interface for
* the visitor, which declares visit methods that take input a ptr/ref to each type in the class hierarchy.
* In order for this to work, the classes in the hierarchy must be forward declared. Then, an implementation
* for this interface will define a certain behavior for these overloads.
* Additionally, the class hierarchy's interface declares a virtual method that accepts a visit. It takes as
* argument a ptr/ref to visitor interface. Then visitor implementation can call these accept methods. This can
* lead to a sort of recursive call: 
*   VisitorImpl.visit(Type3)->breaks down Type3 into Type2 and Type1 => call type2.accept() and type1.accept()
*   then, these accept methods call visit on their own kind, where the control flow can reach the end with
* a last call to visit which has nothing to accept
*/


//Step 1: define interface for visitor and forward declare class hierarchy implementations
struct Value;
struct AdditionExpression;
struct MultiplicationExpression;

struct ExpressionVisitor
{
    //declare virtual method overloads for each type in class hierarchy
    virtual void visit(Value&) = 0;
    virtual void visit(AdditionExpression&) = 0;
    virtual void visit(MultiplicationExpression&) = 0;
};

// Step 2: define interface of the class hierarchy that encapsulates the accept method.
// The method simply is implemented by each class in hierarchy so they pass this pointer, 
// in order to identify the type of the implementation
struct Expression
{
    virtual void accept(ExpressionVisitor& ev) = 0;
};

//Step 3: define class hierarchy implementations
struct Value : Expression
{
    int value;
    
    Value(int value) : value(value) {};
    
    void accept(ExpressionVisitor& ev) override
    {
        //simply pass this so the corresponding visit method is called
        // Each call to visit breaks down the expression which may lead to a recursive call to this accept method
        // or to the other accept methods in class hierarchy
        ev.visit(*this);
    }
};

struct AdditionExpression : Expression
{
    Expression &lhs, &rhs;
    
    AdditionExpression(Expression &lhs, Expression &rhs) : lhs(lhs), rhs(rhs) {};
    
    void accept(ExpressionVisitor& ev) override
    {
        //simply pass this so the corresponding visit method is called
        // Each call to visit breaks down the expression which may lead to a recursive call to this accept method
        // or to the other accept methods in class hierarchy
        ev.visit(*this);
    }
};

struct MultiplicationExpression : Expression
{
    Expression &lhs, &rhs;
    
    MultiplicationExpression(Expression &lhs, Expression &rhs)
        : lhs(lhs), rhs(rhs) {};
    
    void accept(ExpressionVisitor& ev) override
    {
        // simply pass this so the corresponding visit method is called
        // Each call to visit breaks down the expression which may lead to a recursive call to this accept method
        // or to the other accept methods in class hierarchy
        ev.visit(*this);
    }
};

//Step 4: implement visitor interface
struct ExpressionPrinter : ExpressionVisitor
{
    stringstream ss;
    
    void visit(Value& valExpr) override
    {
        // when accepting a accept for Value type, just add its value to final result such that 
        // the recursive callback flow ends at this point
        ss << to_string(valExpr.value);
    };
    
    virtual void visit(AdditionExpression& addExpr) override
    {
        // when accepting addition expression, add characters typical to addition expression and for each member perform a further accept
        // Its memebrs can be value, addition or multiplication expressions, hence the need for a further call which describes
        // a sort of recursive callback flow that ends when lhs or rhs are values (as expressions are further decomposed at each call)
        ss << '(';
        addExpr.lhs.accept(*this);
        ss << '+';
        addExpr.rhs.accept(*this);
        ss << ')';
    };
    
    virtual void visit(MultiplicationExpression& mulExpr) override
    {
        // when accepting multiplication expression, add characters typical to multiplication expression and for each member perform a further accept
        // Its memebrs can be value, multiplication or multiplication expressions, hence the need for a further call which describes
        // a sort of recursive callback flow that ends when lhs or rhs are values (as expressions are further decomposed at each call)
        mulExpr.lhs.accept(*this);
        ss << '*';
        mulExpr.rhs.accept(*this);
    };

    string str() const { return ss.str(); };
};