#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include <iostream>
#include <boost/function.hpp>

struct T {

  float v;
};


typedef edmNew::DetSetVector<T> DSTV;
typedef edmNew::DetSet<T> DST;
typedef DSTV::FastFiller FF;

void print0(DST const & d) {
  std::cout << d[0].v << std::endl;
}


int main() {
  DSTV dstv;

  {
    FF ff(dstv,1);
    ff.push_back(T());
    ff[0].v=2.1;
  }
  {
    FF ff(dstv,2);
    ff.push_back(T());
    ff.push_back(T());
  }
  std::cout << dstv.size() << std::endl;
  std::cout << dstv.dataSize() << std::endl;
  std::cout << dstv.detsetSize(0) << std::endl;

  DST d1 = *dstv.find(2);
  d1[0].v=3.14;
  DST d2 = dstv.insert(4,3);
  d2[0].v=4.15;

  std::for_each(dstv.begin(),dstv.end(),boost::function<void(DST const&)>(print0));

  return 0;
}
