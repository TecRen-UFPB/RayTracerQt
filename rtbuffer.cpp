#include "rtbuffer.h"

#include <QRgb>
#include <QColor>

// static
RTBuffer *RTBuffer::buffer = 0;

bool RTBuffer::init(int width, int height)
{
    RTBuffer::buffer = new RTBuffer(width, height);
    return true;
}

void RTBuffer::close()
{
    delete RTBuffer::buffer;
    RTBuffer::buffer = 0;
}

RTBuffer * RTBuffer::getInstance()
{
    return RTBuffer::buffer;
}

// instance

RTBuffer::RTBuffer(int width, int height) :
    QObject(0)
{
    image = new QImage(width, height, QImage::Format_ARGB32);
    image->fill(QColor(0,0,0));
}

RTBuffer::~RTBuffer()
{
    delete image;
}

void RTBuffer::setPixel(unsigned int i, unsigned int j, unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    image->setPixel(i, j, qRgba(r, g, b, a) );

    emit onBufferChange();
}

void RTBuffer::addPixel(unsigned int i, unsigned int j, unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    unsigned int cr, cg, cb;
    QRgb rgb = image->pixel(i, j);
    cr = qRed(rgb) + r;
    cg = qGreen(rgb) + g;
    cb = qBlue(rgb) + b;

    image->setPixel(i, j, qRgba(cr, cg, cb, a));

    emit onBufferChange();

}

void RTBuffer::save(QString &filename)
{
    image->save(filename);
}

QImage *RTBuffer::getQImage()
{
    return this->image;
}
