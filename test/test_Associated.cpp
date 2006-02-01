#include "DataFormats/Common/interface/Associated.h"
#include <vector>

struct AAA { 
  void xxx() const { }
};

struct BBB { 
};

typedef std::vector<AAA> AAACollection;

class BBBRefProds {
public:
  typedef edm::RefProd<AAACollection> AAAsRef;
  BBBRefProds() { }
  const AAAsRef & aaas() const { return aaas_; }
  void setAaas( const AAAsRef & r ) { aaas_ = r; }
  
private:
  AAAsRef aaas_;
};

typedef edm::ExtCollection<std::vector<BBB>, BBBRefProds> BBBCollection;
typedef edm::Ref<BBBCollection> BBBRef;


void testRef() {
  const BBBRef bbbRef;
  const AAA & aaa = edm::Associated<AAACollection>::get( bbbRef, & BBBRefProds::aaas );
  aaa.xxx();
}

int main() {
  return 0;
}

