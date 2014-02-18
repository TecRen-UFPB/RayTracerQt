#ifndef RTTRIANGLE_H
#define RTTRIANGLE_H

#include "rtobject.h"
#include "rtpoint.h"

/**
  * Calculate area of triangle using Heron's Formula
  */
extern double TriangleArea( const RTPoint &A, const RTPoint &B, const RTPoint &C );

class RTTriangle : public RTObject
{
public:
    RTTriangle(RTPoint &p1, RTPoint &p2, RTPoint &p3);
    RTTriangle(const RTTriangle &cpy);
    RTTriangle();

    bool intersect(RTRay &ray, double &t);
    RTVector normalOfHitPoint(RTVector hit);

    RTVector getNormalOfPlane() const;

    RTPoint getP1() const;
    void setP1(const RTPoint &value);

    RTPoint getP2() const;
    void setP2(const RTPoint &value);

    RTPoint getP3() const;
    void setP3(const RTPoint &value);

    RTVector getNormal1() const;
    void setNormal1(const RTVector &value);

    RTVector getNormal2() const;
    void setNormal2(const RTVector &value);

    RTVector getNormal3() const;
    void setNormal3(const RTVector &value);

private:
    RTPoint p1, p2, p3;
    RTVector normal1, normal2, normal3;

};

#endif // RTTRIANGLE_H
