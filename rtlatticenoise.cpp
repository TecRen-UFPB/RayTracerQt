#include "rtlatticenoise.h"
#include<cmath>
#include<cstdlib>


inline double
clamp(const double x, const double min, const double max) {
    return (x < min ? min : (x > max ? max : x));
}


const unsigned char RTLatticeNoise::permutation_table[kTableSize] =
{ 					        225,155,210,108,175,199,221,144,203,116, 70,213, 69,158, 33,252,
                            5, 82,173,133,222,139,174, 27,  9, 71, 90,246, 75,130, 91,191,
                            169,138,  2,151,194,235, 81,  7, 25,113,228,159,205,253,134,142,
                            248, 65,224,217, 22,121,229, 63, 89,103, 96,104,156, 17,201,129,
                            36,  8,165,110,237,117,231, 56,132,211,152, 20,181,111,239,218,
                            170,163, 51,172,157, 47, 80,212,176,250, 87, 49, 99,242,136,189,
                            162,115, 44, 43,124, 94,150, 16,141,247, 32, 10,198,223,255, 72,
                            53,131, 84, 57,220,197, 58, 50,208, 11,241, 28,  3,192, 62,202,
                            18,215,153, 24, 76, 41, 15,179, 39, 46, 55,  6,128,167, 23,188,
                            106, 34,187,140,164, 73,112,182,244,195,227, 13, 35, 77,196,185,
                            26,200,226,119, 31,123,168,125,249, 68,183,230,177,135,160,180,
                            12,  1,243,148,102,166, 38,238,251, 37,240,126, 64, 74,161, 40,
                            184,149,171,178,101, 66, 29, 59,146, 61,254,107, 42, 86,154,  4,
                            236,232,120, 21,233,209, 45, 98,193,114, 78, 19,206, 14,118,127,
                            48, 79,147, 85, 30,207,219, 54, 88,234,190,122, 95, 67,143,109,
                            137,214,145, 93, 92,100,245,  0,216,186, 60, 83,105, 97,204, 52

   };



RTLatticeNoise::RTLatticeNoise()
{
    initValueTable();
}


double RTLatticeNoise::linearNoise(RTVector hit) const
{

    int x= hit.getX();
    int y= hit.getY();
    int z= hit.getZ();

        int 	ix, iy, iz;
        double 	fx, fy, fz;
        double 	xknots[4], yknots[4], zknots[4];

        ix = floor(x);
        fx = x - ix;

        iy = floor(y);
        fy = y - iy;

        iz = floor(z);
        fz = z - iz;

        for (int k = -1; k <= 2; k++) {
            for (int j = -1; j <= 2; j++) {
                for (int i = -1; i <= 2; i++) {
                    xknots[i+1] = value_table[INDEX(ix + i, iy + j, iz + k)];
                }
                yknots[j+1] = four_knot_spline(fx, xknots);
            }
            zknots[k+1] = four_knot_spline(fy, yknots);
        }

        return (clamp(four_knot_spline(fz, zknots), -1.0, 1.0));
}



void RTLatticeNoise::initValueTable()
{

    srand(seed_value);
        for (int i = 0; i < kTableSize; i++)
            value_table[i] = 1.0 - 2.0 * rand();

}

double RTLatticeNoise::lerp(double t, double a, double b) const
{
            return (a + t * (b - a));
}



double RTLatticeNoise::four_knot_spline(const double x, const double knots[]) const
{
    double c3 = -0.5 * knots[0] + 1.5 * knots[1] - 1.5 * knots[2] + 0.5 * knots[3];
    double c2 = knots[0] - 2.5 * knots[1] + 2.0 * knots[2] - 0.5 * knots[3];
    double c1 = 0.5 * (-knots[0] + knots [2]);
    double c0 = knots[1];

    return ((double)((c3*x + c2)*x + c1)*x + c0);
}




