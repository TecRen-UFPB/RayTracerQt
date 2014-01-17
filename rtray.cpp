#include "rtray.h"


RTPoint RTRay::getPos() const
{
    return pos;
}

void RTRay::setPos(const RTPoint &value)
{
    pos = value;
}

RTVector RTRay::getDir() const
{
    return dir;
}

void RTRay::setDir(const RTVector &value)
{
    dir = value;
}
RTRay::RTRay()
{
}

RTRay::RTRay(RTPoint pos,RTVector dir){

    this->pos=pos;
    this->dir=dir;
}
