#include "rtraytracer.h"
#include <vector>

#define INF                                         1e20

RTRayTracer::RTRayTracer()
{
}

RTColor RTRayTracer::traceRay(RTRay &ray, int depth)
{

    RTColor color(0,0,0);

    if(depth>scene.getMaxDepth()){

        return color; //BLACK
    }


    std::vector<RTObject> objects = this->scene.getPrimitives();

    RTObject *closestObject=NULL;
    RTVector hitPoint,closestPoint;
    double t,nearest=INF;



    //percorre objetos da cena
    for(int io=0;io<objects.size();io++){
        //testa a interseção
        if(!objects[io].intersect(ray,t))
            continue;
        else{ //hit
            hitPoint = ray.getPos()+(ray.getDir()*t);
            t= hitPoint.getNorma();
            if(t<nearest){
                t=nearest;
                closestObject=&objects[io];
                closestPoint=hitPoint;
            }
        }
    }

    if(nearest==INF){ //nao intersecionou
        return color;
    }

    //calcula a cor do pixel
    return color;

}
RTScene RTRayTracer::getScene() const
{
    return scene;
}

void RTRayTracer::setScene(const RTScene &value)
{
    scene = value;
}

