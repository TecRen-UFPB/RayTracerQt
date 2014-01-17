#include "rtcamera.h"


RTCamera::RTCamera()
{
}

RTCamera::RTCamera(RTPoint e,RTPoint look_at,RTVector up, double fovx,double fovy, double focal_length){

    RTVector viewDirection;
    viewDirection = look_at-e;
    viewDirection=viewDirection*-1;

    //campo de visão
    this->fovx=fovx;
    this->fovy=fovy;


    this->focal_length=focal_length;


    //base ortonormal
    this->w=viewDirection;
    this->w.normalize();
    this->u=(up*w);
    this->u.normalize();
    this->v=(w*u);
    this->v.normalize();
}


RTRay RTCamera::generateRay(int i,int j){

    int wid=RTFilm::getInstance()->getWidth();
    int hei=RTFilm::getInstance()->getHeight();


    double alfa,betha; //pixel view plane coordinates

    alfa = ((2*i-wid)/wid)*tan(this->fovx);
    betha = ((2*j-hei)/hei)*tan(this->fovy);

    RTVector _w;
    w=(this->w*(-1.0));
    RTVector _u;
    _u= (this->u*alfa);
    RTVector _v;
    _v= (this->v*betha);

    RTVector direction;
    direction=((_w+_u)+_v);

    RTRay ray(this->e,direction);

    return ray;

}


RTPoint RTCamera::getE() const
{
    return e;
}

void RTCamera::setE(const RTPoint &value)
{
    e = value;
}

double RTCamera::getFovx() const
{
    return fovx;
}

void RTCamera::setFovx(double value)
{
    fovx = value;
}

double RTCamera::getFovy() const
{
    return fovy;
}

void RTCamera::setFovy(double value)
{
    fovy = value;
}

double RTCamera::getFocal_length() const
{
    return focal_length;
}

void RTCamera::setFocal_length(double value)
{
    focal_length = value;
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
