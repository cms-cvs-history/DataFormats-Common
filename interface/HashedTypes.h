#ifndef DataFormatsCommonHashedTypes_h
#define DataFormatsCommonHashedTypes_h

// $Id: HashedTypes.h,v 1.1.2.1 2006/06/27 21:05:17 paterno Exp $
//

/// Declaration of the enum HashedTypes, used in defining several "id"
/// classes.

namespace edm
{
  enum HashedTypes 
    {
      ModuleDescriptionType,
      ParameterSetType,
      ProcessHistoryType
    };		     
}

#endif // DataFormatsCommonHashedTypes_h
