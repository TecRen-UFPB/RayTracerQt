#include "rtcolor.h"

RTColor::RTColor(unsigned int r, unsigned int g, unsigned int b)
{
    unsigned int rr=(r>255)?255:r;
    unsigned int rg=(g>255)?255:g;
    unsigned int rb=(b>255)?255:b;

    this->_r=rr;
    this->_g=rg;
    this->_b=rb;

}



RTColor::RTColor(const RTColor &c)
{
    unsigned int r = (c.getR()>255?255:c.getR());
    unsigned int g = (c.getG()>255?255:c.getG());
    unsigned int b = (c.getB()>255?255:c.getB());

    this->_r=r;
    this->_g=g;
    this->_b=b;
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

RTColor RTColor::operator+(RTColor color)
{
    RTColor newColor( this->_r + color.getR(),
                      this->_g + color.getG(),
                      this->_b + color.getB());
    return newColor;
}

RTColor RTColor::operator-(RTColor color)
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

RTColor RTColor::operator *(RTColor c)
{
    RTColor newColor( this->_r * c.getR(),
                      this->_g * c.getG(),
                      this->_b * c.getB());
    return newColor;
}

RTColor RTColor::operator/(double value)
{
    RTColor newColor( this->_r / value,
                      this->_g / value,
                      this->_b / value);
    return newColor;
}


