#ifndef RCBUFFER_H
#define RCBUFFER_H

#include <QObject>
#include <QImage>

#include "rtsample.h"
#include "rtcolor.h"

/**
 * @brief The RTBuffer class. Singleton
 */
class RTFilm : public QObject
{
    Q_OBJECT

/*
 * Static scope
 *
 */
public:
    /**
     * @brief init Creates a unic buffer.
     * @param width The width of the buffer
     * @param height The height of the buffer
     */
    static bool init(int width, int height);

    /**
     * @brief close Destroy the buffer instance
     */
    static void close();

    /**
     * @brief getInstance Returns a reference to the instance of the RTBuffer
     * @return Pointer to the RTBuffer
     */
    static RTFilm *getInstance();

private:
    /**
     * @brief buffer Unic instance of the buffer
     */
    static RTFilm *buffer;

/*
 * Instance scope
 *
 */

public:
    virtual ~RTFilm();

    /**
     * @brief commit Write the color to the image buffer at position specified by sample
     * @param sample Position
     * @param color Color to write
     */
    void commit(RTSample &sample, RTColor &color);

    /**
     * @brief save Save the current buffer to an archive
     * @param filename The file name to be saved
     */
    void writeImage(QString &filename);

    /**
     * @brief getQImage returns the Qt native object to image processing
     * @return reference to a QImage
     */
    QImage *getQImage();

signals:
    /**
     * @brief onBufferChange Emitted when the buffer is changed.
     */
    void onBufferChange();

public slots:

private:
    explicit RTFilm(int width, int height);

    QImage *image;

};

#endif // RCBUFFER_H
