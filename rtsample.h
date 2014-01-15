#ifndef RTSAMPLE_H
#define RTSAMPLE_H

class RTSample
{

private:
    int x;
    int y;

public:
    RTSample();
    RTSample(int x,int y);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
};

#endif // RTSAMPLE_H
