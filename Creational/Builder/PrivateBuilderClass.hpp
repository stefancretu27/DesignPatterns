#pragma once 

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <iostream>

/*
* The below implementation aims at not exposing the Builder's implementation, whereas making possible to construct the Built object in phases
* only by using the Builder. This is possible as the Built class uses a GetBuilder() static public method for retrieveing the Builder instance
* which is default created and returned as an anonymous object. Thus, each time the method is called, a new PrivateBuilder() instance is created, which
* means there is no 1 to 1 ampping between the Built and PrivateBuilder instances. Consequently, there is no required double dependency injection
* so each class can keep track of the other's existence.
*
* Create the PrivateBuilder class as a private class for the Built class. Then, make the AppendItem method private in the Built class, with
* the PrivateBuilder's AddItem wrapping a call to AppendItem as the only way to construct the object in phases, enforcing hereby
* the usage of the PrivateBuilder instance. Furthermore, for allowing chaining of the build phases, the Builder's AppendItem method shall 
* return the instance of the Builder, for being reused. After the chained construction os ver, call () operator or ConstructObject() for
* retrieving the built object.
*
* Additionallty, the GetBuilder() methods gets an overloaded template implementation with variadic args, which calls the Builder's template c-tor with
* variadic args. This constructs the Built root object with the specificed args using perfect frowarding twice in a row.
*/

class Built
{
    private:
    //forward declaration
    class PrivateBuilder;
    
    public:
    //c-tors
    Built() = default;
    ~Built() = default;
    
    Built(const std::pair<std::string, std::string>& initValue)
    {
        mData.emplace(initValue);
    };
    
    Built(const Built& input) : mData{input.mData}
    {};
    
    Built(Built&& input) : mData{std::move(input.mData)}
    {};
    
    Built& operator=(Built input)
    {
        if(this != &input)
        {
            std::swap(this->mData, input.mData);
        }
        
        return *this;
    }
    
    //setter and getter
    std::map<std::string, std::string> GetData() const {return mData;};
    void SetData(const std::map<std::string, std::string>& input)
    {
        mData = std::move(input);
    }
    
    //other methods
    void DisplayContents()
    {
        for(auto&& keyVal : mData)
        {
            std::cout<<keyVal.first<<" "<<keyVal.second<<std::endl;
        }
    }
    
    static PrivateBuilder GetStaticPrivateBuilder()
    {
        return PrivateBuilder();
    }
    
    template<class ... Args>
    static PrivateBuilder GetStaticPrivateBuilder(Args&& ... args)
    {
        return PrivateBuilder(std::forward<Args>(args)...);
    }
    
    private:
    //Built members and private methods
    void AppendItem(const std::pair<std::string, std::string>& item)
    {
        mData.insert(item);
    }
 
    std::map<std::string, std::string> mData;
    
    //Private builder class declaration and definition
    class PrivateBuilder
    {
        public:
        template<class ... Args>
        PrivateBuilder(Args&& ... args)
        {
            if(!mUptrRootObject)
            {
                mUptrRootObject = std::make_unique<Built>(std::forward<Args>(args)...);
            }
        };
        
        PrivateBuilder()
        {
            if(!mUptrRootObject)
            {
                mUptrRootObject = std::make_unique<Built>();
            }
        };
        
        Built& operator()()
        {
            return *mUptrRootObject;
        }
        
        Built& ConstructObject()
        {
            return *mUptrRootObject;
        }
        
        //variadic template AddItem method which can comply with overloads for Appenditem
        template<class ... Args>
        PrivateBuilder& AddItem(Args&& ... args)
        {
            mUptrRootObject->AppendItem(std::forward<Args>(args)...);
            
            return *this;
        }

        //or use the dependency to insert data directly into the member map, bypassing the call to AppendItem
        PrivateBuilder& AddItem(const std::pair<std::string, std::string>& item)
        {
            mUptrRootObject->mData.insert(item);
            
            return *this;
        }
        
        private:
        std::unique_ptr<Built> mUptrRootObject{nullptr};
    };
};
