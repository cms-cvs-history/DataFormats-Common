#include "DataFormats/Common/interface/ProcessConfiguration.h"

int main()
{
  edm::ProcessConfiguration pc1;
  assert( pc1 == pc1 );
  edm::ProcessConfiguration pc2;
  assert( pc1 == pc2 );
  pc2.processName_ = "reco2";
  edm::ProcessConfiguration pc3;
  pc3.processName_ = "reco3";
  
  edm::ProcessConfigurationID id1 = pc1.id();
  edm::ProcessConfigurationID id2 = pc2.id();
  edm::ProcessConfigurationID id3 = pc3.id();

  assert( id1 != id2 );
  assert( id2 != id3 );
  assert( id3 != id1 );

  edm::ProcessConfiguration pc4;
  pc4.processName_ = "reco2";
  edm::ProcessConfigurationID id4 = pc4.id();
  assert( pc4 == pc2 );
  assert ( id4 == id2 );
}
