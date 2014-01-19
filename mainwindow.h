#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "rtfilm.h"
#include "rtcamera.h"
#include "rtscene.h"

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

public slots:
    void slotOnBufferChange();
    void slotMenuSaveTriggered();

};

#endif // MAINWINDOW_H
