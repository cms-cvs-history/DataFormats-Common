#include <sstream>
#include <string>

#include "SealZip/MD5Digest.h"
#include "DataFormats/Common/interface/ModuleDescription.h"

/*----------------------------------------------------------------------

$Id: ModuleDescription.cc,v 1.1.2.1 2006/06/27 21:05:18 paterno Exp $

----------------------------------------------------------------------*/

namespace edm {

  ModuleDescription::ModuleDescription() :
    pid(),
    moduleName_(),
    moduleLabel_(),
    versionNumber_(0UL),
    processName_(),
    pass(0UL)
  { }

  bool
  ModuleDescription::operator<(ModuleDescription const& rh) const {
    if (moduleLabel_ < rh.moduleLabel_) return true;
    if (rh.moduleLabel_ < moduleLabel_) return false;
    if (processName_ < rh.processName_) return true;
    if (rh.processName_ < processName_) return false;
    if (moduleName_ < rh.moduleName_) return true;
    if (rh.moduleName_ < moduleName_) return false;
    if (pid < rh.pid) return true;
    if (rh.pid < pid) return false;
    if (versionNumber_ < rh.versionNumber_) return true;
    if (rh.versionNumber_ < versionNumber_) return false;
    if (pass < rh.pass) return true;
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
    oss << pid << ' ' 
	<< moduleName_ << ' '
	<< moduleLabel_ << ' '
	<< versionNumber_ << ' '
	<< processName_ << ' '
	<< pass;
    std::string stringrep = oss.str();
    md5alg.update(stringrep.data(), stringrep.size());
    return ModuleDescriptionID(md5alg.format());
  }

}
