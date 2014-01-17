#include "rtcolor.h"

RTColor::RTColor(unsigned int r, unsigned int g, unsigned int b) :
    _r(r), _g(g), _b(b)
{

}

RTColor::RTColor(RTColor &c)
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
    this->_r = r;
}

void RTColor::setG(unsigned int g)
{
    this->_g = g;
}

void RTColor::setB(unsigned int b)
{
    this->_b = b;
}

unsigned int RTColor::getR()
{
    return this->_r;
}

unsigned int RTColor::getG()
{
    return this->_g;
}

unsigned int RTColor::getB()
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
