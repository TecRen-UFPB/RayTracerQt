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



              float 	amplitude 	= 1.0;
              float	frequency 	= 1.0;
              float 	turbulence	= 0.0;

              for (int j = 0 ; j < num_octaves; j++) {
                  turbulence	+= amplitude * fabs(perlinNoise.linearNoise(hitPoint*frequency));
                  //turbulence	+= amplitude * sqrt(fabs(perlinNoise.linearNoise(hitPoint*frequency)));  // for the thin lines in Figure 30.6 (c) & (d)
                  amplitude 	*= 0.5;
                  frequency 	*= 2.0;
              }

              turbulence /= scale;  // map to [0, 1]



              RTColor c1= colorTurbulence;
              return c1*turbulence;

       /*  double noiseCoef = 0;




       for (int level = 1; level < 10; level ++) {

           RTVector v(level * 0.05 * x,
                      level * 0.05 * y,
                      level * 0.05 * z);
           noiseCoef += (1.0f / level) * fabsf(perlinNoise.linearNoise(v));
       }*/


   //  RTColor c1= colorTurbulence1;
    // RTColor c2=colorTurbulence2;

     //return  c1* noiseCoef + c2 * (1.0f - noiseCoef);
}

double RTTurbulenceTexture::getRefracIndex() const
{
    return 0;
}

