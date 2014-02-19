#ifndef RTSCENE_H
#define RTSCENE_H

#define M_PI 3.14159265358979323846;

#include "rtcamera.h"
#include "rtobject.h"
#include "rtfog.h"
#include <vector>

class RTScene
{
public:
    RTScene();

    RTScene(RTCamera cam, std::vector<RTObject *> &primitives, int maxDepth);
    RTScene(RTCamera cam, std::vector<RTObject*> &primitives, int maxDepth, double z_start, double z_end, RTColor fogColor);

    /**
     * @brief render a scene
     */
    void render(int samples);

    RTCamera getCam() const;
    void setCam(const RTCamera &value);

    std::vector<RTObject*> getPrimitives() const;
    void setPrimitives(const std::vector<RTObject*> &value);

    int getMaxDepth() const;
    void setMaxDepth(int value);



    bool getHasFog() const;
    void setHasFog(bool value);

    RTFog getFog() const;
    void setFog(const RTFog &value);

private:
    RTCamera cam;
    std::vector<RTObject*> primitives;
    bool hasFog;
    RTFog fog;
    int maxDepth;
};

#endif // RTSCENE_H
