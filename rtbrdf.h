#ifndef RTBRDF_H
#define RTBRDF_H

#include "rtcolor.h"

class RTBRDF
{
public:
    /**
     * @brief RTBRDF Default constructor
     */
    RTBRDF();

    /**
     * @brief RTBRDF Default copy constructor
     * @param cpy
     */
    RTBRDF(const RTBRDF &cpy);

    /**
     * @brief RTBRDF Constructor
     * @param kd
     * @param ks
     * @param ka
     * @param kr
     */
    RTBRDF(RTColor &kd, RTColor &ks, RTColor &ka, RTColor &kr);

    RTColor getKd() const;
    void setKd(const RTColor &value);

    RTColor getKs() const;
    void setKs(const RTColor &value);

    RTColor getKa() const;
    void setKa(const RTColor &value);

    RTColor getKr() const;
    void setKr(const RTColor &value);

private:
    RTColor kd, ks, ka, kr;

};

#endif // RTBRDF_H
