#ifndef RTLOCALGEO_H
#define RTLOCALGEO_H

#include "rtpoint.h"
#include "rtvector.h"

class RTLocalGeo
{
public:

    /**
     * @brief RTLocalGeo Constructor for local geometry
     * @param point Hit point
     * @param normal Normal at the point
     */
    RTLocalGeo(RTPoint &point, RTVector &normal);

    /**
     * @brief RTLocalGeo Does a copy of the object
     * @param localgeo Object to be copied
     */
    RTLocalGeo(RTLocalGeo &localgeo);

    /**
     * @brief RTLocalGeo Default constructor.
     */
    RTLocalGeo();

    void setPoint(RTPoint &point);
    RTPoint getPoint();

    void setNormal(RTVector &vector);
    RTVector getNormal();

private:
    RTPoint point;
    RTVector normal;

};

#endif // RTLOCALGEO_H
