#include "rtsphere.h"
#include <cstdio>
#include <cmath>

RTSphere::RTSphere() : RTObject()
{
    this->radius = 1.0;
}

RTSphere::RTSphere(const RTSphere &sph) : RTObject(sph.getBrdf())
{
    this->radius = sph.getRadius();
    this->center = sph.center;
}

RTSphere::RTSphere(RTPoint &center, double radius, RTBRDF &brdf) : RTObject(brdf)
{
    this->center = center;
    this->radius = radius;
}

RTPoint RTSphere::getCenter() const
{
    return center;
}

void RTSphere::setCenter(const RTPoint &value)
{
    center = value;
}
double RTSphere::getRadius() const
{
    return radius;
}

void RTSphere::setRadius(double value)
{
    radius = value;
}

bool RTSphere::intersect(RTRay &ray, double &t)
{
    double a, b, c, delta, t0, t1;

    // calculates the A term
    a = std::pow( ray.getDir().getX() , 2.0 ) +
            std::pow( ray.getDir().getY() , 2.0 ) +
            std::pow( ray.getDir().getZ(), 2.0 );

    // calculates the B term
    b = 2*(
            ray.getDir().getX() * ( ray.getPos().getX() - center.getX() ) +
            ray.getDir().getY() * ( ray.getPos().getY() - center.getY() ) +
            ray.getDir().getZ() * ( ray.getPos().getZ() - center.getZ() )
            );

    // calculates the C term
    c = std::pow( ray.getPos().getX() - center.getX() , 2.0 )
            + std::pow( ray.getPos().getY() - center.getY() , 2.0 )
            + std::pow( ray.getPos().getZ() - center.getZ() , 2.0 )
            - std::pow( radius, 2.0 );

    // a*t² + b*t + c = 0

    // calculates the delta
    delta = b*b - 4*a*c;

    // No results
    if(delta<0)
        return false;

    //numeric precision
    if(b<0){
        t0 = (( -b + std::sqrt(delta) ) / 2*a)/a;
        t1 = c/(( -b + std::sqrt(delta) ) / 2*a);
    }else{

        t0 = (( -b - std::sqrt(delta) ) / 2*a)/a;
        t1 = c/(( -b - std::sqrt(delta) ) / 2*a);
    }

    if(t0>t1){
        float temp=t0;
        t0=t1;
        t1=temp;
    }


    if (t1 < 0)
       return false;

    if (t0 < 0)
    {
            t = t1;
            return true;
    }
    else
    {
            t = t0;
            return true;
    }


}

RTVector RTSphere::normalOfHitPoint(RTVector hit)
{

    RTVector normal =(hit-(this->center*1.0));
    normal.normalize();
    return normal;
}
