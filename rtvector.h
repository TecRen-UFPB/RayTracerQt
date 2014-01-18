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
     * @brief setX Sets a new value for x-coord
     * @param x New value
     */
    void setX(double x);

    /**
     * @brief getX Returns the value of x-coord
     * @return x-coord value
     */
    double getX() const;

    /**
     * @brief setY Sets a new value for y-coord
     * @param y New value
     */
    void setY(double y);

    /**
     * @brief getY Returns the value of y-coord
     * @return y-coord value
     */
    double getY() const;

    /**
     * @brief setZ Sets a new value for z-coord
     * @param z New value
     */
    void setZ(double z);

    /**
     * @brief getZ Returns the value of z-coord
     * @return z-coord value
     */
    double getZ() const;


    /**
     * @brief normalize Normalizes the vector
     */
    void normalize();

    RTVector operator+(RTVector v);

    RTVector operator-(RTVector v);
    RTVector operator*(RTVector v);

    RTVector operator*(double v);
    RTVector operator/(double v);

    double getNorma();


private:
    double x, y, z;
};

#endif // RTVECTOR_H
