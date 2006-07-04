#ifndef Common_ModuleDescription_h
#define Common_ModuleDescription_h

/*----------------------------------------------------------------------
  
ModuleDescription: The description of a producer module.

$Id: ModuleDescription.h,v 1.2.2.2 2006/06/28 17:07:58 paterno Exp $
----------------------------------------------------------------------*/
#include <string>
#include <iostream>

#include "DataFormats/Common/interface/PassID.h"
#include "DataFormats/Common/interface/ParameterSetID.h"
#include "DataFormats/Common/interface/ReleaseVersion.h"
#include "DataFormats/Common/interface/ModuleDescriptionID.h"

namespace edm {

  // once a module is born, these parts of the module's product provenance
  // are constant   (change to ModuleDescription)

  struct ModuleDescription {

    ModuleDescription();
    // compiler-written copy c'tor, assignment, and d'tor are correct.

    bool operator<(ModuleDescription const& rh) const;

    bool operator==(ModuleDescription const& rh) const;

    bool operator!=(ModuleDescription const& rh) const;
    
    ModuleDescriptionID id() const;

    // ID of parameter set of the creator
    ParameterSetID parameterSetID_;

    // The class name of the creator
    std::string moduleName_;    

    // A human friendly string that uniquely identifies the EDProducer
    // and becomes part of the identity of a product that it produces
    std::string moduleLabel_;

    // the release tag of the executable
    ReleaseVersion releaseVersion_;

    // the physical process that this program was part of (e.g. production)
    std::string processName_;

    // what the heck is this? I think its the version of the processName_
    // e.g. second production pass
    PassID passID_;

  };

  inline
  std::ostream& operator<<(std::ostream& ost, const ModuleDescription& md) {
    ost << "Module type=" << md.moduleName_ << ", "
	<< "Module label=" << md.moduleLabel_ << ", "
	<< "Process name=" << md.processName_;

    return ost;
  }
}
#endif
