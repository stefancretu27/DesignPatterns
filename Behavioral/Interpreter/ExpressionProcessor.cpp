#include "ExpressionProcessor.hpp"

/*
* The Token class stores its value as a string, in the tokenizedItem field. When encountering a token whose type
* is variable or floatingPointValue, this private method is called to convert its tokeneziedItem from string to double.
* For compound variables or those not found in the "variables" map, break and return min value for double, used for result initialization.
*/
double ExpressionProcessor::getValueFromNumericToken(Token tk)
{
    double result{numeric_limits<double>::min()};
    switch(tk.type)
    {
        case Token::floatingPointValue:
        {
            //convert from string to double
            result = stod(tk.tokenizedItem);

            break;
        }
        case Token::variable:
        {
            //return 0 if variable has more than 1 letter
            if( tk.tokenizedItem.size() > 1 )
            {
                break;
            }
            //return 0 if variable is not found in variables, so to get its value
            else if (variables.find(*tk.tokenizedItem.c_str()) == variables.end())
            {
                break;
            }
            else
            {
                result = variables[*tk.tokenizedItem.c_str()];
            }
                
            break;
        }  
    }
    
    return result;
}

/*
* After the input string expression goes through lexing transformation, a vector of Token objects
* is obtained and represents the input to this private method. 
*
* This method iterates over the input vector and computes all multiplications and divisions, if any.
* The results of these operations are added to the result vector, together with tokens of all other types.
* In detail, the result vector layout will contain only additions and substractions tokens as well as their
* operands. If their operands were involved in mul/div operations, then the results of such operations will
* be added, othwerwise the original value from the inputy vector will be added to the result vector of tokens.
*
* Each object yields a type, which identifies whether it is operand or operator and which of them ,
* as it is expected to have 4 types of operators and 2 types of operands.
*/
vector<Token> ExpressionProcessor::computeMultiplicationsAndDivisions(const vector<Token>& tokens)
{
    // variables to hold operands and result of partial operations
    double partialResult{}, leftOperand{}, rightOperand{};
    // the vector of token that should contain only add and sub operations, at the end
    vector<Token> result{};

    //iterate over the tokenized string obtained after lexing and compute multiplications and divisions
    for(size_t idx{0}; idx < tokens.size(); )
    {
        switch(tokens[idx].type)
        {
            /* 
            * When encountering a token that is not multiply or divide, add it to the result vector of tokens
            * then go to the next token in the input vector
            * */
            case Token::add:
            case Token::substract:
            case Token::floatingPointValue:
            case Token::variable:
            {
                result.push_back(tokens[idx]);
                ++idx;
                break;
            }
            case Token::multiply:
            {
                // leftOperand is empty or zero if no previous operation was already performed
                if(!leftOperand)
                {
                    /*
                    * Left operand has already been pushed to the result vector, as it represents an operand, 
                    * so it must be poped back and replaced with the result of the operation.
                    * */
                    leftOperand = getValueFromNumericToken(result.back());
                    result.pop_back();

                    // The right operand has not been pushed to the result vector, so it is retrieved from the input vector
                    rightOperand = getValueFromNumericToken(tokens[idx+1]);

                    /*
                    * If the double values were successfully obtained from the Tokens, compute the operation and set the 
                    * leftOperand to the result of the operation, so it can be used subsequently, if a mul or div follows
                    * */
                    if(leftOperand != numeric_limits<double>::min() && rightOperand != numeric_limits<double>::min())
                    {
                        partialResult = leftOperand * rightOperand;
                        leftOperand = partialResult;
                    }
                    // Otherwise return empty vector result, as it does not make sense to continue computing the expression
                    else
                    {
                        return {};
                    }
                }
                else
                {
                    /*
                    * If leftOperand has been set, it means that the previous operation was a mul or div. Thus, the computation of
                    * the result should go further with the current operation, which only requires to get the right hand side operand
                    * */
                    rightOperand = getValueFromNumericToken(tokens[idx+1]);
                    if(rightOperand != numeric_limits<double>::min())
                    {
                        partialResult *= rightOperand;
                    }
                    else
                    {
                        return {};
                    }
                }
                
                /* 
                * If the multiplication operation is not followed by another multiplication or by a division push back
                * the partial result to the intermediated vector of tokens
                * */
                if( (idx + 2) < tokens.size() && tokens[idx+2].type != Token::multiply && tokens[idx+2].type !=Token::divide) 
                {
                    result.push_back(Token{to_string(partialResult), Token::floatingPointValue});
                    //reset temporary values used to compute mul and div
                    partialResult = leftOperand = rightOperand = 0.0f;
                }
                //If no further elements are left in the input vetcor of tokens, push back the partialResult computed so far
                else if((idx + 2) >= tokens.size() )
                {

                    result.push_back(Token{to_string(partialResult), Token::floatingPointValue});
                }
                
                /*
                * If the input vector of token has not been fully processed and the next operation is not add or sub,
                * it means the next operation is wether mul or div, so go to the next multiplication or division
                * */
                idx = idx+2;

                break;
            }
            case Token::divide:
            {
                //leftOperand is empty or zero if no previous operations was already performed
                if(!leftOperand)
                {
                    /*
                    * Left operand has already been pushed to the result vector, as it represents an operand, 
                    * so it must be poped back and replaced with the result of the operation.
                    * */
                    leftOperand = getValueFromNumericToken(result.back());
                    result.pop_back();
      
                    // The right operand has not been pushed to the result vector, so it is retrieved from the input vector
                    rightOperand = getValueFromNumericToken(tokens[idx+1]);

                    /*
                    * If the double values were successfully obtained from the Tokens, compute the operation and set the 
                    * leftOperand to the result of the operation, so it can be used subsequently, if a mul or div follows
                    * */
                    if(leftOperand != numeric_limits<double>::min() && rightOperand != numeric_limits<double>::min())
                    {
                        partialResult = leftOperand / rightOperand;
                        leftOperand = partialResult;
                    }
                    // Otherwise return empty vector result, as it does not make sense to continue computing the expression
                    else
                    {
                        return {};
                    }
                }
                else
                {
                     /*
                    * If leftOperand has been set, it means that the previous operation was a mul or div. Thus, the computation of
                    * the result should go further with the current operation, which only requires to get the right hand side operand
                    * */
                    rightOperand = getValueFromNumericToken(tokens[idx+1]);
                    if(rightOperand != numeric_limits<double>::min())
                    {
                        partialResult /= rightOperand;
                    }
                    else
                    {
                        return {};
                    }
                }
                
                /* 
                * If the multiplication operation is not followed by another multiplication or by a division push back
                * the partial result to the intermediated vector of tokens
                * */
                if( (idx + 2) < tokens.size() && tokens[idx+2].type != Token::multiply && tokens[idx+2].type !=Token::divide )
                {
                    result.push_back(Token{to_string(partialResult), Token::floatingPointValue});
                    //reset temporary values used to compute mul and div
                    partialResult = leftOperand = rightOperand = 0.0f;
                }
                //If no further elements are left in the input vetcor of tokens, push back the partialResult computed so far
                if( (idx + 2) >= tokens.size() )
                {
                    result.push_back(Token{to_string(partialResult), Token::floatingPointValue});

                }
                
                /*
                * If the input vector of token has not been fully processed and the next operation is not add or sub,
                * it means the next operation is wether mul or div, so go to the next multiplication or division
                * */
                idx = idx+2;

                break;
            }
            default:
                ++idx;
                break;
        }
    }

    return move(result);
}

