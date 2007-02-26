// Test of the ReflexTools functions.

#include <typeinfo>
#include <vector>

#include <Utilities/Testing/interface/CppUnit_testdriver.icpp>
#include <cppunit/extensions/HelperMacros.h>

#include "Reflex/Type.h"
#include "DataFormats/Common/interface/ReflexTools.h"
#include "DataFormats/Common/interface/Wrapper.h"

using ROOT::Reflex::Type;

class TestReflex: public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestReflex);
  CPPUNIT_TEST(default_is_invalid);
  CPPUNIT_TEST(no_dictionary_is_invalid);
  CPPUNIT_TEST(find_nested);
  CPPUNIT_TEST(burrowing);
  CPPUNIT_TEST(burrowing_failure);
  CPPUNIT_TEST(wrapper_type);
  CPPUNIT_TEST(wrapper_type_failure);
  CPPUNIT_TEST(sequence_wrapper);
  CPPUNIT_TEST(sequence_wrapper_failure);
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
  void sequence_wrapper();
  void sequence_wrapper_failure();

 private:
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestReflex);

void TestReflex::default_is_invalid()
{
  Type t;
  CPPUNIT_ASSERT(!t);
}


void TestReflex::no_dictionary_is_invalid()
{
  Type t(Type::ByName("ThereIsNoTypeWithThisName"));
  CPPUNIT_ASSERT(!t);
}

void TestReflex::find_nested()
{
  Type intvec(Type::ByName("std::vector<int>"));
  CPPUNIT_ASSERT(intvec);

  Type found_type;

  CPPUNIT_ASSERT(edm::find_nested_type_named("const_iterator",
					     intvec,
					     found_type));

  CPPUNIT_ASSERT(!edm::find_nested_type_named("WankelRotaryEngine",
					      intvec,
					      found_type));
}

void TestReflex::burrowing()
{
  Type wrapper_type(Type::ByTypeInfo(typeid(edm::Wrapper<int>)));
  CPPUNIT_ASSERT(wrapper_type);
  Type wrapped_type;
  CPPUNIT_ASSERT(edm::find_nested_type_named("wrapped_type",
					     wrapper_type,
					     wrapped_type));
  CPPUNIT_ASSERT(wrapped_type);
  CPPUNIT_ASSERT(!wrapped_type.IsTypedef());
  CPPUNIT_ASSERT(wrapped_type.IsFundamental());
  CPPUNIT_ASSERT(wrapped_type == Type::ByName("int"));
  CPPUNIT_ASSERT(wrapped_type.TypeInfo() == typeid(int));
}

void TestReflex::burrowing_failure()
{
  Type not_a_wrapper(Type::ByName("double"));
  CPPUNIT_ASSERT(not_a_wrapper);
  Type no_such_wrapped_type;
  CPPUNIT_ASSERT(!no_such_wrapped_type);
  CPPUNIT_ASSERT(!edm::find_nested_type_named("wrapped_type",
					      not_a_wrapper,
					      no_such_wrapped_type));
  CPPUNIT_ASSERT(!no_such_wrapped_type);
}

void TestReflex::wrapper_type()
{
  Type wrapper_type(Type::ByTypeInfo(typeid(edm::Wrapper<int>)));
  Type wrapped_type;
  CPPUNIT_ASSERT(edm::wrapper_type_of(wrapper_type, wrapped_type));
  CPPUNIT_ASSERT(!wrapped_type.IsTypedef());
  CPPUNIT_ASSERT(wrapped_type == Type::ByName("int"));
}

void TestReflex::wrapper_type_failure()
{
  Type not_a_wrapper(Type::ByName("double"));
  CPPUNIT_ASSERT(not_a_wrapper);
  Type no_such_wrapped_type;
  CPPUNIT_ASSERT(!no_such_wrapped_type);
  CPPUNIT_ASSERT(!edm::wrapper_type_of(not_a_wrapper,
				       no_such_wrapped_type));
  CPPUNIT_ASSERT(!no_such_wrapped_type);
}

void TestReflex::sequence_wrapper()
{
  Type wrapper(Type::ByTypeInfo(typeid(edm::Wrapper<std::vector<int> >)));
  CPPUNIT_ASSERT(wrapper);
  Type value_type;
  CPPUNIT_ASSERT(!value_type);
  CPPUNIT_ASSERT(edm::is_sequence_wrapper(wrapper, value_type));
  CPPUNIT_ASSERT(value_type);
  CPPUNIT_ASSERT(value_type == Type::ByName("int"));
}

void TestReflex::sequence_wrapper_failure()
{
  Type not_a_wrapper(Type::ByName("std::vector<int>"));
  CPPUNIT_ASSERT(not_a_wrapper);
  Type no_such_value_type;
  CPPUNIT_ASSERT(!no_such_value_type);
  CPPUNIT_ASSERT(!edm::is_sequence_wrapper(not_a_wrapper,
					   no_such_value_type));
  CPPUNIT_ASSERT(!no_such_value_type);

  Type wrapper_of_nonsequence(Type::ByName("edm::Wrapper<int>"));
  CPPUNIT_ASSERT(wrapper_of_nonsequence);
  CPPUNIT_ASSERT(!edm::is_sequence_wrapper(wrapper_of_nonsequence,
					   no_such_value_type));
  CPPUNIT_ASSERT(!no_such_value_type);
}
