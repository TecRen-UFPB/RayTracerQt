#ifndef RTCRISSCROSSTEXTURE_H
#define RTCRISSCROSSTEXTURE_H

#include"rtbrdf.h"
#include"rtlatticenoise.h"
#include "rtcolor.h"
#include "rtvector.h"

class RTCrissCrossTexture : public RTBRDF
{
private:

    RTLatticeNoise perlimNoise;
    RTColor colorCC1;
    RTColor colorCC2;
    RTColor colorCC3;
    double scale;

public:
    RTCrissCrossTexture();

    RTCrissCrossTexture(double ka, double kd, double ks, double kr, int n, int surfaceType, int material, RTColor colorCC1, RTColor colorCC2, RTColor colorCC3, double scale);
    RTCrissCrossTexture(RTCrissCrossTexture& cpy);

    virtual ~RTCrissCrossTexture(){}


    // RTBRDF interface
    virtual RTColor getColor(RTVector hitPoint) const;
    virtual double getRefracIndex() const;
    RTColor getColorCC1() const;
    void setColorCC1(const RTColor &value);
    RTColor getColorCC2() const;
    void setColorCC2(const RTColor &value);
    RTColor getColorCC3() const;
    void setColorCC3(const RTColor &value);
    double getScale() const;
    void setScale(double value);
    RTLatticeNoise getPerlimNoise() const;
    void setPerlimNoise(const RTLatticeNoise &value);
};

#endif // RTCRISSCROSSTEXTURE_H
