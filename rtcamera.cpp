#include "rtcamera.h"


RTCamera::RTCamera()
{
}

RTCamera::RTCamera(RTPoint e,RTPoint look_at,RTVector up,double fovy){


    //campo de visão
    this->e=e;
    this->fovy=fovy;

    //base ortonormal
    RTVector viewDirection = (look_at*1.0);
    this->w=viewDirection;
    this->w.normalize();
    this->u=(up*w);
    this->u.normalize();
    this->v=(w*u);
    this->v.normalize();
}


RTRay RTCamera::generateRay(int i,int j){



    int width=RTFilm::getInstance()->getWidth();
    int height=RTFilm::getInstance()->getHeight();



    double aux = 2.0 * tan(fovy / 2.0) / width;

    double a = j + 0.5 - height / 2.0;
    double b = i + 0.5 - width / 2.0;

    RTVector dir=this->w+(((this->v*aux)*a)+((this->u*aux)*b));
    dir.normalize();
    return RTRay(e,dir);

   /* double fov = this->fovy*M_PI/180.0;
    double x_range = tan(fov / 2.0) * width / height;
    double b = tan(fov / 2.0) * (height/2.0 - i) / (height / 2.0);
    double a =  x_range * (j - width/2.0) / (width / 2.0);
    RTVector dirRay=((w*-1.0)+(u*a)+(v*b));
    dirRay.normalize();
    */


}


RTPoint RTCamera::getE() const
{
    return e;
}

void RTCamera::setE(const RTPoint &value)
{
    e = value;
}


double RTCamera::getFovy() const
{
    return fovy;
}

void RTCamera::setFovy(double value)
{
    fovy = value;
}


RTVector RTCamera::getW() const
{
    return w;
}

void RTCamera::setW(const RTVector &value)
{
    w = value;
}

RTVector RTCamera::getU() const
{
    return u;
}

void RTCamera::setU(const RTVector &value)
{
    u = value;
}

RTVector RTCamera::getV() const
{
    return v;
}

void RTCamera::setV(const RTVector &value)
{
    v = value;
}
