#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    showMaximized();

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionOpenAP, SIGNAL(triggered()), this, SLOT(openAP()));
    connect(ui->actionOpenLAT, SIGNAL(triggered()), this, SLOT(openLAT()));
//  connect(ui->actionCloseAP, SIGNAL(triggered()), ui->APLabel, SLOT(clear()));
//  connect(ui->actionCloseLAT, SIGNAL(triggered()), ui->LATLabel, SLOT(clear()));

//  mLabel[Screen::AP] = ui->APLabel;
//   mLabel[Screen::LAT] = ui->LATLabel;

    mImageWidth = 0;
    mImageHeight = 0;
    mScaleFactor = 1.0;
    mZoomScreen = Screen::AP; // use mouse tracking later
}

MainWindow::~MainWindow()
{
    for (QPixmap* p : mImage)
    {
        delete p;
    }

    delete ui;
}

void MainWindow::openFile(Screen screen)
{
    QString dir = QFileDialog::getOpenFileName(this,
                               "Select image",
                               QDir::currentPath(),
                               "*.jpg ;; *.jpeg");
    mImage[screen] = new QPixmap;
    mImage[screen]->load(dir);

    mLabel[screen]->setPixmap(*mImage[screen]);
    //mLabel[screen]->adjustSize();
    //this->resize(1280,720);
    //this->adjustSize();
}

void MainWindow::openAP()
{
    openFile(Screen::AP);
}

void MainWindow::openLAT()
{
    openFile(Screen::LAT);
}

void MainWindow::scaleImage(double factor)
{
    QLabel* screen = nullptr;
    if (mZoomScreen == Screen::AP)
    {
//        screen = ui->APLabel;
    }
    else // mZoomScreen == ZoomScreen::LAT
    {
//        screen = ui->LATLabel;
    }

    if (screen == nullptr)
    {
        return;
    }


    qDebug() << factor;

//    int w = ui->APLabel->width();
//    int h = ui->APLabel->height();

//    qDebug() << "input" << w << "," << h;

//    w *= factor;
//    h *= factor;
//    qDebug() << "output" <<w << "," << h;

//    ui->APLabel->setPixmap(mImage[mZoomScreen]->scaled(w, h, Qt::KeepAspectRatio));
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

void MainWindow::zoomIn()
{
    scaleImage(1.25);
}

void MainWindow::zoomOut()
{
    scaleImage(0.8);
}
