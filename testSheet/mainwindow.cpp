#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsRectItem>


QLabel* lb1;
QLabel* lb2;
QLabel* lb3;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* wg = new QWidget();
    MainWindow::setCentralWidget(wg);

    QPixmap pix("./b.png");


    QGraphicsScene* gs = new QGraphicsScene();
    QGraphicsView* gv = new QGraphicsView(gs);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix);
    QGraphicsRectItem* rect = new QGraphicsRectItem(20, 30, 200, 100);
    QPen* p = new QPen(Qt::green);
    p->setWidth(3);
    rect->setPen(*p);
    QGraphicsRectItem* rect2 = new QGraphicsRectItem(50, 60, 100, 100);
    gs->addItem(item);
    gs->addItem(rect);
    gs->addItem(rect2);


    QVBoxLayout* vl = new QVBoxLayout();
    vl->addWidget(gv);
    wg->setLayout(vl);
}

MainWindow::~MainWindow()
{
    delete ui;
}

