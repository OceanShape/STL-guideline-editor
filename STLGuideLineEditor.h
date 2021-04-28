#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_STLGuideLineEditor.h"

class STLGuideLineEditor : public QMainWindow
{
    Q_OBJECT

public:
    STLGuideLineEditor(QWidget *parent = Q_NULLPTR);

private:
    Ui::STLGuideLineEditorClass ui;
};
