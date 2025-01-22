#include <stdio.h>
#include "CuTest.h"
#include "distance.h"
#include "co2.h"
#include "retrieveAPI.h"

// Distance.c tests
void testCalcDistance(CuTest *tc){
    double actual = calcDistKm(55.6263671087489, 12.591567764206339, 55.664031622239605, 12.60097718762547);
    double expected = 4.22;
    CuAssertDblEquals(tc, expected, actual, 0.1);
}

void testCalcDistanceERROR(CuTest *tc){
    double actual = calcDistKm(524325.626087489, -14322.591567764206339, 55.664031625, 12.60097718762547);
    double expected = -1;
    CuAssertDblEquals(tc, expected, actual, 0.1);
}

// CO2 tests
void testCalcCO2(CuTest *tc){
    double actual = calculateEmissions(42, "Car");
    double expected = 6.972;
    CuAssertDblEquals(tc, expected, actual, 0.1);
}

// Test GetCoordinates
void testGetCoords(CuTest *tc){
    double lat, lon;
    getCoordinates(2650, "Bymuren", &lat, &lon);
    double actualLat = lat;
    double expectedLat = 55.63014;
    CuAssertDblEquals(tc, expectedLat, actualLat, 0.1);
    double actualLon = lon;
    double expectedLon = 12.447102897280857;
    CuAssertDblEquals(tc, expectedLon, actualLon, 0.1);
}

// Test GetCoordinates Fail
void testGetCoordsERROR(CuTest *tc){
    double lat, lon;
    int res = getCoordinates(2650, "Falskvej", &lat, &lon);
    int expectedRes = 0;

    CuAssertDblEquals(tc, expectedRes, res, 0);
}


CuSuite *test_calc_GetSuite() {
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testCalcDistance);
    SUITE_ADD_TEST(suite, testCalcDistanceERROR);
    SUITE_ADD_TEST(suite, testCalcCO2);
    SUITE_ADD_TEST(suite, testGetCoords);
    SUITE_ADD_TEST(suite, testGetCoordsERROR);

    return suite;
}

void RunAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();
     
    // Adding test suites:
    CuSuiteAddSuite(suite, (CuSuite *)test_calc_GetSuite());

 
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}

