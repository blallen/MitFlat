#ifndef MitFlat_DataFormats_Collection_h
#define MitFlat_DataFormats_Collection_h

#include "Utils.h"

#include "TString.h"
#include "TTree.h"

#include <stdexcept>
#include <algorithm>

namespace flatutils {

  template<Bool_t F>
  class BaseCollection {
  public:
    typedef BaseCollection<F> self_type;
    typedef self_type base_type;

    static const Bool_t FIXED{F};

    BaseCollection(TString const& name = "") : name_(name) {}
    BaseCollection(self_type const& src) : name_(src.name_) {}
    virtual ~BaseCollection() {}
    self_type& operator=(self_type const& rhs) { name_ = rhs.name_; return *this; }

    void setName(TString const& name) { name_ = name; }

    UInt_t size() const { return size_; }

  protected:
    BaseCollection(TString const& name, Bool_t) : name_(name) {}

    TString name_;
    UInt_t objSize_{0};
    UInt_t size_{0};
    Char_t* array_{0};
  };

  typedef BaseCollection<kTRUE> StaticCollection;
  typedef BaseCollection<kFALSE> DynamicCollection;

  template<class T, class B>
  class Collection : public B {
  public:
    typedef typename B::base_type base_type;
    typedef Collection<T, B> self_type;
    typedef Collection<T, B> container_type;
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<container_type> iterator;
    typedef flatutils::const_iterator<container_type> const_iterator;

    static const Bool_t FIXED{base_type::FIXED};

    Collection(TString const& name = "");
    Collection(self_type const&);
    ~Collection();
    self_type& operator=(self_type const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(this->base_type::array_, this->base_type::objSize_); }
    const_iterator begin() const { return const_iterator(this->base_type::array_, this->base_type::objSize_); }
    iterator end() { return iterator(this->base_type::array_ + this->base_type::objSize_ * this->base_type::size_, this->base_type::objSize_); }
    const_iterator end() const { return const_iterator(this->base_type::array_ + this->base_type::objSize_ * this->base_type::size_, this->base_type::objSize_); }
    reference front() { return operator[](0); }
    const_reference front() const { return operator[](0); }
    reference back() { return operator[](this->base_type::size_ - 1); }
    const_reference back() const { return operator[](this->base_type::size_ - 1); }
    void push_back(const_reference);
    //    void copy(self_type const& source) { resize(source.size()); std::copy(source.begin(), source.end(), begin()); }
    void copy(self_type const& source) { clear(); for (auto& s : source) push_back(s); }
    void resize(UInt_t size);
    void init();
    void clear();

    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);

    typename value_type::array_data data{};

