#include "rtpoint.h"

RTPoint::RTPoint()
{
}

RTPoint::RTPoint(double x,double y,double z){
    this->x=x;
    this->y=y;
    this->z=z;
}

RTPoint RTPoint::operator+ (RTVector v){

    double x= this->x+v.getX();
    double y= this->y+v.getY();
    double z= this->z+v.getZ();
    RTPoint p(x,y,z);
    return p;

}

RTPoint RTPoint::operator- (RTVector v){

    double x= this->x-v.getX();
    double y= this->y-v.getY();
    double z= this->z-v.getZ();
    RTPoint p(x,y,z);
    return p;

}


RTVector RTPoint::operator- (RTPoint p2){

    double x= this->x-p2.getX();
    double y= this->y-p2.getY();
    double z= this->z-p2.getZ();
    RTVector v(x,y,z);
    return v;
}

double RTPoint::getX(){
    return this->x;
}

double RTPoint::getY(){
    return this->y;
}

double RTPoint::getZ(){
    return this->z;
}
