/**
 * This is a test for the wgrib2 project. 
 * 
 * This test is for the regular2ll() routine from geo.c.
 * Alyson Stahl, 9/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "wgrib2.h"

#define TOL 1e-6

int regular2ll(unsigned char **sec, double **lat, double **lon);

extern enum output_order_type output_order;

int
main(){

    printf("Testing regular2ll()...\n");
    printf("Test Case 1: Grid Template 0 and WESN output order.\n");
    {
        unsigned char sec1[16] = {0};
        unsigned char sec3[72] = {0};
        unsigned char *sec[8] = {NULL};
        double *lat = NULL;
        double *lon = NULL;
        unsigned int exp_size = 6;
        const double expected_lat[6] = {10.0, 10.0, 10.0, 20.0, 20.0, 20.0};
        const double expected_lon[6] = {350.0, 0.0, 10.0, 350.0, 0.0, 10.0};

        sec[1] = sec1;
        sec[3] = sec3;

        sec1[3] = 16;
        sec1[4] = 1;

        sec3[3] = 72;
        sec3[4] = 3;
        sec3[9] = 6;
        sec3[33] = 3;
        sec3[37] = 2;
        sec3[47] = 152;
        sec3[48] = 150;
        sec3[49] = 128;
        sec3[50] = 20;
        sec3[51] = 220;
        sec3[52] = 147;
        sec3[53] = 128;
        sec3[54] = 48;
        sec3[55] = 1;
        sec3[56] = 49;
        sec3[57] = 45;
        sec3[59] = 0;
        sec3[60] = 152;
        sec3[61] = 150;
        sec3[62] = 128;
        sec3[63] = 0;
        sec3[64] = 152;
        sec3[65] = 150;
        sec3[66] = 128;
        sec3[67] = 0;
        sec3[68] = 152;
        sec3[69] = 150;
        sec3[70] = 128;
        sec3[71] = 64;

        output_order = wesn;

        if (regular2ll(sec, &lat, &lon) != 0 || lat == NULL || lon == NULL) {
            printf("regular2ll() failed on valid input.\n");
            free(lat);
            free(lon);
            return 1;
        }

        for (unsigned int i = 0; i < exp_size; i++) {
            if (fabs(lat[i] - expected_lat[i]) > TOL ||
                fabs(lon[i] - expected_lon[i]) > TOL) {
                printf("regular2ll() produced an unexpected coordinate at index %u.\n", i);
                free(lat);
                free(lon);
                return 1;
            }
        }

        free(lat);
        free(lon);
    }
    printf("Test Case 2: Thinned quasi-regular grid with WESN-oriented rows.\n");
    {
        unsigned char sec1[16] = {0};
        unsigned char sec3[74] = {0};
        unsigned char *sec[8] = {NULL};
        double *lat = NULL;
        double *lon = NULL;
        unsigned int exp_size = 5;
        const double expected_lat[5] = {10.0, 10.0, 20.0, 20.0, 20.0};
        const double expected_lon[5] = {350.0, 10.0, 350.0, 0.0, 10.0};

        sec[1] = sec1;
        sec[3] = sec3;

        sec1[3] = 16;
        sec1[4] = 1;

        sec3[3] = 74;
        sec3[4] = 3;
        sec3[9] = 5;
        sec3[10] = 1;
        sec3[30] = 255;
        sec3[31] = 255;
        sec3[32] = 255;
        sec3[33] = 255;
        sec3[37] = 2;
        sec3[47] = 152;
        sec3[48] = 150;
        sec3[49] = 128;
        sec3[50] = 20;
        sec3[51] = 220;
        sec3[52] = 147;
        sec3[53] = 128;
        sec3[54] = 48;
        sec3[55] = 1;
        sec3[56] = 49;
        sec3[57] = 45;
        sec3[59] = 0;
        sec3[60] = 152;
        sec3[61] = 150;
        sec3[62] = 128;
        sec3[63] = 0;
        sec3[64] = 152;
        sec3[65] = 150;
        sec3[66] = 128;
        sec3[67] = 0;
        sec3[68] = 152;
        sec3[69] = 150;
        sec3[70] = 128;
        sec3[71] = 64;
        sec3[72] = 2;
        sec3[73] = 3;

        output_order = wesn;

        if (regular2ll(sec, &lat, &lon) != 0 || lat == NULL || lon == NULL) {
            printf("regular2ll() failed on valid input.\n");
            free(lat);
            free(lon);
            return 2;
        }

        for (unsigned int i = 0; i < exp_size; i++) {
            if (fabs(lat[i] - expected_lat[i]) > TOL ||
                fabs(lon[i] - expected_lon[i]) > TOL) {
                printf("regular2ll() produced an unexpected coordinate at index %u.\n", i);
                free(lat);
                free(lon);
                return 2;
            }
        }

        free(lat);
        free(lon);
    }
    /**
     * TODO: Replace the ??? in the print statement below with a brief 
     * description of the test case.
     */
    printf("Test Case 3: Grid Template 0 with negative y scanning order.\n");
    {
        /**
         * TODO: Replace the ??? below with code that sets up the input and output
         * for the regular2ll() function. The intention of the input values selected
         * is to execute the else branch of the following if statement:
         *  if (GDS_Scan_y(nscan)) {
         *      s = lat1;
         *      n = lat2;
         *  }
         *  else {
         *      s = lat2;
         *      n = lat1;
         *  }
         * 
         * In other words, the input you choose should result in GDS_Scan_y(nscan) == FALSE
         * in the context where this if statement exists. Your input should not
         * result in any errors or fatal_error() being triggered.
         * You are only providing function input, output, and expected value SETUP here. Do not call
         * the function under test or implement any assertions / expected value checks.
         * Do not add any unneccessary "scope" around the setup code.
         */
        unsigned char sec1[16] = {0};
        unsigned char sec3[72] = {0};
        unsigned char *sec[8] = {NULL};
        double *lat = NULL;
        double *lon = NULL;
        unsigned int exp_size = 6;
        const double expected_lat[6] = {10.0, 10.0, 10.0, 20.0, 20.0, 20.0};
        const double expected_lon[6] = {350.0, 0.0, 10.0, 350.0, 0.0, 10.0};

        sec[1] = sec1;
        sec[3] = sec3;

        sec1[3] = 16;
        sec1[4] = 1;

        sec3[3] = 72;
        sec3[4] = 3;
        sec3[9] = 6;
        sec3[33] = 3;
        sec3[37] = 2;
        sec3[46] = 1;
        sec3[47] = 49;
        sec3[48] = 45;
        sec3[50] = 20;
        sec3[51] = 220;
        sec3[52] = 147;
        sec3[53] = 128;
        sec3[54] = 48;
        sec3[55] = 0;
        sec3[56] = 152;
        sec3[57] = 150;
        sec3[58] = 128;
        sec3[59] = 0;
        sec3[60] = 152;
        sec3[61] = 150;
        sec3[62] = 128;
        sec3[63] = 0;
        sec3[64] = 152;
        sec3[65] = 150;
        sec3[66] = 128;
        sec3[67] = 0;
        sec3[68] = 152;
        sec3[69] = 150;
        sec3[70] = 128;
        sec3[71] = 0;

        output_order = wesn;
      
        if (regular2ll(sec, &lat, &lon) != 0 || lat == NULL || lon == NULL) {
            printf("regular2ll() failed on valid input.\n");
            free(lat);
            free(lon);
            return 3;
        }

        for (unsigned int i = 0; i < exp_size; i++) {
            if (fabs(lat[i] - expected_lat[i]) > TOL ||
                fabs(lon[i] - expected_lon[i]) > TOL) {
                printf("regular2ll() produced an unexpected coordinate at index %u.\n", i);
                free(lat);
                free(lon);
                return 3;
            }
        }

        free(lat);
        free(lon);
    }
    printf("SUCCESS!\n");
    return 0;
}