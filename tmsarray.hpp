// tmsarray.hpp
// Lisa Jacklin && Jewel Maldonado
// 2023-11-01
//
// For CS 311 Fall 2023
// Header for template class TMSArray
// Template for a Marvelously Smart array
// Assignment 5

#ifndef FILE_TMSARRAY_HPP_INCLUDED
#define FILE_TMSARRAY_HPP_INCLUDED

#include <algorithm> // For std::copy, std::rotate, std::swap, std::min
#include <cstddef>   // For std::size_t

// class TMSArray
// Template for a Marvelously Smart Array.
// Resizable, copyable/movable, exception-safe.
template <typename ValueType>
class TMSArray {

// ***** TMSArray: types *****
public:
    using size_type = std::size_t;
    using value_type = ValueType;
    using iterator = value_type *;
    using const_iterator = const value_type *;

// ***** TMSArray: ctors, op=, dctor *****
public:
    // Default ctor and ctor from size
    explicit TMSArray(size_type thesize = 0)
        : _size(thesize), _data(new value_type[thesize]) {}

    // Copy constructor
    TMSArray(const TMSArray & other)
        : _size(other._size), _data(new value_type[_size])
    {
        std::copy(other.begin(), other.end(), begin());
    }

    // Move constructor
    TMSArray(TMSArray && other) noexcept
        : _size(other._size), _data(other._data)
    {
        other._size = 0;
        other._data = nullptr;
    }

    // Destructor
    ~TMSArray()
    {
        delete [] _data;
    }

    // Copy assignment operator
    TMSArray & operator=(const TMSArray & other)
    {
        if (this != &other) {
            TMSArray temp(other); // Copy-and-swap idiom
            swap(temp);
        }
        return *this;
    }

    // Move assignment operator
    TMSArray & operator=(TMSArray && other) noexcept
    {
        if (this != &other) {
            swap(other);
        }
        return *this;
    }

// ***** TMSArray: general public operators *****
public:
    value_type & operator[](size_type index)
    {     
        return _data[index]; // Access violation error checking should be handled externally
    }

    const value_type & operator[](size_type index) const
    {
        return _data[index]; // Access violation error checking should be handled externally
    }

    size_type size() const
    {
        return _size;
    }

    bool empty() const
    {
        return size() == 0;
    }

    iterator begin()
    {
        return _data;
    }

    const_iterator begin() const
    {
        return _data;
    }

    iterator end()
    {
        return begin() + size();
    }

    const_iterator end() const
    {
        return begin() + size();
    }

    void resize(size_type newsize)
    {
        if (newsize != _size) { // Resize only if the new size is different
            TMSArray temp(newsize); // Create a temporary TMSArray with the new size
            std::copy(begin(), begin() + std::min(_size, newsize), temp._data); // Copy the data
            swap(temp); // Swap the temporary array with the current array
        }
        // Note: The destructor of temp will deallocate the old array memory.
    }

    iterator insert(iterator pos, const value_type & value)
    {
        size_type index = pos - begin();
        resize(size() + 1); // Increase the size by one before inserting
        iterator newPos = begin() + index; // Find the new position for inserting
        std::move_backward(newPos, end() - 1, end()); // Shift elements to the right
        *newPos = value; // Insert the value
        return newPos; // Return the position where the value was inserted
    }

    iterator erase(iterator pos)
    {
        if (pos < end()) { // Check if pos is within the bounds
            std::move(pos + 1, end(), pos); // Shift elements to the left
            resize(size() - 1); // Decrease the size by one after erasing
        }
        return pos; // Return the position following the last removed element
    }

    void push_back(const value_type & value)
    {
        resize(size() + 1); // Increase the size by one before pushing back
        _data[size() - 1] = value; // Add the new value
    }

    void pop_back()
    {
        if (size() > 0) {
            resize(size() - 1); // Decrease the size by one
        }
        // No need to deallocate memory since resize handles it.
    }

    void swap(TMSArray & other) noexcept
    {
        using std::swap;
        swap(_size, other._size); // Swap the sizes
        swap(_data, other._data); // Swap the pointers to the data
    }


// ***** TMSArray: data members *****
private:
    size_type _size;
    value_type *_data;

};  // End class TMSArray

#endif  //#ifndef FILE_TMSARRAY_HPP_INCLUDED
