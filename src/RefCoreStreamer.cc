#include "DataFormats/Common/interface/RefCore.h"
#include "DataFormats/Common/interface/RefCoreStreamer.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "TROOT.h"
#include <ostream>
#include <limits>
#include <cassert>

namespace edm {
  void 
  ProductIDStreamer::operator()(TBuffer &R__b, void *objp) {
    if (R__b.IsReading()) {
      if (oldFormat_) {
        UInt_t i0, i1;
        R__b.ReadVersion(&i0, &i1, cl_);
        unsigned int id;
        R__b >> id;
	assert (id <= std::numeric_limits<unsigned short>::max());
        ProductID* obj = static_cast<ProductID *>(objp);
        *obj = ProductID(0, id);
      } else {
        cl_->ReadBuffer(R__b, objp);
      }
    } else {
      cl_->WriteBuffer(R__b, objp);
    }
  }

  void 
  RefCoreStreamer::operator()(TBuffer &R__b, void *objp) {
    if (R__b.IsReading()) {
      cl_->ReadBuffer(R__b, objp);
      RefCore* obj = static_cast<RefCore *>(objp);
      obj->setProductGetter(prodGetter_);
      obj->setProductPtr(0);
    } else {
      cl_->WriteBuffer(R__b, objp);
    }
  }

  void 
  RefCoreTransientStreamer::operator()(TBuffer &R__b, void *objp) {
    typedef RefCore::RefCoreTransients RefCoreTransients;
    if (R__b.IsReading()) {
      cl_->ReadBuffer(R__b, objp);
      RefCoreTransients* obj = static_cast<RefCoreTransients *>(objp);
      obj->setProductGetter(prodGetter_);
      obj->setProductPtr(0);
    } else {
      RefCoreTransients* obj = static_cast<RefCoreTransients *>(objp);
      if (obj->isTransient()) {
        throw Exception(errors::InvalidReference,"Inconsistency")
          << "RefCoreStreamer: transient Ref or Ptr cannot be made persistent.";
      }
      cl_->WriteBuffer(R__b, objp);
    }
  }

  void setRefCoreStreamer() {
    {
      TClass *cl = gROOT->GetClass("edm::RefCore::RefCoreTransients");
      if (cl->GetStreamer() == 0) {
        cl->AdoptStreamer(new RefCoreTransientStreamer(0));
      }
    }
    {
      TClass *cl = gROOT->GetClass("edm::RefCore");
      if (cl->GetStreamer() != 0) {
        cl->AdoptStreamer(0);
      }
    }
    {
      TClass *cl = gROOT->GetClass("edm::ProductID");
      if (cl->GetStreamer() != 0) {
        cl->AdoptStreamer(0);
      }
    }
  }

  void setRefCoreStreamer(EDProductGetter const* ep, bool oldFormat) {
    {
      TClass *cl = gROOT->GetClass("edm::RefCore::RefCoreTransients");
      RefCoreTransientStreamer *st = static_cast<RefCoreTransientStreamer *>(cl->GetStreamer());
      if (st == 0) {
        cl->AdoptStreamer(new RefCoreTransientStreamer(ep));
      } else {
        st->setProductGetter(ep);
      }
    }
    {
      TClass *cl = gROOT->GetClass("edm::RefCore");
      RefCoreStreamer *st = static_cast<RefCoreStreamer *>(cl->GetStreamer());
      if (st == 0) {
        cl->AdoptStreamer(new RefCoreStreamer(ep));
      } else {
        st->setProductGetter(ep);
      }
    }
    {
      TClass *cl = gROOT->GetClass("edm::ProductID");
      ProductIDStreamer *st = static_cast<ProductIDStreamer *>(cl->GetStreamer());
      if (st == 0) {
        cl->AdoptStreamer(new ProductIDStreamer(oldFormat));
      }
    }
  }
}
