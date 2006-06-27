#ifndef Common_ProcessNameList_h
#define Common_ProcessNameList_h

#include <string>
#include <vector>
namespace edm {
  class ProcessNameList {
  public:
    typedef std::string value_type;
    typedef std::vector<std::string>::const_iterator const_iterator;
    typedef std::vector<std::string>::const_reverse_iterator const_reverse_iterator;
    typedef std::vector<std::string>::size_type size_type;
    ProcessNameList() : data_() {}
    explicit ProcessNameList(size_type n) : data_(n) {}
    explicit ProcessNameList(std::vector<std::string> const& vec) : data_(vec) {}
    ~ProcessNameList() {}
    void push_back(std::string const& t) {data_.push_back(t);}
    void swap(ProcessNameList& other) {data_.swap(other.data_);}
    ProcessNameList& operator=(ProcessNameList const& rhs) {
      ProcessNameList temp(rhs);
      this->swap(temp);
      return *this;
    }
    bool empty() const {return data_.empty();}
    size_type size() const {return data_.size();}
    size_type capacity() const {return data_.capacity();}
    void reserve(size_type n) {data_.reserve(n);}
    std::string& operator[](size_type i) {return data_[i];}
    std::string const& operator[](size_type i) const {return data_[i];}
    std::string& at(size_type i) {return data_.at(i);}
    std::string const& at(size_type i) const {return data_.at(i);}
    const_iterator begin() const {return data_.begin();}
    const_iterator end() const {return data_.end();}
    const_reverse_iterator rbegin() const {return data_.rbegin();}
    const_reverse_iterator rend() const {return data_.rend();}
  private:
    std::vector<std::string> data_;
  };
}

#endif
