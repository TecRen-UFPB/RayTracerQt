#include "rtmarbletexture.h"
#include <cmath>



RTMarbleTexture::RTMarbleTexture():perlimNoise()
{
}

RTMarbleTexture::RTMarbleTexture(double ka, double kd, double ks, double kr, int n, int surfaceType,
                                 int material, RTColor colorMarbe1, RTColor colorMarbe2, double scale)
                                 :RTBRDF(ka,kd,ks,kr,n,surfaceType,material),perlimNoise()
{

    this->colorMarbe1=colorMarbe1;
    this->colorMarbe2=colorMarbe2;
    this->scale=scale;
}

RTMarbleTexture::RTMarbleTexture(RTMarbleTexture &cpy):RTBRDF(ka,kd,ks,kr,n,surfaceType,material)
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
        this->colorMarbe1=cpy.getColorMarbe1();
        this->colorMarbe1=cpy.getColorMarbe2();
        this->scale=cpy.getScale();
        this->perlimNoise=cpy.getPerlimNoise();
}


RTColor RTMarbleTexture::getColor(RTVector hitPoint) const
{
    double x = hitPoint.getX() * scale;
    double y = hitPoint.getY() * scale ;
    double z = hitPoint.getZ() * scale;
    double noiseCoef = 0;

    for (int level = 1; level < 30; level++) {

        RTVector v1( level * 0.05 * x,level * 0.15 * y,level*0.05 * z);

        noiseCoef += (1.0f / level) * fabsf(perlimNoise.linearNoise(v1));
    }


    noiseCoef = 0.5f * sinf((x + y) * 0.05f + noiseCoef) + 0.5f;

    RTColor color1=colorMarbe1;
    RTColor color2=colorMarbe2;

    return color1 * noiseCoef + color2 * (1.0f - noiseCoef);
}

double RTMarbleTexture::getRefracIndex() const
{
    return 0;
}


RTLatticeNoise RTMarbleTexture::getPerlimNoise() const
{
    return perlimNoise;
}

void RTMarbleTexture::setPerlimNoise(const RTLatticeNoise &value)
{
    perlimNoise = value;
}

RTColor RTMarbleTexture::getColorMarbe1() const
{
    return colorMarbe1;
}

void RTMarbleTexture::setColorMarbe1(const RTColor &value)
{
    colorMarbe1 = value;
}

RTColor RTMarbleTexture::getColorMarbe2() const
{
    return colorMarbe2;
}

void RTMarbleTexture::setColorMarbe2(const RTColor &value)
{
    colorMarbe2 = value;
}

double RTMarbleTexture::getScale() const
{
    return scale;
}

void RTMarbleTexture::setScale(double value)
{
    scale = value;
}
