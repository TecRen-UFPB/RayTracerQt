#include "rtlatticenoise.h"
#include<cmath>
#include<cstdlib>

const unsigned char RTLatticeNoise::permutation_table[kTableSize] =
{
    225,155,210,108,175,199,221,144,203,116, 70,213, 69,158, 33,252,
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
    initValueTable(seed_value);
}


double RTLatticeNoise::linearNoise(RTVector hit) const
{

        //utiliza interpolação trilinear, fazendo 4 interpolações em x, 2 em y e 1 em z

        int 	ix, iy, iz;
        float 	fx, fy, fz;
        float 	d[2][2][2];
        float 	x0, x1, x2, x3, y0, y1, z0;

        ix = floor(hit.getX());
        fx = hit.getX() - ix;

        iy = floor(hit.getY());
        fy = hit.getY() - iy;

        iz = floor(hit.getZ());
        fz = hit.getZ() - iz;

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

        return (z0);

}



void RTLatticeNoise::initValueTable(int seed_value)
{
    srand(static_cast <unsigned> (seed_value));
       for (int i = 0; i < kTableSize; i++)
           value_table[i] = -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2))); //[-1,1]

}

double RTLatticeNoise::lerp(double t, double a, double b) const
{
            return (a + t * (b - a));
}


