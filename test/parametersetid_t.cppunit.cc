/*
 *  parametersetid_t.cppunit.cc
 *  CMSSW
 *
 */

#include <map>

#include <cppunit/extensions/HelperMacros.h>

#include "DataFormats/Common/interface/ParameterSetID.h"


class testParameterSetID: public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(testParameterSetID);
  CPPUNIT_TEST(constructTest);
  CPPUNIT_TEST(comparisonTest);
  CPPUNIT_TEST(suitableForMapTest);
  CPPUNIT_TEST_SUITE_END();
 public:
  void setUp(){}
  void tearDown(){}
   
  void constructTest();
  void comparisonTest();
  void suitableForMapTest();
};

///registration of the test so that the runner can find it
CPPUNIT_TEST_SUITE_REGISTRATION(testParameterSetID);

void testParameterSetID::constructTest()
{
  edm::ParameterSetID id1;
  CPPUNIT_ASSERT(!id1.isValid());

  edm::ParameterSetID id2("DEADBEEFDEADBEEF");
  CPPUNIT_ASSERT(id2.isValid());
}

void testParameterSetID::comparisonTest()
{  
  edm::ParameterSetID a;
  edm::ParameterSetID b;
  CPPUNIT_ASSERT(a == b);
  CPPUNIT_ASSERT(! (a != b));
  CPPUNIT_ASSERT(! (a < b));
  CPPUNIT_ASSERT(! (a > b));  
}

void testParameterSetID::suitableForMapTest()
{
  typedef std::map<edm::ParameterSetID, int> map_t;
  map_t m;
  CPPUNIT_ASSERT (m.empty());

  edm::ParameterSetID a;
  m[a] = 100;
  CPPUNIT_ASSERT (m.size() == 1);
  CPPUNIT_ASSERT (m[a] == 100);

  edm::ParameterSetID b("DEADBEEFDEADBEEF");
  m[b] = 200;
  CPPUNIT_ASSERT (m.size() == 2);
  CPPUNIT_ASSERT (m[a] == 100);
  CPPUNIT_ASSERT (m[b] == 200);

  CPPUNIT_ASSERT (m.erase(a) == 1);
  CPPUNIT_ASSERT (m.size() == 1);
  CPPUNIT_ASSERT (m[b] == 200);
  CPPUNIT_ASSERT (m.find(a) == m.end());
}

