#include "rttriangle.h"

#include <cmath>

RTTriangle::RTTriangle(RTPoint &p1, RTPoint &p2, RTPoint &p3) :
    RTObject(),
    p1(p1), p2(p2), p3(p3)
{
    RTVector normal = this->getNormalOfPlane();
    setNormal1(normal);
    setNormal2(normal);
    setNormal3(normal);
}

RTTriangle::RTTriangle(const RTTriangle &cpy) :
    RTObject(),
    p1(cpy.getP1()),
    p2(cpy.getP2()),
    p3(cpy.getP3()),
    normal1(cpy.getNormal1()),
    normal2(cpy.getNormal2()),
    normal3(cpy.getNormal3())
{

}

RTTriangle::RTTriangle()
{
    this->p1 = RTPoint(0,0,0);
    this->p2 = RTPoint(0,0,0);
    this->p3 = RTPoint(0,0,0);

    RTVector normal = this->getNormalOfPlane();
    setNormal1(normal);
    setNormal2(normal);
    setNormal3(normal);
}

bool RTTriangle::intersect(RTRay &ray, double &t)
{

    RTVector normal = this->getNormalOfPlane();

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

RTVector RTTriangle::normalOfHitPoint(RTVector hit)
{
    RTPoint ph(hit.getX(), hit.getY(), hit.getZ());

    double aT = TriangleArea(p1, p2, p3);
    double aB = TriangleArea(p1, ph, p3);
    double aC = TriangleArea(p1, ph, p2);
    double aA = aT - aB - aC;

    double c1 = aA/aT;
    double c2 = aB/aT;
    double c3 = aC/aT;

    double nX = normal1.getX()*c1 + normal2.getX()*c2 + normal3.getX()*c3;
    double nY = normal1.getY()*c1 + normal2.getY()*c2 + normal3.getY()*c3;
    double nZ = normal1.getZ()*c1 + normal2.getZ()*c2 + normal3.getZ()*c3;

    RTVector normal(nX, nY, nZ);

    return normal;
}

RTVector RTTriangle::getNormalOfPlane() const
{
    // calculate normal using counterclockwise
    RTVector n1 = ( this->getP2() - this->getP1() );
    RTVector n2 = ( this->getP3() - this->getP1() );
    RTVector n = n1 * n2;
    return n;
}

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
RTVector RTTriangle::getNormal1() const
{
    return normal1;
}

void RTTriangle::setNormal1(const RTVector &value)
{
    normal1 = value;
}
RTVector RTTriangle::getNormal2() const
{
    return normal2;
}

void RTTriangle::setNormal2(const RTVector &value)
{
    normal2 = value;
}
RTVector RTTriangle::getNormal3() const
{
    return normal3;
}

void RTTriangle::setNormal3(const RTVector &value)
{
    normal3 = value;
}

double TriangleArea( const RTPoint &A, const RTPoint &B, const RTPoint &C )
{

    // Calculate the side lengths
    double a = std::sqrt( std::pow( ( A.getX() - B.getX() ) , 2) +
                          std::pow( ( A.getY() - B.getY() ) , 2) +
                          std::pow( ( A.getZ() - B.getZ() ) , 2) );

    double b = std::sqrt( std::pow( ( A.getX() - C.getX() ) , 2) +
                          std::pow( ( A.getY() - C.getY() ) , 2) +
                          std::pow( ( A.getZ() - C.getZ() ) , 2) );

    double c = std::sqrt( std::pow( ( B.getX() - C.getX() ) , 2) +
                          std::pow( ( B.getY() - C.getY() ) , 2) +
                          std::pow( ( B.getZ() - C.getZ() ) , 2) );

    // Calculate half the perimeter
    double s = (1/2)*(a+b+c);

    // Calculate total Area
    double area = std::sqrt(s*(s-a)*(s-b)*(s-c));

    return area;

}





