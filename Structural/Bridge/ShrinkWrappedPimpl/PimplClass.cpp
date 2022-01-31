#include "PimplClass.hpp"

#include <iostream>
#include <utility>
#include <tuple>

using namespace std;

class PimplClass::PimplClassImpl
{
    public:
    PimplClassImpl() = default;
    ~PimplClassImpl() = default;

    template<class...Args>
    PimplClassImpl(const tuple<Args...>& ); 

    PimplClassImpl(const PimplClassImpl& obj) = delete;
    PimplClassImpl& operator=(const PimplClassImpl& obj) = delete;

    void addData(std::string value);
    void printData();

    private:
    std::map<unsigned, std::string> mData;
    const int& mRefToMockIFace;
};

//calls template<class...Args> ShrinkWrappedPimpl c-tor which will forward the Args... as tuple
//thus calling template<class...Args> PimplClassImpl(const tuple<Args...>& )
PimplClass::PimplClass(int&& refToMockIface):impl{std::forward<int>(refToMockIface)}
{

}

PimplClass::~PimplClass() = default;

void PimplClass::addData(const std::string& value)
{
    impl->addData(move(value));
}

void PimplClass::printData()
{
    impl->printData();
}

//Impl part

template<class...Args>
PimplClass::PimplClassImpl::PimplClassImpl(const tuple<Args...>& args):mRefToMockIFace(get<0>(args))
{
}

void PimplClass::PimplClassImpl::addData(std::string value)
{
    static unsigned key{0};

    mData.emplace(make_pair<unsigned, std::string>(key++, move(value)));
}

void PimplClass::PimplClassImpl::printData()
{
    for(auto&& keyVal : mData)
        cout<<keyVal.first<<" "<<keyVal.second<<endl;
}