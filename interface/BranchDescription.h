#ifndef Common_BranchDescription_h
#define Common_BranchDescription_h

/*----------------------------------------------------------------------
  
BranchDescription: The full description of a product and how it came into
existence.

$Id: BranchDescription.h,v 1.8 2006/05/09 03:19:09 lsexton Exp $
----------------------------------------------------------------------*/
#include <ostream>
#include <string>
#include "boost/shared_ptr.hpp"

#include "DataFormats/Common/interface/ProductID.h"
#include "DataFormats/Common/interface/ModuleDescription.h"

/*
  BranchDescription

  definitions:
  The event-independent description of an EDProduct.

*/

namespace edm {
  class EDProduct;
  struct BranchDescription {

    BranchDescription();

    explicit BranchDescription(ModuleDescription const& m,
			       std::string const& name, 
			       std::string const& fName, 
			       std::string const& pin, 
			       std::string const& alias);

    ~BranchDescription() {}

    ModuleDescription module;

    ProductID productID_;

    // the full name of the type of product this is
    std::string fullClassName_;

    // a readable name of the type of product this is
    std::string friendlyClassName_;

    // a user-supplied name to distinguish multiple products of the same type
    // that are produced by the same producer
    std::string productInstanceName_;

    // The branch ROOT alias , which is settable by the user.
    mutable std::string branchAlias_;

    // The branch name, which is currently derivable fron the other
    // attributes.
    mutable std::string branchName_;

    void init() const;

    void write(std::ostream& os) const;

    bool operator<(BranchDescription const& rh) const;

    bool operator==(BranchDescription const& rh) const;

    std::string const& branchName() const {return branchName_;}
    std::string const& className() const {return fullClassName_;}
    std::string const& moduleLabel() const {return module.moduleLabel_;}
    std::string const& moduleName() const {return module.moduleName_;}
    PassID passID() const {return module.pass;}
    std::string const& processName() const {return module.processName_;}
    ProductID productID() const {return productID_;}
    std::string const& productInstanceName() const {return productInstanceName_;} 
    std::string const& productType() const {return friendlyClassName_;}
    ParameterSetID const& psetID() const {return module.pid;}
    VersionNumber versionNumber() const {return module.versionNumber_;}

    std::string branchAlias() const {return branchAlias_;}
  };
  
  inline
  std::ostream&
  operator<<(std::ostream& os, const BranchDescription& p) {
    p.write(os);
    return os;
  }
}
#endif
