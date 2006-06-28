#ifndef Common_ProcessNameList_h
#define Common_ProcessNameList_h

#include <string>
#include <vector>

#include "DataFormats/Common/interface/ProcessNameListID.h"

namespace edm {
  class ProcessNameList {
  public:
    typedef std::string value_type;
    typedef std::vector<value_type> collection_type;

    typedef collection_type::iterator       iterator;
    typedef collection_type::const_iterator const_iterator;

    typedef collection_type::reverse_iterator       reverse_iterator;
    typedef collection_type::const_reverse_iterator const_reverse_iterator;

    typedef collection_type::reference reference;
    typedef collection_type::const_reference const_reference;

    typedef collection_type::size_type size_type;

    ProcessNameList() : data_() {}
    explicit ProcessNameList(size_type n) : data_(n) {}
    explicit ProcessNameList(collection_type const& vec) : data_(vec) {}

    void push_back(const_reference t) {data_.push_back(t);}
    void swap(ProcessNameList& other) {data_.swap(other.data_);}
    bool empty() const {return data_.empty();}
    size_type size() const {return data_.size();}
    size_type capacity() const {return data_.capacity();}
    void reserve(size_type n) {data_.reserve(n);}

    reference operator[](size_type i) {return data_[i];}
    const_reference operator[](size_type i) const {return data_[i];}

    reference at(size_type i) {return data_.at(i);}
    const_reference at(size_type i) const {return data_.at(i);}

    const_iterator begin() const {return data_.begin();}
    const_iterator end() const {return data_.end();}

    const_reverse_iterator rbegin() const {return data_.rbegin();}
    const_reverse_iterator rend() const {return data_.rend();}

//     iterator begin() {return data_.begin();}
//     iterator end() {return data_.end();}

//     reverse_iterator rbegin() {return data_.rbegin();}
//     reverse_iterator rend() {return data_.rend();}

    bool operator== (ProcessNameList const& o) const {return data_==o.data_;}

    ProcessNameListID id() const;
  private:
    collection_type data_;
  };

  inline bool operator!= (ProcessNameList const& a, ProcessNameList const& b)
  { return !(a==b); }
}

#endif
