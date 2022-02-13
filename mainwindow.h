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
  QPointF basePoint;
  View* view[2];
  QPointF defaultBaseLinePoint[2] = {
      {DEFAULT_BASELINE_AP_X, DEFAULT_BASELINE_AP_Y},
      {DEFAULT_BASELINE_LAT_Z, DEFAULT_BASELINE_LAT_Y} };
  QGraphicsScene* scene[2];
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
  bool openImage(const QString dir[2]);
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
