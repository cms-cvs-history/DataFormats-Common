#ifndef Common_DetSetAlgorithm_H
#define Common_DetSetAlgorithm_H

#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <algoritm>

//FIXME remove New when ready
namespace edmNew {

  // adapt the RecHit accessors to DSTV
  template <typename DSTV, typename A, typename B>
  typename DSTV::Range detsetRangeFromPair(DSVT const & v, std::pair<A,B> const & p) {
    return v.equal_range(p.first,p.second);
  }


  // invoke f for each object in the range of DataSets selected by sel
  // to ease use, f is passed by reference
  template <typename DSTV, typename A, typename B, typename F>
  void foreachDetSetObject(DSTV const & v, std::pair<A,B> const & sel, F & f) {
    typedef typename DSTV::data_type data_type;
    typename DSTV::Range range = rangeFromPair(v,sel);
    for(typename DSTV::const_iterator id=range.first; id!=range.second; id++)
      std::for_each((*id).begin(), (*id).end(),
		    boost::function<void(const data_type &)>(boost::ref(f)));
  }

  namespace dstvdetails {

    struct Pointer {
      template<typename H> 
      H const * operator()(H const& h) const { return &h;}
    };

  }

  // to write an easy iterator on objects in a range of DataSets selected by sel
  // is left as exercise to the reader 
  // here we provide this not optimal solution...
  template <typename DSTV, typename A, typename B>
  void copyDetSetRange(DSTV const & dstv,    
		       std::vector<typename DSTV::data_type const *> v, 
		       std::pair<A,B> const & sel) {
    typename DSTV::Range range = dstv.equal_range(sel.first,sel.second);
    for(typename DSTV::const_iterator id=range.first; id!=range.second; id++){
      size_t cs = v.size();
      v.resize(cs+range.second-range.first);
      std::transform((*id).begin(), (*id).end(),v.begin()+cs,dstvdetails::Pointer());
    } 
  }
}


#endif //  Common_DetSetAlgorithm_H
