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

    // objects loader
    QJsonArray arr = obj.value("objects").toArray();

    QString type;
    for(int i=0;i<arr.size();i++)
    {
        type = arr.at(i).toObject().value("type").toString();
        qDebug()<<type;
        if(type=="triangle")
            doTriangle(arr.at(i).toObject(), objects);
        else if(type=="sphere")
            doSphere(arr.at(i).toObject(), objects);
    }

    // Camera loader
    QJsonObject camObj = obj.value("camera").toObject();

    RTPoint e = this->arrayToPoint(camObj.value("e").toArray());
    RTPoint look_at = this->arrayToPoint(camObj.value("look_at").toArray());
    RTVector up = this->arrayToVector(camObj.value("up").toArray());
    double fovy = camObj.value("fovy").toDouble();

    this->camera = RTCamera(e, look_at, up, fovy);

    // scene config loader
    int maxDepth = obj.value("maxDepth").toInt();
    double z_start = obj.value("z_start").toDouble();
    double z_end = obj.value("z_end").toDouble();
    RTColor fogColor = this->objToColor(obj.value("fogColor").toObject());

    this->scene = RTScene(this->camera,
                          objects,
                          maxDepth,
                          z_start,
                          z_end,
                          fogColor);
    bool hasFog = obj.value("hasFog").toBool();
    this->scene.setHasFog(hasFog);

    this->samples = obj.value("samples").toInt();

}

RTCamera RTSceneLoader::getCamera()
{
    return this->camera;
}

RTScene RTSceneLoader::getScene()
{
    return this->scene;
}

