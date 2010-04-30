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

int RTTurbulenceTexture::getNum_octaves() const
{
    return num_octaves;
}

void RTTurbulenceTexture::setNum_octaves(int value)
{
    num_octaves = value;
}

RTColor RTTurbulenceTexture::getColorTurbulence() const
{
    return colorTurbulence;
}

void RTTurbulenceTexture::setColorTurbulence(const RTColor &value)
{
    colorTurbulence = value;
}
RTTurbulenceTexture::RTTurbulenceTexture():perlinNoise()
{

}

RTTurbulenceTexture::RTTurbulenceTexture(double ka, double kd, double ks, double kr, int n, int surfaceType, int material,
                                         RTColor colorTurbulence, int num_octaves, double scale):
                                         RTBRDF(ka,kd,ks,kr,n,surfaceType,material),perlinNoise()
{
    this->colorTurbulence=colorTurbulence;
    this->num_octaves=num_octaves;
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
    this->colorTurbulence=cpy.getColorTurbulence();
    this->num_octaves=cpy.getNum_octaves();
    this->scale=cpy.getScale();
    this->perlinNoise=cpy.getPerlinNoise();
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




       for (int level = 1; level < num_octaves; level ++) {

           RTVector v(level * 0.05 * x,
                      level * 0.05 * y,
                      level * 0.05 * z);
           noiseCoef += (1.0f / level) * fabsf(perlinNoise.linearNoise(v));
       }


     RTColor c1= colorTurbulence;
    // RTColor c2=colorTurbulence2;

     return  c1* noiseCoef;// + c2 * (1.0f - noiseCoef);
}

double RTTurbulenceTexture::getRefracIndex() const
{
    return 0;
}

