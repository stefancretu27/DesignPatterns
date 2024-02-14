#pragma once

#include <functional>
#include <vector>
#include <string>
#include <memory>
#include <map>

/*
* The builder class is enhanced with the capacity to hold an instances of the object to be built, associated with a key.
* This allows the builder to reuse the same instance of the built object for later use in copy assignment operations,
* subsequent to initial construction.
*/
class ToBuild
{
    class Builder;
    
    public:
    ToBuild() = default;
    ToBuild(const ToBuild&) = default;
    ToBuild(ToBuild&&) = default;
    ToBuild& operator=(const ToBuild&) = default;
    
    static std::unique_ptr<Builder> GetStaticBuilder() 
    {
       return std::make_unique<Builder>();
    }
    
    static std::unique_ptr<Builder> GetStaticBuilder(const std::string& key) 
    {
        return std::make_unique<Builder>(key);
    }
    
    void PrintElements() const
    {
        for(const auto& elem : mVecStr)
        {
            std::cout<<elem<<std::endl;
        }
        std::cout<<std::endl;
    }
    
    
    private:
    std::vector<std::string> mVecStr;
    
    void AddItem(const std::string& item)
    {
        mVecStr.push_back(item);
    }
    
    class Builder
    {
        public:
        Builder()
        {
            if(!mRoot)
            {
                mRoot = std::make_shared<ToBuild>();
            }
        }
        
        Builder(const std::string& key)
        {
            if(mMapBuiltInstances.find(key) == mMapBuiltInstances.end())
            {
                mMapBuiltInstances[key] = std::make_shared<ToBuild>();
            }
            mRoot = mMapBuiltInstances[key];
        }

        //return Builder instance for calling in chain
        Builder& AppendItem(const std::string& item)
        {
            if(mRoot)
            {

                mRoot->AddItem(item);
            }
            
            return *this;
        }
        
        ToBuild& GetBuiltObject()
        {
            return *mRoot;
        }
        
        private:
        std::shared_ptr<ToBuild> mRoot;
        static std::map<std::string, std::shared_ptr<ToBuild>> mMapBuiltInstances;
    };
};

std::map<std::string, std::shared_ptr<ToBuild>> ToBuild::Builder::mMapBuiltInstances;
