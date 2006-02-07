#ifndef Common_TestHandle_h
#define Common_TestHandle_h

/*----------------------------------------------------------------------
  
$Id: TestHandle.h,v 1.1 2005/12/01 22:10:51 wmtan Exp $

Version of Handle 

----------------------------------------------------------------------*/

#include <algorithm>
#include <stdexcept>
#include <typeinfo>

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits.hpp"

#include "DataFormats/Common/interface/ProductID.h"
#include "FWCore/Utilities/interface/EDMException.h"

namespace edm {
  template <class T>
  class TestHandle {
  public:
    // Default constructed handles are invalid.
    TestHandle();

    TestHandle(const TestHandle<T>& h);

    TestHandle(T const* prod, ProductID const& id);

    ~TestHandle();

    void swap(TestHandle<T>& other);

    TestHandle<T>& operator=(const TestHandle<T>& rhs);

    bool isValid() const;

    T const* product() const;
    T const* operator->() const; // alias for product()
    T const& operator*() const;

    ProductID id() const;

  private:
    T const* prod_;
    ProductID id_;
  };

  template <class T>
  TestHandle<T>::TestHandle() :
    prod_(0),
    id_(0)
  { }

  template <class T>
  TestHandle<T>::TestHandle(const TestHandle<T>& h) :
    prod_(h.prod_),
    id_(h.id_)
  { }

  template <class T>
  TestHandle<T>::TestHandle(T const* product, ProductID const& id) :
    prod_(product),
    id_(id) { 
  }

  template <class T>
  TestHandle<T>::~TestHandle() { 
    // Nothing to do -- we do not own the things to which we point.
  }

  template <class T>
  void
  TestHandle<T>::swap(TestHandle<T>& other) {
    std::swap(prod_, other.prod_);
    std::swap(id_, other.id_);
  }

  template <class T>
  TestHandle<T>&
  TestHandle<T>::operator=(const TestHandle<T>& rhs) {
    TestHandle<T> temp(rhs);
    this->swap(temp);
    return *this;
  }

  template <class T>
  bool
  TestHandle<T>::isValid() const {
    return prod_ != 0 && id_ != ProductID();
  }

  template <class T>
  T const* 
  TestHandle<T>::product() const {
    return prod_;
  }

  template <class T>
  T const* 
  TestHandle<T>::operator->() const {
    return product();
  }

  template <class T>
  T const& 
  TestHandle<T>::operator*() const {
    return *product();
  }

  template <class T>
  ProductID 
  TestHandle<T>::id() const {
    return id_;
  }
}

#endif
