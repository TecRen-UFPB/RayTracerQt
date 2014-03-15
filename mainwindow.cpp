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
#include "rtsceneloader.h"

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

    RTSceneLoader loader("/media/Arquivos/g5/ufpb/Tecnicas.Avancadas.Em.Rendering/TrabalhoFinal/RayTracer/cenas_teste/cena_teste.rt");
    loader.load(objects);

    // TODO parameterize the camera
    RTPoint e(300, 300, 300);
    RTPoint look_at(0,0,-1);
    RTVector up(0,1,0);
    this->cam = RTCamera(e, look_at, up, 2);
    RTColor white(250,250,250);
    this->scene = RTScene(this->cam, objects, 10,300,-300,white);

        this->scene.render(2);

    double time_elapsed=myTimer.elapsed()/1000.0;

    std::cout<<"Total de objetos: "<<objects.size()<<std::endl;

    std::cout<<"Tempo de Rendering da Cena: "<<time_elapsed<<" segundos"<<std::endl;

    // force the first update
    slotOnBufferChange();



}
