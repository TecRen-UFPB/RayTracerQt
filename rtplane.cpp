#include "rtplane.h"
#include<cstdlib>

RTPlane::RTPlane()
{
    this->objTag=PLANE;
}

RTPlane::RTPlane(RTPoint point, RTVector normal)
{

    this->point=point;
    this->normal=normal;
    this->objTag=PLANE;
}

bool RTPlane::intersect(RTRay &ray, double &t)
{
    double NdotD=this->normal.dot(ray.getDir());
    double aux=(NdotD<0)?(NdotD*-1):NdotD;
    if(aux<0.00001)
        return false;
    t=(this->normal.dot(ray.getPos()-this->point)/NdotD);
    if(t<0)
        return false;
    else return true;
}

RTVector RTPlane::normalOfHitPoint(RTVector hit)
{
    return this->normal;
}
RTPoint RTPlane::getPoint() const
{
    return point;
}

void RTPlane::setPoint(const RTPoint &value)
{
    point = value;
}
RTVector RTPlane::getNormal() const
{
    return normal;
}

void RTPlane::setNormal(const RTVector &value)
{
    normal = value;
}


