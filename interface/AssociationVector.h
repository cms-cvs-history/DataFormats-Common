#ifndef Common_AssociationVector_h
#define Common_AssociationVector_h
/* class edm::AssociationVector<CKey, CVal>
 *
 * adds to a std::vector<CVal> a edm::RefProd<CKey>, in such a way
 * that, assuming that the CVal and CKey collections have the same
 * size and are properly ordered, the two collections can be
 * in one-to-one correspondance
 *
 * \author Luca Lista, INFN
 *
 * \version $Revision: 1.19 $
 */

#include "FWCore/Utilities/interface/EDMException.h"

#include "DataFormats/Common/interface/traits.h"
#include "DataFormats/Common/interface/EDProduct.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/FillView.h"

#include "DataFormats/Provenance/interface/ProductID.h"

#include "boost/static_assert.hpp"
#include "boost/type_traits/is_same.hpp"

namespace edm {
  namespace helper {

    struct AssociationIdenticalKeyReference {
      template<typename T>
      static const T & get( const T & t, edm::ProductID ) { return t; }
    };
    
    template<typename T>
    struct AssociationKeyReferenceTrait {
      typedef AssociationIdenticalKeyReference type;
    };
  }

  template<typename KeyRefProd, typename CVal, 
    typename KeyRef=edm::Ref<typename KeyRefProd::product_type>,
    typename SizeType=typename KeyRefProd::product_type::size_type,
    typename KeyReferenceTrait = typename helper::AssociationKeyReferenceTrait<KeyRef>::type>
  class AssociationVector {
    BOOST_STATIC_ASSERT( ( boost::is_same<SizeType, typename CVal::size_type>::value ) );
    typedef AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait> self;

  public:
    typedef typename KeyRefProd::product_type CKey;
    typedef SizeType size_type;
    typedef typename KeyRef::value_type key_type;
    typedef typename std::pair<KeyRef, typename CVal::value_type> value_type;
    typedef std::vector<value_type> transient_vector_type;
    typedef const value_type & const_reference;
    AssociationVector();
    AssociationVector(KeyRefProd ref);
    AssociationVector(const AssociationVector &);
    ~AssociationVector();
    
    size_type size() const;
    bool empty() const;
    const_reference operator[](size_type n) const;
    const typename CVal::value_type & operator[](const KeyRef & k) const;
    typename CVal::value_type & operator[](const KeyRef & k);
    
    self & operator=(const self & );
    
    void clear();
    void swap( self & other);
    const KeyRefProd & keyProduct() const { return ref_; }
    KeyRef key(size_type i) const { return KeyRef(ref_, i); }
    const typename CVal::value_type & value(size_type i) const { return data_[ i ]; }
    void setValue(size_type i, const typename CVal::value_type & val ) { 
      data_[ i ] = val; 
      transientVector_[ i ].first = KeyRef(ref_, i);
      transientVector_[ i ].second = data_[ i ];
    }   
    void fillView(ProductID const& id,
		  std::vector<void const*>& pointers,
		  std::vector<helper_ptr>& helpers) const;

    typedef typename transient_vector_type::const_iterator const_iterator;

    const_iterator begin() const { fixup(); return transientVector_.begin(); } 
    const_iterator end() const { fixup(); return transientVector_.end(); } 

  private:
    CVal data_;
    KeyRefProd ref_;
    mutable transient_vector_type transientVector_;
    mutable bool fixed_;
    void fixup() const { 
      if (!fixed_) {
	fixed_ = true;
	transientVector_.resize( size() );
	for( size_type i = 0; i != size(); ++ i ) {
	  transientVector_[ i ] = make_pair( KeyRef(ref_, i), data_[ i ] );
	}
      }
    }
  };
  
  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::AssociationVector() : 
    data_(), ref_(), transientVector_(), fixed_(false)  { }
  
  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::AssociationVector(KeyRefProd ref) : 
    data_(ref->size()), ref_(ref), transientVector_(ref->size()), fixed_(true) { }
  
  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::
    AssociationVector(const AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait> & o) : 
    data_(o.data_), ref_(o.ref_), transientVector_(o.transientVector_), fixed_(o.fixed_) { }
  
  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::~AssociationVector() { }

  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline typename AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::const_reference 
  AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::operator[](size_type n) const { 
    fixup(); 
    return transientVector_[ n ]; 
  }
  
  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline const typename CVal::value_type &
  AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::operator[]( const KeyRef & k ) const {
    KeyRef keyRef = KeyReferenceTrait::get( k, ref_.id() );
    if ( keyRef.id() == ref_.id() ) 
      return data_[ keyRef.key() ];
    else 
      throw edm::Exception(edm::errors::InvalidReference) 
	<< "AssociationVector: trying to use [] operator passing a reference"
	<< " with the wrong product id (i.e.: pointing to the wrong collection)";
  }

  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline typename CVal::value_type &
  AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::operator[]( const KeyRef & k ) {
    KeyRef keyRef = KeyReferenceTrait::get( k, ref_.id() );
    if ( keyRef.id() == ref_.id() ) 
      return data_[ keyRef.key() ];
    else 
      throw edm::Exception(edm::errors::InvalidReference) 
	<< "AssociationVector: trying to use [] operator passing a reference"
	<< " with the wrong product id (i.e.: pointing to the wrong collection)";
  }

  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait> & 
  AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::operator=(const self & o) {
    data_ = o.data_;
    ref_ = o.ref_;
    transientVector_ = o.transientVector_;
    fixed_ = o.fixed_;
    return * this;
  }
  
  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline typename AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::size_type 
    AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::size() const {
    return data_.size();
  }
  
  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline bool AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::empty() const {
    return data_.empty();
  }
  
  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline void AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::clear() {
    data_.clear();
    transientVector_.clear();
    ref_ = KeyRefProd();
    fixed_ = true;
  }

  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline void AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::swap(self & other) {
    data_.swap(other.data_);
    transientVector_.swap(other.transientVector_);
    std::swap(ref_, other.ref_);
    std::swap(fixed_, other.fixed_);
  }

  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  void AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait>::fillView(ProductID const& id,
								       std::vector<void const*>& pointers, 
								       std::vector<helper_ptr>& helpers) const
  {
    detail::reallyFillView(*this, id, pointers, helpers);
//     pointers.reserve(this->size());
//     for(typename CVal::const_iterator i=data_.begin(), e=data_.end(); i!=e; ++i)
//       pointers.push_back(&(*i));
//     // helpers is not yet filled in.
//     //throw edm::Exception(errors::UnimplementedFeature, "AssociationVector<T>::fillView(...)");
  }

  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline void swap(AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait> & a, 
		   AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait> & b) {
    a.swap(b);
  }

  //----------------------------------------------------------------------
  //
  // Free function template to support creation of Views.

  template <typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  inline
  void
  fillView(AssociationVector<KeyRefProd,CVal, KeyRef, SizeType, KeyReferenceTrait> const& obj,
	   ProductID const& id,
	   std::vector<void const*>& pointers,
	   std::vector<helper_ptr>& helpers) {
    obj.fillView(id, pointers, helpers);
  }

  template <typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  struct has_fillView<edm::AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait> > {
    static bool const value = true;
  };

#if ! GCC_PREREQUISITE(3,4,4)
  // has swap function
  template<typename KeyRefProd, typename CVal, typename KeyRef, typename SizeType, typename KeyReferenceTrait>
  struct has_swap<edm::AssociationVector<KeyRefProd, CVal, KeyRef, SizeType, KeyReferenceTrait> > {
    static bool const value = true;
  };
#endif

}

#endif
