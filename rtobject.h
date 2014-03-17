#ifndef RTOBJECT_H
#define RTOBJECT_H

#include "rtray.h"
#include "rtbrdf.h"
#include "rtvector.h"

#include <vector>

/**
 * @brief The RTObject class Generic class for objects
 */
class RTObject
{
public:
    /**
     * @brief RTObject Default constructor
     */
    RTObject() {}

    RTObject(RTBRDF* brdfAux){



        double kd = brdfAux->getKa();
        double ks = brdfAux->getKs();
        double ka = brdfAux->getKa();
        double kr=  brdfAux->getKr();
        double refracIndex=brdfAux->getRefracIndex();
        int n = brdfAux->getN();
        RTColor color = brdfAux->getColor();
        int surfaceType=brdfAux->getSurfaceType();
        int material=brdfAux->getMaterial();

        RTBRDF *cpyBrdf= new RTBRDF(ka,kd,ks,kr,refracIndex,n,surfaceType,material,color);
        this->brdf=cpyBrdf;


    }

     RTObject(const RTObject &cpy) {


        this->objTag=cpy.getObjTag();

        RTBRDF *brdfAux=cpy.getBrdf();
        double kd = brdfAux->getKa();
        double ks = brdfAux->getKs();
        double ka = brdfAux->getKa();
        double kr=  brdfAux->getKr();
        double refracIndex=brdfAux->getRefracIndex();
        int n = brdfAux->getN();
        RTVector v;
        RTColor color = brdfAux->getColor();
        int surfaceType=brdfAux->getSurfaceType();
        int material=brdfAux->getMaterial();

        RTBRDF *cpyBrdf= new RTBRDF(ka,kd,ks,kr,refracIndex,n,surfaceType,material,color);
        this->brdf=cpyBrdf;

    }

    RTObject &  operator=(const RTObject &other){

        this->objTag=other.getObjTag();
        RTBRDF *brdfAux=other.getBrdf();
        double kd = brdfAux->getKa();
        double ks = brdfAux->getKs();
        double ka = brdfAux->getKa();
        double kr=  brdfAux->getKr();
        double refracIndex=brdfAux->getRefracIndex();
        int n = brdfAux->getN();
        RTVector v;
        RTColor color = brdfAux->getColor();
        int surfaceType=brdfAux->getSurfaceType();
        int material=brdfAux->getMaterial();

        delete brdf;

        RTBRDF *cpyBrdf= new RTBRDF(ka,kd,ks,kr,refracIndex,n,surfaceType,material,color);
        this->brdf=cpyBrdf;

    }






    virtual ~RTObject(){

//        delete brdf;
    }

    /**
     * @brief intersect Check if the ray intersect the object and return the hit point.
     * @param ray The ray to check.
     * @param hitPoint The point where the ray touched.
     * @return True if an intersect was found, false otherwise.
     */
    virtual bool intersect( RTRay &ray,double &t){

        return false;
    }

    virtual RTVector normalOfHitPoint(RTVector hit){

        return RTVector(0,0,0);
    }




    int getObjTag() const
    {
    return objTag;
    }

    void setObjTag(int value)
    {
    objTag = value;
    }



    RTBRDF *getBrdf() const
    {
    return brdf;
    }

    void setBrdf(RTBRDF *value)
    {
    brdf = value;
    }


private:
    RTBRDF *brdf;

protected:
    int objTag;



};

enum {PLANE=1,SPHERE,TRIANGLES,TORUS};


#endif // RTOBJECT_H









