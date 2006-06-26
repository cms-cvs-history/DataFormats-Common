#ifndef Common_MD5Hash_h
#define Common_MD5Hash_h

/*----------------------------------------------------------------------
  
MD5Hash:

$Id: MD5Hash.h,v 1.2 2006/06/22 17:33:53 wmtan Exp $
----------------------------------------------------------------------*/
namespace edm {
  struct MD5Hash {
    static int const size = 8;
    MD5Hash() {}
    ~MD5Hash() {}
    unsigned char value_[size];
  };

  bool operator<(MD5Hash const& a, MD5Hash const& b);

  bool operator==(MD5Hash const& a, MD5Hash const& b);

  inline
  bool operator!=(MD5Hash const& a, MD5Hash const& b) {
    return !(a == b);
  }
}
#endif
