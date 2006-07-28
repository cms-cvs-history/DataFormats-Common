#include <iterator>
#include <sstream>
#include <string>
#include "SealZip/MD5Digest.h"

#include "DataFormats/Common/interface/ProcessHistory.h"


namespace edm {
  ProcessHistoryID
  ProcessHistory::id() const
  {
    if(id_.isValid() ) {
      return id_;
    }
    // This implementation is ripe for optimization.
    // We do not use operator<< because it does not write out everything.
    std::ostringstream oss;
    for (const_iterator i = begin(), e = end(); i != e; ++i) {
      oss << i->processName() << ' '
	  << i->parameterSetID() << ' ' 
	  << i->releaseVersion() << ' '
	  << i->passID() << ' ';
    }
    std::string stringrep = oss.str();
    seal::MD5Digest md5alg;
    md5alg.update(stringrep.data(), stringrep.size());
    ProcessHistoryID tmp(md5alg.format());
    id_.swap( tmp );
    return id_;
  }

  std::ostream&
  operator<<(std::ostream& ost, ProcessHistory const& ph) {
    ost << "Process History = ";
    std::copy(ph.begin(),ph.end(), std::ostream_iterator<ProcessHistory::value_type>(ost,";"));
    return ost;
  }
}
