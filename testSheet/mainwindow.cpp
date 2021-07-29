#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* centWidget = new QWidget();
    MainWindow::setCentralWidget(centWidget);

    QGraphicsScene* gs = new QGraphicsScene();
    View* gv = new View();


    QPixmap pix("./a.png");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix);
    gs->addItem(item);


    gv->setScene(gs);
    QHBoxLayout* hl = new QHBoxLayout();
    hl->addWidget(gv);
    centWidget->setLayout(hl);
}

MainWindow::~MainWindow()
{
    delete ui;
}
