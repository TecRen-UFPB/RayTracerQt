#include "rtfilm.h"

#include <QRgb>
#include <QColor>

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

void RTFilm::commit(RTSample &sample, RTColor &color)
{
    image->setPixel(sample.getX(), sample.getY(), qRgb(color.getR(), color.getG(), color.getB()) );
}

void RTFilm::writeImage(QString &filename)
{
    image->save(filename);
}

QImage *RTFilm::getQImage()
{
    return this->image;
}
