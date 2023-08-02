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
    JsonFileStructure(const std::map<std::string, std::string>& inputParsedJsonFile) : mJsonStructure{std::move(inputParsedJsonFile)}
    {};
    
    JsonFileStructure(const std::pair<std::string, std::string>& initValue)
    {
        mJsonStructure.emplace(initValue);
    };
    
    JsonFileStructure(const JsonFileStructure& inputJsonFileStructure) : mJsonStructure{inputJsonFileStructure.mJsonStructure}
    {};
    
    JsonFileStructure(JsonFileStructure&& inputJsonFileStructure) : mJsonStructure{std::move(inputJsonFileStructure.mJsonStructure)}
    {};
    
    //apply rule of 4 and a half
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
    void SetJsonFileStructure(const std::map<std::string, std::string>& inputParsedJsonFile)
    {
        mJsonStructure =std:: move(inputParsedJsonFile);
    }
    
    //other methods
    void DisplayContents()
    {
        for(auto&& keyVal : mJsonStructure)
        {
            cout<<keyVal.first<<" "<<keyVal.second<<endl;
        }
    }
    
    void AppendItem(const std::pair<std::string, std::string>& item)
    {
        mJsonStructure.insert(item);
    }
    
    //combine builder with singleton,such that the built class interface exposes the builder object. 
    //In such cases, the builder class can be made private
    Builder<JsonFileStructure>& GetUPtrBuilder() 
    {
        static Builder<JsonFileStructure> builderUPtr(*this);
        
        return builderUPtr;
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
};
