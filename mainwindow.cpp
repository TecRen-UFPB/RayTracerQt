#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QFileDialog>
#include <QDebug>
#include <QTime>
#include <QSet>
#include <QMessageBox>

#include "rtobject.h"
#include "rtsphere.h"
#include "rtplane.h"
#include "rtchecktexture.h"
#include "rtturbulencetexture.h"
#include "rtcrisscrosstexture.h"
#include "rtmarbletexture.h"
#include "rtwoodtexture.h"
#include "rttriangle.h"
#include "rtsceneloader.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusBar->addWidget(&statusLabel);

    running = false;

    initRayTracer();
}

MainWindow::~MainWindow()
{
    delete ui;

    if(running)
    {
        future.cancel();
    }

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
    running = true;
    future = QtConcurrent::run(this, &MainWindow::_loadScene, filename);
}

void MainWindow::_loadScene(QString filename)
{
    this->statusLabel.setText("Executando raytracing...");

    QTime myTimer;
    myTimer.start();

    RTSceneLoader loader(filename);
    loader.load(objects);

    this->cam = loader.getCamera();

    this->scene = loader.getScene();

    this->scene.render(loader.getSamples());

    double time_elapsed=myTimer.elapsed()/1000.0;

    std::cout<<"Total de objetos: "<<objects.size()<<std::endl;

    std::cout<<"Tempo de Rendering da Cena: "<<time_elapsed<<" segundos"<<std::endl;

    this->statusLabel.setText(QString("Objetos: %1 Tempo total: %2 segundos").arg(objects.size()).arg(time_elapsed));

    clearAll();

    // force update
    emit slotOnBufferChange();

    running = false;
}

void MainWindow::on_actionAbrir_cena_triggered()
{
    if(running)
    {
        QMessageBox::warning(this, "Aviso", "Aguarde o término da operação!");
        return;
    }

    QString selfilter = tr("RT Files (*.rt)");
    QString fileName = QFileDialog::getOpenFileName(this,"Abrir cena", "",selfilter);

    if(fileName.size()==0 || fileName.isEmpty())
        return;

    loadScene(fileName);

}

void MainWindow::clearAll()
{
    QSet<RTBRDF *> brdfs;
    for(int i=0;i<objects.size();i++)
    {
        brdfs.insert( objects.at(i)->getBrdf() );
        delete objects.at(i);
    }
    qDeleteAll(brdfs);
    objects.clear();
}
