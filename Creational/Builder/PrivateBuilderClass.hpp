#pragma once 

/*
* Create the PrivateBuilder class as a private class for the Built class. Then, make the AppendItem method private, in the Built class.
* Thus, the PrivateBuilder's AddItem that wrapps a call to AppendItem will be the only way to construct the object in phases, enforcing hereby
* the usage of the PrivateBuilder instance.
* Therefater, create a non-static method which constructs a PrivateBuilder object for each built instance, statically, following a singleton-like pattern,
* only that the PrivateBuilder is tied to the Built object, as it gets the *this pointer as argument upon creation. The pointer is uised for calling the
* AppendItem, as the PrivateBuilder must know to which object the new itesm must be added, hence the need for coupling the 2 classes.
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
    
    Built(const pair<string, string>& initValue)
    {
        mData.emplace(initValue);
    };
    
    Built(const Built& input) : mData{input.mData}
    {
    };
    
    Built(Built&& input) : mData{move(input.mData)}
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
        static PrivateBuilder privateBuilderInstance{this};
        
        return privateBuilderInstance;
    }
    
    private:
    class PrivateBuilder
    {
        public:
        PrivateBuilder(Built* root):rootObject{root}
        {};
        
        //variadic template AddItem emthod which can comply with overloads for Appenditem
        template<class ... Args>
        void AddItem(Args&& ... args)
        {
            rootObject->AppendItem(std::forward<Args>(args)...);
        }
        
        private:
        Built* rootObject;
    };
    
    void AppendItem(const pair<string, string>& item)
    {
        mData.insert(item);
    }
 
    map<string, string> mData;
};
