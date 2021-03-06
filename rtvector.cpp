#include "rtvector.h"

#include <cmath>


RTVector::RTVector(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}


RTVector::RTVector(const RTVector &v)
{
    this->x = v.getX();
    this->y = v.getY();
    this->z = v.getZ();
}

RTVector::RTVector()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

void RTVector::setX(double x)
{
    this->x = x;
}

double RTVector::getX() const
{
    return this->x;
}

void RTVector::setY(double y)
{
    this->y = y;
}

double RTVector::getY() const
{
    return this->y;
}

void RTVector::setZ(double z)
{
    this->z = z;
}

double RTVector::getZ() const
{
    return this->z;
}

void RTVector::normalize()
{

    double len = sqrt( pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0) );
    if(len<0.000001)
        return;

    this->x /= len;
    this->y /= len;
    this->z /= len;
}

RTVector RTVector::operator +(RTVector v)
{
    double sx, sy, sz;
    sx = this->x + v.getX();
    sy = this->y + v.getY();
    sz = this->z + v.getZ();

    RTVector vr(sx, sy, sz);
    return vr;
}

RTVector RTVector::operator -()
{
    RTVector vr(-this->x,
                -this->y,
                -this->z);
    return vr;
}

RTVector RTVector::operator -(RTVector v)
{
    double sx, sy, sz;
    sx = this->x-v.getX();
    sy = this->y-v.getY();
    sz = this->z-v.getZ();

    RTVector vr(sx, sy, sz);
    return vr;
}

//Cross product

RTVector RTVector::operator*(RTVector v)
{
    double x = this->y*v.getZ()-this->z*v.getY();
    double y = this->z*v.getX()-this->x*v.getZ();
    double z = this->x*v.getY()-this->y*v.getX();

    RTVector cross(x,y,z);

    return cross;

}

RTVector RTVector::operator*(double v)
{
    double cx = this->x * v;
    double cy = this->y * v;
    double cz = this->z * v;

    RTVector vr(cx, cy, cz);
    return vr;
}

RTVector RTVector::operator/(double v)
{
    double cx = this->x / v;
    double cy = this->y / v;
    double cz = this->z / v;

    RTVector vr(cx, cy, cz);
    return vr;
}

double RTVector::getNorma(){

    double norm = sqrt( pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0) );
    return norm;
}

double RTVector::dot(RTVector vec2)
{
    double sum = this->x * vec2.getX() +
            this->y * vec2.getY() +
            this->z * vec2.getZ();
    return sum;
}
