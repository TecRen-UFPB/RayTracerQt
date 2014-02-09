#include "rtfog.h"

RTFog::RTFog()
{
}



RTFog::RTFog(double z_start, double z_end, RTColor fogColor)
{
    this->z_start=z_start;
    this->z_end=z_end;
    this->fogColor=fogColor;

}
double RTFog::getZ_start() const
{
    return z_start;
}

void RTFog::setZ_start(double value)
{
    z_start = value;
}
double RTFog::getZ_end() const
{
    return z_end;
}

void RTFog::setZ_end(double value)
{
    z_end = value;
}
RTColor RTFog::getFogColor() const
{
    return fogColor;
}

void RTFog::setFogColor(const RTColor &value)
{
    fogColor = value;
}











