#ifndef DataFormats_Common_RefCore_h
#define DataFormats_Common_RefCore_h

/*----------------------------------------------------------------------
  
RefCore: The component of edm::Ref containing the product ID and product getter.

$Id: RefCore.h,v 1.12 2007/05/15 17:10:24 wmtan Exp $

----------------------------------------------------------------------*/
#include <typeinfo>
#include "DataFormats/Provenance/interface/ProductID.h"
#include "DataFormats/Common/interface/EDProductGetter.h"
#include "DataFormats/Common/interface/EDProductfwd.h"

namespace edm {

  class RefCore {
  public:
    RefCore() : id_(), prodPtr_(0), prodGetter_(0) {}

    RefCore(ProductID const& theId, void const *prodPtr, EDProductGetter const* prodGetter) :
      id_(theId), 
      prodPtr_(prodPtr), 
      prodGetter_(prodGetter) { }

    ProductID id() const {return id_;}

    void const* productPtr() const {return prodPtr_;}

    void setProductPtr(void const* prodPtr) const {prodPtr_ = prodPtr;}

    // Checks for null
    bool isNull() const {return !isNonnull(); }

    // Checks for non-null
    bool isNonnull() const {return id_.isValid(); }

    // Checks for null
    bool operator!() const {return isNull();}

    EDProductGetter const* productGetter() const {
      if (!prodGetter_) setProductGetter(EDProductGetter::instance());
      return prodGetter_;
    }

    void setProductGetter(EDProductGetter const* prodGetter) const {prodGetter_ = prodGetter;}

    void setProductPointer(void const* prodPtr) const {prodPtr_ = prodPtr;}

    void checkDereferenceability() const;

 private:

    ProductID id_;
    mutable void const *prodPtr_;               // transient
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

  inline
  bool
  operator<(RefCore const& lhs, RefCore const& rhs) {
    return lhs.id() < rhs.id();
  }

  void wrongReType(std::string const& found, std::string const& requested);

  void checkProduct(RefCore const& productToBeInserted, RefCore & commonProduct);

}

#endif
