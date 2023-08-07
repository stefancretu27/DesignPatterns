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
    JsonFileStructure(const std::map<std::string, std::string>& inputParsedJsonFile) : mJsonStructure{move(inputParsedJsonFile)}
    {};
    
    JsonFileStructure(const std::pair<std::string, std::string>& initValue)
    {
        mJsonStructure.emplace(initValue);
    };
    
    JsonFileStructure(const JsonFileStructure& inputJsonFileStructure) : mJsonStructure{inputJsonFileStructure.mJsonStructure}
    {};
    
    JsonFileStructure(JsonFileStructure&& inputJsonFileStructure) : mJsonStructure{std::move(inputJsonFileStructure.mJsonStructure)}
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
    std::map<std::string, std::string> GetJsonFileStructure() const {return mJsonStructure;};
    void SetJsonFileStructure(const std::map<std::string, std::string>& inputParsedJsonFile)
    {
        mJsonStructure = move(inputParsedJsonFile);
    }
    
    static TemplateBuilder<JsonFileStructure> GetStaticBuilder() 
    {
        return TemplateBuilder<JsonFileStructure>();
    }
    
    template<class ... Args>
    static TemplateBuilder<JsonFileStructure> GetStaticBuilder(Args&& ... args) 
    {
        return TemplateBuilder<JsonFileStructure>(std::forward<Args>(args)...);
    }
    
    //other methods
    void DisplayContents()
    {
        for(auto&& keyVal : mJsonStructure)
        {
            std::cout<<keyVal.first<<" "<<keyVal.second<<std::endl;
        }
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
    std::map<std::string, std::string> mJsonStructure;
    
    void AppendItem(const std::pair<std::string, std::string>& item)
    {
        mJsonStructure.insert(item);
    }
    
    friend class TemplateBuilder<JsonFileStructure>;
};
