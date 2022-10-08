#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr, QString coinImg="");
    int posX;
    int posY;
    int flag;
    void changeFlag();
    QTimer *timer1, *timer2;
    int min, max;
signals:

};

#endif // MYCOIN_H
