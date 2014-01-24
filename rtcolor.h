#ifndef RTCOLOR_H
#define RTCOLOR_H

class RTColor
{
public:
    /**
     * @brief RTColor Color model. RGB is unsigned int
     * @param r Red value
     * @param g Green value
     * @param b Blue value
     */
    RTColor(unsigned int r, unsigned int g, unsigned int b);

    /**
     * @brief RTColor Does a copy of the color
     * @param c Object to be copied.
     */
    RTColor(const RTColor &c);

    /**
     * @brief RTColor Default constructor. Black color.
     */
    RTColor();

    /**
     * @brief setR Set the value for red component
     * @param r Amount of red
     */
    void setR(unsigned int r);

    /**
     * @brief setG Set the value for green component
     * @param g Amount of green
     */
    void setG(unsigned int g);

    /**
     * @brief setB Set the value of blue component
     * @param b Amount of blue
     */
    void setB(unsigned int b);

    /**
     * @brief getR Get the amount of red
     * @return Amount of red
     */
    unsigned int getR() const;

    /**
     * @brief getG Get the amount of green
     * @return Amount of green
     */
    unsigned int getG() const;

    /**
     * @brief getB Get the amount of blue
     * @return Amount of blue
     */
    unsigned int getB() const;

    /**
     * @brief operator + Performs the sum of two colors
     * @param color
     */
    RTColor operator +(RTColor color);

    /**
     * @brief operator - Performs the subtraction of two colors
     * @param color
     */
    RTColor operator -(RTColor color);

    /**
     * @brief operator * Performs the multiplication by a scalar
     * @param value
     */
    RTColor operator *(double value);

    RTColor operator *(RTColor c);

    /**
     * @brief operator / Performs the division by a scalar
     * @param value
     */
    RTColor operator /(double value);


private:
    unsigned int _r, _g, _b;

};

#endif // RTCOLOR_H
