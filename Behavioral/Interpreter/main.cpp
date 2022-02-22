#include "ExpressionProcessor.hpp"

/*
* Interpreter is a design pattern that deals with text interpretation. Mainly, it comprises of 2 steps
*   1) Lexing: the input text comes as a string for which certain characters are expected to be
* encountered. For example, a string denoting mathematical operations would contain numbers and characters
* symbolizing operations (+, -, *, /, =), eventually parenthesis. The expected characters can be listed,
* using an enumeration of types, which is then used to identify/map each character in the input text.
*   In such cases, the input big string is tokenized, which means that it is iterated over all its characters
* and each character is classified based on the types in the enumeration described above. Each character is 
* converted to a string, such that it offers an uniform representation regardless the type of the character.
* Therefore, the output of lexing is a vector of Token objects, with the Token class encapsulating the
* enumeration of types and the string to which each character is converted.
*
*   2) Parsing: the vector of Token objects outputted by the lexing steps acts as input for parsing.
* Concretely it is iterated over it and based on the type of each character, an appropriate action is taken.
* For example, when computing math operations and a number is encountered, it is marked as an operand for an
* operation. This step uses struct/classes which act as OOp models for tokens. Namely, these classes define
* APIs allowing each token to be used appropriately, based on its type (a number is treated as int or double,
* an operation character takes 2 operands and perform that operation, returning the result). 
*/

int main()
{
    ExpressionProcessor ep;
    
    double result = ep.Calculate("1+24-8+3-21");
    cout<<endl<<"result = "<<result<<endl;

    result = ep.Calculate("1+2+xy");
    cout<<endl<<"result = "<<result<<endl;

    ep.variables['x'] = 3;
    result = ep.Calculate("10-2-x");
    cout<<endl<<"result = "<<result<<endl;

    result = ep.Calculate("1");
    cout<<endl<<"result = "<<result<<endl;

    ep.variables['y'] = 8;
    result = ep.Calculate("-y");
    cout<<endl<<"result = "<<result<<endl;

    ep.variables['z'] = -8.2;
    result = ep.Calculate("z - 2 + 3.5 + 15.15");
    cout<<endl<<"result = "<<result<<endl;

    result = ep.Calculate("2/");
    cout<<endl<<"result = "<<result<<endl;

    result = ep.Calculate("23.56+1.2");
    cout<<endl<<"result = "<<result<<endl;

    result = ep.Calculate("1+3*2/1-2.5+4/2+1.5");
    cout<<endl<<"result = "<<result<<endl;

    result = ep.Calculate("1*2.1/4.2+3.9-4.5/3.0");
    cout<<endl<<"result = "<<result<<endl;

    result = ep.Calculate("1*2.0/(0.2/2+3.9*1)-4.5/3.0");
    cout<<endl<<"result = "<<result<<endl;

    result = ep.Calculate("2*(1+4/2)/(4.5-3.0)+4*(7.5-5)");
    cout<<endl<<"result = "<<result<<endl;

    result = ep.Calculate("2+((5+3*2-1)-(5*1-2.5)*2)");
    cout<<endl<<"result = "<<result<<endl;

    return 0;
}