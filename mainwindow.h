#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtConcurrent/QtConcurrent>
#include <QLabel>

#include "rtfilm.h"
#include "rtcamera.h"
#include "rtscene.h"

#include "startdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Raytracer
    RTScene scene;
    RTCamera cam;
    std::vector<RTObject*> objects;

    void initRayTracer();

    void clearAll();

    bool running;

    QFuture<void> future;

    QLabel statusLabel;

public slots:
    void slotOnBufferChange();
    void slotMenuSaveTriggered();

    void loadScene(QString filename);
    void _loadScene(QString filename);

private slots:
    void on_actionAbrir_cena_triggered();
};

#endif // MAINWINDOW_H
