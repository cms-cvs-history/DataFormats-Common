#ifndef Common_RefProd_h
#define Common_RefProd_h

/*----------------------------------------------------------------------
  
Ref: A template for an interproduct reference to a product.

$Id: RefProd.h,v 1.6 2006/12/16 03:45:47 wmtan Exp $

----------------------------------------------------------------------*/

/*----------------------------------------------------------------------
//  This defines the public interface to the class RefProd<T>.
//
//  ProductID productID		is the product ID of the collection. (0 is invalid)
//  const RefProd<T> & ref		is another RefProd<T>

//  Constructors
    RefProd(); // Default constructor
    RefProd(const RefProd<T> & ref);	// Copy constructor  (default, not explicitly specified)

    RefProd(Handle<T> const& handle);
    RefProd(ProductID pid, EDProductGetter const* prodGetter);

//  Destructor
    virtual ~RefProd() {}

// Operators and methods
    RefProd<T>& operator=(const RefProd<T> &);	// assignment (default, not explicitly specified)
    T const& operator*() const;			// dereference
    T const* operator->() const;		// member dereference
    bool operator==(RefProd<T> const& ref) const;	// equality
    bool operator!=(RefProd<T> const& ref) const;	// inequality
    bool operator<(RefProd<T> const& ref) const;	// ordering
    bool isNonnull() const;			// true if an object is referenced
    bool isNull() const;			// equivalent to !isNonnull()
    bool operator!() const;			// equivalent to !isNonnull()
----------------------------------------------------------------------*/ 

#include "DataFormats/Common/interface/RefCore.h"
#include "DataFormats/Provenance/interface/ProductID.h"

namespace edm {
  template <typename T, typename V, typename F> class Ref;
  template <typename T>
  class RefProd {
  public:

    /// Default constructor needed for reading from persistent store. Not for direct use.
    RefProd() : product_() {}

    /// General purpose constructor from handle like object.
    // The templating is artificial.
    // HandleT must have the following methods:
    // id(), returning a ProductID,
    // product(), returning a T*.
    template <class HandleT>
    explicit RefProd(HandleT const& handle) :
    product_(handle.id(), handle.product(), 0) {
      checkTypeAtCompileTime(handle.product());
    }

    /// Constructor from Ref.
    template <typename V, typename F>
    explicit RefProd(Ref<T, V, F> const& ref);

    // Constructor for those users who do not have a product handle,
    // but have a pointer to a product getter (such as the EventPrincipal).
    // prodGetter will ususally be a pointer to the event principal.
    RefProd(ProductID const& productID, EDProductGetter const* prodGetter) :
      product_(productID, 0, prodGetter) {
    }

    /// Destructor
    ~RefProd() {}

    /// Dereference operator
    T const&  operator*() const {return *getProduct<T>(product_);}

    /// Member dereference operator
    T const* operator->() const {return getProduct<T>(product_);} 

    /// Returns C++ pointer to the product
    /// Will attempt to retrieve product
    T const* get() const {
      return isNull() ? 0 : this->operator->();
    }

    /// Returns C++ pointer to the product
    /// Will attempt to retrieve product
    T const* product() const {
      return isNull() ? 0 : this->operator->();
    }

    RefCore const& refCore() const {
      return product_;
    }

    /// Checks for null
    bool isNull() const {return id() == ProductID();}

    /// Checks for non-null
    bool isNonnull() const {return !isNull();}

    /// Checks for null
    bool operator!() const {return isNull();}

    /// Accessor for product ID.
    ProductID id() const {return product_.id();}

    /// Accessor for product getter.
    EDProductGetter const* productGetter() const {return product_.productGetter();}

    /// Checks if product is in memory.
    bool hasCache() const {return product_.productPtr() != 0;}

  private:
    // Compile time check that the argument is a T* or T const*
    // or derived from it.
    void checkTypeAtCompileTime(T const* ptr) {}

    RefCore product_;
  };
}

#include "DataFormats/Common/interface/Ref.h"

namespace edm {

  /// Constructor from Ref.
  template <typename T>
  template <typename V, typename F>
  inline
  RefProd<T>::RefProd(Ref<T, V, F> const& ref) :
      product_(ref.id(), ref.hasProductCache() ? ref.product() : 0, ref.productGetter()) {
  }

  template <typename T>
  inline
  bool
  operator==(RefProd<T> const& lhs, RefProd<T> const& rhs) {
    return lhs.refCore() == rhs.refCore();
  }

  template <typename T>
  inline
  bool
  operator!=(RefProd<T> const& lhs, RefProd<T> const& rhs) {
    return !(lhs == rhs);
  }

  template <typename T>
  inline
  bool
  operator<(RefProd<T> const& lhs, RefProd<T> const& rhs) {
    return (lhs.refCore() < rhs.refCore());
  }
}
#endif
