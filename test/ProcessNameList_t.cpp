#include <cassert>
#include <string>
#include "DataFormats/Common/interface/ProcessNameList.h"

int main()
{
  edm::ProcessNameList pnl1;
  assert( pnl1 == pnl1 );
  edm::ProcessNameList pnl2;
  assert( pnl1 == pnl2 );
  pnl2.push_back(std::string("HLT"));
  assert( pnl1 != pnl2 );
  edm::ProcessNameList pnl3;
  pnl3.push_back(std::string("HLT"));
  pnl3.push_back(std::string("RECO"));
  
  edm::ProcessNameListID id1 = pnl1.id();
  edm::ProcessNameListID id2 = pnl2.id();
  edm::ProcessNameListID id3 = pnl3.id();

  assert( id1 != id2 );
  assert( id2 != id3 );
  assert( id3 != id1 );

  edm::ProcessNameList pnl4;
  pnl4.push_back(std::string("HLT"));
  edm::ProcessNameListID id4 = pnl4.id();
  assert( pnl4 == pnl2 );
  assert ( id4 == id2 );

  edm::ProcessNameList pnl5;
  pnl5 = pnl3;
  assert( pnl5 == pnl3 );
  assert( pnl5.id() == pnl3.id() );
}
