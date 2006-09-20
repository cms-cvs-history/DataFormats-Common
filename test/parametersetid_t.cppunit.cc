/*
 *  parametersetid_t.cppunit.cc
 *  CMSSW
 *
 */

#include <map>
#include <string>

#include <cppunit/extensions/HelperMacros.h>

#include "DataFormats/Common/interface/ParameterSetID.h"
#include "FWCore/Utilities/interface/EDMException.h"


class testParameterSetID: public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(testParameterSetID);
  CPPUNIT_TEST(constructTest);
  CPPUNIT_TEST_EXCEPTION(badConstructTest, edm::Exception);
  CPPUNIT_TEST(comparisonTest);
  CPPUNIT_TEST(suitableForMapTest);
  CPPUNIT_TEST(unhexifyTest);
  CPPUNIT_TEST(printTest);
  CPPUNIT_TEST_SUITE_END();

  std::string default_id_string;
  std::string cow16;

 public:
  void setUp()
  {
    default_id_string = "d41d8cd98f00b204e9800998ecf8427e";
    cow16 = "DEADBEEFDEADBEEF";
  }
  void tearDown(){}
   
  void constructTest();
  void badConstructTest();
  void comparisonTest();
  void suitableForMapTest();
  void unhexifyTest();
  void printTest();
};

///registration of the test so that the runner can find it
CPPUNIT_TEST_SUITE_REGISTRATION(testParameterSetID);

void testParameterSetID::constructTest()
{
  edm::ParameterSetID id1;
  CPPUNIT_ASSERT(!id1.isValid());

  edm::ParameterSetID id2(cow16);
  CPPUNIT_ASSERT(id2.isValid());
  CPPUNIT_ASSERT(id2.compactForm() == cow16);
}

void testParameterSetID::badConstructTest()
{
  edm::ParameterSetID a("1");
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

  edm::ParameterSetID b(cow16);
  m[b] = 200;
  CPPUNIT_ASSERT (m.size() == 2);
  CPPUNIT_ASSERT (m[a] == 100);
  CPPUNIT_ASSERT (m[b] == 200);

  CPPUNIT_ASSERT (m.erase(a) == 1);
  CPPUNIT_ASSERT (m.size() == 1);
  CPPUNIT_ASSERT (m[b] == 200);
  CPPUNIT_ASSERT (m.find(a) == m.end());
}



void testParameterSetID::unhexifyTest()
{
  // 'a' has the MD5 checksum for an empty string.
  edm::ParameterSetID a(default_id_string);
  std::string a_compact = a.compactForm();
  CPPUNIT_ASSERT((unsigned char)a_compact[0] == 0xd4);
  CPPUNIT_ASSERT((unsigned char)a_compact[1] == 0x1d);
  CPPUNIT_ASSERT((unsigned char)a_compact[2] == 0x8c);
  CPPUNIT_ASSERT((unsigned char)a_compact[3] == 0xd9);
  CPPUNIT_ASSERT((unsigned char)a_compact[4] == 0x8f);
  CPPUNIT_ASSERT((unsigned char)a_compact[5] == 0x00);
  CPPUNIT_ASSERT((unsigned char)a_compact[6] == 0xb2);
  CPPUNIT_ASSERT((unsigned char)a_compact[7] == 0x04);
  CPPUNIT_ASSERT((unsigned char)a_compact[8] == 0xe9);
  CPPUNIT_ASSERT((unsigned char)a_compact[9] == 0x80);
  CPPUNIT_ASSERT((unsigned char)a_compact[10] == 0x09);
  CPPUNIT_ASSERT((unsigned char)a_compact[11] == 0x98);
  CPPUNIT_ASSERT((unsigned char)a_compact[12] == 0xec);
  CPPUNIT_ASSERT((unsigned char)a_compact[13] == 0xf8);
  CPPUNIT_ASSERT((unsigned char)a_compact[14] == 0x42);
  CPPUNIT_ASSERT((unsigned char)a_compact[15] == 0x7e);

  edm::ParameterSetID b;
  std::string b_compact = b.compactForm();
  CPPUNIT_ASSERT(b_compact.size() == 16);
}

void testParameterSetID::printTest()
{
  std::ostringstream os;
  edm::ParameterSetID id(default_id_string);
  os << id;
  std::string output = os.str();
  CPPUNIT_ASSERT(output == default_id_string);

  std::ostringstream os2;
  std::string s2("0123456789abcdef0123456789abcdef");
  edm::ParameterSetID id2(s2);
  CPPUNIT_ASSERT(id2.isValid());
  os2 << id2;
  std::string output2 = os2.str();
  CPPUNIT_ASSERT(output2 == s2);
}
