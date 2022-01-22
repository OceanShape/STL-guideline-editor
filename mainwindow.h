#pragma once

#define UTC_TIME_ASIA_SEOUL 9 * 60 * 60

#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QInputDialog>
#include <QLabel>
#include <QLineedit>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>

#include "ui_mainwindow.h"
#include "GlobalState.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = Q_NULLPTR);
  MainWindow::~MainWindow();
  void update();

 private:
  Ui::MainWindowClass ui;
  QString imageFileName[2];
 private slots:
  void New();
  void Open();
  void Save();
  void Close();
  void BaseLine();
  void Spine();
  void SpinousProcess();
  void Pelvis();
  void Tailbone();
};
