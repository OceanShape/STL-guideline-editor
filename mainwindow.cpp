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
    if (mImage[Screen::AP] != nullptr)
    {
        delete mImage[Screen::AP];
    }

    if (mImage[Screen::LAT] != nullptr)
    {
        delete mImage[Screen::LAT];
    }

    delete ui;
}

void MainWindow::openAP()
{
    QString dir = QFileDialog::getOpenFileName(this,
                               "Select AP image",
                               QDir::currentPath(),
                               "*.jpg ;; *.jpeg");
    mImage[Screen::AP] = new QPixmap;
    mImage[Screen::AP]->load(dir);

    mAPwidth = ui->APLabel->width();
    mAPheight = ui->APLabel->height();

    ui->APLabel->setPixmap(mImage[Screen::AP]->scaled(mAPwidth, mAPheight, Qt::KeepAspectRatio));
}

void MainWindow::openLAT()
{
    QString dir = QFileDialog::getOpenFileName(this,
                               "Select LAT image",
                               QDir::currentPath(),
                               "*.jpg ;; *.jpeg");
    mImage[Screen::LAT] = new QPixmap;
    mImage[Screen::LAT]->load(dir);

    mLATwidth = ui->LATLabel->width();
    mLATheight = ui->LATLabel->height();

    ui->LATLabel->setPixmap(mImage[Screen::LAT]->scaled(mLATwidth, mLATheight, Qt::KeepAspectRatio));
}

void MainWindow::scaleImage(double factor)
{
    QLabel* screen = nullptr;
    if (mZoomScreen == Screen::AP)
    {
        screen = ui->APLabel;
    }
    else // mZoomScreen == ZoomScreen::LAT
    {
        screen = ui->LATLabel;
    }

    if (screen == nullptr)
    {
        return;
    }


    qDebug() << factor;

    int w = ui->APLabel->width();
    int h = ui->APLabel->height();

    qDebug() << "input" << w << "," << h;

    w *= factor;
    h *= factor;
    qDebug() << "output" <<w << "," << h;

    ui->APLabel->setPixmap(mImage[mZoomScreen]->scaled(w, h, Qt::KeepAspectRatio));
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
    else if(event->key() == Qt::Key_H)
    {
        ui->APLabel->adjustSize();
    }
}

void MainWindow::zoomIn()
{
    scaleImage(1.25);
}

void MainWindow::zoomOut()
{
    scaleImage(0.8);
}
