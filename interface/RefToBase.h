#ifndef Common_RefToBase_h
#define Common_RefToBase_h
// -*- C++ -*-
//
// Package:     Common
// Class  :     RefToBase
// 
/**\class RefToBase RefToBase.h DataFormats/Common/interface/RefToBase.h

 Description: Interface to a reference to an item based on the base class of the item

 Usage:
    Using an edm:RefToBase<T> allows one to hold references to items in different containers
within the edm::Event where those objects are only related by a base class, T.

\code
   edm::Ref<Foo> foo(...);
   std::vector<edm::RefToBase<Bar> > bars;
   bars.push_back( edm::RefToBase<Bar>( foo ) );
\endcode

*/
//
// Original Author:  Chris Jones
//         Created:  Mon Apr  3 16:37:59 EDT 2006
// $Id: RefToBase.h,v 1.1 2006/04/04 01:54:51 chrjones Exp $
//

// system include files
#include <algorithm>

// user include files

// forward declarations
namespace edm {
  namespace reftobase {
    template <class T>
    class BaseHolder {
     public:
      BaseHolder() {}
      virtual ~BaseHolder() {}
      virtual BaseHolder<T>* clone() const = 0;
      virtual const T* getPtr() const = 0;
    };
    template <class T, class TRef>
      class Holder : public BaseHolder<T> {
       public:
        Holder() {}
        explicit Holder(const TRef& iRef) : ref_(iRef) {}
        virtual ~Holder() {}
        virtual BaseHolder<T>* clone() const { return new Holder<T,TRef>(*this);}
        virtual const T* getPtr() const { return ref_.operator->(); }
       private:
        TRef ref_;
      };
  }
  
  template <class T>
  class RefToBase
{

   public:
      RefToBase() :holder_(0) {}
      template <class TRef>
      explicit RefToBase(const TRef& iRef) : holder_(new reftobase::Holder<T,TRef>(iRef)) {}
      RefToBase(const RefToBase<T>& iOther): 
       holder_( (0==iOther.holder_) ? static_cast<reftobase::BaseHolder<T>*>(0) : iOther.holder_->clone() ) {
      }
      const RefToBase& operator=(const RefToBase<T>& iRHS) {
        RefToBase<T> temp(iRHS);
        this->swap(temp);
        return *this;
      }
      ~RefToBase() { delete holder_;}

      // ---------- const member functions ---------------------

      const T& operator*() const { return *getPtrImpl(); }
      const T* operator->() const { return getPtrImpl(); }
      const T* get() const { return getPtrImpl();}
      
      // ---------- member functions ---------------------------
      void swap( RefToBase<T>& iOther) {
        std::swap(holder_, iOther.holder_);
      }
  
   private:

      // ---------- member data --------------------------------
      const T* getPtrImpl() const {
        if(0 == holder_) { return 0;}
        return holder_->getPtr();
      }

      reftobase::BaseHolder<T>* holder_;
};

}
#endif
