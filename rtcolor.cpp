#include "rtcolor.h"

RTColor::RTColor(unsigned int r, unsigned int g, unsigned int b) :
    _r(r), _g(g), _b(b)
{

}

RTColor::RTColor(const RTColor &c)
{
    this->_r = c.getR();
    this->_g = c.getG();
    this->_b = c.getB();
}

RTColor::RTColor()
{
    this->_r = 0;
    this->_g = 0;
    this->_b = 0;
}

void RTColor::setR(unsigned int r)
{
    unsigned int rx=(r>255)?255:r;

    this->_r = rx;
}

void RTColor::setG(unsigned int g)
{
    unsigned int gx=(g>255)?255:g;
    this->_g = gx;
}

void RTColor::setB(unsigned int b)
{
    unsigned int bx=(b>255)?255:b;
    this->_b = bx;
}

unsigned int RTColor::getR() const
{
    return this->_r;
}

unsigned int RTColor::getG() const
{
    return this->_g;
}

unsigned int RTColor::getB() const
{
    return this->_b;
}

RTColor RTColor::operator+(RTColor &color)
{
    RTColor newColor( this->_r + color.getR(),
                      this->_g + color.getG(),
                      this->_b + color.getB());
    return newColor;
}

RTColor RTColor::operator-(RTColor &color)
{
    RTColor newColor( this->_r - color.getR(),
                      this->_g - color.getG(),
                      this->_b - color.getB());
    return newColor;
}

RTColor RTColor::operator*(double value)
{
    RTColor newColor( this->_r * value,
                      this->_g * value,
                      this->_b * value);
    return newColor;
}

RTColor RTColor::operator/(double value)
{
    RTColor newColor( this->_r / value,
                      this->_g / value,
                      this->_b / value);
    return newColor;
}
