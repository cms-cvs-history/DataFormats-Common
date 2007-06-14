#ifndef DataFormats_Common_EDProduct_h
#define DataFormats_Common_EDProduct_h

/*----------------------------------------------------------------------
  
EDProduct: The base class of all things that will be inserted into the
Event.

$Id: EDProduct.h,v 1.8 2007/05/24 16:35:46 paterno Exp $

----------------------------------------------------------------------*/

#include <vector>
#include "boost/shared_ptr.hpp"
#include "DataFormats/Common/interface/EDProductfwd.h"

namespace edm {


  typedef boost::shared_ptr<reftobase::RefHolderBase> helper_ptr;

  class EDProduct {
  public:
    EDProduct();
    virtual ~EDProduct();
    bool isPresent() const {return isPresent_();}

    // We have to use vector<void*> to keep the type information out
    // of the EDProduct class.
    void fillView(ProductID const& id,
		  std::vector<void const*>& view,
		  std::vector<helper_ptr>& helpers) const;

  private:
    // This will never be called.
    // For technical ROOT related reasons, we cannot
    // declare it = 0.
    virtual bool isPresent_() const {return true;}

    virtual void do_fillView(ProductID const& id,
			     std::vector<void const*>& pointers,
			     std::vector<helper_ptr>& helpers) const = 0;
  };
}
#endif
