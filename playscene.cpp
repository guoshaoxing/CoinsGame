#include "playscene.h"
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QAction>
#include <QTimer>
#include <QLabel>
#include <QFont>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSoundEffect>

PlayScene::PlayScene(QWidget *parent, int idx)
    : QMainWindow{parent}, levelIdx(idx), isWin(false)
{
    //创建窗口
    this->setFixedSize(320, 588);
    this->setWindowTitle(QString("第%1关").arg(levelIdx));
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    QMenuBar *menubar = menuBar();
    this->setMenuBar(menubar);
    QMenu *startmenu = menubar->addMenu("开始");
    QAction *quitaction = startmenu->addAction("退出");

    connect(quitaction, &QAction::triggered, [=](){
        this->close();
    });
    //返回音效
    QSoundEffect * backSound2 = new QSoundEffect(this);
    backSound2->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    backSound2->setLoopCount(QSoundEffect::Infinite);
    backSound2->setVolume(0.25f);
    backSound2->setLoopCount(1);
    //添加返回上一页按钮
    backBtn = new MyButton(this, ":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->move(this->width()-backBtn->width(), this->height()-backBtn->height());
    connect(backBtn, &QPushButton::clicked, [=](){
        backSound2->play();
        QTimer::singleShot(200, this, [=](){
            emit this->backToSelecScene();
        });
    });
    //添加关卡Label
    QLabel *label = new QLabel(this);
    label->setText(QString("Level:%1").arg(levelIdx));
    label->setGeometry(30, this->height()-50, 120, 50);
    QFont font("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    //添加胜利label
    QLabel *winLabel = new QLabel(this);
    QPixmap winPix(":/res/LevelCompletedDialogBg.png");
    winLabel->setPixmap(winPix);
    winLabel->setGeometry(0, 0, winPix.width(), winPix.height());
    winLabel->move(this->width()/2-winLabel->width()/2, -winLabel->height());
    //胜利音效
    QSoundEffect * winSound = new QSoundEffect(this);
    winSound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));
    winSound->setLoopCount(QSoundEffect::Infinite);
    winSound->setVolume(0.25f);
    winSound->setLoopCount(1);
    //翻硬币音效
    QSoundEffect * coinSound = new QSoundEffect(this);
    coinSound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));
    coinSound->setLoopCount(QSoundEffect::Infinite);
    coinSound->setVolume(0.25f);
    coinSound->setLoopCount(1);
    //创建金币背景与初始化金币
    DataConfig dc;
    if(dc.mData.find(levelIdx)==dc.mData.end()) return;
    rows=dc.mData[levelIdx].size();
    cols=dc.mData[levelIdx][0].size();
    coins.resize(rows);
    for(int i=0;i<rows;i++) coins[i].resize(cols);
    for(int j=0;j<rows;j++)
    {
        for(int i=0;i<cols;i++)
        {
            //QLabel显示图片
            QLabel * bg = new QLabel(this);
            QPixmap pix(":/res/BoardNode.png");
            bg->setGeometry(0, 0, pix.width(), pix.height());
            bg->setPixmap(pix);
            bg->move(57+i*50, 200+j*50);
            //创建金币(显示)
            QString str;
            if(!dc.mData[levelIdx].isEmpty() && dc.mData[levelIdx][j][i]==1)
            {
                str=":/res/Coin0001.png";
            }
            else if(!dc.mData[levelIdx].isEmpty() && dc.mData[levelIdx][j][i]==0)
            {
                str=":/res/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(this, str);
            coin->move(59+i*50, 202+j*50);
            coin->posX=i;
            coin->posY=j;
            coin->flag=dc.mData[levelIdx][j][i];
            coins[j][i]=coin;

            connect(coin, &QPushButton::clicked, [=](){
                if(isWin) return;
                coinSound->play();
                coin->changeFlag();
                //周围的也要变
                if(j-1>=0) coins[j-1][i]->changeFlag();
                if(j+1<rows) coins[j+1][i]->changeFlag();
                if(i-1>=0) coins[j][i-1]->changeFlag();
                if(i+1<cols) coins[j][i+1]->changeFlag();
                //检查如果全变金币了就游戏过关
                isWin=true;
                for(int j=0; j<rows; j++)
                {
                    for(int i=0; i<cols; i++)
                    {
                        if(coins[j][i]->flag==0)
                        {
                            //有银币
                            isWin=false; break;
                        }
                    }
                }
                if(isWin)
                {
                    //添加胜利动效
                    winSound->play();
                    QPropertyAnimation *winAnimation=new QPropertyAnimation(winLabel, "geometry");
                    winAnimation->setDuration(1000);
                    winAnimation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                    winAnimation->setEndValue(QRect(winLabel->x(), winLabel->y()+114, winLabel->width(), winLabel->height()));
                    winAnimation->setEasingCurve(QEasingCurve::OutBounce);
                    winAnimation->start();
                }
            });
        }
    }

}

void PlayScene::paintEvent(QPaintEvent *)
{
    //画画需要有画家
    //1、画背景
    QPainter painter(this);
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    //2、画标题，开始
    pix.load(":/res/Title.png");
    painter.drawPixmap(10, 30, pix);
}
