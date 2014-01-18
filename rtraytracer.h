#ifndef RTRAYTRACER_H
#define RTRAYTRACER_H

#include "rtcolor.h"
#include "rtray.h"
#include "rtscene.h"

class RTRayTracer
{
public:
    RTRayTracer();

    /**
     * @brief traceRay
     * @param ray
     * @param depth
     * @return
     */
    RTColor traceRay(RTRay& ray,int depth);


    RTScene getScene() const;
    void setScene(const RTScene &value);

private:

    RTScene scene;


};

#endif // RTRAYTRACER_H
