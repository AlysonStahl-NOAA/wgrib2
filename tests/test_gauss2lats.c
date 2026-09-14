/**
 * This is a test for the wgrib2 project. 
 * 
 * This test is for the gauss2lats() routine from geo.c.
 * Alyson Stahl, 9/2026
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "wgrib2.h"

#define TOL 1e-6

double gord(int n, double x);

extern enum output_order_type output_order;

int
main(){
    printf("Testing gauss2lats()...\n");
    /**
     * TODO: Replace the ??? in the print statement below with a brief 
     * description of the test case.
     */
    printf("Test Case 1: Gaussian latitude grid with odd number of points.\n");
    {
        /**
         * TODO: Replace the ??? below with code that sets up the input and output
         * for the gauss2lats() function. The intention of the input values selected
         * is to execute the "happy path" of the routine successfully. The values 
         * chosen should reflect typical, valid input values for the function and should
         * also result in as many "branches" of the code being executed as possible.
         * Please double check any expected values.
         */
        int nlat = 5;
        double ylat[5];
        double *ret;
        double rad2deg = 180.0 / acos(-1.0);
        double root1 = sqrt((35.0 + 2.0 * sqrt(70.0)) / 63.0);
        double root2 = sqrt((35.0 - 2.0 * sqrt(70.0)) / 63.0);
        double expected[5] = {
            -asin(root1) * rad2deg,
            -asin(root2) * rad2deg,
            0.0,
            asin(root2) * rad2deg,
            asin(root1) * rad2deg
        };

        ret = gauss2lats(nlat, ylat);
        if (ret != ylat) {
            printf("gauss2lats() did not return the input array.\n");
            return 1;
        }

        for (unsigned int i = 0; i < nlat; i++) {
            printf("ylat[%u] = %.15f\n", i, ylat[i]);
        }

        for (unsigned int i = 0; i < nlat; i++) {
            if (fabs(ylat[i] - expected[i]) > TOL) {
                printf("gauss2lats() returned an unexpected latitude at index %d.\n", i);
                return 1;
            }
        }

    }
    printf("SUCCESS!\n");
    return 0;
}        
