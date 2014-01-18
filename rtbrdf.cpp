#include "rtbrdf.h"

RTBRDF::RTBRDF()
{
}

RTBRDF::RTBRDF(const RTBRDF &cpy)
{
    this->ka = cpy.getKa();
    this->kd = cpy.getKd();
    this->kr = cpy.getKr();
    this->ks = cpy.getKs();
}

RTBRDF::RTBRDF(RTColor &kd, RTColor &ks, RTColor &ka, RTColor &kr)
{
    this->kd = kd;
    this->ks = ks;
    this->ka = ka;
    this->kr = kr;
}

RTColor RTBRDF::getKd() const
{
    return kd;
}

void RTBRDF::setKd(const RTColor &value)
{
    kd = value;
}
RTColor RTBRDF::getKs() const
{
    return ks;
}

void RTBRDF::setKs(const RTColor &value)
{
    ks = value;
}
RTColor RTBRDF::getKa() const
{
    return ka;
}

void RTBRDF::setKa(const RTColor &value)
{
    ka = value;
}
RTColor RTBRDF::getKr() const
{
    return kr;
}

void RTBRDF::setKr(const RTColor &value)
{
    kr = value;
}




