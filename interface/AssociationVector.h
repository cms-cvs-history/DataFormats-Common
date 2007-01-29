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
 * \version $Revision: 1.7 $
 */

#include "DataFormats/Common/interface/traits.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "DataFormats/Common/interface/Ref.h"

namespace edm {

  template<typename CKey, typename CVal>
  class AssociationVector {
  public:
    typedef edm::RefProd<CKey> KeyRefProd;
    typedef edm::Ref<CKey> KeyRef;
    typedef typename CVal::size_type size_type;
    typedef typename CVal::value_type value_type;
    typedef typename CVal::reference reference;
    typedef typename CVal::pointer pointer;
    typedef typename CVal::const_reference const_reference;
    typedef typename CVal::iterator iterator;
    typedef typename CVal::const_iterator const_iterator;
    AssociationVector();
    AssociationVector(KeyRefProd ref);
    AssociationVector(KeyRefProd ref, size_type);
    AssociationVector(const AssociationVector &);
    ~AssociationVector();
    
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    size_type size() const;
    bool empty() const;
    reference operator[](size_type);
    const_reference operator[](size_type) const;
    
    AssociationVector<CKey, CVal> & operator=(const AssociationVector<CKey, CVal> &);
    
    void reserve(size_type);
    void push_back(const value_type &);  
    void clear();
    void swap(AssociationVector<CKey, CVal> & other);
    const KeyRefProd & keyProduct() const { return ref_; }
    KeyRef key(typename CKey::size_type i) const { return KeyRef(ref_, i); }
    void fillView(std::vector<void const*>& pointers) const;

  private:
    CVal data_;
    KeyRefProd ref_;
  };
  
  template<typename CKey, typename CVal>
  inline AssociationVector<CKey, CVal>::AssociationVector() : 
    data_(), ref_() { }
  
  template<typename CKey, typename CVal>
  inline AssociationVector<CKey, CVal>::AssociationVector(KeyRefProd ref) : 
    data_(), ref_(ref) { }
  
  template<typename CKey, typename CVal>
  inline AssociationVector<CKey, CVal>::AssociationVector(KeyRefProd ref, size_type n) : 
    data_(n), ref_(ref) { }
  
  template<typename CKey, typename CVal>
  inline AssociationVector<CKey, CVal>::AssociationVector(const AssociationVector<CKey, CVal> & o) : 
    data_(o.data_), ref_(o.ref_) { }
  
  template<typename CKey, typename CVal>
  inline AssociationVector<CKey, CVal>::~AssociationVector() { }
  
  template<typename CKey, typename CVal>
  inline AssociationVector<CKey, CVal> & 
  AssociationVector<CKey, CVal>::operator=(const AssociationVector<CKey, CVal> & o) {
    data_ = o.data_;
    ref_ = o.ref_;
    return * this;
  }
  
  template<typename CKey, typename CVal>
  inline typename AssociationVector<CKey, CVal>::iterator AssociationVector<CKey, CVal>::begin() {
    return data_.begin();
  }
  
  template<typename CKey, typename CVal>
  inline typename AssociationVector<CKey, CVal>::iterator AssociationVector<CKey, CVal>::end() {
    return data_.end();
  }
  
  template<typename CKey, typename CVal>
  inline typename AssociationVector<CKey, CVal>::const_iterator AssociationVector<CKey, CVal>::begin() const {
    return data_.begin();
  }
  
  template<typename CKey, typename CVal>
  inline typename AssociationVector<CKey, CVal>::const_iterator AssociationVector<CKey, CVal>::end() const {
    return data_.end();
  }
  
  template<typename CKey, typename CVal>
  inline typename AssociationVector<CKey, CVal>::size_type AssociationVector<CKey, CVal>::size() const {
    return data_.size();
  }
  
  template<typename CKey, typename CVal>
  inline bool AssociationVector<CKey, CVal>::empty() const {
    return data_.empty();
  }
  
  template<typename CKey, typename CVal>
  inline typename AssociationVector<CKey, CVal>::reference AssociationVector<CKey, CVal>::operator[](size_type n) {
    return data_[ n ];
  }
  
  template<typename CKey, typename CVal>
  inline typename AssociationVector<CKey, CVal>::const_reference AssociationVector<CKey, CVal>::operator[](size_type n) const {
    return data_[ n ];
  }
  
  template<typename CKey, typename CVal>
  inline void AssociationVector<CKey, CVal>::reserve(size_type n) {
    data_.reserve(n);
  }
  
  template<typename CKey, typename CVal>
  inline void AssociationVector<CKey, CVal>::push_back(const value_type & t) {
    data_.push_back(t);
  }
  
  template<typename CKey, typename CVal>
  inline void AssociationVector<CKey, CVal>::clear() {
    data_.clear();
    ref_ = KeyRefProd();
  }

  template<typename CKey, typename CVal>
  inline void AssociationVector<CKey, CVal>::swap(AssociationVector<CKey, CVal> & other) {
    data_.swap(other.data_);
    std::swap(ref_, other.ref_);
  }

  template<typename CKey, typename CVal>
  void AssociationVector<CKey, CVal>::fillView(std::vector<void const*>& pointers) const
  {
    pointers.reserve(this->size());
    for(const_iterator i=begin(), e=end(); i!=e; ++i)
      pointers.push_back(&(*i));
  }

  template<typename CKey, typename CVal>
  inline void swap(AssociationVector<CKey, CVal> & a, AssociationVector<CKey, CVal> & b) {
    a.swap(b);
  }

  //----------------------------------------------------------------------
  //
  // Free function template to support creation of Views.

  template <typename CKey, typename CVal>
  inline
  void
  fillView(AssociationVector<CKey,CVal> const& obj,
	   std::vector<void const*>& pointers)
  {
    obj.fillView(pointers);
  }

  template <typename CKey, typename CVal>
  struct has_fillView<edm::AssociationVector<CKey, CVal> >
  {
    static bool const value = true;
  };

#if ! GCC_PREREQUISITE(3,4,4)
  // has swap function
  template<typename CKey, typename CVal>
  struct has_swap<edm::AssociationVector<CKey, CVal> > {
    static bool const value = true;
  };
#endif

}

#endif
