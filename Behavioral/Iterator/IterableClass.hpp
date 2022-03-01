#pragma once

#include "Iterator.hpp"
#include <algorithm>

template<class T>
class IterableClass
{
    private:
    T* mBuffer;
    size_t mLength;
    //index of last added element
    size_t currentIndex;

    public:
    using iterator = Iterator<T>;
    IterableClass(const size_t length):mLength{length}, currentIndex{0}
    {
        mBuffer = new T[length];
    }

    IterableClass(const initializer_list<T>& elements):mLength{elements.size()}, currentIndex{mLength-1}
    {
        mBuffer = new T[mLength];
        copy(elements.begin(), elements.end(), mBuffer);
    }

    ~IterableClass()
    {
        if(mBuffer)
        {
            delete [] mBuffer;
        }
    }

    //perform deep copy
    IterableClass(const IterableClass& source)
    {
        /*
        * If the source element's buffer size differs from this buffer size
        * delete this buffer then allocate new memory for this buffer so it fits the new size
        */
        if(source.mLength != mLength)
        {
            if(mBuffer)
            {
                delete [] mBuffer;
            }
            
            mLength = source.mLength;
            mBuffer = new T[mLength];
        }

        // at this point both this and source buffers lengths should be equal, so just copy the elements
        copy(source.cbegin(), source.cend(), mBuffer);

        currentIndex = mLength - 1;
    }

    IterableClass& operator=(const IterableClass& source)
    {
        //check if it is performed assignment against self using pointer comparison, not object comparison
        if(&source == this)
        {
            return *this;
        }

        /*
        * If the source element's buffer size differs from this buffer size
        * delete this buffer then allocate new memory for this buffer so it fits the new size
        */
        if(source.mLength != mLength)
        {
            if(mBuffer)
            {
                delete [] mBuffer;
            }

            mLength = source.mLength;
            mBuffer = new T[mLength];
        }

        // at this point both this and source buffers lengths should be equal, so just copy the elements
        copy(source.cbegin(), source.cend(), mBuffer);

        currentIndex = mLength - 1;

        return *this;
    }

    IterableClass(IterableClass&& source)
    {
        //firstly erase old resources
        if(mBuffer)
        {
            delete [] mBuffer;
        }

        //then point to the new ones
        mLength = source.mLength;
        mBuffer = source.mBuffer;

        //leave source in well defined state
        source.mBuffer = nullptr;
        source.mLength = 0;

        currentIndex = mLength - 1;
    }

    IterableClass& operator=(IterableClass&& source)
    {
        //check if it is performed move assignment against self using pointer comparison, not object comparison
        if(&source == this)
        {
            return *this;
        }
        //firstly erase old resources
        if(mBuffer)
        {
            delete [] mBuffer;
        }

        //then point to the new ones
        mLength = source.mLength;
        mBuffer = source.mBuffer;

        //leave source in well defined state
        source.mBuffer = nullptr;
        source.mLength = 0;

        currentIndex = mLength - 1;

        return *this;
    }

    //begin and end provide head and tail pointers used for iterating
    T* begin() {return mBuffer;};
    T* end() {return mBuffer + mLength;};
    const T* cbegin() const {return mBuffer;};
    const T* cend() const {return mBuffer + mLength;};

    T* rbegin() {return mBuffer + mLength - 1;};
    T* rend() {return mBuffer-1;};
    const T* crbegin() const {return mBuffer + mLength - 1;};
    const T* crend() const {return mBuffer-1;};

    void addElementBack(const size_t index, const T& value)
    {
        if(index < mLength)
        {
            mBuffer[index] = value;
            ++currentIndex;
        }
        else
        {
            // have another temporary pointer to the old buffer
            T* tempBuffer = mBuffer;
            mBuffer = nullptr;

            //enlarge the buffer and length by 1
            ++mLength;
            mBuffer = new T[mLength];

            copy(tempBuffer, tempBuffer + mLength - 1, mBuffer);
            mBuffer[mLength-1] = value;

            currentIndex = mLength - 1; 
        }
    }

    void addElementsBack(const initializer_list<T>& elements)
    {
        if(elements.size() < mLength)
        {
            for(size_t idx = currentIndex; idx < elements.size(); ++idx)
            {
                mBuffer[idx] = *(elements.begin() + idx - currentIndex);
            }
        }
        else
        {
            // have another temporary pointer to the old buffer
            T* tempBuffer = mBuffer;
            size_t tempLength = mLength;
            mBuffer = nullptr;

            //enlarge the buffer and length by 1
            mLength += elements.size();
            mBuffer = new T[mLength];

            copy(tempBuffer, tempBuffer + tempLength, mBuffer);
            copy(elements.begin(), elements.end(), mBuffer+tempLength);
        }
    }
};