  protected:
    Collection(TString const&, Bool_t);
  };

  template<class T, class B>
  Collection<T, B>::Collection(TString const& _name) :
    B(_name, kFALSE)
  {
    this->base_type::objSize_ = sizeof(value_type);
    this->base_type::array_ = reinterpret_cast<Char_t*>(std::allocator<value_type>().allocate(data.NMAX));
    Char_t* p(this->base_type::array_);
    for (unsigned iP(0); iP != data.NMAX; ++iP) {
      new (reinterpret_cast<pointer>(p)) value_type(data, iP);
      p += this->base_type::objSize_;
    }

    if (FIXED)
      this->base_type::size_ = data.NMAX;
  }

  template<class T, class B>
  Collection<T, B>::Collection(self_type const& _src) :
    B(_src.base_type::name_, kFALSE)
  {
    this->base_type::objSize_ = sizeof(value_type);
    this->base_type::array_ = reinterpret_cast<Char_t*>(std::allocator<value_type>().allocate(data.NMAX));
    Char_t* p(this->base_type::array_);
    for (unsigned iP(0); iP != data.NMAX; ++iP) {
      new (reinterpret_cast<pointer>(p)) value_type(data, iP);
      reinterpret_cast<pointer>(p)->operator=(_src[iP]);
      p += this->base_type::objSize_;
    }

    if (FIXED)
      this->base_type::size_ = data.NMAX;
  }

  /*protected*/
  template<class T, class B>
  Collection<T, B>::Collection(TString const& _name, Bool_t) :
    B(_name, kFALSE)
  {
  }

  template<class T, class B>
  Collection<T, B>::~Collection()
  {
    if (this->base_type::array_) {
      std::allocator<value_type>().deallocate(reinterpret_cast<pointer>(this->base_type::array_), data.NMAX);
      this->base_type::array_ = 0;
    }
  }

  template<class T, class B>
  Collection<T, B>&
  Collection<T, B>::operator=(self_type const& _rhs)
  {
    this->base_type::operator=(_rhs);

    Char_t* p(this->base_type::array_);
    for (unsigned iP(0); iP != data.NMAX; ++iP) {
      reinterpret_cast<pointer>(p)->operator=(_rhs[iP]);
      p += this->base_type::objSize_;
    }

    return *this;
  }

  template<class T, class B>
  typename Collection<T, B>::reference
  Collection<T, B>::at(UInt_t _idx)
  {
    if (_idx >= this->base_type::size_)
      throw std::out_of_range((this->base_type::name_ + "::at").Data());

    Char_t* p(this->base_type::array_);
    p += _idx * this->base_type::objSize_;

    return *reinterpret_cast<pointer>(p);
  }

  template<class T, class B>
  typename Collection<T, B>::const_reference
  Collection<T, B>::at(UInt_t _idx) const
  {
    if (_idx >= this->base_type::size_)
      throw std::out_of_range((this->base_type::name_ + "::at").Data());
  
    Char_t* p(this->base_type::array_);
    p += _idx * this->base_type::objSize_;

    return *reinterpret_cast<const_pointer>(p);
  }

  template<class T, class B>
  typename Collection<T, B>::reference
  Collection<T, B>::operator[](UInt_t _idx)
  {
    Char_t* p(this->base_type::array_);
    p += _idx * this->base_type::objSize_;

    return *reinterpret_cast<pointer>(p);
  }

  template<class T, class B>
  typename Collection<T, B>::const_reference
  Collection<T, B>::operator[](UInt_t _idx) const
  {
    Char_t* p(this->base_type::array_);
    p += _idx * this->base_type::objSize_;

    return *reinterpret_cast<const_pointer>(p);
  }

  template<class T, class B>
  void
  Collection<T, B>::push_back(const_reference _elem)
  {
    if (FIXED)
      throw std::domain_error((this->base_type::name_ + "::push_back").Data());

    if (this->base_type::size_ == data.NMAX)
      throw std::length_error((this->base_type::name_ + "::push_back").Data());

    (*this)[this->base_type::size_] = _elem;
    ++this->base_type::size_;
  }

  template<class T, class B>
  void
  Collection<T, B>::resize(UInt_t _size)
  {
    if (FIXED)
      throw std::domain_error((this->base_type::name_ + "::resize").Data());

    if (_size > data.NMAX)
      throw std::length_error((this->base_type::name_ + "::resize").Data());
  
    this->base_type::size_ = _size;
  }

  template<class T, class B>
  void
  Collection<T, B>::init()
  {
    if (FIXED) {
      for (iterator itr(begin()); itr != end(); ++itr)
        itr->init();
    }
    else
      clear();
  }

  template<class T, class B>
  void
  Collection<T, B>::clear()
  {
    if (FIXED)
      throw std::domain_error((this->base_type::name_ + "::clear").Data());

    this->base_type::size_ = 0;
  }

  template<class T, class B>
  void
  Collection<T, B>::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
  {
    if (!_tree.GetBranch(this->base_type::name_ + ".size"))
      return;

    if (!FIXED) {
      if (_status || (_whitelist && flatutils::branchIn("size", _branches)))
        _tree.SetBranchStatus(this->base_type::name_ + ".size", _status);
    }

    data.setStatus(_tree, this->base_type::name_, _status, _branches, _whitelist);
  }

  template<class T, class B>
  void
  Collection<T, B>::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
  {
    if (!FIXED)
      flatutils::setStatusAndAddress(_tree, this->base_type::name_, "size", &this->base_type::size_, {"size"}, true);
  
    data.setAddress(_tree, this->base_type::name_, _branches, _whitelist);
  }

  template<class T, class B>
  void
  Collection<T, B>::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
  {
    bool inList(branchIn(this->base_type::name_, _branches));
    if ((_whitelist && !inList) || (!_whitelist && inList))
      return;

    if (!FIXED)
      _tree.Branch(this->base_type::name_ + ".size", &this->base_type::size_, "size/i");

    data.book(_tree, this->base_type::name_, _branches, _whitelist);
  }

}

#endif
