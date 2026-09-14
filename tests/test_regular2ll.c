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
        unsigned int i;
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

        for (i = 0; i < exp_size; i++) {
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
    /**
     * basic_ang = GDS_LatLon_basic_ang(gds);
     * 1. basic_ang != 0
     * 2. basic_ang == 0
     * 
     * GDS_Scan_y(nscan)
     * 1. True => s = lat1, n = lat2
     * 2. False => s = lat2, n = lat1
     * 
     * nny
     * 1. nny > 1 
     *      a. nres & 16 = False (non-error case)
     * 3. nny = 1 => dy = 0
     * 
     * GDS_Scan_x(nscan)
     * 1. True
     *      a. GDS_Scan_row_rev(nscan) && ((nres & 32) == 0)
     * 2. False 
     *      a. GDS_Scan_row_rev(nscan) && ((nres & 32) == 0)
     * 
     * e <= w
     * 1. True => e += 360
     * 
     * e-w > 360 => e -= 360
     * 
     * w < 0
     *  w+= 360
     *  e += 360
     * 
     * nnx > 0 && nny > 0
     * 1. True -> will return
     *      a. nnx > 1
     *          i. nres & 32 = False
     *      b. nnx <= 1
     * 2. False => continue
     */

    /**
     * Fatal Error Cases
     * 
     * nny < 1
     * 
     * lon1 = GDS_LatLon_lon1(gds) * units;
     * lon2 = GDS_LatLon_lon2(gds) * units;
     * 1. (lon1 < 0.0 || lon2 < 0.0)
     * 2. (lon1 > 360.0 || lon2 > 360.0)
     * 
     * lat1 = GDS_LatLon_lat1(gds) * units;
     * lat2 = GDS_LatLon_lat2(gds) * units;
     * 1. (lat1 < -90.0 || lat2 < -90.0 || lat1 > 90.0 || lat2 > 90.0)
     * 
     * s > n
     * 
     * nn > 1
     *  => nres & 16
     *      => fabs(dy - dlat) > 0.001
     * 
     * GDS_Scan_row_rev(nscan) && (nny % 2 == 0) && ((nres & 32) == 0)
     * 
     * nnx > 0 && nny > 0
     *  => stagger(sec, nnpnts,llon,llat)
     *  => nnx > 1
     *      => nres & 32
     *          => fabs(dx - fabs(dlon)) > 0.001
     */
    
    printf("SUCCESS!\n");
    return 0;
}