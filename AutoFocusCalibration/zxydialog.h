#ifndef ZXYDIALOG_H
#define ZXYDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QLabel>
#include <QGridLayout>
class ZXYDialog : public QDialog
{
    Q_OBJECT
public:
    ZXYDialog(const QPointF &pt,QWidget *parent=0);
    ~ZXYDialog();

    QPointF ZGetPoint() const;
private:
    QLabel *m_llTips[2];
    QLabel *m_llXY[2];
    QToolButton *m_tb[2];
    QGridLayout *m_gridLayout;
private:
    QPointF  m_pt;
};

#endif // ZXYDIALOG_H
