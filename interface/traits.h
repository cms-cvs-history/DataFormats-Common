#ifndef Common_traits_h
#define Common_traits_h

/*----------------------------------------------------------------------

Definition of traits templates used in the EDM.  

$Id: traits.h,v 1.12 2007/02/07 23:01:43 paterno Exp $

----------------------------------------------------------------------*/

#include <deque>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <string>

#include "FWCore/Utilities/interface/GCCPrerequisite.h"

namespace edm
{
  //------------------------------------------------------------
  //
  // The trait struct template key_traits<K> is used to carry
  // information relevant to the type K when used as a 'key' in
  // RefVector and its related classes and templates.
  //
  // The general case works only for integral types K; for more
  // 'esoteric' types, one must introduce an explicit specialization.
  // That specialization must initialize the static data member
  // 'value'.

  template <class K>
  struct key_traits
  {
    typedef K key_type;
    static const key_type value;
  };

  template <class K> 
  typename  key_traits<K>::key_type const
  key_traits<K>::value =
    std::numeric_limits<typename key_traits<K>::key_type>::max();

  // If we ever need to support instantiations of std::basic_string
  // other than std::string, this is the place to do it.

  // For value, we make a 1-character long string that contains an
  // unprintable character; we are hoping nobody ever uses such a
  // string as a legal key.
  template <> 
  struct key_traits<std::string>
  {
    typedef std::string key_type;
    static const key_type value;
  };


  //------------------------------------------------------------
  //
  // DoNotSortUponInsertion is a base class. Derive your own class X
  // from DoNotSortUponInsertion when: 
  //
  // 1. You want to use DetSetVector<X> as an EDProduct, but
  //
  // 2. You do *not* want the Event::put member template to cause the
  // DetSet<X> instances within the DetSetVector<X> to be sorted.
  //
  // DoNotSortUponInsertion has no behavior; it is used at compile
  // time to influence the behavior of Event::put.
  //
  // Usage:
  //    class MyClass : public edm::DoNotSortUponInsertion { ... }
  //
  struct DoNotSortUponInsertion { };

  // Other is a base class. NEVER USE IT. It is for the
  // core of the event model only.
  struct Other { };

#if ! GCC_PREREQUISITE(3,4,4)
  //------------------------------------------------------------
  //
  // The trait struct template has_postinsert_trait<T> is used to
  // indicate whether or not the type T has a member function
  //
  //      void T::post_insert()
  //
  // This is used by Event::put to determine (at compile time) whether
  // or not such a function must be called.
  //
  // We assume the 'general case' for T is to not support post_insert.
  // Classes which do support post_insert must specialize this trait.
  //
  //------------------------------------------------------------

  template <class T>
  struct has_postinsert_trait
  {
    static bool const value = false;
  };

  //------------------------------------------------------------
  //
  // The trait struct template has_swap<T> is used to indicate
  // whether or not the type T has a member function
  //
  //   void T::swap(T&)
  //
  // This is used by Wrapper<T>::Wrapper(std::auto_ptr<T> x) to
  // determine (at compile time) whether a swap or a copy should be
  // used to set the state of the constructed Wrapper<T>.
  //
  // We provide partial specializations for standard library
  // collections here.  EDM container emplates are specialized in
  // their own headers.
  //------------------------------------------------------------

  template <class T>
  struct has_swap
  {
    static bool const value = false;
  };  

  template <class T, class A>
  struct has_swap<std::deque<T,A> >
  {
    static bool const value = true;
  };

  template <class T, class A>
  struct has_swap<std::list<T,A> >
  {
    static bool const value = true;
  };

  
  template <class K, class V, class C, class A>
  struct has_swap<std::map<K,V,C,A> >
  {
    static bool const value = true;
  };

  template <class K, class V, class C, class A>
  struct has_swap<std::multimap<K,V,C,A> >
  {
    static bool const value = true;
  };


  template <class V, class C, class A>
  struct has_swap<std::set<V,C,A> >
  {
    static bool const value = true;
  };


  template <class V, class C, class A>
  struct has_swap<std::multiset<V,C,A> >
  {
    static bool const value = true;
  };


  template <class T, class A>
  struct has_swap<std::vector<T,A> >
  {
    static bool const value = true;
  };

  template <>
  struct has_swap<std::string>
  {
    static bool const value = true;
  };
#endif

  //------------------------------------------------------------
  //
  // The trait struct template has_fillView<T> is used to
  // indicate whether or not the type T has a member function
  //
  //      void T::fillView(std::vector<void const*>&) const
  //
  // We assume the 'general case' for T is to not support fillView.
  // Classes which do support fillView must specialize this trait.
  //
  //------------------------------------------------------------

  template <class T>
  struct has_fillView
  {
    static bool const value = false;
  };

  template <class T, class A>
  struct has_fillView<std::vector<T,A> >
  {
    static bool const value = true;
  };

  template <class A>
  struct has_fillView<std::vector<bool,A> >
  {
    static bool const value = false;
  };

  template <class T, class A>
  struct has_fillView<std::list<T,A> >
  {
    static bool const value = true;
  };

  template <class T, class A>
  struct has_fillView<std::deque<T,A> >
  {
    static bool const value = true;
  };

  template <class T, class A>
  struct has_fillView<std::set<T,A> >
  {
    static bool const value = true;
  };
}

#endif
