#ifndef RTSCENE_H
#define RTSCENE_H

#define M_PI 3.14159265358979323846;

#include "rtcamera.h"
#include "rtobject.h"
#include <vector>

class RTScene
{
public:
    RTScene();

    RTScene(RTCamera cam, std::vector<RTObject *> &primitives, int maxDepth);

    /**
     * @brief render a scene
     */
    void render();

    RTCamera getCam() const;
    void setCam(const RTCamera &value);

    std::vector<RTObject*> getPrimitives() const;
    void setPrimitives(const std::vector<RTObject*> &value);

    int getMaxDepth() const;
    void setMaxDepth(int value);

private:
    RTCamera cam;
    std::vector<RTObject*> primitives;
    int maxDepth;
};

#endif // RTSCENE_H
