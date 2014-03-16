#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = 0);
    ~StartDialog();

    virtual void accept();
    virtual void closeEvent ( QCloseEvent * e );

    QString getSceneFile() const;
    void setSceneFile(const QString &value);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

private slots:
    void on_pushButton_clicked();

private:
    Ui::StartDialog *ui;

    QString sceneFile;
    int width;
    int height;

};

#endif // STARTDIALOG_H
