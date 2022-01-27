#pragma once

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class ISingletondataAccess
{
    public:
    virtual ~ISingletondataAccess() = default;
    virtual void parseFile() = 0;
};

class SingletonDataAccess: public ISingletondataAccess
{
    public:
    static SingletonDataAccess& getInstance();

    SingletonDataAccess(const SingletonDataAccess&) = delete;
    SingletonDataAccess& operator=(const SingletonDataAccess&) = delete;

    void parseFile() override;
    void printData();
    inline const map<unsigned, string>& getData() const {return mData;}

    protected:
    SingletonDataAccess() = default;

    private:
    static map<unsigned, string> mData;
    static const string mFilename;    
};

SingletonDataAccess& SingletonDataAccess::getInstance()
{
    static SingletonDataAccess uniqueInstance{};

    return uniqueInstance;
}

void SingletonDataAccess::parseFile()
{
    //open the file with automatically assumed ios::in from istream
    std::ifstream inputFileStream(mFilename);
    string line;
    unsigned key;

    if(inputFileStream.is_open())
    {
        while(getline(inputFileStream, line))
        {
            stringstream inputStringStream(line);
            inputStringStream >> key >> mData[key];
        }

        inputFileStream.close();
    }
    else
    {
        cout<<"file is not open"<<endl;
    }
}

void SingletonDataAccess::printData()
{
    for(auto& elem : mData)
        cout<<elem.first<<" "<<elem.second<<endl;
}

//Create dummy singleton class to be used for testing purposes

class DummyDataAccess: public ISingletondataAccess
{
    public:
    static DummyDataAccess& getInstance();

    DummyDataAccess(const DummyDataAccess&) = delete;
    DummyDataAccess& operator=(const DummyDataAccess&) = delete;

    void parseFile() override;
    void printData();
    inline const map<unsigned, string>& getData() const {return mData;}

    protected:
    DummyDataAccess() = default;

    private:
    map<unsigned, string> mData;
    const string mFilename{"C:\\Users\\scretu\\VisualCodeProjects\\DesignPatterns\\Creational\\Singleton\\dummy.txt"};    
};

DummyDataAccess& DummyDataAccess::getInstance()
{
    static DummyDataAccess uniqueInstance{};

    return uniqueInstance;
}

void DummyDataAccess::parseFile()
{
    //create dummy data
    mData[3] = "fciwufh";
    mData[7] = ";{}';";
    mData[2] = "qwweerrt";
    mData[4] = "skldkfjhf";
    mData[200] = "long";

    //open the file with automatically assumed ios::out from ostream
    ofstream outputFileStream(mFilename);

    if(outputFileStream.is_open())
    {
        for(auto& elem: mData)
        {
            outputFileStream << elem.first <<" "<<elem.second<<endl;
        }

        cout<<"Data written to dummy file"<<endl;
        outputFileStream.close();
        mData.clear();
    }


    //open the created file with automatically assumed ios::in from istream
    std::ifstream inputFileStream(mFilename);
    string line;
    unsigned key;

    if(inputFileStream.is_open())
    {
        while(getline(inputFileStream, line))
        {
            stringstream inputStringStream(line);
            inputStringStream >> key >> mData[key];
        }

        inputFileStream.close();
    }
    else
    {
        cout<<"file is not open"<<endl;
    }
}

void DummyDataAccess::printData()
{
    for(auto& elem : mData)
        cout<<elem.first<<" "<<elem.second<<endl;
}