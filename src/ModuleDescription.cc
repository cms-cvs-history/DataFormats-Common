#include <sstream>
#include <string>

#include "SealZip/MD5Digest.h"
#include "DataFormats/Common/interface/ModuleDescription.h"

/*----------------------------------------------------------------------

$Id: ModuleDescription.cc,v 1.1.2.2 2006/06/28 17:07:59 paterno Exp $

----------------------------------------------------------------------*/

namespace edm {

  ModuleDescription::ModuleDescription() :
    parameterSetID_(),
    moduleName_(),
    moduleLabel_(),
    releaseVersion_(),
    processName_(),
    passID_()
  { }

  bool
  ModuleDescription::operator<(ModuleDescription const& rh) const {
    if (moduleLabel_ < rh.moduleLabel_) return true;
    if (rh.moduleLabel_ < moduleLabel_) return false;
    if (processName_ < rh.processName_) return true;
    if (rh.processName_ < processName_) return false;
    if (moduleName_ < rh.moduleName_) return true;
    if (rh.moduleName_ < moduleName_) return false;
    if (parameterSetID_ < rh.parameterSetID_) return true;
    if (rh.parameterSetID_ < parameterSetID_) return false;
    if (releaseVersion_ < rh.releaseVersion_) return true;
    if (rh.releaseVersion_ < releaseVersion_) return false;
    if (passID_ < rh.passID_) return true;
    return false;
  } 

  bool
  ModuleDescription::operator==(ModuleDescription const& rh) const {
    return !((*this) < rh || rh < (*this));
  }

  bool
  ModuleDescription::operator!=(ModuleDescription const& rh) const {
    return !((*this) == rh);
  }

  ModuleDescriptionID
  ModuleDescription::id() const
  {
    // This implementation is ripe for optimization.
    // We do not use operator<< because it does not write out everything.
    seal::MD5Digest md5alg;
    std::ostringstream oss;
    oss << parameterSetID_ << ' ' 
	<< moduleName_ << ' '
	<< moduleLabel_ << ' '
	<< releaseVersion_ << ' '
	<< processName_ << ' '
	<< passID_;
    std::string stringrep = oss.str();
    md5alg.update(stringrep.data(), stringrep.size());
    return ModuleDescriptionID(md5alg.format());
  }

}
