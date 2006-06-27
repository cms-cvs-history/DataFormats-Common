#ifndef Common_ProcessNameListMap_h
#define Common_ProcessNameListMap_h

/*----------------------------------------------------------------------
  
ProcessNameListMap: A map of ProcessNameLists.

$Id: ProcessNameListMap.h,v 1.2 2006/06/22 17:33:53 wmtan Exp $
----------------------------------------------------------------------*/
#include <map>

#include "DataFormats/Common/interface/ProcessNameList.h"
#include "DataFormats/Common/interface/ProcessNameListID.h"

namespace edm {
  typedef std::map<ProcessNameListID, ProcessNameList> ProcessNameListMap;
}
#endif
