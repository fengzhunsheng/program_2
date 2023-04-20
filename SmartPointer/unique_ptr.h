#pragma once

#include<iostream>
using std::move;
using std::forward;
using std::cout;
using std::endl;
using std::swap;

template<typename T>
class Unique_ptr
{
private:
    T *_ptr;

public:
    Unique_ptr():_ptr(nullptr)
    {
        cout << "construct for None" << endl;
    }

    explicit Unique_ptr(T* ptr):_ptr(ptr)
    {
        cout << "construct for T*" << endl;
    }

    ~Unique_ptr()
    {
        
        if(_ptr != nullptr)
        {
            cout << "destruct Unique_ptr: no nullptr" << endl;
            delete _ptr;
            _ptr = nullptr;
        }
        else{
            cout << "destruct Unique_ptr: nullptr" << endl;
        }
        
    }

    Unique_ptr(const Unique_ptr&) = delete;
    Unique_ptr& operator=(const Unique_ptr&) = delete;

public:
    Unique_ptr(Unique_ptr&& s)
    {
        cout << "construct for Unique_ptr&&" << endl;
        this->_ptr = forward<T*>(s._ptr);
        s._ptr = nullptr;
    }
    
    Unique_ptr& operator=(Unique_ptr&& s)
    {
        cout << "operate= for Unique_ptr&&" << endl;
        if(this->_ptr != nullptr)
        {
            delete this->_ptr;
        }
        this->_ptr = forward<T*>(s._ptr);
        s._ptr = nullptr;
        return *this;
    }

    void reset(T* ptr)
    {
        if(ptr == nullptr)
        {
            throw std::invalid_argument("A invalid pointer");
        }

        delete this->_ptr;
        this->_ptr = ptr;
    }

    T* operator->()
    {
        return this->_ptr;
    }

    T& operator*()
    {
        return *(this->ptr);
    }
};