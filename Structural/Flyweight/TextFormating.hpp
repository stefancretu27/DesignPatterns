#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <locale>
#include <vector>
#include <functional>
#include <type_traits>
using namespace std;


struct Sentence
{
    //The flyweight class keeps a bool flag for a word that needs to be capitalized
    //the class using the flyweight class, defines a vector of flyweight class instances
    struct WordToken
    {
        bool capitalize;
        
        WordToken() = default;
        WordToken(bool cap):capitalize{cap}{};
    };
    
    Sentence(const string& text):mText{move(text)}
    {
        stringstream ss{mText};
        string word{};
        
        while(ss >> word)
        {
            mTextToWords.emplace_back(word);
        }

        vecWordToken.resize(mTextToWords.size());
    }
    
    WordToken& operator[](const size_t index)
    {
        return vecWordToken[index];
    }
    
    string str() const
    {
        string result{mText};
        stringstream ss{mText};
        string word{};
        size_t lengthSoFar{0};
        size_t word_count{0};
        
        for(const string& word : mTextToWords)
        {
            if(vecWordToken[word_count++].capitalize)
            {
                for(size_t idx{0}; idx < word.size(); ++idx)
                    result[idx + lengthSoFar] = toupper(word[idx], locale()); 
            }

            lengthSoFar += word.size() + 1;
        }
        
        return result;
    }
    
    private:
        string mText{};
        vector<string> mTextToWords{};
        vector<WordToken> vecWordToken{};
};

