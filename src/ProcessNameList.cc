#include <string>
#include "SealZip/MD5Digest.h"

#include "DataFormats/Common/interface/ProcessNameList.h"


namespace edm
{
  ProcessNameListID
  ProcessNameList::id() const
  {
    // This implementation is ripe for optimiziation.
    seal::MD5Digest md5alg;
    for ( const_iterator i = begin(), e = end(); i != e; ++i )
      md5alg.update(i->data(), i->size());

    return ProcessNameListID(md5alg.format());
  }
}
