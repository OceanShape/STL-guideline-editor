#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>

class view : public QGraphicsView
{
    Q_OBJECT
public:
    explicit view(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // VIEW_H
