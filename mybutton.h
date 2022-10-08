#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QEvent>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit StartButton(QWidget *parent = nullptr);
    explicit MyButton(QWidget *parent = nullptr, QString nI="", QString pI="");

    void pressAnimation(); //设置按下动画效果
    void releaseAnimation(); //设置释放动画效果
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QString normalImg; //通常情况下的图片
    QString pressImg; //按下时
signals:

};

#endif // MYBUTTON_H
