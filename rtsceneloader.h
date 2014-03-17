#ifndef RTSCENELOADER_H
#define RTSCENELOADER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <vector>

#include "rtobject.h"
#include "rtpoint.h"
#include "rtplane.h"
#include "rttriangle.h"
#include "rtsphere.h"
#include "rtchecktexture.h"
#include "rtcrisscrosstexture.h"
#include "rtmarbletexture.h"
#include "rtturbulencetexture.h"
#include "rtwoodtexture.h"

#include "rtcamera.h"
#include "rtscene.h"

#include "objLoader.h"

class RTSceneLoader : public QObject
{
    Q_OBJECT
public:
    explicit RTSceneLoader(QString filename);

    void load(std::vector<RTObject*> &objects);

    RTCamera getCamera();

    RTScene getScene();

    int getSamples();

signals:

public slots:

private:
    QString filename;

    RTCamera camera;

    RTScene scene;

    int samples;

    void doTriangle(QJsonObject obj, std::vector<RTObject*> &objects);
    void doSphere(QJsonObject obj, std::vector<RTObject*> &objects);
    void doPlane(QJsonObject obj, std::vector<RTObject*> &objects);
    void doDotObj(QJsonObject obj, std::vector<RTObject*> &objects);
    RTBRDF *doBRDF(QJsonObject brdfObj);

    RTBRDF * doBRDFCheck(QJsonObject brdfObj);
    RTBRDF * doBRDFCrissCross(QJsonObject brdfObj);
    RTBRDF * doBRDFMarble(QJsonObject brdfObj);
    RTBRDF * doBRDFTurbulence(QJsonObject brdfObj);
    RTBRDF * doBRDFWood(QJsonObject brdfObj);

    RTPoint arrayToPoint(QJsonArray arr);
    RTVector arrayToVector(QJsonArray arr);
    RTColor objToColor(QJsonObject obj);

};

#endif // RTSCENELOADER_H
