#include "rtscene.h"

#include "rtfilm.h"

RTScene::RTScene()
{
}



void RTScene::render(){

    int w=RTFilm::getInstance()->getWidth();
    int h=RTFilm::getInstance()->getHeight();



    #pragma omp parallel for
    for(int i=0;i<w;i++){
        #pragma omp parallel for
        for(int j=0;j<h;j++){

            // camera.generateRay(sample, &ray);
            // raytracer.trace(ray, &color);
            // RTFilm::getInstance()->commit(sample, color);
        }
    }




}
