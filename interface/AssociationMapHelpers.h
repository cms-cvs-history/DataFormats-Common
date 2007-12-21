#ifndef DataFormats_Common_AssociationMapKeyVal_h
#define DataFormats_Common_AssociationMapKeyVal_h
/*
 *
 * helper classes for AssociationMap
 *
 * \author Luca Lista, INFN
 *
 * $Id: AssociationMapHelpers.h,v 1.2 2007/01/23 00:25:52 wmtan Exp $
 *
 */
#include "FWCore/Utilities/interface/EDMException.h"

namespace edm {
  namespace helpers {
    template<typename K, typename V>
    struct KeyVal {
      typedef K key_type;
      typedef V value_type;
      KeyVal() { }
      KeyVal(const K & k, const V & v) : key(k), val(v) { }
      K key;
      V val;
    };
    
    template<typename K>
    struct Key {
      typedef K key_type;
      Key() { }
      Key(const K & k) : key(k) { }
      K key;
    };
    
    /// throw if r hasn't the same id as rp
    template<typename RP, typename R>
    void checkRef(const RP & rp, const R & r) {
      if (rp.id() != r.id())
	throw edm::Exception(edm::errors::InvalidReference, "invalid reference");
    }
  }
}

#endif
