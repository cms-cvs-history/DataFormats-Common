#include <cassert>
#include <string>
#include "DataFormats/Common/interface/ProcessHistory.h"
#include "DataFormats/Common/interface/ParameterSetID.h"
#include "FWCore/Utilities/interface/GetPassID.h"
#include "FWCore/Utilities/interface/GetReleaseVersion.h"

int main()
{
  edm::ProcessHistory pnl1;
  assert( pnl1 == pnl1 );
  edm::ProcessHistory pnl2;
  assert( pnl1 == pnl2 );
  edm::ProcessHistoryItem iHLT(std::string("HLT"), edm::ParameterSetID(), edm::getReleaseVersion(), edm::getPassID());
  edm::ProcessHistoryItem iRECO(std::string("RECO"), edm::ParameterSetID(), edm::getReleaseVersion(), edm::getPassID());
  pnl2.push_back(iHLT);
  assert( pnl1 != pnl2 );
  edm::ProcessHistory pnl3;
  pnl3.push_back(iHLT);
  pnl3.push_back(iRECO);
  
  edm::ProcessHistoryID id1 = pnl1.id();
  edm::ProcessHistoryID id2 = pnl2.id();
  edm::ProcessHistoryID id3 = pnl3.id();

  assert( id1 != id2 );
  assert( id2 != id3 );
  assert( id3 != id1 );

  edm::ProcessHistory pnl4;
  pnl4.push_back(iHLT);
  edm::ProcessHistoryID id4 = pnl4.id();
  assert( pnl4 == pnl2 );
  assert ( id4 == id2 );

  edm::ProcessHistory pnl5;
  pnl5 = pnl3;
  assert( pnl5 == pnl3 );
  assert( pnl5.id() == pnl3.id() );
}
