#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QFileDialog>
#include <QDebug>

#include "rtbuffer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    // Inits the buffer
    RTBuffer::init(512, 512);

    // connect buffer update signal
    connect(RTBuffer::getInstance(), SIGNAL(onBufferChange()), this, SLOT(slotOnBufferChange()) );

    // connect menu save triggered
    connect(ui->actionSalvar, SIGNAL(triggered()), this, SLOT(slotMenuSaveTriggered()));

    // force the first update
    slotOnBufferChange();
}

MainWindow::~MainWindow()
{
    delete ui;

    // destroy the buffer
    RTBuffer::close();
}

void MainWindow::slotOnBufferChange()
{
    ui->bufferPreview->setPixmap(QPixmap::fromImage(*RTBuffer::getInstance()->getQImage()));
}

void MainWindow::slotMenuSaveTriggered()
{
    QString fsv = QFileDialog::getSaveFileName(this, tr("Salvar imagem"), QDir::homePath(), "Images (*.png *.xpm *.jpg);; All files (*.*)");
    RTBuffer::getInstance()->save(fsv);
}
