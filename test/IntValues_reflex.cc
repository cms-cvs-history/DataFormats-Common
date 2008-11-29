// -*- C++ -*-
//
// Package:     Common
// Class  :     IntValues_reflex
// 
// Implementation:
//     Hand create the reflex information for some simple tests
//
// Original Author:  Chris Jones
//         Created:  Wed Oct 31 16:23:47 EDT 2007
// $Id: IntValues_reflex.cc,v 1.2 2008/11/28 17:44:48 wmtan Exp $
//

// system include files
#include "Reflex/Builder/ReflexBuilder.h"

// user include files
#include "DataFormats/Common/test/IntValues.h"
#include "FWCore/Utilities/interface/UseReflex.h"

namespace {
  using namespace Reflex;
  using namespace test_with_reflex;
  //Need Reflex dicctionaries for the conversion
  Type type_intvalue = TypeBuilder("IntValue");
  Type type_intvalue2 = TypeBuilder("IntValue2");
  
  void type_intvalue_d() {
    ClassBuilder("IntValue", typeid(IntValue), sizeof(IntValue), PUBLIC, STRUCT);
  }
  void type_intvalue2_d() {
    ClassBuilder("IntValue2",typeid(IntValue2),sizeof(IntValue2),PUBLIC, STRUCT).
    AddBase(type_intvalue,BaseOffset<IntValue,IntValue2>::Get(),PUBLIC);
  }
  
  struct Dictionaries {
    Dictionaries() {
      type_intvalue_d();
      type_intvalue2_d();
    }
    ~Dictionaries() {
      type_intvalue.Unload();
      type_intvalue2.Unload();
    }
  };
  static Dictionaries instance;
}
