#include "mycoin.h"
#include <QPixmap>
#include <QMessageBox>

MyCoin::MyCoin(QWidget *parent, QString coinImg)
    : QPushButton{parent}, min(1), max(8)
{
    //设置图片显示
    QPixmap pix;
    if(!pix.load(coinImg))
    {
        QMessageBox::critical(this,"加载失败", "硬币图片加载失败！！！");
        return ;
    }
    this->setFixedSize(pix.width(), pix.height());
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));
    this->setStyleSheet("QPushButton {border: 0px;}");

    //初始化定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    //监听
    connect(timer1, &QTimer::timeout, [=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(min++);
        if(!pix.load(str))
        {
            QMessageBox::critical(this,"加载失败", "硬币图片加载失败！！！");
            return ;
        }
        this->setFixedSize(pix.width(), pix.height());
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        this->setStyleSheet("QPushButton {border: 0px;}");
        //停止计时
        if(min>max)
        {
            timer1->stop();
            flag=0;
            min=1;
        }
    });
    connect(timer2, &QTimer::timeout, [=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(max--);
        if(!pix.load(str))
        {
            QMessageBox::critical(this,"加载失败", "硬币图片加载失败！！！");
            return ;
        }
        this->setFixedSize(pix.width(), pix.height());
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        this->setStyleSheet("QPushButton {border: 0px;}");
        //停止计时
        if(min>max)
        {
            timer2->stop();
            flag=1;
            max=8;
        }
    });
}

void MyCoin::changeFlag()
{
    //0银币，1金币，2正在进行中
    if(flag==1)
       {
           flag=2;
           timer1->start(30);
       }
    else if(flag==0)
    {
        flag=2;
        timer2->start(30);
    }
}
