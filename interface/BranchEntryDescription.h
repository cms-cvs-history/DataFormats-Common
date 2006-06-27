#ifndef Common_BranchEntryDescription_h
#define Common_BranchEntryDescription_h

/*----------------------------------------------------------------------
  
BranchEntryDescription: The event dependent portion of the description of a product
and how it came into existence.

$Id: BranchEntryDescription.h,v 1.1.2.2 2006/06/27 02:17:49 wmtan Exp $
----------------------------------------------------------------------*/
#include <ostream>
#include <vector>

#include "DataFormats/Common/interface/ConditionsID.h"
#include "DataFormats/Common/interface/ProductID.h"
#include "DataFormats/Common/interface/ModuleDescription.h"

/*
  BranchEntryDescription

  definitions:
  Product: The EDProduct to which a provenance object is associated

  Creator: The EDProducer that made the product.

  Parents: The EDProducts used as input by the creator.
*/

namespace edm {
  struct BranchEntryDescription {
    enum CreatorStatus { Success = 0,
			 ApplicationFailure,
			 InfrastructureFailure,
			 CreatorNotRun };

    BranchEntryDescription ();

    ~BranchEntryDescription() {}

    ProductID productID_;

    // The EDProduct IDs of the parents
    std::vector<ProductID> parents;

    // a single identifier that describes all the conditions used
    ConditionsID cid; // frame ID?

    // the last of these is not in the roadmap, but is on the board

    // if modules can or will place an object in the event
    // even though something not good occurred, like a timeout, then
    // this may be useful - or if the I/O system makes blank or default
    // constructed objects and we need to distinguish between zero
    // things in a collection between nothing was found and the case
    // where a failure caused nothing to be in the collection.
    // Should a provenance be inserted even if a module fails to 
    // create the output it promised?
    CreatorStatus status;

    ModuleDescriptionID moduleDescriptionID_;

    // transient.  Filled in from the hash when needed.
    mutable ModuleDescription module_;

    void init() const;

    void write(std::ostream& os) const;

    std::string const& moduleName() const {init(); return module_.moduleName_;}
    PassID const& passID() const {init(); return module_.pass;}
    ParameterSetID const& psetID() const {init(); return module_.pid;}
    VersionNumber const& versionNumber() const {init(); return module_.versionNumber_;}

    ModuleDescriptionID const& moduleDescriptionID() const {return moduleDescriptionID_;}
  };
  
  inline
  std::ostream&
  operator<<(std::ostream& os, BranchEntryDescription const& p) {
    p.write(os);
    return os;
  }

  bool operator==(BranchEntryDescription const& a, BranchEntryDescription const& b);
}
#endif
