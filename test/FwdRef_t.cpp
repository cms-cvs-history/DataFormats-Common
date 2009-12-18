#include <iostream>
#include <string>
#include <utility>

#include <Utilities/Testing/interface/CppUnit_testdriver.icpp>
#include <cppunit/extensions/HelperMacros.h>

#include "DataFormats/Common/interface/FwdRef.h"
#include "DataFormats/Common/interface/EDProductGetter.h"
#include "FWCore/Utilities/interface/EDMException.h"

#include "SimpleEDProductGetter.h"

class TestFwdRef: public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestFwdRef);
  CPPUNIT_TEST(default_ctor_without_active_getter);
  //CPPUNIT_TEST(default_ctor_without_active_getter_string_key);
  CPPUNIT_TEST(default_ctor_with_active_getter);
  CPPUNIT_TEST(nondefault_ctor);
  //CPPUNIT_TEST(nondefault_ctor_2);
  CPPUNIT_TEST(using_wrong_productid);
  CPPUNIT_TEST_SUITE_END();

 public:
  typedef std::vector<int>           product1_t;
  typedef std::map<std::string, int> product2_t;

  typedef edm::Ref<product1_t>    ref1_t;
  typedef edm::FwdRef<product1_t> fwdref1_t;
  //typedef edm::Ref<product2_t, int> ref2_t;
  

  TestFwdRef() { } 
  ~TestFwdRef() {}
  void setUp() {}
  void tearDown() {}

  void default_ctor_without_active_getter();
  //  void default_ctor_without_active_getter_string_key();
  void default_ctor_with_active_getter();
  void nondefault_ctor();
  //  void nondefault_ctor_2();
  void using_wrong_productid();

 private:
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestFwdRef);

void TestFwdRef::default_ctor_without_active_getter()
{
  fwdref1_t  default_ref;
  CPPUNIT_ASSERT(default_ref.isNull());
  CPPUNIT_ASSERT(default_ref.isNonnull()==false);
  CPPUNIT_ASSERT(!default_ref);
  CPPUNIT_ASSERT(default_ref.productGetter()==0);
  CPPUNIT_ASSERT(default_ref.id().isValid()==false);
  CPPUNIT_ASSERT(default_ref.isAvailable()==false);
}

// void TestFwdRef::default_ctor_without_active_getter_string_key()
// {
//   ref2_t  default_ref;
//   CPPUNIT_ASSERT(default_ref.isNull());
//   CPPUNIT_ASSERT(default_ref.isNonnull()==false);
//   CPPUNIT_ASSERT(!default_ref);
//   CPPUNIT_ASSERT(default_ref.productGetter()==0);
//   CPPUNIT_ASSERT(default_ref.id().isValid()==false);
//   CPPUNIT_ASSERT(default_ref.id().isAvailable()==false);
// }

void TestFwdRef::default_ctor_with_active_getter()
{
  SimpleEDProductGetter getter;
  edm::EDProductGetter::Operate op(&getter);
  fwdref1_t  default_ref;
  CPPUNIT_ASSERT(default_ref.isNull());
  CPPUNIT_ASSERT(default_ref.isNonnull()==false);
  CPPUNIT_ASSERT(!default_ref);
  CPPUNIT_ASSERT(default_ref.productGetter()==&getter);
  CPPUNIT_ASSERT(default_ref.id().isValid()==false);
  CPPUNIT_ASSERT(default_ref.isAvailable()==false);
  CPPUNIT_ASSERT_THROW(default_ref.operator->(), edm::Exception);
  CPPUNIT_ASSERT_THROW(*default_ref, edm::Exception);
}

