#ifndef ZRSSIUI_H
#define ZRSSIUI_H

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
class ZRssiUI : public QWidget
{
    Q_OBJECT
public:
    explicit ZRssiUI(QWidget *parent = nullptr);
    ~ZRssiUI();
signals:

public slots:

private:
    QToolButton *m_tb[10];
    QVBoxLayout *m_vLayout;
};

#endif // ZRSSIUI_H