int RTSceneLoader::getSamples()
{
    return this->samples;
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

void RTSceneLoader::doSphere(QJsonObject obj, std::vector<RTObject *> &objects)
{
    RTSphere *sphere = new RTSphere();

    QJsonArray centerArr = obj.value("center").toArray();

    RTPoint center  = RTPoint(centerArr.at(0).toDouble(),
                 centerArr.at(1).toDouble(),
                 centerArr.at(2).toDouble());

    sphere->setCenter(center);

    double radius = obj.value("radius").toDouble();

    sphere->setRadius(radius);

    RTBRDF *brdf = doBRDF(obj.value("brdf").toObject());

    sphere->setBrdf(brdf);

    objects.push_back(sphere);

}

RTBRDF *RTSceneLoader::doBRDF(QJsonObject brdfObj)
{
    RTBRDF *brdf = NULL;
    // blinn-phong
    QString type = brdfObj.value("type").toString();
    if(type=="blinn-phong")
    {
        brdf = new RTBRDF();

        QJsonObject colorObj = brdfObj.value("color").toObject();
        RTColor color(colorObj.value("r").toInt(),
                      colorObj.value("g").toInt(),
                      colorObj.value("b").toInt());

        brdf->setColor(color);

    } else if(type=="check") {
        brdf = doBRDFCheck(brdfObj);
    } else if(type=="crisscross") {
        brdf = doBRDFCrissCross(brdfObj);
    } else if(type=="marble") {
        brdf = doBRDFMarble(brdfObj);
    } else if(type=="turbulence") {
        brdf = doBRDFTurbulence(brdfObj);
    } else if(type=="wood") {
        brdf = doBRDFWood(brdfObj);
    }

    brdf->setKa(brdfObj.value("ka").toDouble());
    brdf->setKd(brdfObj.value("kd").toDouble());
    brdf->setKs(brdfObj.value("ks").toDouble());
    brdf->setKr(brdfObj.value("kr").toDouble());

    brdf->setRefracIndex(brdfObj.value("refractIndex").toDouble());

    brdf->setN(brdfObj.value("n").toDouble());

    QString surfaceType = brdfObj.value("surface_type").toString();
//    qDebug()<<surfaceType;
    if(surfaceType=="DIFFUSE")
    {
        brdf->setSurfaceType(DIFFUSE);
    } else if(surfaceType=="SPECULAR") {
        brdf->setSurfaceType(SPECULAR);
    } else if(surfaceType=="REFLECTIVE") {
        brdf->setSurfaceType(REFLECTIVE);
    } else if(surfaceType=="REFRACTIVE") {
        brdf->setSurfaceType(REFRACTIVE);
    }

    QString material = brdfObj.value("material").toString();
//    qDebug()<<material;
    if(material=="SHINY")
    {
        brdf->setMaterial(SHINY);
    } else if(material=="CHECK") {
        brdf->setSurfaceType(CHECK);
    } else if(material=="TURBULENCE") {
        brdf->setSurfaceType(TURBULENCE);
    } else if(material=="CRISSCROSS") {
        brdf->setMaterial(CRISSCROSS);
    } else if(material=="MARBLE") {
        brdf->setMaterial(MARBLE);
    } else if(material=="WOOD") {
        brdf->setMaterial(WOOD);
    }

    return brdf;
}

RTBRDF * RTSceneLoader::doBRDFCheck(QJsonObject brdfObj)
{
    RTCheckTexture *brdf = new RTCheckTexture();

    QJsonObject color1Obj = brdfObj.value("color1").toObject();
    RTColor color1(color1Obj.value("r").toInt(),
                  color1Obj.value("g").toInt(),
                  color1Obj.value("b").toInt());

    brdf->setColorCheck1(color1);

    QJsonObject color2Obj = brdfObj.value("color2").toObject();
    RTColor color2(color2Obj.value("r").toInt(),
                  color2Obj.value("g").toInt(),
                  color2Obj.value("b").toInt());

    brdf->setColorCheck2(color2);

    double size = brdfObj.value("size").toDouble();
    brdf->setSize(size);

    return brdf;
}

RTBRDF * RTSceneLoader::doBRDFCrissCross(QJsonObject brdfObj)
{
    RTCrissCrossTexture * brdf = new RTCrissCrossTexture();


    QJsonObject color1Obj = brdfObj.value("color1").toObject();
    RTColor color1(color1Obj.value("r").toInt(),
                  color1Obj.value("g").toInt(),
                  color1Obj.value("b").toInt());

    brdf->setColorCC1(color1);

    QJsonObject color2Obj = brdfObj.value("color2").toObject();
    RTColor color2(color2Obj.value("r").toInt(),
                  color2Obj.value("g").toInt(),
                  color2Obj.value("b").toInt());

    brdf->setColorCC2(color2);

    QJsonObject color3Obj = brdfObj.value("color3").toObject();
    RTColor color3(color3Obj.value("r").toInt(),
                  color3Obj.value("g").toInt(),
                  color3Obj.value("b").toInt());

    brdf->setColorCC3(color3);

    double scale = brdfObj.value("scale").toDouble();
    brdf->setScale(scale);

    return brdf;

}

RTBRDF * RTSceneLoader::doBRDFMarble(QJsonObject brdfObj)
{
    RTMarbleTexture *brdf = new RTMarbleTexture();

    QJsonObject color1Obj = brdfObj.value("color1").toObject();
    RTColor color1(color1Obj.value("r").toInt(),
                  color1Obj.value("g").toInt(),
                  color1Obj.value("b").toInt());

    brdf->setColorMarbe1(color1);

    QJsonObject color2Obj = brdfObj.value("color2").toObject();
    RTColor color2(color2Obj.value("r").toInt(),
                  color2Obj.value("g").toInt(),
                  color2Obj.value("b").toInt());

    brdf->setColorMarbe2(color2);

    double scale = brdfObj.value("scale").toDouble();
    brdf->setScale(scale);

    return brdf;
}

RTBRDF * RTSceneLoader::doBRDFTurbulence(QJsonObject brdfObj)
{
    RTTurbulenceTexture * brdf = new RTTurbulenceTexture();

    QJsonObject colorObj = brdfObj.value("color").toObject();
    RTColor color(colorObj.value("r").toInt(),
                  colorObj.value("g").toInt(),
                  colorObj.value("b").toInt());

    brdf->setColorTurbulence(color);

    int num_octaves = brdfObj.value("num_octaves").toInt();
    brdf->setNum_octaves(num_octaves);

    double scale = brdfObj.value("scale").toDouble();
    brdf->setScale(scale);

    return brdf;

}

RTBRDF *RTSceneLoader::doBRDFWood(QJsonObject brdfObj)
{
    RTWoodTexture *brdf = new RTWoodTexture();

    QJsonObject color1Obj = brdfObj.value("color1").toObject();
    RTColor color1(color1Obj.value("r").toInt(),
                  color1Obj.value("g").toInt(),
                  color1Obj.value("b").toInt());

    brdf->setColorWood1(color1);

    QJsonObject color2Obj = brdfObj.value("color2").toObject();
    RTColor color2(color2Obj.value("r").toInt(),
                  color2Obj.value("g").toInt(),
                  color2Obj.value("b").toInt());

    brdf->setColorWood2(color2);

    double scale = brdfObj.value("scale").toDouble();
    brdf->setScale(scale);

    return brdf;
}

RTPoint RTSceneLoader::arrayToPoint(QJsonArray arr)
{
    RTPoint p = RTPoint(arr.at(0).toDouble(),
                        arr.at(1).toDouble(),
                        arr.at(2).toDouble());
    return  p;
}

RTVector RTSceneLoader::arrayToVector(QJsonArray arr)
{
    RTVector p = RTVector(arr.at(0).toDouble(),
                        arr.at(1).toDouble(),
                        arr.at(2).toDouble());
    return  p;
}

RTColor RTSceneLoader::objToColor(QJsonObject obj)
{
    RTColor color(obj.value("r").toInt(),
                  obj.value("g").toInt(),
                  obj.value("b").toInt());
    return color;
}
