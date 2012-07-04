// Test of the ReflexTools functions.


#include "DataFormats/Common/interface/Wrapper.h"
#include "FWCore/Utilities/interface/ReflexTools.h"
#include "FWCore/Utilities/interface/TypeID.h"
#include "Utilities/Testing/interface/CppUnit_testdriver.icpp"

#include "cppunit/extensions/HelperMacros.h"
#include "Reflex/Type.h"

#include <iostream>
#include <typeinfo>
#include <vector>

class TestReflex: public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(TestReflex);
  CPPUNIT_TEST(default_is_invalid);
  CPPUNIT_TEST(no_dictionary_is_invalid);
  CPPUNIT_TEST(find_nested);
  CPPUNIT_TEST(burrowing);
  CPPUNIT_TEST(burrowing_failure);
  CPPUNIT_TEST(wrapper_type);
  CPPUNIT_TEST(wrapper_type_failure);
  CPPUNIT_TEST(primary_template_id);
  CPPUNIT_TEST(not_a_template_instance);
  CPPUNIT_TEST_SUITE_END();

 public:
  TestReflex() {}
  ~TestReflex() {}
  void setUp() {}
  void tearDown() {}

  void default_is_invalid();
  void no_dictionary_is_invalid();
  void find_nested();
  void burrowing();
  void burrowing_failure();
  void wrapper_type();
  void wrapper_type_failure();
  void primary_template_id();
  void not_a_template_instance();

 private:
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestReflex);

void TestReflex::default_is_invalid() {
  edm::TypeID t;
  CPPUNIT_ASSERT(!t);
}


void TestReflex::no_dictionary_is_invalid() {
  edm::TypeID t(edm::TypeID::byName("ThereIsNoTypeWithThisName"));
  CPPUNIT_ASSERT(!t);
}

void TestReflex::find_nested() {
  edm::TypeID intvec(edm::TypeID::byName("std::vector<int>"));
  CPPUNIT_ASSERT(intvec);

  edm::TypeID found_type;

  CPPUNIT_ASSERT(edm::find_nested_type_named("const_iterator",
                                             intvec,
                                             found_type));

  CPPUNIT_ASSERT(!edm::find_nested_type_named("WankelRotaryEngine",
                                              intvec,
                                              found_type));
}

void TestReflex::burrowing() {
  edm::TypeID wrapper_type(edm::TypeID(typeid(edm::Wrapper<int>)));
  CPPUNIT_ASSERT(wrapper_type);
  edm::TypeID wrapped_type;
  CPPUNIT_ASSERT(edm::find_nested_type_named("wrapped_type",
                                             wrapper_type,
                                             wrapped_type));
  CPPUNIT_ASSERT(wrapped_type);
  Reflex::Type wrapped_Rflx_type(Reflex::Type::ByTypeInfo(wrapped_type.typeInfo()));
  CPPUNIT_ASSERT(!wrapped_Rflx_type.IsTypedef());
  CPPUNIT_ASSERT(wrapped_Rflx_type.IsFundamental());
  CPPUNIT_ASSERT(wrapped_type == edm::TypeID::byName("int"));
  CPPUNIT_ASSERT(wrapped_type.typeInfo() == typeid(int));
}

void TestReflex::burrowing_failure() {
  edm::TypeID not_a_wrapper(edm::TypeID::byName("double"));
  CPPUNIT_ASSERT(not_a_wrapper);
  edm::TypeID no_such_wrapped_type;
  CPPUNIT_ASSERT(!no_such_wrapped_type);
  CPPUNIT_ASSERT(!edm::find_nested_type_named("wrapped_type",
                                              not_a_wrapper,
                                              no_such_wrapped_type));
  CPPUNIT_ASSERT(!no_such_wrapped_type);
}

void TestReflex::wrapper_type() {
  edm::TypeID wrapper_type(edm::TypeID(typeid(edm::Wrapper<int>)));
  edm::TypeID wrapped_type;
  CPPUNIT_ASSERT(edm::wrapper_type_of(wrapper_type, wrapped_type));
  Reflex::Type wrapped_Rflx_type(Reflex::Type::ByTypeInfo(wrapped_type.typeInfo()));
  CPPUNIT_ASSERT(!wrapped_Rflx_type.IsTypedef());
  CPPUNIT_ASSERT(wrapped_type == edm::TypeID::byName("int"));
}

void TestReflex::wrapper_type_failure() {
  edm::TypeID not_a_wrapper(edm::TypeID::byName("double"));
  CPPUNIT_ASSERT(not_a_wrapper);
  edm::TypeID no_such_wrapped_type;
  CPPUNIT_ASSERT(!no_such_wrapped_type);
  CPPUNIT_ASSERT(!edm::wrapper_type_of(not_a_wrapper,
                                       no_such_wrapped_type));
  CPPUNIT_ASSERT(!no_such_wrapped_type);
}

void TestReflex::primary_template_id() {
  Reflex::Type intvec(Reflex::Type::ByName("std::vector<int>"));
  Reflex::TypeTemplate vec(intvec.TemplateFamily());

  // The template std::vector has two template parameters, thus the
  // '2' in the following line.
  Reflex::TypeTemplate standard_vec(Reflex::TypeTemplate::ByName("std::vector",2));
  CPPUNIT_ASSERT(!standard_vec);
  CPPUNIT_ASSERT(vec != standard_vec);

  // reflex in use by CMS as of 26 Feb 2007 understands vector to have
  // one template parameter; this is not standard.
  Reflex::TypeTemplate nonstandard_vec(Reflex::TypeTemplate::ByName("std::vector",1));
  CPPUNIT_ASSERT(nonstandard_vec);
  CPPUNIT_ASSERT(vec == nonstandard_vec);
}

void TestReflex::not_a_template_instance() {
  Reflex::Type not_a_template(Reflex::Type::ByName("double"));
  CPPUNIT_ASSERT(not_a_template);
  Reflex::TypeTemplate nonesuch(not_a_template.TemplateFamily());
  CPPUNIT_ASSERT(!nonesuch);
}