void TestFwdRef::nondefault_ctor()
{
  SimpleEDProductGetter getter1;
  SimpleEDProductGetter getter2;
  
  edm::EDProductGetter::Operate op1(&getter1);
  edm::ProductID id1(1, 201U);
  CPPUNIT_ASSERT(id1.isValid());

  edm::EDProductGetter::Operate op2(&getter2);
  edm::ProductID id2(1, 202U);
  CPPUNIT_ASSERT(id2.isValid());

  // represents "parent" collection
  std::auto_ptr<product1_t> prod1(new product1_t);
  prod1->push_back(1);
  prod1->push_back(2);
  getter1.addProduct(id1, prod1);

  // represents "daughter" collection
  std::auto_ptr<product1_t> prod2(new product1_t);
  prod2->push_back(2);
  getter2.addProduct(id2, prod2);

  // ref to first product in parent
  ref1_t  ref0(id1, 0, &getter1);
  CPPUNIT_ASSERT(ref0.isNull()==false);
  CPPUNIT_ASSERT(ref0.isNonnull());
  CPPUNIT_ASSERT(!!ref0);
  CPPUNIT_ASSERT(ref0.productGetter()==&getter1);
  CPPUNIT_ASSERT(ref0.id().isValid());
  CPPUNIT_ASSERT(ref0.isAvailable()==true);
  CPPUNIT_ASSERT(*ref0 == 1);

  // ref to second product in parent
  ref1_t  ref1(id1, 1, &getter1);
  CPPUNIT_ASSERT(ref1.isNonnull());
  CPPUNIT_ASSERT(ref1.isAvailable()==true);
  CPPUNIT_ASSERT(*ref1 == 2);

  // ref to first product in daughter, which should be
  // the same as the second product in the parent
  ref1_t  ref1_2(id2, 0, &getter2);
  CPPUNIT_ASSERT(ref1_2.isNonnull());
  CPPUNIT_ASSERT(ref1_2.isAvailable()==true);
  CPPUNIT_ASSERT(*ref1_2 == 2);

  fwdref1_t fwdref1( ref1, ref1_2 );
  CPPUNIT_ASSERT(fwdref1.isNonnull());
  CPPUNIT_ASSERT(fwdref1.isAvailable()==true);
  CPPUNIT_ASSERT(*fwdref1 == 2);
  CPPUNIT_ASSERT(*(fwdref1.ref()) == 2);
  CPPUNIT_ASSERT(*(fwdref1.backRef()) == 2);

  // Note that nothing stops one from making an edm::Ref into a
  // collection using an index that is invalid. So there is no testing
  // of such use to be done.
}

// void TestFwdRef::nondefault_ctor_2()
// {
//   SimpleEDProductGetter getter;
  
//   edm::EDProductGetter::Operate op(&getter);
//   edm::ProductID id(1, 201U);
//   CPPUNIT_ASSERT(id.isValid());

//   std::auto_ptr<product2_t> prod(new product2_t);
//   prod->insert(std::make_pair(std::string("a"), 1));
//   prod->insert(std::make_pair(std::string("b"), 2));
//   prod->insert(std::make_pair(std::string("c"), 3));
//   getter.addProduct(id, prod);

//   ref2_t  refa(id, std::string("a"), &getter);
//   CPPUNIT_ASSERT(refa.isNull()==false);
//   CPPUNIT_ASSERT(refa.isNonnull());
//   CPPUNIT_ASSERT(!!refa);
//   CPPUNIT_ASSERT(refa.productGetter()==&getter);
//   CPPUNIT_ASSERT(refa.id().isValid());
//   CPPUNIT_ASSERT(*refa == 1);

//   ref2_t  refb(id, "b", &getter);
//   CPPUNIT_ASSERT(refb.isNonnull());
//   CPPUNIT_ASSERT(*refb == 2);
// }


void TestFwdRef::using_wrong_productid()
{
  SimpleEDProductGetter getter1;
  
  edm::EDProductGetter::Operate op1(&getter1);
  edm::ProductID id1(1, 1U);
  CPPUNIT_ASSERT(id1.isValid());

  std::auto_ptr<product1_t> prod1(new product1_t);
  prod1->push_back(1);
  prod1->push_back(2);
  getter1.addProduct(id1, prod1);

  edm::ProductID wrong_id1(1, 100U);
  CPPUNIT_ASSERT(wrong_id1.isValid()); // its valid, but not used.

  ref1_t  ref1(wrong_id1, 0, &getter1);
  CPPUNIT_ASSERT_THROW(*ref1, edm::Exception);
  CPPUNIT_ASSERT_THROW(ref1.operator->(), edm::Exception);



  SimpleEDProductGetter getter2;
  
  edm::EDProductGetter::Operate op2(&getter2);
  edm::ProductID id2(1, 2U);
  CPPUNIT_ASSERT(id2.isValid());

  std::auto_ptr<product1_t> prod2(new product1_t);
  prod2->push_back(2);
  getter2.addProduct(id2, prod1);

  edm::ProductID wrong_id2(1, 200U);
  CPPUNIT_ASSERT(wrong_id2.isValid()); // its valid, but not used.

  ref1_t  ref2(wrong_id2, 0, &getter2);
  CPPUNIT_ASSERT_THROW(*ref2, edm::Exception);
  CPPUNIT_ASSERT_THROW(ref2.operator->(), edm::Exception);


  fwdref1_t fwdref( ref1, ref2 );
  CPPUNIT_ASSERT_THROW(*fwdref, edm::Exception);
  CPPUNIT_ASSERT_THROW(fwdref.operator->(), edm::Exception);
}

