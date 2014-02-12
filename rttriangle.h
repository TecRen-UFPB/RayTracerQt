#ifndef RTTRIANGLE_H
#define RTTRIANGLE_H

#include "rtobject.h"
#include "rtpoint.h"

class RTTriangle : public RTObject
{
public:
    RTTriangle(RTPoint &p1, RTPoint &p2, RTPoint &p3);
    RTTriangle(const RTTriangle &cpy);
    RTTriangle();

    bool intersect(RTRay &ray, double &t);
    RTVector normalOfHitPoint(RTVector);

    RTVector getNormal() const;
    /*
     * We can obtain from the three vertices
     */
//    void setNormal(const RTVector &value);

    RTPoint getP1() const;
    void setP1(const RTPoint &value);

    RTPoint getP2() const;
    void setP2(const RTPoint &value);

    RTPoint getP3() const;
    void setP3(const RTPoint &value);

private:
    RTPoint p1, p2, p3;

};

#endif // RTTRIANGLE_H
