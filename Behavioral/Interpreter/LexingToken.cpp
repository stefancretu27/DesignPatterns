#include "LexingToken.hpp"

bool LexingProcessor::isDigitOrIsAlpha(const char inputCharFromText, const Token::Type tokenType)
{
    bool result{false};

    if(tokenType == Token::floatingPointValue)
    {
        result = isdigit(inputCharFromText);
    }
    else if(tokenType == Token::variable)
    {
        result = isalpha(inputCharFromText);
    }

    return result;
}

void LexingProcessor::processNumbersAndVariables(const string& inputText, size_t& idx, const Token::Type tokenType, vector<Token>& result)
{
    // in case a number/char is encountered, add it to a stringstream, then check if it is followed by characters of the same type 
    // (i.e if it is > 9, for numbers, or if it as a compound variable name like xyz)
    stringstream ss;
    ss << inputText[idx];

    //it is turned true if '.' is found, as it is a sign of a floating point value. Also, it does not allow for more '.' in the number's representation
    bool isFloatingPoint{false};
    
    // search if the found integer/char is followed by characters of the same kind
    for(string::size_type idy = idx+1; idy < inputText.size(); ++idy)
    {
        // if further caharcters with same tokenType are encountered, add them to stringstream buffer, to construct the number/variable
        if(isDigitOrIsAlpha(inputText[idy], tokenType))
        {
            ss << inputText[idy];
            //also advance with the outer for loop, so to get the next character
            ++idx;
        }
        else if ((inputText[idy] == '.' || inputText[idy] == ',') && !isFloatingPoint)
        {
            ss << inputText[idy];
            //also advance with the outer for loop, so to get the next character
            ++idx;
            //do not considers cases such as 1.556.79. Only the first encountered point is considered valid
            isFloatingPoint = true;
        }
        // if another type of token is encountered, add the number/variable formed in the stringstream to the vector of tokens and break from case
        else
        {
            result.push_back(Token{ss.str(), tokenType});
            ss.str("");
            break;
        }
    }
    
    // if the found token is the last one in expression, it means it has not been pushed yet to the result vector, as no other token type has been found 
    // (in the above else branch)
    if(!ss.str().empty())
    {
        result.push_back(Token{ss.str(), tokenType});
        ss.str("");
    }
}

vector<Token> LexingProcessor::lexingInputText(const string& inputText)
{
    vector<Token> result;

    //iterate over the input text character by character and check it against possible token types
    for(string::size_type idx{0}, length = inputText.size(); idx < length; ++idx)
    {
        switch(inputText[idx])
        {
            case ' ':
            {
                continue;
            }
            case '+':
            {
                result.push_back(Token{"+", Token::add});
                break;
            }
            case '-':
            {
                result.push_back(Token{"-", Token::substract});
                break;
            }
            case '*':
            {
                result.push_back(Token{"*", Token::multiply});
                break;
            }
            case '/':
            {
                result.push_back(Token{"/", Token::divide});
                break;
            }
            case '(':
            {
                result.push_back(Token{"(", Token::lparen});
                break;
            }
            case ')':
            {
                result.push_back(Token{")", Token::rparen});
                break;
            }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                processNumbersAndVariables(inputText, idx, Token::floatingPointValue, result);
                break;
            }
            default:
            {
                processNumbersAndVariables(inputText, idx, Token::variable, result);
                break;
            }
        }
    }
    
    return result;
}