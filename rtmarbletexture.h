#ifndef RTMARBLETEXTURE_H
#define RTMARBLETEXTURE_H

#include"rtbrdf.h"
#include"rtlatticenoise.h"
#include "rtcolor.h"
#include "rtvector.h"

class RTMarbleTexture: public RTBRDF
{

private:

    RTLatticeNoise perlimNoise;
    RTColor colorMarbe1;
    RTColor colorMarbe2;
    double scale;

public:
    RTMarbleTexture();
    RTMarbleTexture(double ka, double kd, double ks, double kr, int n, int surfaceType, int material,
                    RTColor colorMarbe1, RTColor colorMarbe2,double scale);
    RTMarbleTexture(RTMarbleTexture& cpy);



    // RTBRDF interface
public:
    virtual RTColor getColor(RTVector hitPoint) const;
    virtual double getRefracIndex() const;
    RTLatticeNoise getPerlimNoise() const;
    void setPerlimNoise(const RTLatticeNoise &value);
    RTColor getColorMarbe1() const;
    void setColorMarbe1(const RTColor &value);
    RTColor getColorMarbe2() const;
    void setColorMarbe2(const RTColor &value);
    double getScale() const;
    void setScale(double value);
};

#endif // RTMARBLETEXTURE_H
