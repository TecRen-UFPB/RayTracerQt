#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QFileDialog>
#include <QDebug>

#include "rtsphere.h"

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
    RTFilm::init(512, 512);

    // connect buffer update signal
    connect(RTFilm::getInstance(), SIGNAL(onBufferChange()), this, SLOT(slotOnBufferChange()) );

    // connect menu save triggered
    connect(ui->actionSalvar, SIGNAL(triggered()), this, SLOT(slotMenuSaveTriggered()));

    // TODO parameterize the scene objects
    RTSphere *sphere = new RTSphere();
    RTPoint sph_center(0,0,100);
    RTColor blue(0,0,255);
    RTBRDF material(0.6, 0.8, 0.2, 0, blue);
    sphere->setCenter(sph_center);
    sphere->setBrdf(material);
    sphere->setRadius(50);
    objects.push_back(sphere);

    // TODO parameterize the camera
    RTPoint e(0, 0, -10);
    RTPoint look_at(0,0,10);
    RTVector up(0,1,0);
    this->cam = RTCamera(e, look_at, up, 100);
    this->scene = RTScene(this->cam, objects, 4);

    this->scene.render();

    // force the first update
    slotOnBufferChange();
}
