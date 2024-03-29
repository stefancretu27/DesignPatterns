#pragma once

#include <string>
#include <utility>
#include <tuple>
#include <map>

using namespace std;

/*
* Flyweight singleton class that can be used by other classes that want to store strings
* in an efficient way. The storage of duplicate strings is avoided as a map keeps track of
* all strings. They key is a hash of the input string, computed using hash<string> 
* template struct specialization.
*
* template<class Key> struct hash - is a template structure that provides a default c-tor 
* and the operator(), which has an argument of type Key and returns size_t, a result value 
* storing the hash value of the parameter. It does not throw exceptions.
* For two parameters k1 and k2 that are equal, std::hash<Key>()(k1) == std::hash<Key>()(k2),
* and if k1!=k2 the probability of their hashes to be equal is very small.
*/

class NameStorage
{
    public:
    static NameStorage& getInstance();
    void addName(const string& name);

    friend ostream& operator<<(ostream& os, const NameStorage& inst)
    {
        for(auto&& pairElem : inst.mNameMap)
        {
            os << pairElem.first <<" "<< pairElem.second <<endl;
        }

        for(auto&& index : inst.mAllIndeces)
        {
            os << index <<" ";
        }

        os << endl;

        return os;
    }

    private:
    //template struct specialization that hashes a string, implemented in <string>
    hash<string> mStringHasher;
    map<size_t, string> mNameMap;
    vector<size_t> mAllIndeces;

    NameStorage() = default;
    NameStorage(const NameStorage&) = delete;
    NameStorage& operator=(const NameStorage&) = delete;
};

NameStorage& NameStorage::getInstance()
{
    static NameStorage singletonInstance{};

    return singletonInstance;
}

size_t NameStorage::addName(const string& name)
{
    size_t index = mStringHasher(name);
    mAllIndeces.emplace_back(index);

    auto it = mNameMap.find(index);

    if(it != mNameMap.end())
    {
        //name already exists in map
    }
    else
    {
        mNameMap.insert({index, name});
    }

    return index;
}
