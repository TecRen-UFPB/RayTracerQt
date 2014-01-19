#include "rtfilm.h"

#include <QRgb>
#include <QColor>
#include <QDebug>

// static
RTFilm *RTFilm::buffer = 0;

bool RTFilm::init(int width, int height)
{
    RTFilm::buffer = new RTFilm(width, height);
    return true;
}

void RTFilm::close()
{
    delete RTFilm::buffer;
    RTFilm::buffer = 0;
}

RTFilm * RTFilm::getInstance()
{
    return RTFilm::buffer;
}

// instance

RTFilm::RTFilm(int width, int height) :
    QObject(0)
{
    image = new QImage(width, height, QImage::Format_ARGB32);
    image->fill(QColor(0,0,0));
}

RTFilm::~RTFilm()
{
    delete image;
}

void RTFilm::commit(int x,int y, RTColor &color)
{
    image->setPixel(x,y, qRgb(color.getR(), color.getG(), color.getB()) );
}

void RTFilm::writeImage(QString &filename)
{
    image->save(filename);
}

QImage *RTFilm::getQImage()
{
    return this->image;
}

int RTFilm::getHeight()
{
    return image->height();
}

int RTFilm::getWidth()
{
    return image->width();
}
