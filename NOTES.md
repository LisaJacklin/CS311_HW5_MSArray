Below is a header file `tmsarray.hpp` which provides the implementation of the `TMSArray` class template as per the specifications given. 

```cpp
// tmsarray.hpp
// Author: US
// Last revision date: 2023-11-04
// Purpose: Header for class template TMSArray

#ifndef TMSARRAY_HPP
#define TMSARRAY_HPP

#include <algorithm> // For std::copy, std::move
#include <cstddef>   // For std::size_t
#include <iterator>  // For std::distance
#include <stdexcept> // For std::out_of_range
#include <utility>   // For std::swap

// Class invariant: _array points to an allocated array of _size elements, except when _size is 0
// Class invariant: _size is always equal to the number of elements the array is meant to hold

template<typename Val>
class TMSArray {
public:
    // Public member types
    using value_type = Val;
    using size_type = std::size_t;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    // Constructors and Destructor
    TMSArray() noexcept : _array(nullptr), _size(0) {} // Default ctor
    explicit TMSArray(size_type size); // Ctor from size
    TMSArray(const TMSArray& other); // Copy ctor
    TMSArray(TMSArray&& other) noexcept; // Move ctor
    ~TMSArray() noexcept; // Destructor

    // Assignment Operators
    TMSArray& operator=(const TMSArray& other); // Copy assignment
    TMSArray& operator=(TMSArray&& other) noexcept; // Move assignment

    // Access Operators
    Val& operator[](size_type index);
    const Val& operator[](size_type index) const;

    // Size Operations
    size_type size() const noexcept;
    bool empty() const noexcept;

    // Modifiers
    void resize(size_type newSize);
    iterator insert(iterator pos, const value_type& value);
    iterator erase(iterator pos);
    void push_back(const value_type& value);
    void pop_back();
    void swap(TMSArray& other) noexcept;

    // Iterators
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

private:
    value_type* _array;
    size_type _size;

    void allocateAndCopy(size_type newSize);
    void deallocate() noexcept;
};

// All member function definitions follow here, as it is a class template
// ...

#endif // TMSARRAY_HPP
```

__You would continue to implement all the member functions within this header file since the class is a template and should be entirely defined in a header.__ Below is an example of how you might define a few of the member functions inline within the header file.

```cpp
template<typename Val>
TMSArray<Val>::TMSArray(size_type size) : _size(size) {
    _array = _size ? new value_type[_size]() : nullptr;
}

template<typename Val>
TMSArray<Val>::TMSArray(const TMSArray& other) : _size(other._size) {
    _array = _size ? new value_type[_size] : nullptr;
    std::copy(other._array, other._array + _size, _array);
}

template<typename Val>
TMSArray<Val>::TMSArray(TMSArray&& other) noexcept : _array(other._array), _size(other._size) {
    other._array = nullptr;
    other._size = 0;
}

template<typename Val>
TMSArray<Val>::~TMSArray() noexcept {
    delete[] _array;
}

// ... Additional member function definitions ...

// Note: Exception safety and any other important class behaviors or invariants should be documented in comments above each function.
```

It is important to follow the exception safety guarantees and make sure that the move operations do not throw exceptions. Implement all the functions in an exception-safe way, providing at least the basic guarantee, and ensure exception neutrality by allowing the exceptions from value type operations to propagate. Make sure to handle all edge cases like an empty array for `pop_back` and invalid iterators for `erase`.
