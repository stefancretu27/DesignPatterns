#pragma once

#include <string>
#include <sstream>
#include <deque>
#include <iostream>
#include <stack>

class Token
{
    public:
    enum class TokenType
    {
        PLUS,
        MINUS,
        MUL,
        DIV,
        MOD,
        LEFTPAREN,
        RIGHTPAREN,
        VALUE
    };
    
    Token() = default;
    explicit Token(const TokenType& tokType, const std::string& content) : mTokenType{tokType},
                                                                           mContent{content}
    {};
    
    Token(const Token& tk) : mTokenType{tk.mTokenType},
                             mContent{tk.mContent}
    {};
    
    Token(Token&& tk) : mTokenType{std::move(tk.mTokenType)},
                        mContent{std::move(tk.mContent)}
    {};
    
    friend void swap(Token& lhs, Token& rhs)
    {
        using std::swap;
        swap(lhs.mTokenType, rhs.mTokenType);
        swap(lhs.mContent, rhs.mContent);
    }
    
    Token& operator=(Token tk)
    {
        swap(*this, tk);
        return *this;
    }
    
    static std::string TokenTypeToString(const TokenType& tok)
    {
        std::string result{"value"};
        
        switch(tok)
        {
            case Token::TokenType::PLUS:
                result = std::string("plus");
                break;
            case Token::TokenType::MINUS:
                result = std::string("minus");
                break;
            case Token::TokenType::MUL:
                result = std::string("multiply");
                break;
            case Token::TokenType::DIV:
                result = std::string("divide");
                break;
            case Token::TokenType::MOD:
                result = std::string("modulo");
                break;
            case Token::TokenType::LEFTPAREN:
                result = std::string("left parenthesis");
                break;
            case Token::TokenType::RIGHTPAREN:
                result = std::string("right parenthesis");
                break;
            default:
                break;
        }
        
        return result;
    }
    
    TokenType GetTokenType() const {return mTokenType;};
    std::string GetContent() const {return mContent;};
    
    private:
    TokenType mTokenType;
    std::string mContent;
};

/*
* Lexing class purpose is to encapsulate methods that convert an input string, containing math operations,
* to a list of Tokens, with each value, operations sign and parenthesis, being identified classificated as such.
* The list of Tokens is stored internally as deque<Token>, being accessible via a getter.
*/
    
class Lexing
{
    public:
    Lexing() = default;
    ~Lexing() = default;
    Lexing(const Lexing&) = default;
    Lexing& operator=(const Lexing&) = default;
    
    bool CreateTokensList(const std::string& inputExpression);
    
    std::deque<Token> GetTokenizedExpression() const
    {
        return mVecTokenizedExpression;
    }
    
    private:
    //members
    std::deque<Token> mVecTokenizedExpression;
    
    //methods
    void ProcessOperator(const char signOperator);
    constexpr bool IsOperator(const char signOperator)
    {
        return (signOperator == '+' || signOperator == '-' || signOperator == '%' ||
                signOperator == '*' || signOperator == '/' || signOperator == '(' || signOperator == ')');
    }
};

/*
* Private method that converts the input character, already identified as an operations sign,
* into a Token object, adding it to the list of Tokens.
*/
void Lexing::ProcessOperator(const char signOperator)
{
    std::string operatorAsString{signOperator};
    
    switch(signOperator)
    {
        case '+':
            mVecTokenizedExpression.emplace_back(Token::TokenType::PLUS, operatorAsString);
            break;
        case '-':
            mVecTokenizedExpression.emplace_back(Token::TokenType::MINUS, operatorAsString);
            break;
        case '*':
            mVecTokenizedExpression.emplace_back(Token::TokenType::MUL, operatorAsString);
            break;
        case '/':
            mVecTokenizedExpression.emplace_back(Token::TokenType::DIV, operatorAsString);
            break;
        case '%':
            mVecTokenizedExpression.emplace_back(Token::TokenType::MOD, operatorAsString);
            break;
        case '(':
            mVecTokenizedExpression.emplace_back(Token::TokenType::LEFTPAREN, operatorAsString);
            break;
        case ')':
            mVecTokenizedExpression.emplace_back(Token::TokenType::RIGHTPAREN, operatorAsString);
            break;
        default:
            break;
    }
}

