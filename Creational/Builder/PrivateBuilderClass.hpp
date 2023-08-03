#pragma once 

/*
* Create the PrivateBuilder class as a private class for the Built class. Then, make the AppendItem method private, in the Built class.
* Thus, the PrivateBuilder's AddItem that wrapps a call to AppendItem will be the only way to construct the object in phases, enforcing hereby
* the usage of the PrivateBuilder instance.
* Therefater, as the PrivateBuilder is tied to the Built object, it gets the *this pointer as argument upon creation. The pointer is used for calling the
* AppendItem, as the PrivateBuilder must know to which object the new itesm must be added, hence the need for coupling the 2 classes. each Built object
* has a PrivateBuilder instance, that is constructed from this pointer when Built c-tor is called, which applied to each c-tor overload.
* As teher is a direct dependency between each Built and PrivateBuilder insatnce, the singleton patter cannot be applied to PrivateBuilder.
*/

class Built
{
    private:
    //forward declaration
    class PrivateBuilder;
    
    public:
    //c-tors
    Built() : privateBuilderInstance{this}
    {};
    
    ~Built() = default;
    
    Built(const pair<string, string>& initValue) : privateBuilderInstance{this}
    {
        mData.emplace(initValue);
    };
    
    Built(const Built& input) : mData{input.mData},
                                privateBuilderInstance{this}
    {
    };
    
    Built(Built&& input) : mData{move(input.mData)},
                           privateBuilderInstance{this}
    {
    };
    
    Built& operator=(Built input)
    {
        if(this != &input)
        {
            std::swap(this->mData, input.mData);
        }
        
        return *this;
    }
    
    //setter and getter
    map<string, string> GetData() const {return mData;};
    void SetData(const map<string, string>& input)
    {
        mData = move(input);
    }
    
    //other methods
    void DisplayContents()
    {
        for(auto&& keyVal : mData)
        {
            cout<<keyVal.first<<" "<<keyVal.second<<endl;
        }
    }
    
    PrivateBuilder& GetPrivateBuilderInstance()
    {
        return privateBuilderInstance;
    }
    
    private:
    class PrivateBuilder
    {
        public:
        PrivateBuilder() = default;
        
        PrivateBuilder(Built* root):rootObject{root}
        {};
        
        //variadic template AddItem emthod which can comply with overloads for Appenditem
        template<class ... Args>
        void AddItem(Args&& ... args)
        {
            rootObject->AppendItem(std::forward<Args>(args)...);
        }
        
        private:
        Built* rootObject{nullptr};
    };
    
    void AppendItem(const pair<string, string>& item)
    {
        mData.insert(item);
    }
 
    map<string, string> mData;
    PrivateBuilder privateBuilderInstance;
};
