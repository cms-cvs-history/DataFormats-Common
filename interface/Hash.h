#ifndef Common_Hash_h
#define Common_Hash_h

#include "DataFormats/Common/interface/MD5Hash.h"
/*----------------------------------------------------------------------
  
Hash:

$Id: Hash.h,v 1.2 2006/06/22 17:33:53 wmtan Exp $
----------------------------------------------------------------------*/
namespace edm {
  template <typename T>
  class Hash {
  public:
    typedef T value_type;
    MD5Hash const& hash() const {return hash_;}
  private:
    MD5Hash hash_;
  };

  template <typename T>
  inline
  bool
  operator<(Hash<T> const& a, Hash<T> const& b) {
    return a.hash() < b.hash();
  }

  template <typename T>
  inline
  bool
  operator==(Hash<T> const& a, Hash<T> const& b) {
    return a.hash() == b.hash();
  }

  template <typename T>
  inline
  bool
  operator!=(Hash<T> const& a, Hash<T> const& b) {
    return a.hash() != b.hash();
  }
}
#endif
