/**
 * This is a test for the wgrib2 project. 
 * 
 * This test is for the gauss2ll() routine from geo.c.
 * Alyson Stahl, 9/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "wgrib2.h"
#include <setjmp.h>

#define TOL 1e-6

int gauss2ll(unsigned char **sec, double **llat, double **llon);

extern jmp_buf fatal_err;

int
main(){
    printf("Testing gauss2ll()...\n");
    printf("Test Case 1: Regular Gaussian lat-lon grid.\n");
    {
        unsigned char sec1[16] = {0};
        unsigned char sec3[72] = {0};
        unsigned char *sec[8] = {NULL};
        double *llat = NULL;
        double *llon = NULL;
        unsigned int exp_size = 6;
        const double expected_lat[6] = {
            19.875719147440904, 19.875719147440904, 19.875719147440904,
            59.444408289166775, 59.444408289166775, 59.444408289166775
        };
        const double expected_lon[6] = {350.0, 0.0, 10.0, 350.0, 0.0, 10.0};

        sec[1] = sec1;
        sec[3] = sec3;

        sec1[3] = 16;
        sec1[4] = 1;

        sec3[3] = 72;
        sec3[4] = 3;
        sec3[9] = 6;
        sec3[13] = 40;
        sec3[33] = 3;
        sec3[37] = 2;
        sec3[46] = 1;
        sec3[47] = 47;
        sec3[48] = 71;
        sec3[49] = 135;
        sec3[50] = 20;
        sec3[51] = 220;
        sec3[52] = 147;
        sec3[53] = 128;
        sec3[55] = 3;
        sec3[56] = 139;
        sec3[57] = 12;
        sec3[58] = 184;
        sec3[59] = 0;
        sec3[60] = 152;
        sec3[61] = 150;
        sec3[62] = 128;
        sec3[63] = 0;
        sec3[64] = 152;
        sec3[65] = 150;
        sec3[66] = 128;
        sec3[70] = 2;
        sec3[71] = 64;

        if (gauss2ll(sec, &llat, &llon) != 0 || llat == NULL || llon == NULL) {
            printf("gauss2ll() failed on valid input.\n");
            free(llat);
            free(llon);
            return 1;
        }

        for (unsigned int i = 0; i < exp_size; i++) {
            if (fabs(llat[i] - expected_lat[i]) > TOL ||
                fabs(llon[i] - expected_lon[i]) > TOL) {
                printf("gauss2ll() produced an unexpected coordinate at index %u.\n", i);
                free(llat);
                free(llon);
                return 1;
            }
        }

        free(llat);
        free(llon);
    }
    printf("Test Case 2: Quasi-regular Gaussian lat-lon grid.\n");
    {
        unsigned char sec1[16] = {0};
        unsigned char sec3[74] = {0};
        unsigned char *sec[8] = {NULL};
        double *llat = NULL;
        double *llon = NULL;
        unsigned int exp_size = 5;
        const double expected_lat[5] = {
            19.875719147440904, 19.875719147440904,
            59.444408289166775, 59.444408289166775, 59.444408289166775
        };
        const double expected_lon[5] = {350.0, 10.0, 350.0, 0.0, 10.0};

        sec[1] = sec1;
        sec[3] = sec3;

        sec1[3] = 16;
        sec1[4] = 1;

        sec3[3] = 74;
        sec3[4] = 3;
        sec3[9] = 5;
        sec3[10] = 1;
        sec3[13] = 40;
        sec3[30] = 255;
        sec3[31] = 255;
        sec3[32] = 255;
        sec3[33] = 255;
        sec3[37] = 2;
        sec3[46] = 1;
        sec3[47] = 47;
        sec3[48] = 71;
        sec3[49] = 135;
        sec3[50] = 20;
        sec3[51] = 220;
        sec3[52] = 147;
        sec3[53] = 128;
        sec3[55] = 3;
        sec3[56] = 139;
        sec3[57] = 12;
        sec3[58] = 184;
        sec3[59] = 0;
        sec3[60] = 152;
        sec3[61] = 150;
        sec3[62] = 128;
        sec3[63] = 0;
        sec3[64] = 152;
        sec3[65] = 150;
        sec3[66] = 128;
        sec3[70] = 2;
        sec3[71] = 64;
        sec3[72] = 2;
        sec3[73] = 3;

        if (gauss2ll(sec, &llat, &llon) != 0 || llat == NULL || llon == NULL) {
            printf("gauss2ll() failed on valid input.\n");
            free(llat);
            free(llon);
            return 2;
        }

        for (unsigned int i = 0; i < exp_size; i++) {
            if (fabs(llat[i] - expected_lat[i]) > TOL ||
                fabs(llon[i] - expected_lon[i]) > TOL) {
                printf("gauss2ll() produced an unexpected coordinate at index %u.\n", i);
                free(llat);
                free(llon);
                return 2;
            }
        }

        free(llat);
        free(llon);
    }
    printf("Test Case 3: Regular Gaussian lat-lon grid with negative x and y scanning order.\n");
    {
        unsigned char sec1[16] = {0};
        unsigned char sec3[72] = {0};
        unsigned char *sec[8] = {NULL};
        double *llat = NULL;
        double *llon = NULL;
        unsigned int exp_size = 6;
        const double expected_lat[6] = {
            19.875719147440904, 19.875719147440904, 19.875719147440904,
            59.444408289166775, 59.444408289166775, 59.444408289166775
        };
        const double expected_lon[6] = {350.0, 0.0, 10.0, 350.0, 0.0, 10.0};

        sec[1] = sec1;
        sec[3] = sec3;

        sec1[3] = 16;
        sec1[4] = 1;

        sec3[3] = 72;
        sec3[4] = 3;
        sec3[9] = 6;
        sec3[13] = 40;
        sec3[33] = 3;
        sec3[37] = 2;
        sec3[46] = 3;
        sec3[47] = 139;
        sec3[48] = 12;
        sec3[49] = 184;
        sec3[50] = 0;
        sec3[51] = 152;
        sec3[52] = 150;
        sec3[53] = 128;
        sec3[55] = 1;
        sec3[56] = 47;
        sec3[57] = 71;
        sec3[58] = 135;
        sec3[59] = 20;
        sec3[60] = 220;
        sec3[61] = 147;
        sec3[62] = 128;
        sec3[63] = 0;
        sec3[64] = 152;
        sec3[65] = 150;
        sec3[66] = 128;
        sec3[70] = 2;
        sec3[71] = 128;

        if (gauss2ll(sec, &llat, &llon) != 0 || llat == NULL || llon == NULL) {
            printf("gauss2ll() failed on valid input.\n");
            free(llat);
            free(llon);
            return 3;
        }

        for (unsigned int i = 0; i < exp_size; i++) {
            if (fabs(llat[i] - expected_lat[i]) > TOL ||
                fabs(llon[i] - expected_lon[i]) > TOL) {
                printf("gauss2ll() produced an unexpected coordinate at index %u.\n", i);
                free(llat);
                free(llon);
                return 3;
            }
        }

        free(llat);
        free(llon);
    }
    printf("SUCCESS!\n");
    return 0;
}