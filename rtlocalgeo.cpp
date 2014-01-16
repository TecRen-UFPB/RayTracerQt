#include "rtlocalgeo.h"

RTLocalGeo::RTLocalGeo()
{
}

RTLocalGeo::RTLocalGeo(RTLocalGeo &localgeo)
{
    this->normal.setX( localgeo.getNormal().getX() );
    this->normal.setY( localgeo.getNormal().getY() );
    this->normal.setZ( localgeo.getNormal().getZ() );

    this->point = RTPoint(localgeo.getPoint().getX(),
                          localgeo.getPoint().getY(),
                          localgeo.getPoint().getZ() );
}

RTLocalGeo::RTLocalGeo(RTPoint &point, RTVector &normal)
{
    this->normal.setX( normal.getX() );
    this->normal.setY( normal.getY() );
    this->normal.setZ( normal.getZ() );

    this->point = RTPoint( point.getX(),
                          point.getY(),
                          point.getZ() );
}

void RTLocalGeo::setNormal(RTVector &vector)
{
    this->normal.setX( vector.getX() );
    this->normal.setY( vector.getY() );
    this->normal.setZ( vector.getZ() );
}

RTVector RTLocalGeo::getNormal()
{
    return this->normal;
}

void RTLocalGeo::setPoint(RTPoint &point)
{
    this->point = RTPoint( point.getX(),
                          point.getY(),
                          point.getZ() );
}

RTPoint RTLocalGeo::getPoint()
{
    return this->point;
}
