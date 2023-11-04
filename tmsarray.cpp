// msarray.cpp  HAND-OFF
// Lisa Jacklin && Jewel Maldonado
// 2023-11-01
//
// For CS 311 Fall 2023
// Source for class MSArray
// Marvelously smart array of int
// Preliminary to Assignment 5

#include "tmsarray.hpp" // For class MSArray definition

// *********************************************************************
// class MSArray - Member function definitions
// *********************************************************************

// Copy ctor
// See header for info.
MSArray::MSArray(const MSArray &other)
    : _capacity(other._capacity), _size(other.size()),
      _data(other._capacity == 0 ? nullptr : new value_type[other._capacity]) {

  if (other._capacity != 0) {
    try {
      std::copy(other.begin(), other.end(), begin());
    } catch (...) {
      delete[] _data;
      throw;
    }
  }
  // The above call to std::copy does not throw, since it copies int
  // values. But if value_type is changed, then the call may throw, in
  // which case this copy ctor may need to be rewritten.
}

// Move ctor
// See header for info.
MSArray::MSArray(MSArray &&other) noexcept
    : _capacity(other._capacity), _size(other._size), _data(other._data) {
  other._capacity = 0;
  other._size = 0;
  other._data = nullptr;
}

// Copy assignment operator
// See header for info.
MSArray &MSArray::operator=(const MSArray &other) {
  // TODO: WRITE THIS!!!
  return *this; // DUMMY
}

// Move assignment operator
// See header for info.
MSArray &MSArray::operator=(MSArray &&other) noexcept {
  // TODO: WRITE THIS!!!
  return *this; // DUMMY
}

// resize
// See header for info.
void MSArray::resize(MSArray::size_type newsize) {
  // TODO: WRITE THIS!!!
}

// insert
// See header for info.
MSArray::iterator MSArray::insert(MSArray::iterator pos,
                                  MSArray::value_type item) {
  // TODO: WRITE THIS!!!
  return begin(); // DUMMY
}

// erase
// See header for info.
MSArray::iterator MSArray::erase(MSArray::iterator pos) {
  // TODO: WRITE THIS!!!
  return begin(); // DUMMY
}

// swap
// See header for info.
void MSArray::swap(MSArray &other) noexcept {
  // TODO: WRITE THIS!!!
  std::swap(_data, other._data);
  std::swap(_size, other._size);
  std::swap(_capacity, other._capacity);
}
