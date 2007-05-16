#ifndef Common_EDProductfwd_h
#define Common_EDProductfwd_h

/*----------------------------------------------------------------------
  
Forward declarations of types in the EDM.

$Id: EDProductfwd.h,v 1.9 2007/03/23 16:53:27 paterno Exp $

----------------------------------------------------------------------*/

namespace edm 
{
  class BasicHandle;
  class EDProduct;
  class EDProductGetter;
  class ProductID;
  class RefCore;

  template <typename C, typename T, typename F> class Ref;
  template <typename K> class RefBase;
  template <typename K> class RefItem;
  template <typename T> class RefProd;
  template <typename C, typename T, typename F> class RefVector;
  template <typename T> class RefVectorBase;
  template <typename C, typename T, typename F> class RefVectorIterator;
  template <typename T> class Wrapper;
  template <typename T> class Handle;
  template <typename T> class OrphanHandle;



  namespace reftobase
  {
    template <typename T>  class BaseHolder;
    template <typename T, class REF> class Holder;
    class IndirectHolderBaseHelper;
    template <typename T> class IndirectHolder;
    template <typename REF> class IndirectHolderHelper;

  }
}

#endif
