#ifndef MitFlat_DataFormats_Utils_h
#define MitFlat_DataFormats_Utils_h

#include "Rtypes.h"

namespace flatutils {

  template<class T>
  void
  shiftAddr(T*& addr, Int_t shift)
  {
    reinterpret_cast<char*&>(addr) += shift;
  }

  template<class T>
  void
  shiftAddr(T const*& addr, Int_t shift)
  {
    reinterpret_cast<char const*&>(addr) += shift;
  }

  template<class T>
  class iterator {
    typedef iterator<T> selftype;
    typedef T* pointer;
    typedef T& reference;
  public:
    iterator() {}
    iterator(pointer p, UInt_t s) : ptr(p), size(s) {}
    selftype& operator++() { shiftAddr(ptr, size); return *this; }
    selftype operator++(int) { auto itr(*this); shiftAddr(ptr, size); return itr; }
    selftype& operator--() { shiftAddr(ptr, -size); return *this; }
    selftype operator--(int) { auto itr(*this); shiftAddr(ptr, -size); return itr; }
    selftype& operator+=(int n) { shiftAddr(ptr, size * n); return *this; }
    selftype& operator-=(int n) { shiftAddr(ptr, -size * n); return *this; }
    selftype operator+(int n) { auto itr(*this); itr += n; return itr; }
    selftype operator-(int n) { auto itr(*this); itr -= n; return itr; }
    reference operator*() { return *ptr; }
    pointer operator->() { return ptr; }
  private:
    pointer ptr{0};
    UInt_t const size{0};
  };

  template<class T>
  class const_iterator {
    typedef const_iterator<T> selftype;
    typedef T const* pointer;
    typedef T const& reference;
  public:
    const_iterator() {}
    const_iterator(pointer p, UInt_t s) : ptr(p), size(s) {}
    selftype& operator++() { shiftAddr(ptr, size); return *this; }
    selftype operator++(int) { auto itr(*this); shiftAddr(ptr, size); return itr; }
    selftype& operator--() { shiftAddr(ptr, -size); return *this; }
    selftype operator--(int) { auto itr(*this); shiftAddr(ptr, -size); return itr; }
    selftype& operator+=(int n) { shiftAddr(ptr, size * n); return *this; }
    selftype& operator-=(int n) { shiftAddr(ptr, -size * n); return *this; }
    selftype operator+(int n) { auto itr(*this); itr += n; return itr; }
    selftype operator-(int n) { auto itr(*this); itr -= n; return itr; }
    reference operator*() { return *ptr; }
    pointer operator->() { return ptr; }
  private:
    pointer ptr{0};
    UInt_t const size{0};
  };

}

#endif
