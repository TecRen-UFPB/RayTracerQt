#ifndef RTRAY_H
#define RTRAY_H

#include "rtpoint.h"

class RTRAy
{

private:
    RTPoint pos;
    RTVector dir;
    float t_max;
    float t_min;

public:
    RTRAy();
};

#endif // RTRAY_H
