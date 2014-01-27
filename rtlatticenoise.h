#ifndef RTLATTICENOISE_H
#define RTLATTICENOISE_H


#include"rtvector.h"


const int kTableSize	= 256;
const int kTableMask	= kTableSize - 1;
const int seed_value 	= 253;


#define PERM(x)          permutation_table[(x)&kTableMask]
#define INDEX(ix,iy,iz)  PERM((ix)+PERM((iy)+PERM(iz))) //find the integer part of the hit point's coordinates
#define FLOOR(x) 		 ((int)(x) - ((x) < 0 && (x) != (int) (x)))



class RTLatticeNoise
{
public:
    RTLatticeNoise();


    /**
     * @brief linearNoise gerenate noise using trilinear interpolation
     * @param hit point
     * @return
     */
    double linearNoise(RTVector hit) const;

private:
    static const unsigned char permutation_table[kTableSize];	//array de permutações
    double 	value_table[kTableSize]; //array de pseudo-ramdon numbers


    /**
     * @brief initValueTable initialises the integer lattice of PRN's
     * @param seed_value seed for generate PRN's values
     */
    void initValueTable(int seed_value);


    /**
     * @brief lerp function that lineary interpolates two values
     * @param t control
     * @param a first value of linear interpolation
     * @param b second value of linear interpolation
     * @return  the result of linear interpolation between a and b
     */
    double lerp(double t, double a, double b) const;




};

#endif // RTLATTICENOISE_H
