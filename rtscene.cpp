#include "rtscene.h"

RTScene::RTScene()
{
}



void RTScene::render(){

    RTSampler sampler;
    RTSample sample;
    while (!sampler.getSample(sample)){

       // camera.generateRay(sample, &ray);
       // raytracer.trace(ray, &color);
       // film.commit(sample, color);
    }
}
