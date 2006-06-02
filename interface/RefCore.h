#ifndef Common_RefCore_h
#define Common_RefCore_h

/*----------------------------------------------------------------------
  
RefCore: The component of edm::Ref containing the product ID and product getter.

$Id: RefCore.h,v 1.1 2006/02/07 07:01:50 wmtan Exp $

----------------------------------------------------------------------*/

#include "DataFormats/Common/interface/ProductID.h"
#include "DataFormats/Common/interface/Wrapper.h"
#include "DataFormats/Common/interface/EDProductGetter.h"

namespace edm {
  class EDProductGetter;
  class RefCore {
  public:
    RefCore() : id_(), prodPtr_(0), prodGetter_(0) {}
    RefCore(ProductID const& id, void const *prodPtr, EDProductGetter const* prodGetter) :
        id_(id), prodPtr_(prodPtr), prodGetter_(prodGetter) {
      if (id == ProductID()) {badID();}
    }
    ~RefCore() {}

    ProductID id() const {return id_;}

    void const* productPtr() const {return prodPtr_;}

    void setProductPtr(void const* prodPtr) const {prodPtr_ = prodPtr;}

    EDProductGetter const* productGetter() const {return prodGetter_;}

    void setProductGetter(EDProductGetter const* prodGetter) const {prodGetter_ = prodGetter;}

  private:
    void badID() const;

  private:
    ProductID id_;
    mutable void const *prodPtr_; // transient
    mutable EDProductGetter const* prodGetter_; // transient
  };

  inline
  bool
  operator==(RefCore const& lhs, RefCore const& rhs) {
    return lhs.id() == rhs.id();
  }

  inline
  bool
  operator!=(RefCore const& lhs, RefCore const& rhs) {
    return !(lhs == rhs);
  }

  void wrongRefType(std::string const& found, std::string const& requested);

  template <typename T>
  T const* getProduct_(RefCore const& product) {
    if (!product.productGetter()) {
      product.setProductGetter(EDProductGetter::instance());
      assert(product.productGetter());
    }
    Wrapper<T> const* edpw = dynamic_cast<Wrapper<T> const*>(product.productGetter()->getIt(product.id()));
    if (edpw == 0) {
      wrongRefType(typeid(product.productGetter()->getIt(product.id())).name(), typeid(T).name());
    }
    return edpw->product();
  }

  template <typename T>
  inline
  T const* getProduct(RefCore const& product) {
    T const* p = static_cast<T const *>(product.productPtr());
    return(p != 0 ? p : getProduct_<T>(product));
  }

  void checkProduct(RefCore const& prod, RefCore & product);

}

#endif
