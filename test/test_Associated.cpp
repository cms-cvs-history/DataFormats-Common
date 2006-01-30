#include "DataFormats/Common/interface/Associated.h"
#include <vector>

class AAA { };
class BBB { };

typedef std::vector<AAA> AAACollection;

class BBBRefProds {
public:
  typedef edm::RefProd<AAACollection> AAAsRef;
  BBBRefProds() { }
  const AAAsRef & aaas() const { return aaas_; }
  void setAaas( const AAAssRef & r ) { aaas_ = r; }
  
private:
  AAAssRef aaas_;
};

typedef ext_collection<std::vector<BBB>, BBBRefProds> BBBCollection;
typedef edm::Ref<BBBCollection> BBBRef;


void testRef() {
  const BBBRef bbbRef;
  const AAA & aaa = 
    Associated<AAACollection>::get( 
      bbbRef, & BBBRefProds::aaas );
}

int main() {
  return 0;
}

