#ifndef RTCHECKTEXTURE_H
#define RTCHECKTEXTURE_H

#include "rtbrdf.h"

class RTCheckTexture: public RTBRDF
{

private:
    RTColor colorCheck1;
    RTColor colorCheck2;
    double size;

public:
    RTCheckTexture();
    RTCheckTexture(double ka, double kd, double ks, double kr, int n, int surfaceType,int material, RTColor colorCheck1, RTColor colorCheck2, double size);
    RTCheckTexture(RTCheckTexture& cpy);

    virtual ~RTCheckTexture(){}
   // RTBRDF interface
    virtual RTColor getColor(RTVector hitPoint) const;

    RTColor getColorCheck1() const;
    void setColorCheck1(const RTColor &value);
    RTColor getColorCheck2() const;
    void setColorCheck2(const RTColor &value);
    double getSize() const;
    void setSize(double value);

    // RTBRDF interface
public:
    virtual double getRefracIndex() const;
};

#endif // RTCHECKTEXTURE_H