/*
* Main method of the class, that converts the input string into a list of Tokens, stored as class member of deque<Token> type.
* Returns false if the expression is ill-formed: unmatched parenthesis, if any.
*
* Approach: Firstly checks if the expression starts with a negative number, storing it as 2 separated Tokens: the MINUS Token
* and the positive VALUE Token. Then, it ietartes over the input string, checking each character. 
* When a left paren is met, it is firstly added to the list of Tokens, then it is checked if other left parenthesis 
* immediately follow it. If so, add them to the list of Tokens, whilst incrementing the left parenthesis counter. 
* When no left parenthesis is met, check if a MINUS is encountered and process it if so, and increment counter. Then, keep record 
* of the next index in the input string, that corresponds to the last pushed Token, so the iteration continues from it. 
* Proceed similarily for when a right parenthesis is encountered, only that take into account it can be followed by any operation sign.
* If an operation sign is encountered, process the characters preceeding it, which represent a value number. In that regard, the index
* of the current operator is used as upper bound, with the lower bound being another recorded index, that is next index of the last processed
* operator (which can be a parenthesis). Then, get the substring within this bounds, append it as VALUE Token, then asppend a Token created
* for the current operator. Lastly, update the next index of the currently processed operator, so the enxt iteration can start from it.
* In the end, check if a value remianed, as an expression does not end with a sign, but with a value. The last value is bound by input string
* size and starts at the next index of the last processed operator.
*/
bool Lexing::CreateTokensList(const std::string& inputExpression)
{
    bool result{true};
    size_t currentOperatorIndex{0};
    size_t prevOperatorNextIndex{0};
    size_t leftParenCount{0};
    size_t rightParenCount{0};
    size_t parenIndex{0};
    std::string valueAsString{};
    
    if(inputExpression[0] == '-')
    {
        mVecTokenizedExpression.emplace_back(Token::TokenType::MINUS, std::string("-"));
        prevOperatorNextIndex = 1;
    }
    
    for(size_t idx{prevOperatorNextIndex}, len = inputExpression.size(); idx < len; ++idx)
    {
        if(IsOperator(inputExpression[idx]))
        {
            if(leftParenCount < rightParenCount)
            {
                result = false;
                break;
            }
            
            //parenthesis are treated differently from the rest of operators, as more than one can exist on consequent indeces
            if(inputExpression[idx] == '(')
            {
                ++leftParenCount;
                mVecTokenizedExpression.emplace_back(Token::TokenType::LEFTPAREN, std::string("("));
                
                //if more parenthesis are closed, add each parenthesis to the vector
                while(inputExpression[++idx] == '(')
                {
                    ++leftParenCount;
                    mVecTokenizedExpression.emplace_back(Token::TokenType::LEFTPAREN, std::string("("));
                }
                
                //after all parenthesis are open, check if the next character is a MINUS, 
                //as other operations do not make sense. If so, process it
                if(inputExpression[idx].GetTokenType() == Token::TokenType::MINUS)
                {
                    ProcessOperator(inputExpression[idx]);
                    prevOperatorNextIndex = idx+1;
                }
                //if no sign follows, the index of the previous operator stays as the index of last open parenthesis + 1
                else
                {
                    prevOperatorNextIndex = idx;
                }
            }
            else if(inputExpression[idx] == ')')
            {
                ++rightParenCount;
                //process value before the parenthesis is closed, add it to the vector of Tokens, then add the parenthesis to the vector
                valueAsString = inputExpression.substr(prevOperatorNextIndex, idx-prevOperatorNextIndex);
                mVecTokenizedExpression.emplace_back(Token::TokenType::VALUE, valueAsString);
                mVecTokenizedExpression.emplace_back(Token::TokenType::RIGHTPAREN, std::string(")"));
                
                //if more parenthesis are closed, add each parenthesis to the vector
                while(inputExpression[++idx] == ')')
                {
                    ++rightParenCount;
                    mVecTokenizedExpression.emplace_back(Token::TokenType::RIGHTPAREN, std::string(")"));
                }

                //after all parenthesis are open, check if the enxt character is a sign. If so, process it
                if(IsOperator(inputExpression[idx]))
                {
                    ProcessOperator(inputExpression[idx]);
                    prevOperatorNextIndex = idx+1;
                }
                //if no sign follows, the index of the previous operator stays as the index of last closed parenthesis + 1
                else
                {
                    prevOperatorNextIndex = idx;
                }
            }
            //when an operator is encountered, process the value preceeding it and add it to the vector of Token, then add the operator to the vector
            else
            {
                currentOperatorIndex = idx;
                valueAsString = inputExpression.substr(prevOperatorNextIndex, currentOperatorIndex - prevOperatorNextIndex);
                prevOperatorNextIndex = idx+1;
                mVecTokenizedExpression.emplace_back(Token::TokenType::VALUE, valueAsString);
                ProcessOperator(inputExpression[idx]);
            }
        }
    }
    
    //add remaining value if any 
    if(prevOperatorNextIndex < inputExpression.size())
    {
        valueAsString = inputExpression.substr(prevOperatorNextIndex, inputExpression.size()-prevOperatorNextIndex);
        mVecTokenizedExpression.emplace_back(Token::TokenType::VALUE, valueAsString);
    }
    
    if(leftParenCount != rightParenCount)
    {
        result = false;
    }
    
    return result;
}

