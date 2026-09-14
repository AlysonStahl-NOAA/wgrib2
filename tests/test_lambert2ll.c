/**
 * This is a test for the wgrib2 project. 
 * 
 * This test is for the lambert2ll() routine from geo.c.
 * Alyson Stahl, 9/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "wgrib2.h"

#define TOL 1e-6

int lambert2ll(unsigned char **sec, double **lat, double **lon);

extern enum output_order_type output_order;

int
main(){
    printf("Testing lambert2ll()...\n");
    /**
     * TODO: Replace the ??? in the print statement below with a brief 
     * description of the test case.
     */
    printf("Test Case 1: Lambert conformal grid along the projection meridian.\n");
    {
        /**
         * TODO: Replace the ??? below with code that sets up the input and output
         * for the lambert2ll() function. The intention of the input values selected
         * is to execute the "happy path" of the routine successfully. The values 
         * chosen should reflect typical, valid input values for the function and should
         * also result in as many "branches" of the code being executed as possible.
         * Please double check your work for any errors or undefined behavior. 
         * You are only providing function input, output, and expected value SETUP here. Do not call
         * the function under test or implement any assertions / expected value checks.
         * Do not add any unneccessary "scope" around the setup code.
         */
        unsigned char sec1[16] = {0};
        unsigned char sec3[81] = {0};
        unsigned char *sec[8] = {NULL};
        double *lat = NULL;
        double *lon = NULL;
        unsigned int exp_size = 2;
        const double expected_lat[2] = {30.0, 42.1842765};
        const double expected_lon[2] = {0.0, 0.0};

        sec[1] = sec1;
        sec[3] = sec3;

        sec1[3] = 16;
        sec1[4] = 1;

        sec3[3] = 81;
        sec3[4] = 3;
        sec3[9] = 2;
        sec3[13] = 30;
        sec3[33] = 1;
        sec3[37] = 2;
        sec3[38] = 1;
        sec3[39] = 201;
        sec3[40] = 195;
        sec3[41] = 128;
        sec3[46] = 48;
        sec3[47] = 1;
        sec3[48] = 201;
        sec3[49] = 195;
        sec3[50] = 128;
        sec3[55] = 0;
        sec3[56] = 15;
        sec3[57] = 66;
        sec3[58] = 64;
        sec3[59] = 209;
        sec3[60] = 88;
        sec3[61] = 116;
        sec3[62] = 226;
        sec3[64] = 64;
        sec3[65] = 1;
        sec3[66] = 201;
        sec3[67] = 195;
        sec3[68] = 128;
        sec3[69] = 1;
        sec3[70] = 201;
        sec3[71] = 195;
        sec3[72] = 128;

        output_order = wesn;

        if (lambert2ll(sec, &lat, &lon) != 0 || lat == NULL || lon == NULL) {
            printf("lambert2ll() failed on valid input.\n");
            free(lat);
            free(lon);
            return 1;
        }

        for (unsigned int i = 0; i < exp_size; i++) {
            if (fabs(lat[i] - expected_lat[i]) > TOL) {
                printf("lat[%u] = %.15f, diff = %.15f\n", i, lat[i], fabs(lat[i] - expected_lat[i]));
            }
            if (fabs(lon[i] - expected_lon[i]) > TOL) {
                printf("lon[%u] = %.15f, diff = %.15f\n", i, lon[i], fabs(lon[i] - expected_lon[i]));
            }
            if (fabs(lat[i] - expected_lat[i]) > TOL ||
                fabs(lon[i] - expected_lon[i]) > TOL) {
                printf("lambert2ll() produced an unexpected coordinate at index %u.\n", i);
                free(lat);
                free(lon);
                return 1;
            }
        }

        free(lat);
        free(lon);
    }
    printf("SUCCESS!\n");
    return 0;
}