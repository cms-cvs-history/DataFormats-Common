#include "DataFormats/Common/interface/EventID.h"
#include <ostream>

namespace edm {
  std::ostream& operator<<(std::ostream& oStream, EventID const& iID) {
    oStream<< "run: "<< iID.run()<<" event: "<<iID.event();
    return oStream;
  }
}
