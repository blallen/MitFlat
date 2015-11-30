#ifndef MitFlat_DataFormats_Utils_h
#define MitFlat_DataFormats_Utils_h

#include "Rtypes.h"

#include <vector>

class TString;
class TTree;

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

  template<class C>
  class const_iterator;

  template<class C>
  class iterator {
    friend class const_iterator<C>;

    typedef iterator<C> self_type;
    typedef typename C::pointer pointer;
    typedef typename C::reference& reference;
  public:
    iterator() {}
    iterator(void* p, UInt_t objSize) : ptr(static_cast<pointer>(p)), size(objSize) {}
    self_type& operator++() { shiftAddr(ptr, size); return *this; }
    self_type operator++(int) { auto itr(*this); shiftAddr(ptr, size); return itr; }
    self_type& operator--() { shiftAddr(ptr, -size); return *this; }
    self_type operator--(int) { auto itr(*this); shiftAddr(ptr, -size); return itr; }
    self_type& operator+=(int n) { shiftAddr(ptr, size * n); return *this; }
    self_type& operator-=(int n) { shiftAddr(ptr, -size * n); return *this; }
    self_type operator+(int n) { auto itr(*this); itr += n; return itr; }
    self_type operator-(int n) { auto itr(*this); itr -= n; return itr; }
    bool operator==(self_type const& rhs) { return ptr == rhs.ptr; }
    bool operator!=(self_type const& rhs) { return ptr != rhs.ptr; }
    reference operator*() { return *ptr; }
    pointer operator->() { return ptr; }
  private:
    pointer ptr{0};
    UInt_t const size{0}; // needed to properly iterate over derived-class array using base-class iterator
  };

  template<class C>
  class const_iterator {
    typedef const_iterator<C> self_type;
    typedef iterator<C> mutable_type;
    typedef typename C::const_pointer pointer;
    typedef typename C::const_reference& reference;
  public:
    const_iterator() {}
    const_iterator(void* p, UInt_t objSize) : ptr(static_cast<pointer>(p)), size(objSize) {}
    const_iterator(mutable_type const& it) : ptr(it.ptr) {}
    self_type& operator++() { shiftAddr(ptr, size); return *this; }
    self_type operator++(int) { auto itr(*this); shiftAddr(ptr, size); return itr; }
    self_type& operator--() { shiftAddr(ptr, -size); return *this; }
    self_type operator--(int) { auto itr(*this); shiftAddr(ptr, -size); return itr; }
    self_type& operator+=(int n) { shiftAddr(ptr, size * n); return *this; }
    self_type& operator-=(int n) { shiftAddr(ptr, -size * n); return *this; }
    self_type operator+(int n) { auto itr(*this); itr += n; return itr; }
    self_type operator-(int n) { auto itr(*this); itr -= n; return itr; }
    bool operator==(self_type const& rhs) { return ptr == rhs.ptr; }
    bool operator==(mutable_type const& rhs) { return ptr == rhs.ptr; }
    bool operator!=(self_type const& rhs) { return ptr != rhs.ptr; }
    bool operator!=(mutable_type const& rhs) { return ptr != rhs.ptr; }
    reference operator*() { return *ptr; }
    pointer operator->() { return ptr; }
  private:
    pointer ptr{0};
    UInt_t const size{0}; // needed to properly iterate over derived-class array using base-class iterator
  };

  typedef std::vector<TString> BranchList;

  Bool_t branchIn(TString const& bName, BranchList const&);
  BranchList subBranchList(BranchList const&, TString const& objName);

  Int_t setStatus(TTree&, TString const& objName, TString const& bName, Bool_t status, BranchList const&, Bool_t whitelist = kTRUE);
  Int_t setStatusAndAddress(TTree&, TString const& objName, TString const& bName, void* bPtr, BranchList const&, Bool_t whitelist = kTRUE);
  Int_t book(TTree&, TString const& objName, TString const& bName, TString const& size, char lType, void* bPtr, BranchList const&, Bool_t whitelist = kTRUE);
}

#endif
