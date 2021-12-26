#pragma once

#define UTC_TIME_ASIA_SEOUL 9 * 60 * 60

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = Q_NULLPTR);
  MainWindow::~MainWindow();

 private:
  Ui::MainWindowClass ui;
  QString imageFileName[2];
 private slots:
  void New();
  void Open();
  void Save();
  void Close();
  void OpenAP();
  void OpenLAT();
};
