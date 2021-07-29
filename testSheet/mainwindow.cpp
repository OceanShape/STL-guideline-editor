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
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* centWidget = new QWidget();
    MainWindow::setCentralWidget(centWidget);

    QGraphicsScene* gs = new QGraphicsScene();
    QGraphicsView* gv = new QGraphicsView(gs);



    QPixmap pix("./b.png");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix);


    QGraphicsRectItem* rect = new QGraphicsRectItem(20, 30, 200, 100);
    QPen* p = new QPen(Qt::green);
    p->setWidth(3);


    rect->setPen(*p);
    gs->addItem(item);
    gs->addItem(rect);




    QVBoxLayout* vl = new QVBoxLayout();
    vl->addWidget(gv);
    centWidget->setLayout(vl);
}

MainWindow::~MainWindow()
{
    delete ui;
}
