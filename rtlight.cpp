#include "rtlight.h"
#include<cmath>

RTLight::RTLight()
{
}

RTLight::RTLight(const RTLight &cpy) : pos(cpy.getPos()), ia(cpy.getIa()), ip(cpy.getIp()),color(cpy.getColor())
{

}

RTLight::RTLight(RTPoint &pos, double ia, double ip, RTColor color) : pos(pos), ia(ia), ip(ip)
{

    this->color=color;
}

RTPoint RTLight::getPos() const
{
    return pos;
}

void RTLight::setPos(const RTPoint &value)
{
    pos = value;
}

void RTLight::generateLightRay(RTPoint &orig,RTRay &ray)
{
    ray.setPos(orig);
    RTVector dir = pos - orig;
    dir.normalize();
    ray.setDir(dir);
}

void RTLight::getVectorToLight(RTPoint &orig, RTVector &vec)
{
    vec = pos - orig;
}



double RTLight::distToLight(RTPoint ori)
{
   return (double)(sqrt(pow(ori.getX()-pos.getX(),2)+pow(ori.getY()-pos.getY(),2)+pow(ori.getZ()-pos.getZ(),2)));

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
RTColor RTLight::getColor() const
{
    return color;
}

void RTLight::setColor(const RTColor &value)
{
    color = value;
}




