#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionOpenAP, SIGNAL(triggered()), this, SLOT(openAP()));
    connect(ui->actionOpenLAT, SIGNAL(triggered()), this, SLOT(openLAT()));
    connect(ui->actionCloseAP, SIGNAL(triggered()), ui->APLabel, SLOT(clear()));
    connect(ui->actionCloseLAT, SIGNAL(triggered()), ui->LATLabel, SLOT(clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openAP()
{
    QString dir = QFileDialog::getOpenFileName(this,
                               "Select AP image",
                               QDir::currentPath(),
                               "*.jpg ;; *.jpeg");
    mImage[0].load(dir);

    int w = ui->APLabel->width();
    int h = ui->APLabel->height();
    ui->APLabel->setPixmap(mImage[0].scaled(w, h, Qt::KeepAspectRatio));
    //this->resize(w + 200, this->height());
}

void MainWindow::openLAT()
{
    QString dir = QFileDialog::getOpenFileName(this,
                               "Select LAT image",
                               QDir::currentPath(),
                               "*.jpg ;; *.jpeg");
    mImage[1].load(dir);

    int w = ui->LATLabel->width();
    int h = ui->LATLabel->height();
    ui->LATLabel->setPixmap(mImage[1].scaled(w, h, Qt::KeepAspectRatio));
}

void MainWindow::scaleImage(double factor)
{
    scaleFactor *= factor;

    int w = ui->APLabel->width();
    int h = ui->APLabel->height();
    ui->APLabel->setPixmap(mImage[0].scaled(scaleFactor * w, scaleFactor * h, Qt::KeepAspectRatio));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q)
    {
        zoomIn();
    }
    else if(event->key() == Qt::Key_W)
    {
        zoomOut();
    }
}
