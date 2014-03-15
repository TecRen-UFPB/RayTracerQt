#ifndef RTSCENELOADER_H
#define RTSCENELOADER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <vector>

#include "rtobject.h"
#include "rttriangle.h"

class RTSceneLoader : public QObject
{
    Q_OBJECT
public:
    explicit RTSceneLoader(QString filename);

    void load(std::vector<RTObject*> &objects);

signals:

public slots:

private:
    QString filename;

    void doTriangle(QJsonObject obj, std::vector<RTObject*> &objects);
    RTBRDF *doBRDF(QJsonObject brdfObj);

};

#endif // RTSCENELOADER_H
