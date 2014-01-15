#ifndef RTSCENE_H
#define RTSCENE_H

#include "rtsampler.h"

class RTScene
{
public:
    RTScene();

    /**
     * @brief main rendering loop.
     */
    void render();
};

#endif // RTSCENE_H
