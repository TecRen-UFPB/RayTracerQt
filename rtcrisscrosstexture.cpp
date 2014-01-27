#include "rtcrisscrosstexture.h"
#include <cmath>

RTColor RTCrissCrossTexture::getColorCC1() const
{
    return colorCC1;
}

void RTCrissCrossTexture::setColorCC1(const RTColor &value)
{
    colorCC1 = value;
}

RTColor RTCrissCrossTexture::getColorCC2() const
{
    return colorCC2;
}

void RTCrissCrossTexture::setColorCC2(const RTColor &value)
{
    colorCC2 = value;
}

RTColor RTCrissCrossTexture::getColorCC3() const
{
    return colorCC3;
}

void RTCrissCrossTexture::setColorCC3(const RTColor &value)
{
    colorCC3 = value;
}

double RTCrissCrossTexture::getScale() const
{
    return scale;
}

void RTCrissCrossTexture::setScale(double value)
{
    scale = value;
}

RTLatticeNoise RTCrissCrossTexture::getPerlimNoise() const
{
    return perlimNoise;
}

void RTCrissCrossTexture::setPerlimNoise(const RTLatticeNoise &value)
{
    perlimNoise = value;
}
RTCrissCrossTexture::RTCrissCrossTexture():perlimNoise()
{
}

RTCrissCrossTexture::RTCrissCrossTexture(double ka, double kd, double ks, double kr, int n, int surfaceType, int material,
                                         RTColor colorCC1, RTColor colorCC2,RTColor colorCC3, double scale):
                                         RTBRDF(ka,kd,ks,kr,n,surfaceType,material),perlimNoise()

{
    this->colorCC1=colorCC1;
    this->colorCC2=colorCC2;
    this->colorCC3=colorCC3;
    this->scale=scale;

}

RTCrissCrossTexture::RTCrissCrossTexture(RTCrissCrossTexture &cpy):RTBRDF(ka,kd,ks,kr,n,surfaceType,material)
{

    this->ka=cpy.getKa();
    this->kd = cpy.getKd();
    this->ks = cpy.getKs();
    this->ka = cpy.getKa();
    this->kr = cpy.getKr();
    this->n= cpy.getN();
    this->surfaceType=cpy.getSurfaceType();
    RTVector v;
    this->color = cpy.getColor(v);
    this->refracIndex=cpy.getRefracIndex();
    this->material=cpy.getMaterial();
    this->colorCC1=cpy.getColorCC1();
    this->colorCC2=cpy.getColorCC2();
    this->colorCC3=cpy.getColorCC3();
    this->scale=cpy.getScale();
    this->perlimNoise=cpy.getPerlimNoise();
}


RTColor RTCrissCrossTexture::getColor(RTVector hitPoint) const
{
    double x = hitPoint.getX() * scale * 0.5;
    double y = hitPoint.getY() * scale * 0.5;
    double z = hitPoint.getZ() * scale * 0.5;
    double noiseCoefA = 0;
    double noiseCoefB = 0;
    double noiseCoefC = 0;

    for (int level = 1; level < 10; level++) {

        RTVector v1( level * 0.35 * x,level * 0.05 * y,level * z);

        noiseCoefA += (1.0f / level) * fabsf(perlimNoise.linearNoise(v1));


        RTVector v2( level* x,level * 0.35 * y,level*0.05 * z);

        noiseCoefB += (1.0f / level) * fabsf(perlimNoise.linearNoise(v2));

        RTVector v3( level*0.05* x,level * y,level*0.35 * z);


        noiseCoefC += (1.0f / level) * fabsf(perlimNoise.linearNoise(v3));
    }

    noiseCoefA = 0.5f * sinf((x + z) * 0.05f + noiseCoefA) + 0.5f;
    noiseCoefB = 0.5f * sinf((y + x) * 0.05f + noiseCoefB) + 0.5f;
    noiseCoefC = 0.5f * sinf((z + y) * 0.05f + noiseCoefC) + 0.5f;


    RTColor c1= colorCC1;
    RTColor c2=colorCC2;
    RTColor c3=colorCC3;

    return (c1 * noiseCoefA + c2 * (1.0f - noiseCoefA)) * 0.25 +
           (c2 * noiseCoefB + c3 * (1.0f - noiseCoefB)) * 0.25 +
           (c3 * noiseCoefC + c1 * (1.0f - noiseCoefC)) * 0.25;

}


double RTCrissCrossTexture::getRefracIndex() const
{
    return 0;
}
