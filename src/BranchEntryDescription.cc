#include "DataFormats/Common/interface/BranchEntryDescription.h"

/*----------------------------------------------------------------------

$Id: BranchEntryDescription.cc,v 1.1.2.2 2006/06/27 02:17:49 wmtan Exp $

----------------------------------------------------------------------*/

namespace edm {
  BranchEntryDescription::BranchEntryDescription() :
    productID_(),
    parents(),
    cid(),
    status(Success)
  { }

  void
  BranchEntryDescription::init() const {
	assert(0); // Not yet implemented
  }

  void
  BranchEntryDescription::write(std::ostream& os) const {
    // This is grossly inadequate, but it is not critical for the
    // first pass.
    os << "BranchEntryDescription for: " << cid;
  }
    
  bool
  operator==(BranchEntryDescription const& a, BranchEntryDescription const& b) {
    return
      a.productID_ == b.productID_
      && a.cid == b.cid
      && a.status == b.status
      && a.parents == b.parents
      && a.moduleDescriptionID_ == b.moduleDescriptionID_;
  }
}
