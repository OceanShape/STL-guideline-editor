#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "Screen.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    MainWindow::~MainWindow() {}

private:
    Ui::MainWindowClass ui;
    QLabel* lbl[2];
private slots:
    void New();
    void Open();
    void Close();
};
