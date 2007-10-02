#ifndef Common_FillView_h
#define Common_FillView_h

/*----------------------------------------------------------------------
  
Several fillView function templates, to provide View support for 
Standard Library containers.

$Id: FillView.h,v 1.6 2007/09/17 14:15:21 llista Exp $

----------------------------------------------------------------------*/

#include <string>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include "DataFormats/Common/interface/RefTraits.h"
#include "DataFormats/Common/interface/RefVectorTraits.h"

namespace edm {
  template<typename C, typename T, typename F> class RefVector;
  template<typename C, typename T, typename F> class Ref;
  namespace detail {

    // Function template reallyFillView<C> can fill views for
    // standard-library collections of appropriate types (vector, list,
    // deque, set).

    template<typename C, typename T, typename F>
    struct FillViewRefTypeTrait {
      typedef Ref<C, T, F> type;
    };
    
    template<typename C, typename T, typename F, typename T1, typename F1>
    struct FillViewRefTypeTrait<RefVector<C, T, F>, T1, F1> {
      typedef typename refhelper::RefVectorTrait<C, T, F>::ref_type type;
    };
  }
}

#include "DataFormats/Common/interface/EDProductfwd.h"
#include "DataFormats/Common/interface/RefHolder_.h"
#include "DataFormats/Provenance/interface/ProductID.h"
#include "DataFormats/Common/interface/RefVectorHolderBase.h"

namespace edm {
  namespace detail {
    template<typename COLLECTION>
    struct GetProduct {
      typedef typename COLLECTION::value_type element_type;
      typedef typename COLLECTION::const_iterator iter;
      static const element_type * address( const iter & i ) {
	return &*i;
      }
      static const COLLECTION * product( const COLLECTION & coll ) {
	return & coll;
      }
    };

    template<typename C, typename T, typename F>
    struct GetProduct<RefVector<C, T, F> > {
     typedef T element_type;
      typedef typename RefVector<C, T, F>::const_iterator iter;
      static const element_type * address( const iter & i ) {
	return &**i;
      }
      static const C * product( const RefVector<C, T, F> & coll ) {
	return coll.product();
      }
    };

    template <class COLLECTION>
    void
    reallyFillView(COLLECTION const& coll,
		   ProductID const& id,
		   std::vector<void const*>& ptrs,
		   helper_vector& helpers)
    {
      typedef COLLECTION                            product_type;
      typedef typename GetProduct<product_type>::element_type     element_type;
      typedef typename product_type::const_iterator iter;
      typedef typename product_type::size_type      size_type;
      typedef typename FillViewRefTypeTrait<product_type, 
	typename refhelper::ValueTrait<product_type>::value, 
	typename refhelper::FindTrait<product_type, 
	typename refhelper::ValueTrait<product_type>::value>::value>::type ref_type;
      typedef reftobase::RefHolder<ref_type>        holder_type;
      
      size_type key = 0;
      for (iter i = coll.begin(), e = coll.end(); i!=e; ++i, ++key) {
	element_type const* address = GetProduct<product_type>::address(i);
	ptrs.push_back(address);
	ref_type ref(id, address, key, GetProduct<product_type>::product(coll) );
	holder_type h(ref);
	helpers.push_back(&h);
      }
    }
  }

  template <class T, class A>
  void
  fillView(std::vector<T,A> const& obj,
	   ProductID const& id,
	   std::vector<void const*>& ptrs,
	   helper_vector& helpers)
  {
    detail::reallyFillView(obj, id, ptrs, helpers);
  }

  template <class T, class A>
  void
  fillView(std::list<T,A> const& obj,
	   ProductID const& id,
	   std::vector<void const*>& ptrs,
	   helper_vector& helpers)
  {
    detail::reallyFillView(obj, id, ptrs, helpers);
  }

  template <class T, class A>
  void
  fillView(std::deque<T,A> const& obj,
	   ProductID const& id,
	   std::vector<void const*>& ptrs,
	   helper_vector& helpers)
  {
    detail::reallyFillView(obj, id, ptrs, helpers);
  }

  template <class T, class A, class Comp>
  void
  fillView(std::set<T,A,Comp> const& obj,
	   ProductID const& id,
	   std::vector<void const*>& ptrs,
	   helper_vector& helpers)
  {
    detail::reallyFillView(obj, id, ptrs, helpers);
  }

}

#include "DataFormats/Common/interface/RefHolder.h"

/*
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefVector.h"
#include "DataFormats/Common/interface/RefToBase.h"
*/

#endif
