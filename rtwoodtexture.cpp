#include "rtwoodtexture.h"
#include<cmath>


RTLatticeNoise RTWoodTexture::getPerlimNoise() const
{
    return perlimNoise;
}

void RTWoodTexture::setPerlimNoise(const RTLatticeNoise &value)
{
    perlimNoise = value;
}

RTColor RTWoodTexture::getColorWood1() const
{
    return colorWood1;
}

void RTWoodTexture::setColorWood1(const RTColor &value)
{
    colorWood1 = value;
}

RTColor RTWoodTexture::getColorWood2() const
{
    return colorWood2;
}

void RTWoodTexture::setColorWood2(const RTColor &value)
{
    colorWood2 = value;
}

double RTWoodTexture::getScale() const
{
    return scale;
}

void RTWoodTexture::setScale(double value)
{
    scale = value;
}
RTWoodTexture::RTWoodTexture():perlimNoise()
{
}

RTWoodTexture::RTWoodTexture(double ka, double kd, double ks, double kr, int n, int surfaceType, int material,
                             RTColor colorWood1, RTColor colorWood2, double scale):
                            RTBRDF(ka,kd,ks,kr,n,surfaceType,material),perlimNoise()
{
    this->colorWood1=colorWood1;
    this->colorWood2=colorWood2;
    this->scale=scale;

}

RTWoodTexture::RTWoodTexture(RTWoodTexture &cpy):RTBRDF(ka,kd,ks,kr,n,surfaceType,material)
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
    this->colorWood1=cpy.getColorWood1();
    this->colorWood2=cpy.getColorWood2();
    this->scale=cpy.getScale();
    this->perlimNoise=cpy.getPerlimNoise();

}



RTColor RTWoodTexture::getColor(RTVector hitPoint) const
{
    double x = hitPoint.getX() * scale;
    double y = hitPoint.getY() * scale ;
    double z = hitPoint.getZ() * scale;



    int sCell = floor(x+0.5/scale);
    int tCell = floor(y+0.5/scale);

    RTVector v1(x,y,z);



    double grain = perlimNoise.linearNoise(hitPoint) * 5;

    grain = grain - (int)grain;

   RTColor color1=colorWood1;
    RTColor color2=colorWood2;

    return color1 * grain + color2 * (1.0f - grain);
}

double RTWoodTexture::getRefracIndex() const
{
    return 0;
}
