#ifndef RTSAMPLER_H
#define RTSAMPLER_H

#include "rtsample.h"

class RTSampler
{

private:
    int i;
    int j;

public:
    RTSampler();

    /**
     * @brief  It will generate (x,y) of a screen sample and return true.
               Next time it gets called, it will generate another sample for the next pixel. It will return false when all the samples from all the pixels
               are generated.
     * @param sample sample of screen
     */
    bool getSample(RTSample &sample);
};

#endif // RTSAMPLER_H
