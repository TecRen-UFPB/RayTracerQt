#include "rtscene.h"
#include "rtfilm.h"

RTScene::RTScene()
{
}

RTScene::RTScene(RTCamera cam, std::vector<RTObject> &primitives, int maxDepth)
{
    this->cam=cam;
    this->primitives=primitives;
    this->maxDepth=maxDepth;

}





void RTScene::render(){

    int w=RTFilm::getInstance()->getWidth();
    int h=RTFilm::getInstance()->getHeight();


    #pragma omp parallel for
    for(int i=0;i<w;i++){
        #pragma omp parallel for
        for(int j=0;j<h;j++){

            RTRay ray=this->cam.generateRay(i,j);
            // raytracer.trace(ray, &color);
            // RTFilm::getInstance()->commit(sample, color);
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
std::vector<RTObject> RTScene::getPrimitives() const
{
    return primitives;
}

void RTScene::setPrimitives(const std::vector<RTObject> &value)
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



