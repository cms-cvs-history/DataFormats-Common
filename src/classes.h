#include "DataFormats/Common/interface/BranchDescription.h"
#include "DataFormats/Common/interface/BranchEntryDescription.h"
#include "DataFormats/Common/interface/BranchKey.h"
#include "DataFormats/Common/interface/EDProduct.h"
#include "DataFormats/Common/interface/EventAux.h"
#include "DataFormats/Common/interface/EventID.h"
#include "DataFormats/Common/interface/EventProvenance.h"
#include "DataFormats/Common/interface/ParameterSetBlob.h"
#include "DataFormats/Common/interface/ParameterSetID.h"
#include "DataFormats/Common/interface/ProductID.h"
#include "DataFormats/Common/interface/ProductRegistry.h"
#include "DataFormats/Common/interface/RefBase.h"
#include "DataFormats/Common/interface/RefItem.h"
#include "DataFormats/Common/interface/RefVectorBase.h"
#include "DataFormats/Common/interface/Timestamp.h"
#include "DataFormats/Common/interface/HLTPathStatus.h"
#include "DataFormats/Common/interface/HLTGlobalStatus.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Common/interface/Wrapper.h"

#include <vector>

namespace { namespace {
  edm::Wrapper<std::vector<unsigned long> > dummy1;
  edm::Wrapper<std::vector<unsigned int> > dummy2;
  edm::Wrapper<std::vector<long> > dummy3;
  edm::Wrapper<std::vector<int> > dummy4;
  edm::Wrapper<std::vector<std::string> > dummy5;
  edm::Wrapper<std::vector<char> > dummy6;
  edm::Wrapper<std::vector<unsigned char> > dummy7;
  edm::Wrapper<std::vector<short> > dummy8;
  edm::Wrapper<std::vector<unsigned short> > dummy9;
  edm::Wrapper<std::vector<double> > dummy10;
  edm::Wrapper<std::vector<long double> > dummy11;
  edm::Wrapper<std::vector<float> > dummy12;
  edm::Wrapper<std::vector<bool> > dummy13;

  edm::Wrapper<unsigned long> dummyw1;
  edm::Wrapper<unsigned int> dummyw2;
  edm::Wrapper<long> dummyw3;
  edm::Wrapper<int> dummyw4;
  edm::Wrapper<std::string> dummyw5;
  edm::Wrapper<char> dummyw6;
  edm::Wrapper<unsigned char> dummyw7;
  edm::Wrapper<short> dummyw8;
  edm::Wrapper<unsigned short> dummyw9;
  edm::Wrapper<double> dummyw10;
  edm::Wrapper<long double> dummyw11;
  edm::Wrapper<float> dummyw12;
  edm::Wrapper<bool> dummyw13;

  edm::Wrapper<edm::HLTPathStatus> dummyx16;
  edm::Wrapper<std::vector<edm::HLTPathStatus> > dummyx17;
  edm::Wrapper<edm::HLTGlobalStatus> dummyx18;
  edm::Wrapper<edm::TriggerResults> dummyx19;

  edm::RefItem<unsigned int> dummyRefItem;
  edm::RefBase<std::vector<unsigned int>::size_type> dummRefBase;
  edm::RefVectorBase<std::vector<unsigned int>::size_type> dummyRefVectorBase;

}}
