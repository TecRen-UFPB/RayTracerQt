#include "rtscene.h"
#include "rtfilm.h"
#include "rtraytracer.h"
#include "rtlight.h"

RTScene::RTScene()
{
}

RTScene::RTScene(RTCamera cam, std::vector<RTObject*> &primitives, int maxDepth)
{
    this->cam=cam;
    this->primitives=primitives;
    this->maxDepth=maxDepth;

}





void RTScene::render(){

    int w=RTFilm::getInstance()->getWidth();
    int h=RTFilm::getInstance()->getHeight();

    RTRayTracer raytracer;
    raytracer.setScene(*this);

    // TODO parameterize the light source.
    double ia = 1.0, ip = 1.0;
    RTColor light_color(255,255,255);
    RTPoint light_pos(0,0,2);
    RTLight light(light_pos, ia, ip, light_color);

    //#pragma omp parallel for
    for(int i=0;i<w;i++){
      //#pragma omp parallel for
        for(int j=0;j<h;j++){

            RTRay ray=this->cam.generateRay(i,j);
            RTColor color = raytracer.traceRay(ray, maxDepth, light);
            RTFilm::getInstance()->commit(i, j, color);
        }
    }




}
RTCamera RTScene::getCam() const
{
    return cam;
}

void RTScene::setCam(const RTCamera &value)
{
    cam = value;
}
std::vector<RTObject *> RTScene::getPrimitives() const
{
    return primitives;
}

void RTScene::setPrimitives(const std::vector<RTObject *> &value)
{
    primitives = value;
}
int RTScene::getMaxDepth() const
{
    return maxDepth;
}

void RTScene::setMaxDepth(int value)
{
    maxDepth = value;
}



