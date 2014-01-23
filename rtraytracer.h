#ifndef RTRAYTRACER_H
#define RTRAYTRACER_H

#include "rtcolor.h"
#include "rtray.h"
#include "rtscene.h"
#include "rtlight.h"
#include "rtcamera.h"

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
    RTColor traceRay(RTRay& ray, int depth, RTLight light);


    RTScene getScene() const;
    void setScene(const RTScene &value);


private:

    RTScene scene;

    RTColor shading(RTObject *obj, RTVector &hit, RTLight light);

    bool shadowTest(RTRay shadowRay, double distLight, RTObject *hitObject);
};

#endif // RTRAYTRACER_H
