#include "DataFormats/Common/interface/EventAux.h"
#include "FWCore/Framework/interface/ProcessNameListRegistry.h"

/*----------------------------------------------------------------------

$Id: EventAux.cc,v 1.1.2.2 2006/06/27 02:17:50 wmtan Exp $

----------------------------------------------------------------------*/

namespace edm {
  void
  EventAux::init() const {
    if (processHistoryPtr_.get() == 0) {
      processHistoryPtr_ = boost::shared_ptr<ProcessNameList>(new ProcessNameList);
      if (processHistoryID_ != ProcessNameListID()) {
        bool found = ProcessNameListRegistry::instance()->getMapped(processHistoryID_, *processHistoryPtr_);
        assert(found);
      }
    }
  }
}
