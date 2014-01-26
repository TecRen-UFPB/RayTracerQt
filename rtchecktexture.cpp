#include "rtchecktexture.h"
#include<cmath>


double RTCheckTexture::getSize() const
{
    return size;
}

void RTCheckTexture::setSize(double value)
{
    size = value;
}

double RTCheckTexture::getRefracIndex() const
{
    return 0;

}
RTCheckTexture::RTCheckTexture(){


}



RTCheckTexture::RTCheckTexture(double ka, double kd, double ks, double kr,int n, int surfaceType, int material,
                               RTColor colorCheck1, RTColor colorCheck2, double size):RTBRDF(ka,kd,ks,kr,n,surfaceType,material)
{
    this->colorCheck1=colorCheck1;
    this->colorCheck2=colorCheck2;
    this->size=size;

}

RTCheckTexture::RTCheckTexture(RTCheckTexture &cpy)
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
    this->colorCheck1=cpy.getColorCheck1();
    this->colorCheck2=cpy.getColorCheck2();
    this->size=cpy.getSize();

}


RTColor RTCheckTexture::getColor(RTVector hitPoint) const
{

    double eps=-0.000187453738;
    double x= hitPoint.getX()+eps;
    double y= hitPoint.getY()+eps;
    double z = hitPoint.getZ()+eps;

    bool colorChek = (((int) floor(x/size)+(int)floor(y/size)+(int)floor(z/size))%2==0);

    if(colorChek)
        return colorCheck1;
    else {
        return colorCheck2;
    }

}


RTColor RTCheckTexture::getColorCheck1() const
{
    return colorCheck1;
}

void RTCheckTexture::setColorCheck1(const RTColor &value)
{
    colorCheck1 = value;
}

RTColor RTCheckTexture::getColorCheck2() const
{
    return colorCheck2;
}

void RTCheckTexture::setColorCheck2(const RTColor &value)
{
    colorCheck2 = value;
}



