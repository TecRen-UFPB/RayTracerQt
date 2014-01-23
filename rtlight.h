#ifndef RTLIGHT_H
#define RTLIGHT_H

#include "rtpoint.h"
#include "rtray.h"
#include "rtcolor.h"

class RTLight
{
public:
    /**
     * @brief RTLight Default constructor
     */
    RTLight();

    /**
     * @brief RTLight Default copy constructor
     * @param cpy
     */
    RTLight(const RTLight &cpy);

    /**
     * @brief RTLight Constructor
     * @param pos
     */
    RTLight(RTPoint &pos, double ia, double ip,RTColor color);

    RTPoint getPos() const;
    void setPos(const RTPoint &value);

    void generateLightRay(RTPoint &orig, RTRay &ray);

    void getVectorToLight(RTPoint &orig, RTVector &vec );

    double distToLight(RTPoint ori);

    double getIa() const;
    void setIa(double value);

    double getIp() const;
    void setIp(double value);

    RTColor getColor() const;
    void setColor(const RTColor &value);

private:
    RTPoint pos;
    RTColor color;
    double ia, ip;

};

#endif // RTLIGHT_H
