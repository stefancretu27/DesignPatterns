#pragma once

#include <iostream>
#include <map>
#include <utility>
#include <memory>

#include "TemplateBuilder.hpp"

class JsonFileStructure
{
    public:
    //c-tors
    JsonFileStructure() = default;
    ~JsonFileStructure() = default;
    JsonFileStructure(const map<string, string>& inputParsedJsonFile) : mJsonStructure{move(inputParsedJsonFile)}
    {};
    
    JsonFileStructure(const pair<string, string>& initValue)
    {
        mJsonStructure.emplace(initValue);
    };
    
    JsonFileStructure(const JsonFileStructure& inputJsonFileStructure) : mJsonStructure{inputJsonFileStructure.mJsonStructure}
    {};
    
    JsonFileStructure(JsonFileStructure&& inputJsonFileStructure) : mJsonStructure{move(inputJsonFileStructure.mJsonStructure)}
    {};
    
    //apply rule of 4 and a half. Copy and swap idiom: swap content of this with a copy of rhs, which is destroyed/deallocated at the end of the method
    JsonFileStructure& operator=(JsonFileStructure inputJsonFileStructure)
    {
        if(this != &inputJsonFileStructure)
        {
            std::swap(this->mJsonStructure, inputJsonFileStructure.mJsonStructure);
        }
        
        return *this;
    }
    
    //setter and getter
    map<string, string> GetJsonFileStructure() const {return mJsonStructure;};
    void SetJsonFileStructure(const map<string, string>& inputParsedJsonFile)
    {
        mJsonStructure = move(inputParsedJsonFile);
    }
    
    void SetTemplateBuilder(TemplateBuilder<JsonFileStructure>* templateBuilder)
    {
        mTemplateBuilder = templateBuilder; 
    }
    
    TemplateBuilder<JsonFileStructure>& GetBuilder() 
    {
        if(!mTemplateBuilder)
        {
            mTemplateBuilder = new TemplateBuilder<JsonFileStructure>(*this);
        }
        return *mTemplateBuilder;
    }
    
    //other methods
    void DisplayContents()
    {
        for(auto&& keyVal : mJsonStructure)
        {
            cout<<keyVal.first<<" "<<keyVal.second<<endl;
        }
    }
    
    void AppendItem(const pair<string, string>& item)
    {
        mJsonStructure.insert(item);
    }
    
    
    //friend functions
    //the half part of 4 and a half rule, not needed as map object already specialziez std::swap
    friend void swap(JsonFileStructure& lhs, JsonFileStructure& rhs)
    {
        //exchange: lhs gets the value of rhs, while the old value of lhs is return
        auto&& oldLhs = lhs.GetJsonFileStructure();
        lhs.SetJsonFileStructure(rhs.GetJsonFileStructure());
        rhs.SetJsonFileStructure(oldLhs);
    }
    
    private:
    map<string, string> mJsonStructure;
    TemplateBuilder<JsonFileStructure>* mTemplateBuilder;
};
