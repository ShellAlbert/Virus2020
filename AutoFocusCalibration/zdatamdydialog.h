#ifndef ZDATAMDYDIALOG_H
#define ZDATAMDYDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
class ZDataMdyDialog : public QDialog
{
    Q_OBJECT
public:
    ZDataMdyDialog(const QList<QPointF> &listPt,QWidget *parent=0);
    ~ZDataMdyDialog();

private slots:
    void ZSlotAdd();
    void ZSlotDel();
    void ZSlotCleanAll();
    void ZSlotOkay();

private:
    QToolButton *m_btnAdd;
    QToolButton *m_btnDel;
    QToolButton *m_btnCleanAll;
    QToolButton *m_btnOkay;
    QHBoxLayout *m_hLayoutBtns;
    QTableWidget *m_tableWidget;
    QVBoxLayout *m_vLayout;
};

#endif // ZDATAMDYDIALOG_H
