#include "rtlatticenoise.h"
#include<cmath>
#include<cstdlib>


inline double
clamp(const double x, const double min, const double max) {
    return (x < min ? min : (x > max ? max : x));
}

//kTableSize
const unsigned char RTLatticeNoise::permutation_table[] =
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
/*                           151,160,137,91,90,15,
                                 131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
                                 190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
                                 88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,134,139,48,27,166,
                                 77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
                                 102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208,89,18,169,200,196,
                                 135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,250,124,123,
                                 5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
                                 23,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167,43,172,9,
                                 129,22,39,253,19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
                                 251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,107,
                                 49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127,4,150,254,
                                 138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180*/

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


/*    int X = (int)floor(x) & 255, // FIND UNIT CUBE THAT
        Y = (int)floor(y) & 255, // CONTAINS POINT.
        Z = (int)floor(z) & 255;
    x -= floor(x);                   // FIND RELATIVE X,Y,Z
    y -= floor(y);                   // OF POINT IN CUBE.
    z -= floor(z);
    double u = fade(x),              // COMPUTE FADE CURVES
           v = fade(y),              // FOR EACH OF X,Y,Z.
           w = fade(z);
    int A = value_table[X]+Y,    // HASH COORDINATES OF
        AA = value_table[A]+Z,   // THE 8 CUBE CORNERS,
        AB = value_table[A+1]+Z,
        B = value_table[X+1]+Y,
        BA = value_table[B]+Z,
        BB = value_table[B+1]+Z;

   return
    lerp(w, lerp(v, lerp(u, grad(value_table[AA], x, y, z),       // AND ADD
                            grad(value_table[BA], x-1, y, z)),    // BLENDED
                    lerp(u, grad(value_table[AB], x, y-1, z),     // RESULTS
                            grad(value_table[BB], x-1, y-1, z))), // FROM 8
            lerp(v, lerp(u, grad(value_table[AA+1], x, y, z-1),   // CORNERS
                            grad(value_table[BA+1], x-1, y, z-1)),// OF CUBE
                    lerp(u, grad(value_table[AB+1], x, y-1, z-1 ),
                            grad(value_table[BB+1], x-1, y-1, z-1 ))));


    */int 	ix, iy, iz;
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





    /*int 	ix, iy, iz;
    double 	fx, fy, fz;
    double 	d[2][2][2];
    double 	x0, x1, x2, x3, y0, y1, z0;

    ix = FLOOR(x);
    fx = x - ix;

    iy = FLOOR(y);
    fy = y - iy;

    iz = FLOOR(z);
    fz = z - iz;

    for (int k = 0; k <= 1; k++)
        for (int j = 0; j <= 1; j++)
            for (int i = 0; i <= 1; i++)
                d[k][j][i] = value_table[INDEX(ix + i, iy + j, iz + k)];

    x0 = lerp(fx, d[0][0][0], d[0][0][1]);
    x1 = lerp(fx, d[0][1][0], d[0][1][1]);
    x2 = lerp(fx, d[1][0][0], d[1][0][1]);
    x3 = lerp(fx, d[1][1][0], d[1][1][1]);
    y0 = lerp(fy, x0, x1);
    y1 = lerp(fy, x2, x3);
    z0 = lerp(fz, y0, y1);

    return z0;*/

}



void RTLatticeNoise::initValueTable()
{


   /* for (int i = 0; i < 256; i++) {
          value_table[256+i] = value_table[i] = permutation_table[i];
       }*/
    srand(seed_value);
        for (int i = 0; i < kTableSize; i++)
            value_table[i] = -1 + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(2)));//1.0 - 2.0 * rand();

}

double RTLatticeNoise::fade(double t) const {
   return t * t * t * (t * (t * 6 - 15) + 10);
}

double RTLatticeNoise::grad(int hash, double x, double y, double z) const {
   int h = hash & 15;
   // CONVERT LO 4 BITS OF HASH CODE
   double u = h<8||h==12||h==13 ? x : y, // INTO 12 GRADIENT DIRECTIONS.
          v = h < 4||h == 12||h == 13 ? y : z;
   return ((h & 1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
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




