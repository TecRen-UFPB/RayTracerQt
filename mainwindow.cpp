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
#include "rtLoadObj.h"

using namespace std;

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

    RTColor blue(255,0,0);
    RTColor red(255,0,0);

    OBJ *objeto;
    objeto = loadObj("/home/everaldo/workspace/RayTracerQt/Deer.obj", "/home/everaldo/workspace/RayTracerQt/Deer.mtl");

    int a =0, b=1;
    for(int i=0; i<objeto->totalF; i++){

        RTPoint p1(objeto->vertexs[(objeto->faces[i].v1-1)].x,
                   objeto->vertexs[(objeto->faces[i].v1-1)].y,
                   objeto->vertexs[(objeto->faces[i].v1-1)].z);

//        cout << objeto->vertexs[(objeto->faces[i].v1-1)].x << " " << objeto->vertexs[(objeto->faces[i].v1-1)].y << " " << objeto->vertexs[(objeto->faces[i].v1-1)].z << endl;
        RTPoint p2(objeto->vertexs[(objeto->faces[i].v2-1)].x,
                   objeto->vertexs[(objeto->faces[i].v2-1)].y,
                   objeto->vertexs[(objeto->faces[i].v2-1)].z);
//        cout << objeto->vertexs[(objeto->faces[i].v2-1)].x << " " << objeto->vertexs[(objeto->faces[i].v2-1)].y << " " << objeto->vertexs[(objeto->faces[i].v2-1)].z << endl;
        RTPoint p3(objeto->vertexs[(objeto->faces[i].v3-1)].x,
                   objeto->vertexs[(objeto->faces[i].v3-1)].y,
                   objeto->vertexs[(objeto->faces[i].v3-1)].z);
//        cout << objeto->vertexs[(objeto->faces[i].v3-1)].x << " " << objeto->vertexs[(objeto->faces[i].v3-1)].y << " " << objeto->vertexs[(objeto->faces[i].v3-1)].z << endl;

        RTVector n1(objeto->normais[(objeto->faces[i].n1-1)].nx,
                    objeto->normais[(objeto->faces[i].n1-1)].ny,
                    objeto->normais[(objeto->faces[i].n1-1)].nz);
        RTVector n2(objeto->normais[(objeto->faces[i].n2-1)].nx,
                    objeto->normais[(objeto->faces[i].n2-1)].ny,
                    objeto->normais[(objeto->faces[i].n2-1)].nz);
        RTVector n3(objeto->normais[(objeto->faces[i].n3-1)].nx,
                    objeto->normais[(objeto->faces[i].n3-1)].ny,
                    objeto->normais[(objeto->faces[i].n3-1)].nz);

        RTTriangle *triangle = new RTTriangle();
        triangle->setP1(p1);
        triangle->setP2(p2);
        triangle->setP3(p3);
        triangle->setNormal1(n1);
        triangle->setNormal1(n2);
        triangle->setNormal1(n3);

        if(i < objeto->a[b].f && b<objeto->mtl->TotalMTL){
            a++;
            b++;
        }

        RTBRDF *material_tri=new RTCheckTexture(objeto->mtl->CO[a].Ka,
                                                objeto->mtl->CO[a].Kd,
                                                objeto->mtl->CO[a].Ks,
                                                0,100,DIFFUSE,CHECK,blue,red,20);
//        cout << "Ka " << objeto->mtl->CO[a].Ks << " Kd " << objeto->mtl->CO[a].Kd << " Ks " << objeto->mtl->CO[a].Ks << endl;
        triangle->setBrdf(material_tri);
        objects.push_back(triangle);
    }

    RTColor sky(135,206,250);
    RTPoint p(0,0,1000000);
    RTVector n1(0,0,1);
    RTPlane *pl1= new RTPlane(p,n1);
    RTBRDF *material3=new RTBRDF(0.14, 0.7, 0,0.5,1.55, 100, SPECULAR,SHINY, sky);

    pl1->setBrdf(material3);
    objects.push_back(pl1);

    // TODO parameterize the camera
    RTPoint e(2, 0, 6);
    RTPoint look_at(0,0,-1);
    RTVector up(0,-1,0);
    this->cam = RTCamera(e, look_at, up, 2);
    RTColor white(250,250,250);
    this->scene = RTScene(this->cam, objects, 10,300,-300,white);

        this->scene.render(2);

    double time_elapsed=myTimer.elapsed()/1000.0;


    std::cout<<"Tempo de Rendering da Cena: "<<time_elapsed<<" segundos"<<std::endl;

    // force the first update
    slotOnBufferChange();
    delete pl1;
}
