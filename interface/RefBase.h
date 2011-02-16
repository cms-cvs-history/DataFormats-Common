#ifndef DataFormats_Common_RefBase_h
#define DataFormats_Common_RefBase_h

/*----------------------------------------------------------------------
  
RefBase: Base class for a single interproduct reference.

$Id: RefBase.h,v 1.11 2008/02/15 05:57:03 wmtan Exp $

----------------------------------------------------------------------*/

#include "DataFormats/Common/interface/EDProductfwd.h"
#include "DataFormats/Common/interface/RefCore.h"
#include "DataFormats/Common/interface/traits.h"
#include "DataFormats/Common/interface/ConstPtrCache.h"

namespace edm {

  template<typename KEY>
  class RefBase {
  public:
    typedef KEY key_type;

    /// Default constructor needed for reading from persistent store. Not for direct use.
    RefBase() : product_(), index_(key_traits<key_type>::value), cache_(0) {}

    /// General purpose constructor. 
    RefBase(ProductID const& productID, void const* prodPtr, key_type itemKey,
            void const* itemPtr, EDProductGetter const* prodGetter, bool transient):
      product_(productID, prodPtr, prodGetter, transient), index_(itemKey),cache_(itemPtr) {}

    /// Constructor from RefVector. 
    RefBase(RefCore const& prod, RefItem<KEY> const& itm) :
      product_(prod), index_(itm.key()),cache_(itm.ptr()) {}

    /// Compiler-generated copy constructor, assignment operator, and
    /// destructor do the right thing.

    /// Accessor for product ID and product getter.
    RefCore const& refCore() const { return product_;}

    /// Accessor for index and pointer
    RefItem<KEY> item() const {return RefItem<KEY>(index_,cache_.ptr_);}

    // /// Return the index for the referenced element.
    // key_type key() const { return item_.key(); }
    

    /// Return true if this RefBase is non-null
    bool isValid() const { return index_!=edm::key_traits<key_type>::value; }
    bool isNull() const { return !isValid(); }
    bool isNonnull() const { return isValid(); }

  private:
    RefCore product_;
    //RefItem<KEY> item_;
    key_type index_;
    mutable ConstPtrCache cache_; //Type handles the transient
  };

  template <typename KEY>
  bool
  operator==(RefBase<KEY> const& lhs, RefBase<KEY> const& rhs) {
    return lhs.refCore() == rhs.refCore() && lhs.item() == rhs.item();
  }
  
  template <typename KEY>
  bool
  operator!=(RefBase<KEY> const& lhs, RefBase<KEY> const& rhs) {
    return !(lhs == rhs);
  }

  template <typename KEY>
  bool
  operator<(RefBase<KEY> const& lhs, RefBase<KEY> const& rhs) {
    return (lhs.refCore() == rhs.refCore() ?  lhs.item() < rhs.item() : lhs.refCore() < rhs.refCore());
  }
}
  
#endif
