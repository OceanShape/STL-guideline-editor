#pragma once

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = Q_NULLPTR);
  MainWindow::~MainWindow();

 private:
  Ui::MainWindowClass ui;
 private slots:
  void New();
  void Open();
  void Save();
  void Close();
  void OpenAP();
  void OpenLAT();
};
