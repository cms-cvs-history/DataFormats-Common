#ifndef Common_EventAux_h
#define Common_EventAux_h

#include "DataFormats/Common/interface/ProcessNameList.h"
#include "DataFormats/Common/interface/ProcessNameListID.h"
#include "DataFormats/Common/interface/EventID.h"
#include "DataFormats/Common/interface/Timestamp.h"
#include "DataFormats/Common/interface/LuminosityBlockID.h"

// Aux2iliary event data that is persistent

namespace edm
{
  struct EventAux {
    EventAux() :
	processHistoryID_(),
	processHistory_(),
	id_(),
	time_(),
	luminosityBlockID_() {}
    //FIXME: keep temporarily for backwards compatibility
    explicit EventAux(EventID const& id) :
	processHistoryID_(),
	processHistory_(),
	id_(id),
	time_(),
	luminosityBlockID_() {}
    EventAux(EventID id, Timestamp const& time, LuminosityBlockID lb) :
	processHistoryID_(),
	processHistory_(),
	id_(id),
	time_(time),
	luminosityBlockID_(lb) {}
    ~EventAux() {}
    void init() const;
    ProcessNameList& processHistory() const {init(); return processHistory_;}
    EventID const& id() const {return id_;}
    Timestamp const& time() const {return time_;}
    LuminosityBlockID const& luminosityBlockID() const {return luminosityBlockID_;}
    // most recently process that processed this event
    // is the last on the list, this defines what "latest" is
    mutable ProcessNameListID processHistoryID_;
    // Transient
    mutable ProcessNameList processHistory_;
    // Event ID
    EventID id_;
    // Time from DAQ
    Timestamp time_;
    // Associated Luminosity Block identifier.
    LuminosityBlockID luminosityBlockID_;
  };
}

#endif
