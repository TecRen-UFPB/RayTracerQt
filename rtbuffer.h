#ifndef RCBUFFER_H
#define RCBUFFER_H

#include <QObject>
#include <QImage>

/**
 * @brief The RTBuffer class. Singleton
 */
class RTBuffer : public QObject
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
    static RTBuffer *getInstance();

private:
    /**
     * @brief buffer Unic instance of the buffer
     */
    static RTBuffer *buffer;

/*
 * Instance scope
 *
 */

public:
    virtual ~RTBuffer();

    /**
     * @brief setPixel change the color in the position ixj of the image
     * @param i line
     * @param j col
     * @param r red amount
     * @param g green amount
     * @param b blue amount
     * @param a alpha amount
     */
    void setPixel(unsigned int i, unsigned int j, unsigned int r, unsigned int g, unsigned int b, unsigned int a=254);

    /**
     * @brief addPixel add the 'r', 'g', 'b' to the current color at ixj
     * @param i line
     * @param j col
     * @param r red amount
     * @param g green amount
     * @param b blue amount
     * @param a alpha amount
     */
    void addPixel(unsigned int i, unsigned int j, unsigned int r, unsigned int g, unsigned int b, unsigned int a=254);

    /**
     * @brief save Save the current buffer to an archive
     * @param filename The file name to be saved
     */
    void save(QString &filename);

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
    explicit RTBuffer(int width, int height);

    QImage *image;

};

#endif // RCBUFFER_H
