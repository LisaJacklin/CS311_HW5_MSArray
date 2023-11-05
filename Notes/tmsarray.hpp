// msarray.hpp 
// Lisa Jacklin && Jewel Maldonado
// 2023-11-01
//
// For CS 311 Fall 2023
// Header for class MSArray
// Marvelously smart array of int
// Assignment 5

#ifndef FILE_MSARRAY_HPP_INCLUDED
#define FILE_MSARRAY_HPP_INCLUDED

#include <algorithm> // For std::copy, std::move_backward, std::rotate, std::swap
#include <cstddef>   // For std::size_t

class MSArray {
public:
    using size_type = std::size_t;
    using value_type = int;
    using iterator = value_type *;
    using const_iterator = const value_type *;

    // Constructor from size, with optional initialization value
    explicit MSArray(size_type size = 0, value_type init_val = value_type())
        : _size(size), _data(size ? new value_type[size] : nullptr) {
        std::fill(begin(), end(), init_val);
    }

    // Copy constructor
    MSArray(const MSArray & other)
        : _size(other._size), _data(other._size ? new value_type[other._size] : nullptr) {
        std::copy(other.begin(), other.end(), begin());
    }

    // Move constructor
    MSArray(MSArray && other) noexcept
        : _size(other._size), _data(other._data) {
        other._size = 0;
        other._data = nullptr;
    }

    // Destructor
    ~MSArray() {
        delete[] _data;
    }

    // Copy assignment operator
    MSArray & operator=(const MSArray & other) {
        if (this != &other) {
            MSArray temp(other);
            swap(temp);
        }
        return *this;
    }

    // Move assignment operator
    MSArray & operator=(MSArray && other) noexcept {
        swap(other);
        return *this;
    }

    // Subscript operator for non-const objects
    value_type & operator[](size_type index) {
        return _data[index];
    }

    // Subscript operator for const objects
    const value_type & operator[](size_type index) const {
        return _data[index];
    }

    // Returns the size of the array
    size_type size() const {
        return _size;
    }

    // Checks if the array is empty
    bool empty() const {
        return _size == 0;
    }

    // Returns an iterator to the beginning
    iterator begin() {
        return _data;
    }

    // Returns a const iterator to the beginning
    const_iterator begin() const {
        return _data;
    }

    // Returns an iterator to the end
    iterator end() {
        return begin() + _size;
    }

    // Returns a const iterator to the end
    const_iterator end() const {
        return begin() + _size;
    }

    // Resizes the array to the specified size
    void resize(size_type newsize) {
        if (newsize != _size) {
            value_type* newData = newsize ? new value_type[newsize] : nullptr;
            if (_data) {
                std::copy(begin(), begin() + std::min(_size, newsize), newData);
                delete[] _data;
            }
            _data = newData;
            _size = newsize;
        }
    }

    // Inserts an element at the specified position
    iterator insert(iterator pos, value_type value) {
        size_type index = pos - begin();
        resize(_size + 1);
        iterator newPos = begin() + index;
        std::move_backward(newPos, end() - 1, end());
        *newPos = value;
        return newPos;
    }

    // Erases an element at the specified position
    iterator erase(iterator pos) {
        if (pos != end()) {
            std::move(pos + 1, end(), pos);
            resize(_size - 1);
        }
        return pos;
    }

    // Adds an element to the end
    void push_back(value_type value) {
        resize(_size + 1);
        _data[_size - 1] = value;
    }

    // Removes the last element
    void pop_back() {
        if (_size > 0) {
            resize(_size - 1);
        }
    }

    // Swaps the contents of this array with another
    void swap(MSArray & other) noexcept {
        std::swap(_size, other._size);
        std::swap(_data, other._data);
    }

private:
    size_type _size;   // Size of the array
    value_type *_data; // Pointer to the array of elements
};

#endif // #ifndef FILE_MSARRAY_HPP
