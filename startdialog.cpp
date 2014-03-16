#include "startdialog.h"
#include "ui_startdialog.h"

#include <QMessageBox>
#include <QFileDialog>

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
    this->setModal(true);

}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::accept()
{

    this->width = ui->width_spin->value();
    this->height = ui->height_spin->value();

    this->sceneFile = ui->filename_edit->text();

    if(this->sceneFile=="")
        QMessageBox::warning(this, "Erro", "Informe uma cena!");
    else
        QDialog::accept();

}
QString StartDialog::getSceneFile() const
{
    return sceneFile;
}

void StartDialog::setSceneFile(const QString &value)
{
    sceneFile = value;
}
int StartDialog::getWidth() const
{
    return width;
}

void StartDialog::setWidth(int value)
{
    width = value;
}
int StartDialog::getHeight() const
{
    return height;
}

void StartDialog::setHeight(int value)
{
    height = value;
}

void StartDialog::closeEvent(QCloseEvent *e)
{
    exit(0);
}

void StartDialog::on_pushButton_clicked()
{
    QString selfilter = tr("RT Files (*.rt)");
    QString fileName = QFileDialog::getOpenFileName(this,"Abrir cena", "",selfilter);

    ui->filename_edit->setText(fileName);

}
