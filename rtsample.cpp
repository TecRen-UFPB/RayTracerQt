#include "rtsample.h"

RTSample::RTSample()
{
}

RTSample::RTSample(int x,int y)
{
    this->x=x;
    this->y=y;
}

int RTSample::getX(){
    return this->x;
}

int RTSample::getY(){
    return this->y;
}

void RTSample::setX(int x){
    this->x=x;
}

void RTSample::setY(int y){
    this->y=y;
}
