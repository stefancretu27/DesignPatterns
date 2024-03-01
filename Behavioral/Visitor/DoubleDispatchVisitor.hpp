#pragma once

#include <string>
#include <sstream>
using namespace std;

/*
* Purpose:
*    - Encapsulates an operation executed on an object of class hierarchy type
*    - Enables to define new operations without changing the object hierarchy, but changes the interface,
*      as a new Accept method is added to the class hierarchy
*
* Use Case:
*    - Operations should be performed on an object hierarchy
*    - The object hierarchy is stable, but the operations change frequently
*    - The class' hierarchy newly added method Accept is used to inject dependency (*this) into Visitor hierarchy,
*    used by the Visitor's encapsulated operation to access the class' interface
*
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
*
*    ________________________________________                            __________________________________________    
*    |            VisitorInterface          |                            |                Base                    |        
*    |                                      |            Uses            |                                        |
*    |virtual void Visit(Base&) = 0;        |<---------------------------| void Accept(VisitorInterface& visitor) |
*    |virtual void Visit(Derived&) = 0;     |                            |  {                                     |    
*    |virtual void Visit(MostDerived&) = 0; |                            |     visitor.Visit(*this);}             |
*    |______________________________________|                            |________________________________________|
*                    ^                                                                      ^  
*                    |                                                                      |  
*                    | Inheritance                                                          | Inheritance         
*                    |                                                                      |  
*    ________________|_______________________________                     __________________|______________________   
*    |            VisitorImpl                       |                     |                Derived                 |
*    |                                              |                     |                                        |
*    |virtual void Visit(Base& b) override          |                     | void Accept(VisitorInterface& visitor) |
*    |{ b.GetValue(); }                             |                     |    {                                   |
*    |virtual void Visit(Derived& d) override       |                     |        visitor.Visit(*this);}          |     
*    |{   d.GetValue1();                            |                     |________________________________________|
*    |    d.GetValue2(); }                          |                                       ^ 
*    |virtual void Visit(MostDerived& md) override  |                                       | 
*    |{   md.GetValue1();                           |                                       |  
*    |    md.GetValue2();                           |                                       |   
*    |    md.GetValue3(); }                         |                     __________________|______________________ 
*    |______________________________________________|                     |            MostDerived                 | 
*                                                                         |                                        |
*                                                                         | void Accept(VisitorInterface& visitor) |
*                                                                         |    {                                   |
*                                                                         |        visitor.Visit(*this);}          |
*                                                                         |________________________________________|
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
