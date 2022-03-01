#pragma once

template<class T>
class Iterator
{
    private:
    T* currentElem;

    public:
    Iterator(T* startPtr):currentElem{startPtr}{};

    Iterator(const Iterator& it)
    {
        currentElem = it.currentElem;
    }

    Iterator& operator=(const Iterator& it)
    {
        currentElem = it.currentElem;
        return *this;
    }

    Iterator& operator=(T* it)
    {
        currentElem = it;
        return *this;
    }

    bool operator!=(const Iterator& it)
    {
        return currentElem != it.currentElem;
    }

    Iterator& operator++()
    {
        ++currentElem;

        return *this;
    }

    T operator*(){return *currentElem;};

};

