#include "DataFormats/Common/interface/RefCore.h"
#include "DataFormats/Common/interface/RefCoreStreamer.h"
#include "FWCore/Utilities/interface/EDMException.h"
class TBuffer;
#include "TROOT.h"
#include <ostream>

namespace edm {
  void 
  RefCoreStreamer::operator()(TBuffer &R__b, void *objp) {
    if (R__b.IsReading()) {
      cl_->ReadBuffer(R__b, objp);
      RefCore* obj = static_cast<RefCore *>(objp);
      obj->setProductGetter(prodGetter_);
      obj->setProductPtr(0);
    } else {
	assert("Obsolete streamer" == 0);
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
  }

  void setRefCoreStreamer(EDProductGetter const* ep) {
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
  }
}