/*
* Parser class' purpose is to encapsualte methods that compute expressions stored as list of tokens, specifically
* in a deque<Token>. It is implemented as Singleton, does not store any data, with the result being returned from
* the methods. It could have been a monostate, as well.
*/
class Parser
{
    public:
    Token ComputeExpressionNoParenthesis(const std::deque<Token>& tokenizedExpression);
    Token ComputeExpressionWithParenthesis(const std::deque<Token>& tokenizedExpression);
    
    static Parser& GetInstance()
    {
        static Parser instance{};
        
        return instance;
    }
    
    private:
    Parser() = default;
    ~Parser() = default;
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(Parser&&) = delete;
};

/*
* Dedicated method to compute the result of math expressions that do not have parenthesis, but only values and operations.
* The result is stored in a Token that is returned.
*
* Approach: Respecting the order of operations, the procedure is divided in 2 steps. Firstly, *,/,% are computed, resulting in
* another list of tokens containing values and +,- operations. Then, at the second step, the resulted list of Tokens is processed
* with the operations being evaluated from left to right, that is their order in the list. 
* At each step, it is firstly checked if the first Token is of MINUS type, indicating that the expression starts with a negative
* value. If so, the MINUS Token and the next VALUE token are replaced with a VALUE token, containing the negative number.
* Then, it is iterated over the list of Tokens and is looked for an operation Token. When it is met, computed the appropiate
* operation between the value Tokens placed at idx-1 and idx+1, where idx is the index of the curretnly evaluated operation.
* The result is stored in the list of Tokens at idx-1, with the Tokens at positions idx and idx+1 being erased. This causes
* a change in size of the list of Tokens, hence it is required for it to be checked at each iteration.
* The iterator index is incremented only when a non operator is met. When an operator is met, as the result is stored at idx-1,
* its value isn't changed, as it should evaluate in the next iteration the new Token placed at position idx.
*/

