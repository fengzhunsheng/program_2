#pragma once

#include<iostream>

template<typename T>
class Shared_ptr
{
private:
    T *_ptr;
    int *_count;

public:
    Shared_ptr(T* ptr = nullptr):_ptr(ptr),_count(new int(1))
    {}

    Shared_ptr(const Shared_ptr& s):_ptr(s._ptr),_count(s._count)
    {
        (*_count)++;
    }

    Shared_ptr<T>& operator=(const Shared_ptr& s)
    {
        if(this->_ptr != s._ptr)
        {
            (*(this->_count))--;;
            if(*(this->_count) == 0)
            {
                delete this->_ptr;
                this->_ptr = nullptr;
                delete this->_count;
                this->_count = nullptr;
            }

            this->_ptr = s._ptr;
            this->_count = s._count;

            (*(this->_count))++;
        }
        return *this;
    }

    T& operator*()
    {
        return *(this->_ptr);
    }

    T* operator->()
    {
        return this->_ptr;
    }

    ~Shared_ptr()
    {
        (*(this->_count))--;
        if(*(this->_count) == 0)
        {
            delete this->_ptr;
            this->_ptr = nullptr;
            delete this->_count;
            this->_count = nullptr;
        }
    }

    void ptrint_count()
    {
        std::cout << *(this->_count) << std::endl;
    }
};