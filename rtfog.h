#ifndef RTFOG_H
#define RTFOG_H

#include"rtcolor.h"

class RTFog
{
public:
    RTFog();
    RTFog(double z_start,double z_end,RTColor fogColor);



    double getZ_start() const;
    void setZ_start(double value);

    double getZ_end() const;
    void setZ_end(double value);

    RTColor getFogColor() const;
    void setFogColor(const RTColor &value);

private:
    double z_start;
    double z_end;
    RTColor fogColor;
};

#endif // RTFOG_H
