#include "rtsampler.h"

RTSampler::RTSampler()
{
    this->i=0;
    this->j=0;
}

 bool RTSampler::getSample(RTSample &sample){

     if(i>=512)
         return false;
     j = (j<512)?(j++):0;
     sample.setX(i);
     sample.setY(j);
     if(j==0){
         i++;
     }
     return true;
 }
