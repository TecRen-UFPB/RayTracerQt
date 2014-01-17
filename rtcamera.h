#ifndef RTCAMERA_H
#define RTCAMERA_H


#include<cmath>
#include "rtpoint.h"
#include "rtray.h"
#include "rtfilm.h"

class RTCamera
{

    /**
     * @brief camera position
     */
    RTPoint e;

    /**
     * @brief campo de visão
     */
    double fovx;
    double fovy;

    /**
     * @brief focal_length
     */
    double focal_length;


    /**
     * @brief ortonormal basis
     */
    RTVector w;
    RTVector u;
    RTVector v;



public:
    RTCamera();

    /**
     * @brief RTCamera
     * @param e
     * @param look_at
     * @param up
     * @param fovx
     * @param fovy
     * @param focal_length
     */
    RTCamera(RTPoint e,RTPoint look_at,RTVector up, double fovx,double fovy,double focal_length);

    /**
     * @brief genRay
     * @param i
     * @param j
     * @return
     */
    RTRay generateRay(int i,int j);


    RTPoint getE() const;
    void setE(const RTPoint &value);
    double getFovx() const;
    void setFovx(double value);
    double getFovy() const;
    void setFovy(double value);
    double getFocal_length() const;
    void setFocal_length(double value);
    RTVector getW() const;
    void setW(const RTVector &value);
    RTVector getU() const;
    void setU(const RTVector &value);
    RTVector getV() const;
    void setV(const RTVector &value);
};



#endif // RTCAMERA_H
