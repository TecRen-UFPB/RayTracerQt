#ifndef RTWOODTEXTURE_H
#define RTWOODTEXTURE_H

#include"rtbrdf.h"
#include"rtlatticenoise.h"
#include "rtcolor.h"
#include "rtvector.h"

class RTWoodTexture: public RTBRDF
{

private:
    RTLatticeNoise perlimNoise;
    RTColor colorWood1;
    RTColor colorWood2;
    double scale;


public:
    RTWoodTexture();
    RTWoodTexture(double ka, double kd, double ks, double kr, int n, int surfaceType, int material,
                    RTColor colorWood1, RTColor colorWood2,double scale);
    RTWoodTexture(RTWoodTexture& cpy);

    RTLatticeNoise getPerlimNoise() const;
    void setPerlimNoise(const RTLatticeNoise &value);
    RTColor getColorWood1() const;
    void setColorWood1(const RTColor &value);
    RTColor getColorWood2() const;
    void setColorWood2(const RTColor &value);
    double getScale() const;
    void setScale(double value);

    // RTBRDF interface
public:
    virtual RTColor getColor(RTVector hitPoint) const;
    virtual double getRefracIndex() const;
};

#endif // RTWOODTEXTURE_H
