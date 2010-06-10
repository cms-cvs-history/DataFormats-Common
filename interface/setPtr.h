#ifndef DataFormats_Common_setPtr_h
#define DataFormats_Common_setPtr_h
// -*- C++ -*-
//
// Package:     Common
// Class  :     setPtr
// 
/**\class setPtr setPtr.h DataFormats/Common/interface/setPtr.h

 Description: Helper function used to implement the edm::Ptr class

 Usage:
    This is an internal detail of edm::Ptr interaction with edm::Wrapper and should not be used by others

*/
//
// Original Author:  Chris Jones
//         Created:  Sat Oct 20 11:45:38 CEST 2007
//

// system include files

// user include files
#include "DataFormats/Common/interface/FillView.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "Reflex/Object.h"
#include "Reflex/Type.h"

// forward declarations
namespace edm {
  namespace detail {
    
    
    template <class COLLECTION>
    void
    reallySetPtr(COLLECTION const& coll,
                 const std::type_info& iToType,
                 unsigned long iIndex,
                 void const*& oPtr)
    {
      typedef COLLECTION                            product_type;
      typedef typename GetProduct<product_type>::element_type     element_type;
      typedef typename product_type::const_iterator iter;
      typedef typename product_type::size_type      size_type;
      
      if(iToType == typeid(element_type)) {
        iter it = coll.begin();
        std::advance(it,iIndex);
        element_type const* address = GetProduct<product_type>::address( it );
        oPtr = address;
      } else {
        using Reflex::Type;
        using Reflex::Object;
        static const Type s_type(Type::ByTypeInfo(typeid(element_type)));

        iter it = coll.begin();
        std::advance(it,iIndex);
        element_type const* address = GetProduct<product_type>::address( it );

        // The const_cast below is needed because
        // Object's constructor requires a pointer to
        // non-const void, although the implementation does not, of
        // course, modify the object to which the pointer points.
        Object obj(s_type, const_cast<void*>(static_cast<const void*>(address)));
        Object cast = obj.CastObject(Type::ByTypeInfo(iToType));
        if(0 != cast.Address()) {
          oPtr = cast.Address(); // returns void*, after pointer adjustment
        } else {
          Exception::throwThis(errors::LogicError,
            "TypeConversionError"
             "edm::Ptr<> : unable to convert type ",
             typeid(element_type).name(),
             " to ",
             iToType.name(),
             "\n");
        }
      }
    }
  }
  
  template <class T, class A>
  void
  setPtr(std::vector<T,A> const& obj,
         const std::type_info& iToType,
         unsigned long iIndex,
         void const*& oPtr) {
    detail::reallySetPtr(obj, iToType, iIndex, oPtr);
  }
  
  template <class T, class A>
  void
  setPtr(std::list<T,A> const& obj,
         const std::type_info& iToType,
         unsigned long iIndex,
         void const*& oPtr) {
    detail::reallySetPtr(obj, iToType, iIndex, oPtr);
  }
  
  template <class T, class A>
  void
  setPtr(std::deque<T,A> const& obj,
         const std::type_info& iToType,
         unsigned long iIndex,
         void const*& oPtr) {
    detail::reallySetPtr(obj, iToType, iIndex, oPtr);
  }
  
  template <class T, class A, class Comp>
  void
  setPtr(std::set<T,A,Comp> const& obj,
         const std::type_info& iToType,
         unsigned long iIndex,
         void const*& oPtr) {
    detail::reallySetPtr(obj, iToType, iIndex, oPtr);
  }

}

#endif
