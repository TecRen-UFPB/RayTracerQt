#include "rtsphere.h"

#include <cmath>

RTSphere::RTSphere()
{
    this->radius = 1.0;
}

RTSphere::RTSphere(const RTSphere &sph)
{
    this->radius = sph.getRadius();
    this->center = sph.center;
}

RTSphere::RTSphere(RTPoint &center, double radius)
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

bool RTSphere::intersect(RTRay &ray, std::vector<double> &tValues)
{
    double a, b, c, delta, x1, x2;

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

    x1 = ( -b + std::sqrt(delta) ) / 2*a;
    tValues.push_back(x1);

    if(delta!=0)
    {
        x2 = ( -b - std::sqrt(delta) ) / 2*a;
        tValues.push_back(x2);
    }

    // TODO check if this is correct
    // TODO check the normal required for RTLocalGeo
    // TODO check what t value is used in the case of delta>0
//    RTPoint point(ray.getPos().getX() + x1*ray.getDir().getX(),
//                  ray.getPos().getY() + x1*ray.getDir().getY(),
//                  ray.getPos().getZ() + x1*ray.getDir().getZ()
//                );

//    hitPoint.setPoint(point);

    return true;

}
