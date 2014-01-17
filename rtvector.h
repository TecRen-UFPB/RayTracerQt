#ifndef RTVECTOR_H
#define RTVECTOR_H

/**
 * @brief The RTVector class model for vector
 */
class RTVector
{
public:



    /**
     * @brief RTVector Constructor for RTVector
     * @param x x-coord
     * @param y y-coord
     * @param z z-coord
     */
    RTVector(double x, double y, double z);

    /**
     * @brief RTVector Does a copy the vector v
     * @param v The vector to be copied
     */
    RTVector(const RTVector &v);

    /**
     * @brief RTVector Default constructor
     */
    RTVector();


    /**
     * @brief normalize Normalizes the vector
     */
    void normalize();

    RTVector operator+(RTVector &v);
    RTVector operator-(RTVector &v);
    RTVector operator*(RTVector &v);

    RTVector operator*(double v);
    RTVector operator/(double v);

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    double getZ() const;
    void setZ(double value);

private:
    double x, y, z;
};

#endif // RTVECTOR_H
