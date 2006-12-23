#ifndef Common_BranchType_h
#define Common_BranchType_h

#include <string>
/*----------------------------------------------------------------------
  
BranchType: The type of a Branch (Event, LuminosityBlock, or Run)

$Id: BranchType.h,v 1.3 2006/11/07 00:30:43 wmtan Exp $
----------------------------------------------------------------------*/

namespace edm {
  // Note: These enum values are used as subscripts for a fixed size array, so they must not change.
  enum BranchType {
    InEvent = 0,
    InLumi = 1,
    InRun = 2,
    EndBranchType = 3
  };

  inline
  std::string BranchTypeToString(BranchType const& branchType) {
    std::string st = ((branchType == InEvent) ? "Event" : ((branchType == InRun) ? "Run" : "LuminosityBlock"));
    return st;
  }

  inline
  std::string BranchTypeToProductTreeName(BranchType const& branchType) {
    return BranchTypeToString(branchType) + "s";
  }

  inline
  std::string BranchTypeToMetaDataTreeName(BranchType const& branchType) {
    return BranchTypeToString(branchType) + "MetaData";
  }

  inline
  std::string BranchTypeToAuxiliaryBranchName(BranchType const& branchType) {
    return BranchTypeToString(branchType) + "Aux";
  }

  inline
  std::ostream&
  operator<<(std::ostream& os, BranchType const& branchType) {
    os << BranchTypeToString(branchType);
    return os;
  }

  namespace poolNames {
    inline
    std::string containerName(std::string const& tree, std::string const& branch) {
      return tree + "(" + branch + ")";
    }

    // MetaData Tree (1 entry per file)
    inline
    std::string
    metaDataTreeName() { return "MetaData"; }

    // Branch on MetaData Tree
    inline
    std::string
    productDescriptionBranchName() {return "ProductRegistry";}

    // Branch on MetaData Tree
    inline
    std::string
    parameterSetMapBranchName() {return "ParameterSetMap";}

    // Branch on MetaData Tree
    inline
    std::string
    moduleDescriptionMapBranchName() {return "ModuleDescriptionMap";}

    // Branch on MetaData Tree
    inline
    std::string
    processHistoryMapBranchName() {return "ProcessHistoryMap";}

    // Branch on MetaData Tree
    inline
    std::string
    processConfigurationMapBranchName() {return "ProcessConfigurationMap";}

    // Branch on MetaData Tree
    inline
    std::string
    fileFormatVersionBranchName() {return "FileFormatVersion";}

    inline
    std::string
    eventTreeName() {return BranchTypeToProductTreeName(InEvent);}

    inline
    std::string
    eventMetaDataTreeName() {return BranchTypeToMetaDataTreeName(InEvent);}
  }
}
#endif
