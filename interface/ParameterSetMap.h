#ifndef Common_ParameterSetMap_h
#define Common_ParameterSetMap_h

/*----------------------------------------------------------------------
  
ParameterSetMap: A map of parameter sets.

$Id: ParameterSetMap.h,v 1.2 2006/06/22 17:33:53 wmtan Exp $
----------------------------------------------------------------------*/
#include <map>

#include "DataFormats/Common/interface/ParameterSetBlob.h"
#include "DataFormats/Common/interface/ParameterSetID.h"

namespace edm {
  typedef std::map<ParameterSetID, ParameterSetBlob> ParameterSetMap;
}
#endif
