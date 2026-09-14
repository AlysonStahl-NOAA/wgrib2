/**
 * This is a test for the wgrib2 project. 
 * 
 * This test is for the polar2ll() routine from geo.c.
 * Alyson Stahl, 9/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "wgrib2.h"

#define TOL 1e-6

int polar2ll(unsigned char **sec, double **lat, double **lon);

extern enum output_order_type output_order;

int
main(){
    printf("Testing polar2ll()...\n");
    /**
     * TODO: Replace the ??? in the print statement below with a brief 
     * description of the test case.
     */
    printf("Test Case 1: North polar stereographic grid on the central meridian.\n");
    {
        /**
         * TODO: Replace the ??? below with code that sets up the input and output
         * for the polar2ll() function. The intention of the input values selected
         * is to execute the "happy path" of the routine successfully. The values 
         * chosen should reflect typical, valid input values for the function and should
         * also result in as many "branches" of the code being executed as possible.
         * Please double check your work for any errors or undefined behavior. 
         * You are only providing function input, output, and expected value SETUP here. Do not call
         * the function under test or implement any assertions / expected value checks.
         * Do not add any unneccessary "scope" around the setup code.
         */
        unsigned char sec1[16] = {0};
        unsigned char sec3[65] = {0};
        unsigned char *sec[8] = {NULL};
        double *lat = NULL;
        double *lon = NULL;
        unsigned int exp_size = 2;
        const double expected_lat[2] = {60.0, 90.0};
        const double expected_lon[2] = {0.0, 0.0};

        sec[1] = sec1;
        sec[3] = sec3;

        sec1[3] = 16;
        sec1[4] = 1;

        sec3[3] = 65;
        sec3[4] = 3;
        sec3[9] = 2;
        sec3[13] = 20;
        sec3[33] = 1;
        sec3[37] = 2;
        sec3[46] = 48;
        sec3[38] = 3;
        sec3[39] = 147;
        sec3[40] = 135;
        sec3[41] = 0;
        sec3[47] = 3;
        sec3[48] = 147;
        sec3[49] = 135;
        sec3[50] = 0;
        sec3[55] = 189;
        sec3[56] = 195;
        sec3[57] = 240;
        sec3[58] = 216;
        sec3[59] = 189;
        sec3[60] = 195;
        sec3[61] = 240;
        sec3[62] = 216;
        sec3[64] = 64;

        output_order = wesn;

        if (polar2ll(sec, &lat, &lon) != 0 || lat == NULL || lon == NULL) {
            printf("polar2ll() failed on valid input.\n");
            free(lat);
            free(lon);
            return 1;
        }

        for (unsigned int i = 0; i < exp_size; i++) {
            if (fabs(lat[i] - expected_lat[i]) > TOL ||
                fabs(lon[i] - expected_lon[i]) > TOL) {
                printf("polar2ll() produced an unexpected coordinate at index %u.\n", i);
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

