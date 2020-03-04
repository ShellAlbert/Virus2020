#ifndef ZVIDEOUI_H
#define ZVIDEOUI_H

#include <QWidget>
#include <QPainter>
class ZVideoUI : public QWidget
{
    Q_OBJECT
public:
    explicit ZVideoUI(QWidget *parent = nullptr);

protected:
    QSize sizeHint() const;
    void paintEvent(QPaintEvent *e);
signals:

public slots:
};

#endif // ZVIDEOUI_H
