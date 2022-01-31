#pragma once

#include "ShrinkWrappedPimpl.hpp"
#include <map>
#include <string>

class PimplClass
{
    public:
    PimplClass() = default;
    PimplClass(int&& refToMockIface);
    //needs to be implemented in source code file
    ~PimplClass();

    PimplClass(const PimplClass& obj) = delete;
    PimplClass& operator=(const PimplClass& obj) = delete;

    void addData(const std::string& value);
    void printData();

    private:
    class PimplClassImpl;
    ShrinkWrappedPimpl<PimplClassImpl> impl;
};