Token Parser::ComputeExpressionNoParenthesis(const std::deque<Token>& tokenizedExpression)
{
    std::deque<Token> modifiableExpression{std::move(tokenizedExpression)};
    double singleOperationsResult{};
    
    //step 1: compute mul, div, modulo. This produces another vector<Token> containing +,- and values, input for the step below
    //if the expression starts with a negative value, replace the token minus and the token of the first value, with -1*value
    if(modifiableExpression[0].GetTokenType() == Token::TokenType::MINUS)
    {
        singleOperationsResult = -1.0f * std::stod(modifiableExpression[1].GetContent());
        modifiableExpression.pop_front();
        modifiableExpression.pop_front();
        modifiableExpression.emplace_front(Token::TokenType::VALUE, std::to_string(singleOperationsResult));
    }

    //as the size of modifiableExpression is shrinked by 2 each time a * / % operation is computed,
    //it is necessary to reevaluate modifiableExpression.size() at each iteration
    for(size_t idx{0}; idx < modifiableExpression.size(); )
    {
        if( modifiableExpression[idx].GetTokenType() == Token::TokenType::MUL ||
            modifiableExpression[idx].GetTokenType() == Token::TokenType::MOD || 
            modifiableExpression[idx].GetTokenType() == Token::TokenType::DIV )
        {
            if(modifiableExpression[idx].GetTokenType() == Token::TokenType::MUL)
            {
                singleOperationsResult = std::stod(modifiableExpression[idx-1].GetContent()) * std::stod(modifiableExpression[idx+1].GetContent());
            }
            else if (modifiableExpression[idx].GetTokenType() == Token::TokenType::DIV)
            {
                singleOperationsResult = std::stod(modifiableExpression[idx-1].GetContent()) / std::stod(modifiableExpression[idx+1].GetContent());
            }
            else if (modifiableExpression[idx].GetTokenType() == Token::TokenType::MOD)
            {
                singleOperationsResult = std::stoi(modifiableExpression[idx-1].GetContent()) % std::stoi(modifiableExpression[idx+1].GetContent());
            }
            
            //replacing the 1st operand, at idx-1, with result of the operation
            modifiableExpression[idx-1] = Token(Token::TokenType::VALUE, std::to_string(singleOperationsResult));
            //erase Tokens at positions idx and idx+1
            //idx is not incremented, so the next iteration starts with the same idx, now containing the next Token required for processing
            modifiableExpression.erase( modifiableExpression.begin() + idx, 
                                        modifiableExpression.begin() + idx + 2);
        }
        else
        {
            //only get to the next token if * / % operation is not encountered
            ++idx;
        }
    }

    //step 2: compute + and -
    //if the expression starts witha  negative value, replace the token minus and the token of the first value, with 0-value
    if(modifiableExpression[0].GetTokenType() == Token::TokenType::MINUS)
    {
        singleOperationsResult = 0.0f - std::stod(modifiableExpression[1].GetContent());
        modifiableExpression.pop_front();
        modifiableExpression.pop_front();
        modifiableExpression.emplace_front(Token::TokenType::VALUE, std::to_string(singleOperationsResult));
    }
    
    //as the size of modifiableExpression is shrinked by 2 each time a +,- operation is computed,
    //it is necessary to reevaluate modifiableExpression.size() at each iteration
    for(size_t idx{0}; idx < modifiableExpression.size(); )
    {
        if( modifiableExpression[idx].GetTokenType() == Token::TokenType::MINUS ||
            modifiableExpression[idx].GetTokenType() == Token::TokenType::PLUS)
        {
            if(modifiableExpression[idx].GetTokenType() == Token::TokenType::PLUS)
            {
                singleOperationsResult = std::stod(modifiableExpression[idx-1].GetContent()) + std::stod(modifiableExpression[idx+1].GetContent());
            }
            else
            {
                singleOperationsResult = std::stod(modifiableExpression[idx-1].GetContent()) - std::stod(modifiableExpression[idx+1].GetContent());
            }
            
            //replacing the 1st operand, at idx-1, with result of the operation
            modifiableExpression[idx-1] = Token(Token::TokenType::VALUE, std::to_string(singleOperationsResult));
            //erase Tokens at positions idx and idx+1
            //idx is not incremented, so the next iteration starts with the same idx, now containing the next Token required for processing
            modifiableExpression.erase( modifiableExpression.begin()+idx, 
                                        modifiableExpression.begin()+idx+2);
        }
        else
        {
            ++idx;
        }
    }

    return modifiableExpression[0];
}

