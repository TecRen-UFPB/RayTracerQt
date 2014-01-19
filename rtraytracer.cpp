#include "rtraytracer.h"
#include <vector>
#include <QDebug>

#define INF                                         1e20

RTRayTracer::RTRayTracer()
{
}

RTColor RTRayTracer::traceRay(RTRay &ray, int depth, RTLight light)
{

    RTColor color(0,0,0);

    if(depth>scene.getMaxDepth()){

        return color; //BLACK
    }


    std::vector<RTObject*> objects = this->scene.getPrimitives();

    RTObject *closestObject=NULL;
    RTVector hitPoint,closestPoint;
    double t,nearest=INF;

    //percorre objetos da cena
    for(unsigned int io=0;io<objects.size();io++){
        //testa a interseção
        if(!objects[io]->intersect(ray,t))
            continue;
        else{ //hit
            hitPoint = ray.getPos()+(ray.getDir()*t);
            t= hitPoint.getNorma();
            if(t<nearest){
                nearest = t;
                closestObject=objects[io];
                closestPoint=hitPoint;
            }
        }
    }

    if(nearest==INF){ //nao intersecionou
        return color;
    }

    //calcula a cor do pixel
    color = shading(closestObject, closestPoint, light);

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

RTColor RTRayTracer::shading(RTObject *obj, RTVector &hit, RTLight light)
{
    RTColor color = obj->getBrdf().getColor();

    RTPoint point(hit.getX(), hit.getY(), hit.getZ());


    double ambient,diffuse,specular;

    // ambient
    // Ia*Ka
    ambient = light.getIa() * obj->getBrdf().getKa();

    // diffuse
    RTVector normal = obj->normalOfHitPoint(hit);
    RTVector dir_light;
    light.getVectorToLight(point, dir_light);
    dir_light.normalize();

    double dotNL= normal.dot(dir_light);
    dotNL = std::max(0.0, dotNL);

    // Ip*Kd
    diffuse= light.getIp() * obj->getBrdf().getKd() * dotNL;



    // specular

    RTVector cam_dir = this->scene.getCam().getE() - point;
    cam_dir.normalize();
    RTVector halfway= dir_light + cam_dir;
    halfway.normalize();
    double dotHN = halfway.dot(normal);
    dotHN = std::max(0.0, dotHN);

    // Ip*Ks*pow(blinnTerm, coef)

    specular = light.getIp() * obj->getBrdf().getKs() * std::pow(dotHN, obj->getBrdf().getN());


    color.setR( obj->getBrdf().getColor().getR() * (ambient+diffuse)+light.getColor().getR()*specular );
    color.setG( obj->getBrdf().getColor().getG() * (ambient+diffuse)+light.getColor().getG()* specular);
    color.setB( obj->getBrdf().getColor().getB() * (ambient+diffuse)+light.getColor().getB()*specular );

    return color;
}

