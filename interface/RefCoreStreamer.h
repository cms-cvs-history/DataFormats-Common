#ifndef DataFormats_Common_RefCoreStreamer_h
#define DataFormats_Common_RefCoreStreamer_h

#include "TClassStreamer.h"
#include "TClassRef.h"
#include <assert.h>

class TBuffer;

namespace edm {
  class EDProductGetter;
  class RefCoreStreamer : public TClassStreamer {
  public:
    explicit RefCoreStreamer(EDProductGetter const* ep) : cl_("edm::RefCore"), prodGetter_(ep) {}

    EDProductGetter const* setProductGetter(EDProductGetter const* ep) {
        EDProductGetter const* old = prodGetter_;
        prodGetter_ = ep;
        return old;
    }
    void operator() (TBuffer &R__b, void *objp);

  private:
    TClassRef cl_;
    EDProductGetter const* prodGetter_;
  };


  class RefCoreCheckTransientOnWriteStreamer : public TClassStreamer {
  public:
    explicit RefCoreCheckTransientOnWriteStreamer() : cl_("edm::RefCore::CheckTransientOnWrite"){}

    void operator() (TBuffer &R__b, void *objp);

  private:
    TClassRef cl_;
  };

  void setRefCoreStreamer(bool resetAll = false);
  EDProductGetter const* setRefCoreStreamer(EDProductGetter const* ep);
}
#endif
