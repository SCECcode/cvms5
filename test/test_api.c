/**
 * @file test.c
 * @brief Bootstraps the test framework for the CVM-S5 library.
 * @author David Gill - SCEC <davidgil@usc.edu>
 * @version 1.0
 *
 * Tests the CVM-S5 library by loading it and executing the code as
 * UCVM would do it.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "cvms5.h"

/**
 * Initializes and runs the test program. Tests link against the
 * static version of the library to prevent any dynamic loading
 * issues.
 *
 * @param argc The number of arguments.
 * @param argv The argument strings.
 * @return A zero value indicating success.
 */
int main(int argc, const char* argv[]) {

	// Declare the structures.
	cvms5_point_t pt;
	cvms5_properties_t ret;

	// Initialize the model.
        char *envstr=getenv("UCVM_INSTALL_PATH");
        if(envstr != NULL) {
           assert(cvms5_init(envstr, "cvms5") == 0);
           } else {
             assert(cvms5_init("..", "cvms5") == 0);
        }

	printf("Loaded the model successfully.\n");

	// Query a point.
	pt.longitude = -118;
	pt.latitude = 34;
	pt.depth = 0;

	cvms5_query(&pt, &ret, 1);

	assert(ret.vs > 0);
	assert(ret.vp > 0);
	assert(ret.rho > 0);

	printf("Query was successful.\n");

	// Close the model.
	assert(cvms5_finalize() == 0);

	printf("Model closed successfully.\n");

	printf("\nALL CVM-S5 TESTS PASSED");

	return 0;
}
