// msarray.hpp  UNFINISHED
// Glenn G. Chappell
// 2023-10-17
//
// For CS 311 Fall 2023
// Header for class MSArray
// Marvelously smart array of int
// Preliminary to Assignment 5

#ifndef FILE_MSARRAY_HPP_INCLUDED
#define FILE_MSARRAY_HPP_INCLUDED


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
//
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
        : _size(thesize),
        _data(new value_type[thesize])
    {}

    MSArray(size_type thesize=0)
    {}

    MSArray(const MSArray & other)
    {
        //TODO: WRITE THIS
    }

    MSArray(MSArray && other) noexcept
    {
        //TODO: WRITE THIS
    }

    ~MSArray()
    {
        //it has current obj has respons to destrct this cause the obj owns it, think in terms of RAII
        delete [] _data;
    }

    MSArray & operator=(const MSArray & other)
    {
        //TODO: WRITE THIS
        return *this;
    }

    MSArray & operator=(MSArray && other) noexcept
    {
        //TODO: WRITE THIS
        //move is like a destructive copy
        return *this;
    }

// ***** MSArray: general public operators *****
public:
    value_type & operator[](size_type index)
    {
        
        return _data[index]; //*(_data+ index) take pointer and dereference it would be okay too
    }
    const value_type & operator[](size_type index) const
    {
        return _data[index]; //
    }
    size_type size() const
    {
        return size;
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
    }
    iterator insert(iterator pos,
                    value_type value) // we pass by value, but for when we do it we pass by reference to const
    {
        //write me
        return pos;
    }
    iterator erase(iterator pos)
    {
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

    }
// ***** MSArray: general public functions *****
public:


// ***** MSArray: data members *****
private:
    size_type _size;
    value_type *_data;

};  // End class MSArray


#endif  //#ifndef FILE_MSARRAY_HPP_INCLUDED

