#include "rtsceneloader.h"

#include <QFile>
#include <QDebug>

RTSceneLoader::RTSceneLoader(QString filename) :
    QObject(0)
{
    this->filename = filename;
}

void RTSceneLoader::load(std::vector<RTObject *> &objects)
{
    QFile file(this->filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text );
    QString sceneTxt(file.readAll());
    file.close();

    QScriptValue loaderObj = engine.newQObject(this);
    engine.globalObject().setProperty("loader", loaderObj);

    QScriptValue context = engine.evaluate(sceneTxt);

    QScriptValue main = engine.globalObject().property("main");
    main.call(context);
}

void RTSceneLoader::addObject()
{
    qDebug()<<"ok";
}
