#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QFileDialog>
#include <QDebug>
#include<QTime>
#include<iostream>

#include "rtsphere.h"
#include "rtplane.h"
#include "rtchecktexture.h"
#include "rtturbulencetexture.h"
#include "rtcrisscrosstexture.h"
#include "rtmarbletexture.h"
#include "rtwoodtexture.h"
#include "rttriangle.h"
#include "objLoader.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initRayTracer();
}

MainWindow::~MainWindow()
{
    delete ui;

    // destroy the buffer
    RTFilm::close();
}

void MainWindow::slotOnBufferChange()
{
    ui->bufferPreview->setPixmap(QPixmap::fromImage(*RTFilm::getInstance()->getQImage()));
}

void MainWindow::slotMenuSaveTriggered()
{
    QString fsv = QFileDialog::getSaveFileName(this, tr("Salvar imagem"), QDir::homePath(), "Images (*.png *.xpm *.jpg);; All files (*.*)");
    RTFilm::getInstance()->writeImage(fsv);
}

void MainWindow::initRayTracer()
{
    // Initiates the buffer
    RTFilm::init(680, 512);

    // connect buffer update signal
    connect(RTFilm::getInstance(), SIGNAL(onBufferChange()), this, SLOT(slotOnBufferChange()) );

    // connect menu save triggered
    connect(ui->actionSalvar, SIGNAL(triggered()), this, SLOT(slotMenuSaveTriggered()));

    // TODO parameterize the scene objects

    /**
     * sistemas de coordenadas: z-> para tras, y se comporta como x e x como y
     */

    QTime myTimer;
    myTimer.start();


    RTSphere *sphere = new RTSphere();
    RTPoint sph_center(200,200,0); //200 200 100
    RTColor blue(106,90,205);
    RTBRDF *material=new RTBRDF(0.14, 0.7, 1.0,0.5,1.55, 100, REFLECTIVE,SHINY,blue);
    sphere->setCenter(sph_center);
    sphere->setBrdf(material);
    sphere->setRadius(70);
   // objects.push_back(sphere);

    RTColor with(255,255,255);

    RTSphere *sphere2 = new RTSphere();
    RTPoint p1(300,400,100);
    sphere2->setCenter(p1);
    sphere2->setRadius(50);
    RTColor red(255,50,50);
    RTBRDF *material1=new RTTurbulenceTexture(0.14, 0.7, 1.0,0.1,100, SPECULAR,TURBULENCE, red,10,10);

    sphere2->setBrdf(material1);
   // objects.push_back(sphere2);


    RTColor green(0,102,51);
    RTSphere *sphere3 = new RTSphere();
    RTPoint p2(200,300,100); //0 0 10
    sphere3->setCenter(p2);
    sphere3->setRadius(70);
    RTBRDF *marble = new RTMarbleTexture(0.2,0.8,0,0,100,SPECULAR,MARBLE,with,blue,4);

    sphere3->setBrdf(marble);
    //objects.push_back(sphere3);

    RTColor echo(205,102,29);
    RTColor pink(199,21,133);
    RTSphere *sphere4 = new RTSphere();
    RTPoint p4(470,400,50); //0 0 10
    sphere4->setCenter(p4);
    sphere4->setRadius(50);
    RTColor y(255,255,0);
    RTBRDF *material4=new RTCrissCrossTexture(0.14, 0.7, 1.0,1.0, 100, SPECULAR,CRISSCROSS, pink,blue,y,50);
    sphere4->setBrdf(material4);
    //objects.push_back(sphere4);

    RTColor muchaco(255,193,47);

    RTSphere *sphere5 = new RTSphere();
    RTPoint p5(570,400,0); //0 0 10
    sphere5->setCenter(p5);
    sphere5->setRadius(30);
    RTBRDF *material5=new RTBRDF(0.14, 0.7, 1,0.1,1.55, 100, REFLECTIVE, SHINY, muchaco);
    sphere5->setBrdf(material5);
    //objects.push_back(sphere5);

    RTColor sayajin(255,69,0);



    RTSphere *sphere6 = new RTSphere();
    RTPoint p6(570,300,-100); //0 0 10
    sphere6->setCenter(p6);
    sphere6->setRadius(100);
    RTBRDF *material6=new RTBRDF(0.14, 0.7, 1,1,1.5, 100, REFLECTIVE,SHINY, green);
    sphere6->setBrdf(material6);
    //objects.push_back(sphere6);

    RTTriangle *triangle1 = new RTTriangle();
    RTPoint tr1_p1( 50,  50, 50);
    RTPoint tr1_p2(100,  50, 50);
    RTPoint tr1_p3(100, 100, 50);
    triangle1->setP1(tr1_p1);
    triangle1->setP2(tr1_p2);
    triangle1->setP3(tr1_p3);

    RTBRDF *material_tri=new RTCheckTexture(0.2,0.8,0,0,100,DIFFUSE,CHECK,blue,red,20);
    triangle1->setBrdf(material_tri);
//    objects.push_back(triangle1);


    RTColor sky(135,206,250);
    RTPoint p(0,0,1000000);
    RTVector n1(0,0,1);
    RTPlane *pl1= new RTPlane(p,n1);
    RTBRDF *material3=new RTBRDF(0.14, 0.7, 0,0.5,1.55, 100, SPECULAR,SHINY, sky);

    pl1->setBrdf(material3);
    //objects.push_back(pl1);


    RTColor yelow(255,255,0);
    RTCheckTexture *check=new RTCheckTexture(0.2,0.8,0,0,100,SPECULAR,CHECK,yelow,red,200);
    RTPoint p10(0,1,0);
    RTVector n10(0,-1,0);
    RTPlane *pl20= new RTPlane(p10,n10);
    RTColor zas(255,255,0);
    //RTBRDF *material30=new RTBRDF(0.2, 0.8, 0,0.5,1.55, 100, REFLECTIVE,SHINY, zas);
    pl20->setBrdf(check);
    //objects.push_back(pl20);


    RTPoint p20(1000,0,0);
    RTVector n20(1,0,0);
    RTPlane *pl30= new RTPlane(p20,n20);
    RTColor iupi(0,139,139);
    RTBRDF *material20=new RTBRDF(0.2, 0.8, 1,0,1.55, 100, SPECULAR, SHINY, iupi);
    pl30->setBrdf(material20);
    //objects.push_back(pl30);


    //add importador

    objLoader *objData;
    objData = new objLoader();
    objData->load("/home/marcilio/workspace/raytracing_ufpb/RayTracerQt/box.obj");


    for(int i=0; i<objData->faceCount; i++)
    {
        obj_face *o = objData->faceList[i];

        RTPoint p1(objData->vertexList[o->vertex_index[0]]->e[0], // primeira linha
                   objData->vertexList[o->vertex_index[0]]->e[1],
                   objData->vertexList[o->vertex_index[0]]->e[2]);

        RTPoint p2(objData->vertexList[o->vertex_index[1]]->e[0],
                objData->vertexList[o->vertex_index[1]]->e[1],
                objData->vertexList[o->vertex_index[1]]->e[2]);

        RTPoint p3(	objData->vertexList[o->vertex_index[2]]->e[0],
                objData->vertexList[o->vertex_index[2]]->e[1],
                objData->vertexList[o->vertex_index[2]]->e[2]);



        RTTriangle *triangle= new RTTriangle(p1,p2,p3);
        RTVector n1(objData->normalList[o->normal_index[0]]->e[0],
                objData->normalList[o->normal_index[0]]->e[1],
                objData->normalList[o->normal_index[0]]->e[2]);
        RTVector n2(objData->normalList[o->normal_index[1]]->e[0],
                objData->normalList[o->normal_index[1]]->e[1],
                objData->normalList[o->normal_index[1]]->e[2]);
        RTVector n3(objData->normalList[o->normal_index[2]]->e[0],
                objData->normalList[o->normal_index[2]]->e[1],
                objData->normalList[o->normal_index[2]]->e[2]);
        triangle->setNormal1(n1);
        triangle->setNormal2(n2);
        triangle->setNormal3(n3);
        triangle->setBrdf(material);
        objects.push_back(triangle);
    }

    // TODO parameterize the camera
    RTPoint e(0, 0, 0); //300
    RTPoint look_at(0,0,-1);
    RTVector up(0,1,0);
    this->cam = RTCamera(e, look_at, up, 2);
    RTColor white(250,250,250);
    this->scene = RTScene(this->cam, objects, 5);

        this->scene.render(2);

    double time_elapsed=myTimer.elapsed()/1000.0;


    std::cout<<"Tempo de Rendering da Cena: "<<time_elapsed<<" segundos"<<std::endl;

    // force the first update
    slotOnBufferChange();
    delete sphere;
    delete sphere2;
    delete sphere4;
    delete sphere5;
    delete sphere6;
    delete pl1;
    delete pl20;
    delete sphere3;
    delete objData;


}
