#include "rtraytracer.h"
#include "rtplane.h"
#include "rtsphere.h"
#include "rtchecktexture.h"
#include <vector>
#include <QDebug>
#include <iostream>       // std::cout
#include <typeinfo>

#define INF                                         1e20
#define AIR_REFRA                                   1.000293

RTRayTracer::RTRayTracer()
{
}

RTColor RTRayTracer::traceRay(RTRay &ray, int depth, RTLight light)
{

    RTColor color(135,206,250);

    if(depth>scene.getMaxDepth()){

        RTColor zero(0,0,0);
        return zero; //BLACK

    }


    std::vector<RTObject*> objects = this->scene.getPrimitives();

    RTObject *closestObject=NULL;
    RTVector hitPoint,closestPoint;
    double t,nearest=INF;

    //percorre objetos da cena
    for(unsigned int io=0;io<objects.size();io++){
        //testa a inte  rseção
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

    RTColor reflectColor,refracColor,objColor;
    int surfaceType=closestObject->getBrdf()->getSurfaceType();

    objColor= shading(closestObject, closestPoint, light);

    double reflectivePercentage = closestObject->getBrdf()->getKr();
    double refractivePercentage = 0;
    bool isInside=false;
    double refraIndex=closestObject->getBrdf()->getRefracIndex();

    if(surfaceType==REFLECTIVE||surfaceType==REFRACTIVE){



        RTVector eyedir = -((ray.getPos()*1)-closestPoint);  //d
        eyedir.normalize();
        RTVector normal = closestObject->normalOfHitPoint(closestPoint);//N





        if(surfaceType==REFRACTIVE){ //aplica fresnel


            if(closestObject->getObjTag()==SPHERE){ //verifica se o raio de refração segue para dentro da esfera
                RTSphere *sp= dynamic_cast<RTSphere*>(closestObject);
                double centerDist =sqrt(pow(ray.getPos().getX() - sp->getCenter().getX(), 2)
                                + pow(ray.getPos().getY() - sp->getCenter().getY(), 2)
                                + pow(ray.getPos().getZ() - sp->getCenter().getZ(), 2));
                isInside=(centerDist<sp->getRadius());
            }


            reflectivePercentage=FresnelTerm(eyedir,normal,refraIndex,isInside); //R
            refractivePercentage=1-reflectivePercentage; //(1-R)
        }

        if(reflectivePercentage>0){  //calcula reflexão

            RTRay reflectionRay=genReflectionRay(eyedir,normal,closestPoint);
            reflectColor=(traceRay(reflectionRay,depth+1,light));
        }

        if(refractivePercentage>0){

            double refraIndex=closestObject->getBrdf()->getRefracIndex();
            RTRay refracRay=genRefractRay(eyedir,normal,closestPoint,refraIndex,isInside);
            refracColor=(traceRay(refracRay,depth+1,light));
        }

    }


    if(surfaceType==REFRACTIVE&&!isInside)
        color=reflectColor*reflectivePercentage+refracColor*(refractivePercentage);
    else{
        int kloc=(surfaceType==REFRACTIVE)?0:1;
        color=reflectColor*reflectivePercentage+refracColor*refraIndex+objColor*kloc;
        color=color/(reflectivePercentage+refractivePercentage+kloc);
    }

    return color;

}


RTRay RTRayTracer::genRefractRay(RTVector d, RTVector normal, RTVector closestPoint, double refractionIndex,bool isInside)
{

    double n,nt,ni;

    if(isInside){
        ni=refractionIndex;
        nt=AIR_REFRA;
        normal=-normal;

    }else{
        ni=AIR_REFRA;
        nt=refractionIndex;
    }



       n = ni / nt;
       double cosI = -normal.dot(d);
       double sinT2 = n * n * (1.0 - cosI * cosI);

       if (sinT2 > 1.0) {
          exit(EXIT_FAILURE);
       }

       double cosT = sqrt(1.0 - sinT2);
       RTVector refracVector= d * n + normal * (n * cosI - cosT);



       double bias = 1e-4;
       RTVector ori = (closestPoint-normal)*bias;

   // RTVector ori=closestPoint;
      RTPoint vertice(ori.getX(),ori.getY(),ori.getZ());

      RTRay refracRay(vertice,refracVector);
        return refracRay;
}

double RTRayTracer::FresnelTerm(RTVector d, RTVector normal, double indexRefrac,bool isInside)
{
       double n,nt,ni;

       if(isInside){
           ni=indexRefrac;
           nt=AIR_REFRA;
           normal=-normal;

       }else{
           ni=AIR_REFRA;
           nt=indexRefrac;
       }

       n= ni/nt;

       double cosI = -normal.dot(d);
       double sinT2 = n * n * (1.0 - cosI * cosI);

       if (sinT2 > 1.0) {
          // Total Internal Reflection.
          return 1.0;
       }

       double cosT = sqrt(1.0 - sinT2);
       double r0rth = (ni * cosI - nt * cosT) / (ni * cosI + nt * cosT);
       double rPar = (nt * cosI - ni * cosT) / (nt * cosI + ni * cosT);
       return (r0rth * r0rth + rPar * rPar) / 2.0;

}



RTRay RTRayTracer::genReflectionRay(RTVector d, RTVector n,RTVector closestPoint)
{
    RTVector reflectionDir = (n*2*n.dot(d))-d;
    reflectionDir.normalize();
    reflectionDir=-reflectionDir;
    double bias = 1e-4;
    RTVector aux(closestPoint+n*bias);
    RTPoint vertice(aux.getX(),aux.getY(),aux.getZ());
    RTRay reflectedRay(vertice,reflectionDir);
    return reflectedRay;

}

RTScene RTRayTracer::getScene() const
{
    return scene;
}

void RTRayTracer::setScene(const RTScene &value)
{
    scene = value;
}

RTColor RTRayTracer::getFragmentColor(RTObject* obj,RTVector hit){

    RTColor color;
    RTBRDF *objBrdf=obj->getBrdf();
    int material = objBrdf->getMaterial();

    switch (material) {
    case SHINY:
         color=obj->getBrdf()->getColor(hit);
        break;
    case CHECK:{
        try {
            RTCheckTexture *check = dynamic_cast<RTCheckTexture*>(objBrdf);
            color= check->getColor(hit);

        }  catch (std::bad_cast& bc)
        {
           std::cerr << "bad_cast caught: " << bc.what() << '\n';
        }

        // color= check.getColor(hit);
        }

        break;
    }


    return color;
}


RTColor RTRayTracer::shading(RTObject *obj, RTVector &hit, RTLight light)
{


    RTColor color = getFragmentColor(obj,hit);



    RTPoint point(hit.getX(), hit.getY(), hit.getZ());


    double ambient,diffuse,specular;

    // ambient
    // Ia*Ka
    ambient = light.getIa() * obj->getBrdf()->getKa();


    //shadow test
    double distLigth = light.distToLight(point);
    RTRay shadowRay;
    light.generateLightRay(point,shadowRay);

    if(shadowTest(shadowRay,distLigth,obj)){

        color.setR( obj->getBrdf()->getColor(hit).getR() * ambient);
        color.setG( obj->getBrdf()->getColor(hit).getG() * ambient);
        color.setB( obj->getBrdf()->getColor(hit).getB() * ambient);
        return color;
    }

    // diffuse

    RTVector dir_light;
    light.getVectorToLight(point, dir_light);
    dir_light.normalize();
    RTVector normal = obj->normalOfHitPoint(hit);
    double dotNL= normal.dot(dir_light);
    dotNL = std::max(0.0, dotNL);

    // Ip*Kd
    diffuse= light.getIp() * obj->getBrdf()->getKd() * dotNL;


    // specular

    RTVector cam_dir = this->scene.getCam().getE() - point;
    cam_dir.normalize();
    RTVector halfway= dir_light + cam_dir;
    halfway.normalize();
    double dotHN = halfway.dot(normal);
    dotHN = std::max(0.0, dotHN);

    // Ip*Ks*pow(blinnTerm, coef)

    specular = light.getIp() * obj->getBrdf()->getKs() * std::pow(dotHN, obj->getBrdf()->getN());


    color.setR( obj->getBrdf()->getColor(hit).getR() * (ambient+diffuse)+light.getColor().getR()*specular );
    color.setG( obj->getBrdf()->getColor(hit).getG() * (ambient+diffuse)+light.getColor().getG()* specular);
    color.setB( obj->getBrdf()->getColor(hit).getB() * (ambient+diffuse)+light.getColor().getB()*specular );


    return color;
}

bool RTRayTracer::shadowTest(RTRay shadowRay,double distLight,RTObject* hitObject)
{

    std::vector<RTObject*> objects = this->scene.getPrimitives();
    double t;



    for(int io=0;io<objects.size();io++){

        RTObject *ob= objects[io];


        if(&(*ob)==&(*hitObject))
            continue;

        if(!objects[io]->intersect(shadowRay,t))
            continue;
        else
        {

            RTObject* copy = objects[io];
            if (dynamic_cast<RTPlane*>(copy) != NULL)
                continue;

            if(t< distLight&&t<INF)
                return true;
        }

    }

    return false;
}



