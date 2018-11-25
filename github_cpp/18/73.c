

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_RodCuttingTest_init = false;
#include "rod_cutting_test.h"

static RodCuttingTest suite_RodCuttingTest;

static CxxTest::List Tests_RodCuttingTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_RodCuttingTest( "rod_cutting_test.h", 6, "RodCuttingTest", suite_RodCuttingTest, Tests_RodCuttingTest );

static class TestDescription_suite_RodCuttingTest_test_invalid1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RodCuttingTest_test_invalid1() : CxxTest::RealTestDescription( Tests_RodCuttingTest, suiteDescription_RodCuttingTest, 20, "test_invalid1" ) {}
 void runTest() { suite_RodCuttingTest.test_invalid1(); }
} testDescription_suite_RodCuttingTest_test_invalid1;

static class TestDescription_suite_RodCuttingTest_test_invalid2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RodCuttingTest_test_invalid2() : CxxTest::RealTestDescription( Tests_RodCuttingTest, suiteDescription_RodCuttingTest, 25, "test_invalid2" ) {}
 void runTest() { suite_RodCuttingTest.test_invalid2(); }
} testDescription_suite_RodCuttingTest_test_invalid2;

static class TestDescription_suite_RodCuttingTest_test_normal1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RodCuttingTest_test_normal1() : CxxTest::RealTestDescription( Tests_RodCuttingTest, suiteDescription_RodCuttingTest, 30, "test_normal1" ) {}
 void runTest() { suite_RodCuttingTest.test_normal1(); }
} testDescription_suite_RodCuttingTest_test_normal1;

static class TestDescription_suite_RodCuttingTest_test_normal2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RodCuttingTest_test_normal2() : CxxTest::RealTestDescription( Tests_RodCuttingTest, suiteDescription_RodCuttingTest, 35, "test_normal2" ) {}
 void runTest() { suite_RodCuttingTest.test_normal2(); }
} testDescription_suite_RodCuttingTest_test_normal2;

static class TestDescription_suite_RodCuttingTest_test_normal3 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RodCuttingTest_test_normal3() : CxxTest::RealTestDescription( Tests_RodCuttingTest, suiteDescription_RodCuttingTest, 40, "test_normal3" ) {}
 void runTest() { suite_RodCuttingTest.test_normal3(); }
} testDescription_suite_RodCuttingTest_test_normal3;

static class TestDescription_suite_RodCuttingTest_test_normal4 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RodCuttingTest_test_normal4() : CxxTest::RealTestDescription( Tests_RodCuttingTest, suiteDescription_RodCuttingTest, 45, "test_normal4" ) {}
 void runTest() { suite_RodCuttingTest.test_normal4(); }
} testDescription_suite_RodCuttingTest_test_normal4;

static class TestDescription_suite_RodCuttingTest_test_normal5 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RodCuttingTest_test_normal5() : CxxTest::RealTestDescription( Tests_RodCuttingTest, suiteDescription_RodCuttingTest, 50, "test_normal5" ) {}
 void runTest() { suite_RodCuttingTest.test_normal5(); }
} testDescription_suite_RodCuttingTest_test_normal5;

static class TestDescription_suite_RodCuttingTest_test_solution1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RodCuttingTest_test_solution1() : CxxTest::RealTestDescription( Tests_RodCuttingTest, suiteDescription_RodCuttingTest, 55, "test_solution1" ) {}
 void runTest() { suite_RodCuttingTest.test_solution1(); }
} testDescription_suite_RodCuttingTest_test_solution1;

static class TestDescription_suite_RodCuttingTest_test_solution2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RodCuttingTest_test_solution2() : CxxTest::RealTestDescription( Tests_RodCuttingTest, suiteDescription_RodCuttingTest, 61, "test_solution2" ) {}
 void runTest() { suite_RodCuttingTest.test_solution2(); }
} testDescription_suite_RodCuttingTest_test_solution2;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
