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
    this->color = cpy.getColor();
}

RTBRDF::RTBRDF(double kd, double ks, double ka, double kr, RTColor color)
{
    this->kd = kd;
    this->ks = ks;
    this->ka = ka;
    this->kr = kr;
    this->color = color;
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
double RTBRDF::getKr() const
{
    return kr;
}

void RTBRDF::setKr(const double &value)
{
    kr = value;
}

void RTBRDF::setColor(const RTColor &value)
{
    color = value;
}

RTColor RTBRDF::getColor() const
{
    return color;
}

