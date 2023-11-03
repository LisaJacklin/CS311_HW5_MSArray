// msarray.hpp 
// Lisa Jacklin && Jewel Maldonado
// 2023-11-01
//
// For CS 311 Fall 2023
// Header for class MSArray
// Marvelously smart array of int
// Assignment 5

#ifndef FILE_TMSARRAY_HPP_INCLUDED
#define FILE_TMSARRAY_HPP_INCLUDED

// *********************************************************************
//  Includes - cleans up source file
// *********************************************************************
#include <algorithm> //for std::
using std::copy;
#include <cstddef>   //for std::size_t

// *********************************************************************
// class MSArray - Class definition
// *********************************************************************

// class MSArray
// Marvelously Smart Array of int.
// Resizable, copyable/movable, exception-safe.
// Invariants:
// _size >= 0
// _data points to an array of value_type, allocated with new [], owned by *this, holding _size value_type values.
// _data != nullptr iff _size > 0
// fucnitons that do not copy, move swap resize??

class MSArray {

// ***** MSArray: types *****
public:
    using size_type = std::size_t;

    using value_type = int;

    using iterator = value_type *;

    using const_iterator = const value_type *;

// ***** MSArray: ctors, op=, dctor *****
public:
    //default ctor and ctor from size
    explicit MSArray( size_type thesize=0)
        : _size(thesize), _data(new value_type[thesize]) 
       
    {}
    
    MSArray(size_type thesize=0)
    {}

    //copy constructor
    MSArray(const MSArray & other)
    {
        //TODO: WRITE THIS
        _size = other._size;
        _data = new value_type[_size];
        copy(other.begin(), other.end(), begin());
    }

    //move constructor
    MSArray(MSArray && other) noexcept
    {
        //TODO: WRITE THIS
        _size = other._size;
        _data = other._data;
        other._size = 0;
        other._data = nullptr;
    }

    //deconstructor
    ~MSArray()
    {
        //it has current obj has respons to destrct this cause the obj owns it, think in terms of RAII
        delete [] _data;
    }

    //copy assignment operator
    MSArray & operator=(const MSArray & other)
    {
        //TODO: WRITE THIS
         if (this != &other) {
            delete[] _data;
            _size = other._size;
            _data = new value_type[_size];
            copy(other.begin(), other.end(), begin());
        }
        return *this;
    }
    //move assignment operator
    MSArray & operator=(MSArray && other) noexcept
    {
        //TODO: WRITE THIS
        //move is like a destructive copy
          if (this != &other) {
            delete[] _data;
            _size = other._size;
            _data = other._data;
            other._size = 0;
            other._data = nullptr;
        }
        return *this;
    }

// ***** MSArray: general public operators *****
public:
    value_type & operator[](size_type index)
    {     
       if (index >= _size) index = _size -1;
       if (index <0) index = 0;
       
        return _data[index]; //*(_data+ index) take pointer and dereference it would be okay too
    }

    const value_type & operator[](size_type index) const
    {
        if (index >= _size) index = _size -1;
        if (index <0) index = 0;

        return _data[index]; //
    }

    size_type size() const
    {
        return _size;
    }

    bool empty() const
    {
        // write this
        //return _size == 0;
        return size() == 0; // old school says efficieny issue, its making extra function call. but compilers are smart.
        //return false; //dummy
    }

    iterator begin()
    {
        return _data;
    }

    const iterator begin() const
    {
        return _data;
    }

    iterator end()
    {
        return begin() + size();
        //return _data;
    }

    const iterator end() const
    {
        return begin() + size();
    }

    void resize(size_type newsize)
    {
        //write me
         if (newsize != _size) {
            value_type* newData = new value_type[newsize];
            copy(begin(), begin() + std::min(_size, newsize), newData);
            delete[] _data;
            _data = newData;
            _size = newsize;
        }
    }

    iterator insert(iterator pos,
                    value_type value) // we pass by value, but for when we do it we pass by reference to const
    {
        //write me
         size_type index = pos - begin();
        resize(size() + 1);
        iterator newPos = begin() + index;
        std::rotate(newPos, end() - 1, end());
        *newPos = value;
        return newPos;
    }

    iterator erase(iterator pos)
    {
        std::rotate(pos, pos + 1, end());
        resize(size() - 1);
        return pos;
    }

    void push_back(value_type value)
    {
        resize(size() + 1);
        begin()[size()-1] - value;
    }

    void pop_back()
    {
        resize(size() -1);
    }

    void swap(MSArray & other) noexcept //noexcept is a perm property of a function
    {
        std::swap(_size, other._size);
        std::swap(_data, other._data);
    }
// ***** MSArray: general public functions *****
public:


// ***** MSArray: data members *****
private:
    size_type _size;
    value_type *_data;

};  // End class MSArray


#endif  //#ifndef FILE_TMSARRAY_HPP_INCLUDED

