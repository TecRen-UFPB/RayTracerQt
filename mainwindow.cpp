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
    StartDialog sd;
    sd.exec();

    // Initiates the buffer
    RTFilm::init(sd.getWidth(), sd.getHeight());

    // connect buffer update signal
    connect(RTFilm::getInstance(), SIGNAL(onBufferChange()), this, SLOT(slotOnBufferChange()) );

    // connect menu save triggered
    connect(ui->actionSalvar, SIGNAL(triggered()), this, SLOT(slotMenuSaveTriggered()));

    loadScene(sd.getSceneFile());

    // force the first update
    slotOnBufferChange();

}

void MainWindow::loadScene(QString filename)
{
    QTime myTimer;
    myTimer.start();

    RTSceneLoader loader(filename); //"/media/Arquivos/g5/ufpb/Tecnicas.Avancadas.Em.Rendering/TrabalhoFinal/RayTracer/cenas_teste/cena_teste.rt");
    loader.load(objects);

    this->cam = loader.getCamera();

    this->scene = loader.getScene();

    this->scene.render(loader.getSamples());

    double time_elapsed=myTimer.elapsed()/1000.0;

    std::cout<<"Total de objetos: "<<objects.size()<<std::endl;

    std::cout<<"Tempo de Rendering da Cena: "<<time_elapsed<<" segundos"<<std::endl;

    // force update
    slotOnBufferChange();
}

void MainWindow::on_actionAbrir_cena_triggered()
{
    QString selfilter = tr("RT Files (*.rt)");
    QString fileName = QFileDialog::getOpenFileName(this,"Abrir cena", "",selfilter);

    loadScene(fileName);

}
