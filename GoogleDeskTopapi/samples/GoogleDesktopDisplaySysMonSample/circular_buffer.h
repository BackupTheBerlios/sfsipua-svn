// Copyright 2003-2005 Google, Inc.
// All Rights Reserved. 
//
// circular_buffer.h - simple circular buffer class template.
// 
// Circular buffers are initialized to a fixed length.  New elements
// are added onto the end using add().  When the buffer fills up,
// adding a new element causes the oldest element to fall off the front.
// Elements can also be pulled off the front explicitly using remove().
//
// NB: If the elements placed in the circular buffer are class objects
// (as opposed to pointers), you may need to define the following:
//
//    - a no-arguments constructor (this will be called to fill up
//      the buffer initially)
//
//    - an overloaded '=' operator (this will be used to assign a new object
//      into an old object in the buffer -- only needed, of course,
//      if the default '=' will not suffice)
//
// Example usage:
//
// --------------------
//
// #include <iostream>
// #include "common/circular_buffer.h"
//
// int main() {
//   const int n = 5;
//   CircularBuffer<string> cb(n);
//   string tok;
//
//   // Read tokens from cin until EOF
//   while ((cin >> tok) != NULL) cb.add(tok);
//
//   // Print last n tokens starting with oldest
//   for (int i = 0; i < cb.size(); ++i) cout << cb.at(i) << endl;
//
//   return 0;
// }
//
// --------------------

#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

template <class T>
class CircularBuffer {
 private:

  // ---------- Class members  -----------------------------------------

  T *elements_;                     // pointer to array of elements in buffer
  const uint32 size_;                  // declared length of buffer
  uint32 first_;                       // index of first element in buffer
  uint32 num_filled_;                  // number of elements currently in buffer

  CircularBuffer(const CircularBuffer&);
  CircularBuffer &operator=(const CircularBuffer&);

 public:

  explicit CircularBuffer(uint32 size) :
    elements_(NULL), size_(size), first_(0), num_filled_(0) {
    if (size > 0)
      elements_ = new T[size];
  }

  ~CircularBuffer() {
    delete [] elements_;
  }

 private:

  // Return the index in the elements_ array corresponding
  // to the given "logical position".
  // Logical position 0 corresponds to index first_ in elements_, etc.
  // The logical position i must be in [0, size_]. 
  inline uint32 internal_index(uint32 i) const {
    ATLASSERT (i <= size_);

    // Faster than using "%" operator.
    uint32 elt_i = first_ + i;
    if (elt_i >= size_) elt_i -= size_;
    return elt_i;
  }

 public:

  // Return the number of elements currently stored in the buffer.
  uint32 size() const { return num_filled_; }

  uint32 capacity() const { return size_; }

  // Return true iff the buffer is empty.
  bool empty() const { return (num_filled_ == 0); }

  // Return true iff the buffer is full.
  bool full() const { return (num_filled_ == size_); }

  // As a side effect, add an element onto the end of the buffer.
  // Return true iff an element was overwritten in the process.
  bool add(const T& elt) {
    ATLASSERT (size_ > 0);

    elements_[internal_index(num_filled_)] = elt;

    if (num_filled_ < size_) {
      // Still extra room in buffer
      ++num_filled_;
      return false;
    } else {
      // Buffer is full
      first_ = internal_index(1);   // incr first_ from logical 0 to logical 1
      return true;
    }
  }

  // Return first element from front of buffer.
  // As a side effect, delete it from the buffer.
  // Return by value, because the object itself will be overwritten 
  T remove() {
    ASSERT (num_filled_ > 0, (L""));

    uint32 elt_i = first_;
    first_ = internal_index(1);  // incr first_ from logical 0 to logical 1
    --num_filled_;

    // Do not call destructor on element just deleted --
    // this is deferred until the whole CircularBuffer is deleted.
    return elements_[elt_i];
  }

  // Return the nth element in the buffer.
  // Return by value, because the object itself will be overwritten 
  // when we wrap around.
  // at() is used from the snippet code, but it's not showing up as a
  // significant cost in the Quantify runs.  If it starts showing up,
  // we can return references instead of doing a copy.
  T at(uint32 n) const { 
    ATLASSERT (n < num_filled_);

    return elements_[internal_index(n)];
  }

  // Set the element at a position.
  void set(uint32 n, const T &elt) {
    ATLASSERT (n < num_filled_);

    elements_[internal_index(n)] = elt;
  }

  // Reset the buffer to be empty.  We simply set num_filled_ to 0 --
  // we don't actually delete anything.
  void clear() {
    num_filled_ = 0;
  }

};

#endif  // CIRCULARBUFFER_H
