#ifndef ZBUTTONDIALOG_H
#define ZBUTTONDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QHBoxLayout>
#include <QMap>
class ZButtonDialog : public QDialog
{
    Q_OBJECT
public:
    ZButtonDialog(QWidget *parent=0);
    ~ZButtonDialog();

    void ZAddButton(QToolButton *btn,qint32 bindNum);
    qint32 ZGetClickedBindNum();
private slots:
    void ZSlotBtnClicked();
private:
    QMap<QToolButton*,qint32> m_map;
    QHBoxLayout *m_hLayout;
    qint32 m_clickedBindNum;
};
class ZDataDialog:public ZButtonDialog
{
    Q_OBJECT
public:
    ZDataDialog(QWidget *parent=0);
    ~ZDataDialog();
private:
    QToolButton *m_btnCallOne;
    QToolButton *m_btnCallAll;

    QToolButton *m_btnLoad;
    QToolButton *m_btnSave;
    QToolButton *m_btnMdy;
};
#endif // ZBUTTONDIALOG_H
