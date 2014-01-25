#ifndef RTBRDF_H
#define RTBRDF_H

#include "rtcolor.h"

#include <vector>

class RTBRDF
{
public:
    /**
     * @brief RTBRDF Default constructor
     */
    RTBRDF();

    /**
     * @brief RTBRDF Default copy constructor
     * @param cpy
     */
    RTBRDF(const RTBRDF &cpy);

    /**
     * @brief RTBRDF Constructor
     * @param kd
     * @param ks
     * @param ka
     * @param kr
     */
    RTBRDF(double ka, double kd, double ks, double kr, double refracIndex, int n, int surfaceType, RTColor color);


    RTColor getColor() const;
    void setColor(const RTColor &value);

    double getKa() const;
    void setKa(const double &value);

    double getKd() const;
    void setKd(const double &value);

    double getKs() const;
    void setKs(const double &value);


    int getN() const;
    void setN(int value);

    int getSurfaceType() const;
    void setSurfaceType(int value);


    double getKr() const;
    void setKr(double value);

    double getRefracIndex() const;
    void setRefracIndex(double value);

private:
    double ka, kd, ks,kr,refracIndex;
    int n; //specular power
    int surfaceType;
    RTColor color;

};

enum {DIFFUSE=1,SPECULAR,REFLECTIVE,REFRACTIVE};

#endif // RTBRDF_H
