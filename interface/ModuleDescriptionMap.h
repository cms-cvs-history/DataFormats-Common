#ifndef Common_ModuleDescriptionMap_h
#define Common_ModuleDescriptionMap_h

/*----------------------------------------------------------------------
  
ModuleDescriptionMap: A map of module descriptions.

$Id: ModuleDescriptionMap.h,v 1.2 2006/06/22 17:33:53 wmtan Exp $
----------------------------------------------------------------------*/
#include <map>

#include "DataFormats/Common/interface/ModuleDescription.h"
#include "DataFormats/Common/interface/ModuleDescriptionID.h"

namespace edm {
  typedef std::map<ModuleDescriptionID, ModuleDescription> ModuleDescriptionMap;
}
#endif
