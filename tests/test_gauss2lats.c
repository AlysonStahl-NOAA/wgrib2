/**
 * This is a test for the wgrib2 project. 
 * 
 * This test is for the gauss2lats() routine and it's helper 
 * function gord() from geo.c.
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
    printf("Testing gord()...\n");
    {
        int n = 2;
        double x = 0.5;
        double expected = -0.19764235376052372;
        double ret;

        ret = gord(n, x);
        if (fabs(ret - expected) > TOL) {
            printf("gord() returned an unexpected value.\n");
            return 1;
        }

    }
    printf("SUCCESS!\n");
    return 0;
}