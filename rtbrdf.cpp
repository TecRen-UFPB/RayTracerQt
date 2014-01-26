#include "rtbrdf.h"

RTBRDF::RTBRDF()
{
}


RTBRDF::RTBRDF(const RTBRDF &cpy)
{
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

}

RTBRDF::RTBRDF(double ka, double kd, double ks, double kr,double refracIndex, int n, int surfaceType, int material, RTColor color)
{
    this->kd = kd;
    this->ks = ks;
    this->ka = ka;
    this->kr=kr;
    this->refracIndex=refracIndex;
    this->n = n;
    this->color = color;
    this->surfaceType=surfaceType;
    this->material=material;

}

RTBRDF::RTBRDF(double ka, double kd, double ks, double kr, int n, int surfaceType,int material)
{
    this->kd = kd;
    this->ks = ks;
    this->ka = ka;
    this->kr=kr;
    this->n = n;
    this->surfaceType=surfaceType;
    this->material=material;

}

double RTBRDF::getKa() const
{
    return ka;
}

void RTBRDF::setKa(const double &value)
{
    ka = value;
}
double RTBRDF::getKd() const
{
    return kd;
}

void RTBRDF::setKd(const double &value)
{
    kd = value;
}
double RTBRDF::getKs() const
{
    return ks;
}

void RTBRDF::setKs(const double &value)
{
    ks = value;
}

int RTBRDF::getN() const
{
    return n;
}

void RTBRDF::setN(int value)
{
    n = value;
}
int RTBRDF::getSurfaceType() const
{
    return surfaceType;
}

void RTBRDF::setSurfaceType(int value)
{
    surfaceType = value;
}
double RTBRDF::getKr() const
{
    return kr;
}

void RTBRDF::setKr(double value)
{
    kr = value;
}
double RTBRDF::getRefracIndex() const
{
    return refracIndex;
}

void RTBRDF::setRefracIndex(double value)
{
    refracIndex = value;
}
int RTBRDF::getMaterial() const
{
    return material;
}

void RTBRDF::setMaterial(int value)
{
    material = value;
}







void RTBRDF::setColor(const RTColor &value)
{
    color = value;
}

RTColor RTBRDF::getColor(RTVector hitPoint) const
{
    return color;
}

RTColor RTBRDF::getColor()
{
    return color;
}

