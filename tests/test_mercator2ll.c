/**
 * This is a test for the wgrib2 project. 
 * 
 * This test is for the mercator2ll() routine from geo.c.
 * Alyson Stahl, 9/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "wgrib2.h"

#define TOL 1e-6

int mercator2ll(unsigned char **sec, double **lat, double **lon);

extern enum output_order_type output_order;

int
main(){
    printf("Testing mercator2ll()...\n");
    /**
     * TODO: Replace the ??? in the print statement below with a brief 
     * description of the test case.
     */
    printf("Test Case 1: Mercator grid with reverse x and y scanning.\n");
    {
        /**
         * TODO: Replace the ??? below with code that sets up the input and output
         * for the mercator2ll() function. The intention of the input values selected
         * is to execute the "happy path" of the routine successfully. The values 
         * chosen should reflect typical, valid input values for the function and should
         * also result in as many "branches" of the code being executed as possible.
         * Please double check your work for any errors or undefined behavior. 
         * You are only providing function input, output, and expected value SETUP here. Do not call
         * the function under test or implement any assertions / expected value checks.
         * Do not add any unneccessary "scope" around the setup code.
         */
        unsigned char sec1[16] = {0};
        unsigned char sec3[72] = {0};
        unsigned char *sec[8] = {NULL};
        double *lat = NULL;
        double *lon = NULL;
        unsigned int exp_size = 9;
        const double expected_lat[9] = {
            -45.0, -45.0, -45.0,
            0.0, 0.0, 0.0,
            45.0, 45.0, 45.0
        };
        const double expected_lon[9] = {
            0.0, 10.0, 20.0,
            0.0, 10.0, 20.0,
            0.0, 10.0, 20.0
        };

        sec[1] = sec1;
        sec[3] = sec3;

        sec1[3] = 16;
        sec1[4] = 1;

        sec3[3] = 72;
        sec3[4] = 3;
        sec3[9] = 9;
        sec3[13] = 10;
        sec3[33] = 3;
        sec3[37] = 3;
        sec3[38] = 2;
        sec3[39] = 174;
        sec3[40] = 165;
        sec3[41] = 64;
        sec3[46] = 48;
        sec3[51] = 130;
        sec3[52] = 174;
        sec3[53] = 165;
        sec3[54] = 64;
        sec3[55] = 0;
        sec3[56] = 0;
        sec3[57] = 0;
        sec3[58] = 0;
        sec3[59] = 128;
        sec3[64] = 66;
        sec3[65] = 61;
        sec3[66] = 153;
        sec3[67] = 45;
        sec3[68] = 66;
        sec3[69] = 61;
        sec3[70] = 153;
        sec3[71] = 45;
        sec3[42] = 1;
        sec3[43] = 49;
        sec3[44] = 45;
        sec3[45] = 0;

        output_order = wesn;

        if (mercator2ll(sec, &lat, &lon) != 0 || lat == NULL || lon == NULL) {
            printf("mercator2ll() failed on valid input.\n");
            free(lat);
            free(lon);
            return 1;
        }

        for (unsigned int i = 0; i < exp_size; i++) {
            if (fabs(lat[i] - expected_lat[i]) > TOL ||
                fabs(lon[i] - expected_lon[i]) > TOL) {
                printf("mercator2ll() produced an unexpected coordinate at index %u.\n", i);
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