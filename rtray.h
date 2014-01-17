#ifndef RTRAY_H
#define RTRAY_H

#include "rtpoint.h"

class RTRay
{

private:
    RTPoint pos;
    RTVector dir;
    //float t_max;
    //float t_min;

public:
    RTRay();

    /**
     * @brief RTRay
     * @param pos
     * @param dir
     */
    RTRay(RTPoint pos,RTVector dir);
    RTPoint getPos() const;
    void setPos(const RTPoint &value);
    RTVector getDir() const;
    void setDir(const RTVector &value);
};

#endif // RTRAY_H
