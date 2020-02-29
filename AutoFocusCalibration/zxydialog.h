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

private slots:
    void ZSlotCallData();
private:
    QLabel *m_llTips[2];
    QLabel *m_llXY[2];
    QToolButton *m_tb[2];
    QGridLayout *m_gridLayout;
};

#endif // ZXYDIALOG_H
