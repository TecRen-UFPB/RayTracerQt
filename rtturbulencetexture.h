#ifndef RTTURBULENCETEXTURE_H
#define RTTURBULENCETEXTURE_H

#include"rtbrdf.h"
#include"rtlatticenoise.h"
#include "rtcolor.h"
#include "rtvector.h"

class RTTurbulenceTexture: public RTBRDF
{

private:
    RTLatticeNoise perlinNoise;
    RTColor colorTurbulence1;
    RTColor colorTurbulence2;
    double scale;


public:
    RTTurbulenceTexture();

    RTTurbulenceTexture(double ka, double kd, double ks, double kr, int n, int surfaceType,int material, RTColor colorTurbulence1, RTColor colorTurbulence2, double scale);
    RTTurbulenceTexture(RTTurbulenceTexture& cpy);

    virtual ~RTTurbulenceTexture();
    RTColor getColorTurbulence1() const;
    void setColorTurbulence1(const RTColor &value);
    RTColor getColorTurbulence2() const;
    void setColorTurbulence2(const RTColor &value);
    double getScale() const;
    void setScale(double value);

    // RTBRDF interface
public:
    virtual RTColor getColor(RTVector hitPoint) const;
    virtual double getRefracIndex() const;

    RTLatticeNoise getPerlinNoise() const;
    void setPerlinNoise(const RTLatticeNoise &value);
};

#endif // RTTURBULENCETEXTURE_H
