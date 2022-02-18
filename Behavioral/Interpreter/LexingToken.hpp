
#pragma once

#include <functional>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

/*
* 1. Lexing
*/

/*
* 1.1 Define a struct that models an element in the input string. 
* Its consists of 2 data members: a string where the tokenezied text will be stored and
* an enum whose enumerators define the token's tpe. As the possible elements are +, -, *, /, 
* double or single character variable, the enumerators are explicitly named accordingly.
*/

struct Token
{
    enum Type
    {
        add, 
        substract, 
        multiply, 
        divide, 
        variable, 
        floatingPointValue
    } type;
    string tokenizedItem;
    
    //construct a token as an association of its string representation and its type
    explicit Token(const string& inputToken, Type type):tokenizedItem{inputToken},
                                                    type{type}
    {};
    
    friend ostream& operator<<(ostream& os, const Token& tok)
    {
        os <<" "<< tok.tokenizedItem <<" ";
        
        return os;
    };

};

struct LexingProcessor
{
    /*
    * 1.2 The second and last part of lexing uses the Token struct definition to split the
    * inout string into multiple tokens. Hence the out put is a vector of tokens.
    * The choice here is to encapsulate this business logic into a method of the given struct.
    */
    vector<Token> lexingInputText(const string& inputText);

    private:
    /*
    * Helper method that check if a character is number or alphabetical one
    */
    bool isDigitOrIsAlpha(const char inputCharFromText, const Token::Type tokenType);
    /*
    * Method that only processes characters that are either numbers or alphabetical characters that identify variables.
    * Such entities need separate lexing as it is more complex because they might be compound, such as: 396.89 or xyzt, so
    * they require buffering of each next character of similar type 
    */
    void processNumbersAndVariables(const string& inputText, size_t& idx, const Token::Type tokenType, vector<Token>& result);
};

