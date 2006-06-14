#include "DataFormats/Common/interface/Wrapper.h"

namespace edm {
  std::string
  wrappedClassName(std::string const& className) {
    std::string const wrapperBegin("edm::Wrapper<");
    std::string const wrapperEnd1(">");
    std::string const wrapperEnd2(" >");
    std::string const& wrapperEnd = (className[className.size()-1] == '>' ? wrapperEnd2 : wrapperEnd1);
    return wrapperBegin + className + wrapperEnd;
  }
}
