#ifndef RTOBJECT_H
#define RTOBJECT_H

#include "rtray.h"

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
    virtual ~RTObject(){}

    /**
     * @brief intersect Check if the ray intersect the object and return the hit point.
     * @param ray The ray to check.
     * @param hitPoint The point where the ray touched.
     * @return True if an intersect was found, false otherwise.
     */
    virtual bool intersect( RTRay &ray, std::vector<double> &tValues) = 0;

private:

};

#endif // RTOBJECT_H
