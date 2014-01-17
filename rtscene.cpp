#include "rtscene.h"

#include "rtfilm.h"

RTScene::RTScene()
{
}



void RTScene::render(){

    int w=RTFilm::getInstance()->getWidth();
    int h=RTFilm::getInstance()->getHeight();

    RTPoint camera_position(300.0,300.0,300.0);
    RTPoint look_at(0.0,0.0,-1.0);
    RTVector up(0.0,1.0,0.0);
    double aspect_ration=w/h,focal_length=1.0;
    double fovx=M_PI/4,fovy=aspect_ration*fovx;

    RTCamera camera(camera_position,look_at,up,fovx,fovy,focal_length);

    #pragma omp parallel for
    for(int i=0;i<w;i++){
        #pragma omp parallel for
        for(int j=0;j<h;j++){

            RTRay ray=camera.generateRay(i,j);
            // raytracer.trace(ray, &color);
            // RTFilm::getInstance()->commit(sample, color);
        }
    }




}
