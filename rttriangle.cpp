#include "rttriangle.h"

RTTriangle::RTTriangle(RTPoint &p1, RTPoint &p2, RTPoint &p3) :
    RTObject(),
    p1(p1), p2(p2), p3(p3)
{
}

RTTriangle::RTTriangle(const RTTriangle &cpy) :
    RTObject(),
    p1(cpy.getP1()),
    p2(cpy.getP2()),
    p3(cpy.getP3())
{

}

RTTriangle::RTTriangle()
{
    this->p1 = RTPoint(0,0,0);
    this->p2 = RTPoint(0,0,0);
    this->p3 = RTPoint(0,0,0);
}

bool RTTriangle::intersect(RTRay &ray, double &t)
{

    RTVector normal = this->getNormal();

    // check if the ray intersect the plane

    double plane_t = ( (RTVector)( ray.getPos() - this->p1 ) ).dot( normal );
    plane_t = - plane_t / ray.getDir().dot( normal );

    // the ray does not hit the plane
    if(plane_t<0)
        return false;

    RTVector vecPos(ray.getPos().getX(), ray.getPos().getY(), ray.getPos().getZ());
    RTVector vecP = vecPos + ray.getDir() * plane_t;
    RTPoint p(vecP.getX(), vecP.getY(), vecP.getZ());

    // the ray does hit the plane, now we can
    // check if the hit point of the plane is
    // also into the triangle
    double a = ( (RTVector)( ( p2 - p1 ) * ( p - p1 )  ) ).dot(normal);
    double b = ( (RTVector)( ( p3 - p2 ) * ( p - p2 )  ) ).dot(normal);
    double c = ( (RTVector)( ( p1 - p3 ) * ( p - p3 )  ) ).dot(normal);

    if(a>=0 && b>=0 && c>=0)
    {
        t = plane_t;
        return true;
    } else {
        return false;
    }

}

RTVector RTTriangle::normalOfHitPoint(RTVector)
{
    return this->getNormal();
}

RTVector RTTriangle::getNormal() const
{
    // calculate normal using counterclockwise
    RTVector n1 = ( this->getP2() - this->getP1() );
    RTVector n2 = ( this->getP3() - this->getP1() );
    RTVector n = n1 * n2;
    return n;
}

//void RTTriangle::setNormal(const RTVector &value)
//{
//    normal = value;
//}
RTPoint RTTriangle::getP1() const
{
    return p1;
}

void RTTriangle::setP1(const RTPoint &value)
{
    p1 = value;
}
RTPoint RTTriangle::getP2() const
{
    return p2;
}

void RTTriangle::setP2(const RTPoint &value)
{
    p2 = value;
}
RTPoint RTTriangle::getP3() const
{
    return p3;
}

void RTTriangle::setP3(const RTPoint &value)
{
    p3 = value;
}




