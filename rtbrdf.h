#ifndef RTBRDF_H
#define RTBRDF_H

#include "rtcolor.h"
#include "rtvector.h"

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
    RTBRDF(double ka, double kd, double ks, double kr, double refracIndex, int n, int surfaceType, int material, RTColor color);
    RTBRDF(double ka, double kd, double ks, double kr, int n, int surfaceType, int material);


    virtual ~RTBRDF(){}
    //sera herdada pelas classes de textura
    virtual RTColor getColor(RTVector hitPoint) const;

    RTColor getColor();
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

    virtual double getRefracIndex() const;
    void setRefracIndex(double value);

    int getMaterial() const;
    void setMaterial(int value);

protected:
    double ka, kd, ks,kr,refracIndex;
    int n; //specular power
    int surfaceType;
    RTColor color;
    int material;

};

enum {DIFFUSE=1,SPECULAR,REFLECTIVE,REFRACTIVE};
enum {SHINY=1,CHECK};

#endif // RTBRDF_H
