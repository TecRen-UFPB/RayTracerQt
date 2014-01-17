#ifndef RTSCENE_H
#define RTSCENE_H

#define M_PI 3.14159265358979323846;

#include "rtcamera.h"


class RTScene
{
public:
    RTScene();

    /**
     * @brief render a scene
     */
    void render();
};

#endif // RTSCENE_H
