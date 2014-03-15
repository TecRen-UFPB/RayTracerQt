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

    QJsonDocument doc = QJsonDocument::fromJson(sceneTxt.toUtf8());
    QJsonObject obj = doc.object();

    if(doc.isEmpty() || doc.isNull())
    {
        qDebug()<<"Scene invalid!";
        return;
    }

    QJsonArray arr = obj.value("objects").toArray();

    QString type;
    for(int i=0;i<arr.size();i++)
    {
        type = arr.at(i).toObject().value("type").toString();
        qDebug()<<type;
        if(type=="triangle")
            doTriangle(arr.at(i).toObject(), objects);
    }

}

void RTSceneLoader::doTriangle(QJsonObject obj, std::vector<RTObject*> &objects)
{
    RTTriangle *triangle = new RTTriangle();
    RTPoint p1, p2, p3;

    QJsonArray vertices = obj.value("vertices").toArray();
    QJsonArray vp1 = vertices.at(0).toArray();
    QJsonArray vp2 = vertices.at(1).toArray();
    QJsonArray vp3 = vertices.at(2).toArray();

    p1 = RTPoint(vp1.at(0).toDouble(),
                 vp1.at(1).toDouble(),
                 vp1.at(2).toDouble());

    p2 = RTPoint(vp2.at(0).toDouble(),
                 vp2.at(1).toDouble(),
                 vp2.at(2).toDouble());

    p3 = RTPoint(vp3.at(0).toDouble(),
                 vp3.at(1).toDouble(),
                 vp3.at(2).toDouble());

    triangle->setP1(p1);
    triangle->setP2(p2);
    triangle->setP3(p3);

    RTVector n1, n2, n3;

    QJsonArray normals = obj.value("normals").toArray();
    QJsonArray vn1 = normals.at(0).toArray();
    QJsonArray vn2 = normals.at(1).toArray();
    QJsonArray vn3 = normals.at(2).toArray();

    n1 = RTVector(vn1.at(0).toDouble(),
                  vn1.at(1).toDouble(),
                  vn1.at(2).toDouble());

    n2 = RTVector(vn2.at(0).toDouble(),
                  vn2.at(1).toDouble(),
                  vn2.at(2).toDouble());

    n3 = RTVector(vn3.at(0).toDouble(),
                  vn3.at(1).toDouble(),
                  vn3.at(2).toDouble());

    triangle->setNormal1(n1);
    triangle->setNormal2(n2);
    triangle->setNormal3(n3);

    RTBRDF *brdf = this->doBRDF(obj.value("brdf").toObject());

    triangle->setBrdf(brdf);

    objects.push_back(triangle);

}

RTBRDF *RTSceneLoader::doBRDF(QJsonObject brdfObj)
{
    RTBRDF *brdf = NULL;
    // blinn-phong
    QString type = brdfObj.value("type").toString();
    if(type=="blinn-phong")
    {
        brdf = new RTBRDF();
        brdf->setKa(brdfObj.value("ka").toDouble());
        brdf->setKd(brdfObj.value("kd").toDouble());
        brdf->setKs(brdfObj.value("ks").toDouble());
        brdf->setKr(brdfObj.value("kr").toDouble());

        brdf->setRefracIndex(brdfObj.value("refractIndex").toDouble());

        brdf->setN(brdfObj.value("n").toDouble());

        QString surfaceType = brdfObj.value("surface_type").toString();
        qDebug()<<surfaceType;
        if(surfaceType=="DIFFUSE")
        {
            brdf->setSurfaceType(DIFFUSE);
        }

        QString material = brdfObj.value("material").toString();
        qDebug()<<material;
        if(material=="SHINY")
        {
            brdf->setMaterial(SHINY);
        }

        QJsonObject colorObj = brdfObj.value("color").toObject();
        RTColor color(colorObj.value("r").toInt(),
                      colorObj.value("g").toInt(),
                      colorObj.value("b").toInt());

        brdf->setColor(color);

    }

    return brdf;
}
