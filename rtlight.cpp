#include "rtlight.h"

RTLight::RTLight()
{
}

RTLight::RTLight(const RTLight &cpy) : pos(cpy.getPos()), ia(cpy.getIa()), ip(cpy.getIp()), coef(cpy.getCoef())
{

}

RTLight::RTLight(RTPoint &pos, double ia, double ip, double coef) : pos(pos), ia(ia), ip(ip), coef(coef)
{

}

RTPoint RTLight::getPos() const
{
    return pos;
}

void RTLight::setPos(const RTPoint &value)
{
    pos = value;
}

void RTLight::generateLightRay(RTPoint &orig, RTRay &ray)
{
    ray.setPos(orig);
    RTVector dir = pos - orig;
    ray.setDir(dir);
}

void RTLight::getVectorToLight(RTPoint &orig, RTVector &vec)
{
    vec = pos - orig;
}

double RTLight::getCoef() const
{
    return coef;
}

void RTLight::setCoef(double value)
{
    coef = value;
}
double RTLight::getIa() const
{
    return ia;
}

void RTLight::setIa(double value)
{
    ia = value;
}
double RTLight::getIp() const
{
    return ip;
}

void RTLight::setIp(double value)
{
    ip = value;
}



