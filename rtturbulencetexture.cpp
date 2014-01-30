#include "rtturbulencetexture.h"
#include<cmath>

RTTurbulenceTexture::~RTTurbulenceTexture(){

}


RTLatticeNoise RTTurbulenceTexture::getPerlinNoise() const
{
    return perlinNoise;
}

void RTTurbulenceTexture::setPerlinNoise(const RTLatticeNoise &value)
{
    perlinNoise = value;
}
RTTurbulenceTexture::RTTurbulenceTexture():perlinNoise()
{

}

RTTurbulenceTexture::RTTurbulenceTexture(double ka, double kd, double ks, double kr, int n, int surfaceType, int material,
                                         RTColor colorTurbulence1, RTColor colorTurbulence2, double scale):
                                         RTBRDF(ka,kd,ks,kr,n,surfaceType,material),perlinNoise()
{
    this->colorTurbulence1=colorTurbulence1;
    this->colorTurbulence2=colorTurbulence2;
    this->scale=scale;

}

RTTurbulenceTexture::RTTurbulenceTexture(RTTurbulenceTexture &cpy):RTBRDF(ka,kd,ks,kr,n,surfaceType,material)
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
    this->colorTurbulence1=cpy.getColorTurbulence1();
    this->colorTurbulence2=cpy.getColorTurbulence2();
    this->scale=cpy.getScale();
    this->perlinNoise=cpy.getPerlinNoise();
}



RTColor RTTurbulenceTexture::getColorTurbulence1() const
{
    return colorTurbulence1;
}

void RTTurbulenceTexture::setColorTurbulence1(const RTColor &value)
{
    colorTurbulence1 = value;
}

RTColor RTTurbulenceTexture::getColorTurbulence2() const
{
    return colorTurbulence2;
}

void RTTurbulenceTexture::setColorTurbulence2(const RTColor &value)
{
    colorTurbulence2 = value;
}

double RTTurbulenceTexture::getScale() const
{
    return scale;
}

void RTTurbulenceTexture::setScale(double value)
{
    scale = value;
}

RTColor RTTurbulenceTexture::getColor(RTVector hitPoint) const
{

      double x = hitPoint.getX() * scale;
       double y = hitPoint.getY() * scale;
       double z = hitPoint.getZ() * scale;

       double noiseCoef = 0;




       for (int level = 1; level < 10; level ++) {
            RTVector v( level * 0.05 * x,level * 0.05 * y,level * 0.05 * z);

            noiseCoef += (1.0f / level) * fabsf(perlinNoise.linearNoise(v));
       }


     RTColor c1= colorTurbulence1;
     RTColor c2=colorTurbulence2;

     return  c1* noiseCoef + c2 * (1.0f - noiseCoef);
}

double RTTurbulenceTexture::getRefracIndex() const
{
    return 0;
}

