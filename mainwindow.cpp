#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QFileDialog>
#include <QDebug>

#include "rtsphere.h"
#include "rtplane.h"

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

    RTSphere *sphere = new RTSphere();
    RTPoint sph_center(200,200,0); //200 200 100
    RTColor blue(106,90,205);
    RTBRDF material(0.14, 0.7, 1, 100, SPECULAR, blue);

    sphere->setCenter(sph_center);
    sphere->setBrdf(material);
    sphere->setRadius(70);
    objects.push_back(sphere);

    RTSphere *sphere2 = new RTSphere();
    RTPoint p1(300,400,150);
    sphere2->setCenter(p1);
    sphere2->setRadius(70);
    RTColor red(255,50,50);
    RTBRDF material1(0.14, 0.7, 1, 100, SPECULAR, red);
    material1.setFresnel(0.31);
    sphere2->setBrdf(material1);
    objects.push_back(sphere2);

    RTColor green(0,102,51);
    RTColor pink(199,21,133);
    RTSphere *sphere3 = new RTSphere();
    RTPoint p2(200,300,100); //0 0 10
    sphere3->setCenter(p2);
    sphere3->setRadius(70);
    RTBRDF material2(0.14, 0.7, 1, 100, REFLECTIVE, green);
      material2.setFresnel(0.31);
    sphere3->setBrdf(material2);
    objects.push_back(sphere3);

    RTColor echo(205,102,29);

    RTSphere *sphere4 = new RTSphere();
    RTPoint p4(470,400,50); //0 0 10
    sphere4->setCenter(p4);
    sphere4->setRadius(50);
    RTBRDF material4(0.14, 0.7, 1, 100,SPECULAR, echo);
    sphere4->setBrdf(material4);
    objects.push_back(sphere4);

    RTColor muchaco(255,193,37);

    RTSphere *sphere5 = new RTSphere();
    RTPoint p5(570,400,0); //0 0 10
    sphere5->setCenter(p5);
    sphere5->setRadius(30);
    RTBRDF material5(0.14, 0.7, 1, 100, SPECULAR, muchaco);
    sphere5->setBrdf(material5);
    objects.push_back(sphere5);

    RTColor sayajin(255,69,0);

    RTSphere *sphere6 = new RTSphere();
    RTPoint p6(570,300,-100); //0 0 10
    sphere6->setCenter(p6);
    sphere6->setRadius(100);
    RTBRDF material6(0.14, 0.7, 1, 100, REFLECTIVE, sayajin);
    material6.setFresnel(0.31);
    sphere6->setBrdf(material6);
    objects.push_back(sphere6);


    RTPoint p(0,0,1000000);
    RTVector n1(0,0,1);
    RTPlane *pl1= new RTPlane(p,n1);
    RTBRDF material3(0.14, 0.7, 0, 100, SPECULAR, pink);

    pl1->setBrdf(material3);
    objects.push_back(pl1);

    RTPoint p10(0,1,0);
    RTVector n10(0,-1,0);
    RTPlane *pl20= new RTPlane(p10,n10);
    RTColor zas(255,255,0);
    RTBRDF material30(0.2, 0.8, 0, 100, SPECULAR, zas);
    pl20->setBrdf(material30);
    objects.push_back(pl20);


    RTPoint p20(1000,0,0);
    RTVector n20(1,0,0);
    RTPlane *pl30= new RTPlane(p20,n20);
    RTColor iupi(0,139,139);
    RTBRDF material20(0.2, 0.8, 0, 100, SPECULAR, iupi);
    pl30->setBrdf(material20);
    objects.push_back(pl30);






    // TODO parameterize the camera
    RTPoint e(300, 300, 300);
    RTPoint look_at(0,0,-1);
    RTVector up(0,1,0);
    this->cam = RTCamera(e, look_at, up, 2);
    this->scene = RTScene(this->cam, objects, 10);

    this->scene.render();

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
}