/*
* Dedicated method that computes subexpression within all parenthesis. 
* This produces another list of Tokens whose types are +,-,*,/,% and values, that is used afterwards by the method above.
*
* Approach: iterate over the input list of tokens and check for parenthesis tokens. If the current token is not of parenthesis
* type, simply increment the index iterator. If it is encountered a left parenthesis Token, besides incrementing the index
* iterator, store the index of the Token, eventually in a stack, as the most recent encountered ( will be the first to be used.
*
* When the first right parenthesis is encountered, computed subexpression, as another (smaller) list of Tokens, starting 
* from the next index of last left parenthesis (stack.top()) and ending with the current index, that of the right parenthesis.
* Then, this subexpression, doesn't contain any parenthesis, is computed using the method for operations calculations *,/,+,-,%.
* The result replaces the left parenthesis token, at its index, with all token following it, untill the next index of the 
* right parenthesis token, being erased. Thus, the input list of Tokens is being resized and the iterator index is updated to the
* next index of the left parenthesis, that is now the enxt index of the recently computed result. When the iteration is over, the
* result is a list of Tokens containing operations calculations *,/,+,-,% and values, that is processed with the method implemented above.
*/
Token Parser::ComputeExpressionWithParenthesis(const std::deque<Token>& tokenizedExpression)
{
    std::deque<Token> modifiableExpression{std::move(tokenizedExpression)};
    double singleOperationsResult{};
    std::stack<size_t> stackIdLastLeftParen{};
    size_t idFirstRightParen{};
    
    for(size_t idx{0}; idx < modifiableExpression.size(); )
    {
        if( modifiableExpression[idx].GetTokenType() == Token::TokenType::LEFTPAREN)
        {
            //when a left parenthesis Token is met, stack its index and proceed further with the enxt Token
            stackIdLastLeftParen.push(idx);
            ++idx;
        }
        else if(modifiableExpression[idx].GetTokenType() == Token::TokenType::RIGHTPAREN)
        {
            idFirstRightParen = idx;
            size_t idLastLeftParen = stackIdLastLeftParen.top();
            stackIdLastLeftParen.pop();
            
            //once the first right parenthesis encountered, get the subexpression between it and last left parenthesis
            std::deque<Token> subExpression(idFirstRightParen - idLastLeftParen - 1);
            /*std::copy_n(modifiableExpression.begin() + idLastLeftParen + 1, 
                          idFirstRightParen - idLastLeftParen - 1, 
                          subExpression.begin());*/
            std::move(modifiableExpression.begin() + idLastLeftParen + 1, 
                      modifiableExpression.begin() + idFirstRightParen, 
                      subExpression.begin());
            
            //replace token at last left parenthesis with the value of subexpression
            modifiableExpression[idLastLeftParen] = ComputeExpressionNoParenthesis(subExpression);
            //delete Tokens included in the subexpression and the right parenthesis, from the list of Tokens
            modifiableExpression.erase(modifiableExpression.begin() + idLastLeftParen + 1, 
                                       modifiableExpression.begin() + idFirstRightParen + 1);
            
            //next iteration should start from the next index of the last encountered left parenthesis, 
            //that is the result of the lastly evaluated subexpression
            idx = idLastLeftParen+1;
        }
        else
        {
            //go to the next Token if no parenthesis Token is encountered
            ++idx;
        }
    }
    
    //after all parnthesis are computed and replace, the result is a deque<Token> with values and +,-,*,/,% operations
    Token result = ComputeExpressionNoParenthesis(modifiableExpression);
    
    return result;
}
