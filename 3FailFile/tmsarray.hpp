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

//-------------------------------------------------------------
// Required Headers and Linkers
//-------------------------------------------------------------

#include <algorithm> // For std::copy, std::rotate, std::swap, std::min
#include <cstddef>   // For std::size_t

//-------------------------------------------------------------
//Beginning of Class Template TMSArray
//-------------------------------------------------------------

// class TMSArray
// Template for a Marvelously Smart Array.
// Resizable, copyable/movable, exception-safe.
template <typename ValueType>
class TMSArray {

//-------------------------------------------------------------
// ***** TMSArray: types ****
//-------------------------------------------------------------
public:
    using size_type = std::size_t;
    using value_type = ValueType;
    using iterator = value_type *;
    using const_iterator = const value_type *;

//-------------------------------------------------------------
// ***** TMSArray:Constructors, Deconstructor, Operations *****
//-------------------------------------------------------------
public:
    // Default ctor and ctor from size
    explicit TMSArray(size_type thesize = 0)
        : _size(thesize), _data(new value_type[thesize]) {}

    // Copy constructor
    //COMMENT AND FIX
        //TMSArray(const TMSArray & other)
        //    : _size(other._size), _data(new value_type[_size])
        //{
        //    //using STL copy from Algorithm
        //    //we can simply make a whole new copy from the original
        //    std::copy(other.begin(), other.end(), begin());
        //}
    TMSArray(const TMSArray & other)
    try : _size(other._size), _data(new value_type[_size]) 
    {
        std::copy(other.begin(), other.end(), begin());
    } catch(...) {
        delete [] _data;
        throw;
    }
    

    // Move constructor
    //COMMENTS PLSSSS
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

//-------------------------------------------------------------
// ***** TMSArray: general public operators *****
//-------------------------------------------------------------
public:
    //[] Operators
    value_type & operator[](size_type index)
    {     
        return _data[index];
       // Access violation error checking should be handled externally
    }
    const value_type & operator[](size_type index) const
    {
        return _data[index];
        // Access violation error checking should be handled externally
    }

    //size operator
    size_type size() const
    {
        return _size;
    }

    //empty operator
    bool empty() const
    {
        return size() == 0;
    }

    //begining iterator
    iterator begin()
    {
        return _data;
    }
    const_iterator begin() const
    {
        return _data;
    }

    //ending iterator
    iterator end()
    {
        return begin() + size();
    }
    const_iterator end() const
    {
        return begin() + size();
    }

    //resize Function
        //COMMENT AND FIX
        //void resize(size_type newsize)
        //{
        //    if (newsize != _size) { // Resize only if the new size is different
        //        TMSArray temp(newsize);// Create a temporary TMSArray with the new size
        //        std::copy(begin(), begin() + std::min(_size, newsize), temp._data); // Copy the data
        //        swap(temp); // Swap the temporary array with the current array
        //    } 
        //    // Note: The destructor of temp will deallocate the old array memory.
        //}
    void resize(size_type newsize)
    {
        if (newsize > _size) { // Resize only if the new size is larger
            TMSArray temp(newsize); // Create a temporary TMSArray with the new size
            std::copy(begin(), end(), temp.begin()); // Copy the existing data
            swap(temp); // Swap the temporary array with the current array
        } else if (newsize < _size) {
            // For shrinking, we can simply update the size and not touch the memory.
            // The unused space will be handled when the destructor is called or if
            // the next resize increases the size of the array again.
            _size = newsize;
        }
        // If newsize == _size, do nothing.
    }


    //Insert Iterator
    //COMMENT AND FIX
    iterator insert(iterator pos, const value_type & value)
    {
        if (pos == end()) { // Special case for inserting at the end
            push_back(value); // Use push_back to minimize reallocation logic
            return end() - 1; // Return the iterator to the new element
        } else {
            size_type index = pos - begin();
            resize(size() + 1); // Increase the size by one before inserting
            iterator newPos = begin() + index; // Find the new position for inserting
            std::move_backward(newPos, end() - 1, end()); // Shift elements to the right
            *newPos = value; // Insert the value
            return newPos; // Return the position where the value was inserted
        }
    }

    //Erase Iterator
    //COMMENT AND FIX
        //iterator erase(iterator pos)
        //{
        //    if (pos < end()) { // Check if pos is within the bounds
        //        std::move(pos + 1, end(), pos); // Shift elements to the left
        //        resize(size() - 1); // Decrease the size by one after erasing
        //    }
        //    return pos; // Return the position following the last removed element
        //}
    iterator erase(iterator pos)
    {
        if (pos < end()) {
            std::move(pos + 1, end(), pos);
            --_size; // Just decrease the size, no need for reallocate
        }
        return pos;
    }

    //push-back function
    //COMMENT AND FIX  
        //void push_back(const value_type & value)
        //{
        //  if (_size == 0) {
        //    // Handle going from 0 to 1 element.
        //    resize(1);
        //  } else {
        //    // Allocate more space to avoid frequent reallocations.
        //    resize(_size + 1);
        //  }
        //  _data[_size - 1] = value;
        //}
    void push_back(const value_type & value)
    {
        // If there's enough space, we can simply add the new element.
        if (_size == 0) {
            resize(1);
            _data[0] = value;
        } else {
            // We need to check if we have extra space to avoid reallocation
            // on every push_back. If not, then only we resize.
            // If you had a member tracking capacity, you'd check it here.
            resize(_size + 1);
            _data[_size - 1] = value; // Note that _size has already been increased by resize
        }
    }

  
    void pop_back()
    {
        if (_size > 0) {
          // Just decrease the size by 1 without reallocation.
          --_size;
      }
        // No need to deallocate memory since resize handles it.
    }

    void swap(TMSArray & other) noexcept
    {
        using std::swap;
        swap(_size, other._size); // Swap the sizes
        swap(_data, other._data); // Swap the pointers to the data
    }

//-------------------------------------------------------------
// ***** TMSArray: data members *****
//-------------------------------------------------------------
private:
    size_type _size;
    value_type *_data;

};  // End class TMSArray

#endif  //#ifndef FILE_TMSARRAY_HPP_INCLUDED
