#ifndef RTSPHERE_H
#define RTSPHERE_H

#include "rtpoint.h"
#include "rtobject.h"

class RTSphere : public RTObject
{
public:
    /**
     * @brief RTSphere Default constructor
     */
    RTSphere();

    /**
     * @brief RTSphere Copy constructor
     * @param sph Object to copy
     */
    RTSphere(const RTSphere &sph);

    /**
     * @brief RTSphere Sphere constructor.
     * @param center Center of the sphere
     * @param radius Radius of the sphere
     */
    RTSphere(RTPoint &center, double radius);

    RTPoint getCenter() const;
    void setCenter(const RTPoint &value);

    double getRadius() const;
    void setRadius(double value);

    /**
     * @brief intersect Check if the ray intersect the sphere and return the hit point.
     * @param ray The ray to check.
     * @param hitPoint The point where the ray touched.
     * @return True if an intersect was found, false otherwise.
     */
    virtual bool intersect( RTRay &ray,double &t ) ;

    virtual RTVector normalOfHitPoint(RTVector hit);

private:
    RTPoint center;
    double radius;

};

#endif // RTSPHERE_H
