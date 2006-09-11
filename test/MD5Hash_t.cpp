#include <cassert>
#include "DataFormats/Common/interface/MD5Hash.h"

void work()
{
  using edm::MD5Hash;

  MD5Hash def;
  assert(def.data[0] == 0xd4);
  std::string s("deadbeefdeadbeefdeadbeefdeadbeef");
  MD5Hash cow(s);
  for (int i = 0; i !=4; ++i)
    {
      assert(cow.data[0+4*i] == 0xde);
      assert(cow.data[1+4*i] == 0xad);
      assert(cow.data[2+4*i] == 0xbe);
      assert(cow.data[3+4*i] == 0xef);
    }
}


int main()
{
  try  { work(); }
  catch ( ... ) { return 1; }
  return 0;
}
