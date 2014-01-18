#ifndef RTPOINT_H
#define RTPOINT_H

#include "rtvector.h"

class RTPoint
{

  private:
      double x;
      double y;
      double z;

  public:

    RTPoint();
    RTPoint(double x,double y,double z);
    RTPoint(const RTPoint &point);

    RTVector operator+ (RTVector v);
    RTPoint operator- (RTVector v);
    RTVector operator -(RTPoint p2);

    double getX() const;
    double getY() const;
    double getZ() const;
};

#endif // RTPOINT_H
