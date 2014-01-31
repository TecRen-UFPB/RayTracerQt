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
    RTColor colorTurbulence;
    int num_octaves;
    double scale;


public:
    RTTurbulenceTexture();

    RTTurbulenceTexture(double ka, double kd, double ks, double kr, int n, int surfaceType,int material, RTColor colorTurbulence, int num_octaves, double scale);
    RTTurbulenceTexture(RTTurbulenceTexture& cpy);

    virtual ~RTTurbulenceTexture();
    double getScale() const;
    void setScale(double value);

    // RTBRDF interface
public:
    virtual RTColor getColor(RTVector hitPoint) const;
    virtual double getRefracIndex() const;

    RTLatticeNoise getPerlinNoise() const;
    void setPerlinNoise(const RTLatticeNoise &value);
    int getNum_octaves() const;
    void setNum_octaves(int value);
    RTColor getColorTurbulence() const;
    void setColorTurbulence(const RTColor &value);
};

#endif // RTTURBULENCETEXTURE_H
