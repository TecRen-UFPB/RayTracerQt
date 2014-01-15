#include "rtsampler.h"

#include "rtfilm.h"

RTSampler::RTSampler()
{
    this->i=0;
    this->j=0;
}

 bool RTSampler::getSample(RTSample &sample){

     if( i >= RTFilm::getInstance()->getWidth() )
         return false;
     j = ( j < RTFilm::getInstance()->getHeight() ) ? ( j++ ) : 0;
     sample.setX(i);
     sample.setY(j);
     if(j==0){
         i++;
     }
     return true;
 }
