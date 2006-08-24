#ifndef Common_ModuleDescription_h
#define Common_ModuleDescription_h

/*----------------------------------------------------------------------
  
ModuleDescription: The description of a producer module.

$Id: ModuleDescription.h,v 1.7 2006/08/22 05:50:16 wmtan Exp $
----------------------------------------------------------------------*/
#include <string>
#include <iosfwd>

#include "DataFormats/Common/interface/ParameterSetID.h"
#include "DataFormats/Common/interface/ProcessConfiguration.h"
#include "DataFormats/Common/interface/ProcessConfigurationID.h"
#include "DataFormats/Common/interface/ModuleDescriptionID.h"

namespace edm {

  // once a module is born, these parts of the module's product provenance
  // are constant   (change to ModuleDescription)

  struct ModuleDescription {

    ModuleDescription();

    void write(std::ostream& os) const;

    ParameterSetID const& parameterSetID() const {return parameterSetID_;}
    std::string const& moduleName() const {return moduleName_;}
    std::string const& moduleLabel() const {return moduleLabel_;}
    ProcessConfiguration const& processConfiguration() const {return processConfiguration_;}
    ProcessConfigurationID const processConfigurationID() const {return processConfiguration().id();}
    std::string const& processName() const {return processConfiguration().processName();}
    std::string const& releaseVersion() const {return processConfiguration().releaseVersion();}
    std::string const& passID() const {return processConfiguration().passID();}
    ParameterSetID const& mainParameterSetID() const {return processConfiguration().parameterSetID();}

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

    // The process configuration.
    ProcessConfiguration processConfiguration_;
  };

  inline
  std::ostream&
  operator<<(std::ostream& os, const ModuleDescription& p) {
    p.write(os);
    return os;
  }

}
#endif
