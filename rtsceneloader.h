#ifndef RTSCENELOADER_H
#define RTSCENELOADER_H

#include <QObject>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>

#include <vector>

#include "rtobject.h"

class RTSceneLoader : public QObject
{
    Q_OBJECT
public:
    explicit RTSceneLoader(QString filename);

    void load(std::vector<RTObject*> &objects);

signals:

public slots:
    void addObject();

private:
    QString filename;

    QScriptEngine engine;

};

#endif // RTSCENELOADER_H
