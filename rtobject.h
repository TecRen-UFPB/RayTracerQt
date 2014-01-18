#ifndef RTOBJECT_H
#define RTOBJECT_H

#include "rtray.h"
#include "rtbrdf.h"
#include "rtvector.h"

#include <vector>

/**
 * @brief The RTObject class Generic class for objects
 */
class RTObject
{
public:
    /**
     * @brief RTObject Default constructor
     */
    RTObject() {}
    RTObject(const RTBRDF &brdf) { this->brdf = brdf;  }

    virtual ~RTObject(){}

    /**
     * @brief intersect Check if the ray intersect the object and return the hit point.
     * @param ray The ray to check.
     * @param hitPoint The point where the ray touched.
     * @return True if an intersect was found, false otherwise.
     */
    virtual bool intersect( RTRay &ray,double &t){

        return false;
    }

    virtual RTVector normalOfHitPoint(RTVector hit){

        return RTVector(0,0,0);
    }

    RTBRDF getBrdf() const
    {
        return brdf;
    }

    void setBrdf(const RTBRDF &value)
    {
        brdf = value;
    }


private:
    RTBRDF brdf;

};

#endif // RTOBJECT_H
