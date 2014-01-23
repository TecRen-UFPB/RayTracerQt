#ifndef RTPLANE_H
#define RTPLANE_H

#include "rtpoint.h"
#include "rtobject.h"

class RTPlane : public RTObject
{
public:
    RTPlane();
    RTPlane(RTPoint point, RTVector normal);


    bool intersect(RTRay &ray, double &t);
    RTVector normalOfHitPoint(RTVector hit);

    RTPoint getPoint() const;
    void setPoint(const RTPoint &value);

    RTVector getNormal() const;
    void setNormal(const RTVector &value);

private:
    RTPoint point;
    RTVector normal;

    // RTObject interface

};

#endif // RTPLANE_H