double ExpressionProcessor::Calculate(const string& expression)
{
    double result{};
    //lexing
    LexingProcessor lexProc{};
    vector<Token> tokens = lexProc.lexingInputText(expression);

    cout<<"After lexing:"<<endl;
    for(auto& token : tokens)
    {
        cout << token;
    }

    if(tokens.size() == 1)
    {
        if(tokens[0].type == Token::variable || tokens[0].type == Token::floatingPointValue)
        {
            result = getValueFromNumericToken(tokens[0]);
        }
    }
    else if(tokens.size() == 2)
    {
        if(tokens[0].type == Token::variable || tokens[0].type == Token::floatingPointValue)
        {
            result = getValueFromNumericToken(tokens[0]);
        }
        else if(tokens[1].type == Token::variable || tokens[1].type == Token::floatingPointValue)
        {
            result = getValueFromNumericToken(tokens[1]);

            if(tokens[0].type == Token::substract)
            {
                result *= -1;
            }
        }
    }
    else if(tokens.size() > 2)
    {
        vector<Token> intermediateParsedTokens = computeMultiplicationsAndDivisions(tokens);

        if(!intermediateParsedTokens.empty())
        {
            tokens = move(intermediateParsedTokens);
        }

        cout<<endl<<" After intermediate parsing:"<<endl;
        for(auto& token : tokens)
        {
            cout << token;
        }
    
        if(tokens.size() == 1)
        {
            result = stod(tokens[0].tokenizedItem);
        }
        else
        {
            shared_ptr<FloatingPointNumber> output{make_shared<FloatingPointNumber>(0)};
            Operation operation{};
            bool have_lhs{false}, have_rhs{false};
            
            //iterate over the tokenized string obtained after lexing and compute multiplications and divisions
            for(size_t idx{0}; idx < tokens.size(); ++idx)
            {
                switch(tokens[idx].type)
                {
                    case Token::floatingPointValue:
                    {
                        //convert from string to double
                        double valueOfFloatingPointNr = stod(tokens[idx].tokenizedItem);

                        //a subexpression or operation would always have a left operand, that is result of the previous operation 
                        //except for the case when the very forst operation is built
                        if(!have_lhs)
                        {
                            operation.lhs = make_shared<FloatingPointNumber>(valueOfFloatingPointNr);
                            have_lhs = true;
                        }
                        //if not the 1st operand in the 1st expression, then set the current number as second operand
                        else
                        {
                            operation.rhs = make_shared<FloatingPointNumber>(valueOfFloatingPointNr);
                            have_rhs = true;
                        }
                        break;
                    }
                    case Token::variable:
                    {
                        //return 0 if variable has more than 1 letter
                        if( tokens[idx].tokenizedItem.size() > 1 )
                        {
                            return 0;
                        }
                        //return 0 if variable is not found in variables, so to get its value
                        else if (variables.find(*tokens[idx].tokenizedItem.c_str()) == variables.end())
                        {
                            return 0;
                        }
                        else
                        {
                            double valueOfVariable = variables[*tokens[idx].tokenizedItem.c_str()];
                            
                            //a subexpression or operation would always have a left operand, that is result of the previous operation 
                            //except for the case when the very forst operation is built
                            if(!have_lhs)
                            {
                                operation.lhs = make_shared<FloatingPointNumber>(valueOfVariable);
                                have_lhs = true;
                            }
                            //if not the 1st operand in the 1st expression, then set the current number as second operand
                            else
                            {
                                operation.rhs = make_shared<FloatingPointNumber>(valueOfVariable);
                                have_rhs = true;
                            }
                        }
                            
                        break;
                    }
                    case Token::add:
                    {
                        operation.operationType = Operation::add;
                        break;
                    }
                    case Token::substract:
                    {
                        operation.operationType = Operation::sub;
                        break;
                    }
                }
                
                // if rhs was set, it means that the operation was constructed completely. 
                // Thus, evaluate it and set it as lhs for the next operation
                if(have_rhs)
                {
                    //get the value of the subexpression
                    output->value = operation.eval();
                    operation.lhs = output;
                    
                    //mark having no operand anymore so to compute next operation
                    have_rhs = false;
                }
            }

            result = output->eval();
        }
    }
        
        
    return result;
}