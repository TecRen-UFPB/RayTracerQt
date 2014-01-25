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
    this->color = cpy.getColor();
    this->refracIndex=cpy.getRefracIndex();

}

RTBRDF::RTBRDF(double ka, double kd, double ks, double kr,double refracIndex, int n, int surfaceType, RTColor color)
{
    this->kd = kd;
    this->ks = ks;
    this->ka = ka;
    this->kr=kr;
    this->refracIndex=refracIndex;
    this->n = n;
    this->color = color;
    this->surfaceType=surfaceType;

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






void RTBRDF::setColor(const RTColor &value)
{
    color = value;
}

RTColor RTBRDF::getColor() const
{
    return color;
}

