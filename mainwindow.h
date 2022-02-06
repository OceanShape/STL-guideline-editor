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

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = Q_NULLPTR);
  MainWindow::~MainWindow();

 private:
  Ui::MainWindowClass ui;
  QString imageFileName[2];
  GlobalState& gs = GlobalState::getIncetance();
 private slots:
  void setPointText(QTextBrowser* tb1, QTextBrowser* tb2, const point& p);
  void setSpinousProcessPointText(QTextBrowser* tb1, QTextBrowser* tb2,
                                  QTextBrowser* tb3, const point& apPoint,
                                  const point& latPoint);
  void setBaseLineText(QTextBrowser* tb1, QTextBrowser* tb2,
                       const QGraphicsLineItem* baseLineX,
                       const QGraphicsLineItem* baseLineY);
  void setAngleAPText(QTextBrowser* alpha);
  void setAngleLATText(QTextBrowser* alpha, QTextBrowser* beta);
  void setSpineRotateText(QTextBrowser* tb, const int& spineIdx);
  void New();
  void Open();
  void Close();
  void Update();
  void Save();
  void BaseLine();
  void Spine();
  void SpinousProcess();
  void Pelvis();
  void Tailbone();
};
