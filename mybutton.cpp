#include "mybutton.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QDebug>

MyButton::MyButton(QWidget *parent, QString nI, QString pI)
    : QPushButton(parent), normalImg(nI), pressImg(pI)
{
    QPixmap pix;
    if(!pix.load(normalImg))
    {
        qDebug()<<"normalImg图片加载失败";
        return ;
    }
    //1、设定按钮的大小
    this->setFixedSize(pix.width(), pix.height());
    //2、设置不规则图片的样式
    this->setStyleSheet("QPushButton{border: 0px;}");
    //3、设置图标
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));
}

void MyButton::pressAnimation()
{
    //设置按下动画效果
    QPropertyAnimation *anim = new QPropertyAnimation(this, "geometry");
    //设置间隔时间、开始位置、结束位置
    anim->setDuration(200);
    anim->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    anim->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    anim->setEasingCurve(QEasingCurve::OutBounce);
    anim->start();
}


void MyButton::releaseAnimation()
{
    //设置释放动画效果
    QPropertyAnimation *anim = new QPropertyAnimation(this, "geometry");
    //设置间隔时间、开始位置、结束位置
    anim->setDuration(200);
    anim->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    anim->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    anim->setEasingCurve(QEasingCurve::OutBounce);
    anim->start();
}

void MyButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImg != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImg);
        if(!ret)
        {
            qDebug()<<"图片打开失败！！！";
            return;
        }
        //1、设定按钮的大小
        this->setFixedSize(pix.width(), pix.height());
        //2、设置不规则图片的样式
        this->setStyleSheet("QPushButton{border: 0px;}");
        //3、设置图标
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
    }
    //其余事件交给父亲处理
    QPushButton::mousePressEvent(e);
}

void MyButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->normalImg != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImg);
        if(!ret)
        {
            qDebug()<<"图片打开失败！！！";
            return;
        }
        //1、设定按钮的大小
        this->setFixedSize(pix.width(), pix.height());
        //2、设置不规则图片的样式
        this->setStyleSheet("QPushButton{border: 0px;}");
        //3、设置图标
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
    }
    //其余事件交给父亲处理
    QPushButton::mouseReleaseEvent(e);
}
