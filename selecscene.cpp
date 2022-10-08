#include "selecscene.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QPixmap>
#include "mainscene.h"
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include "playscene.h"
#include<QSoundEffect>

SelecScene::SelecScene(QWidget *parent)
    : QMainWindow{parent}
{
    //创建窗口
    this->setFixedSize(320, 588);
    this->setWindowTitle("选择关卡");
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    QMenuBar *menubar = menuBar();
    this->setMenuBar(menubar);
    QMenu *startmenu = menubar->addMenu("开始");
    QAction *quitaction = startmenu->addAction("退出");

    connect(quitaction, &QAction::triggered, [=](){
        this->close();
    });
    //返回音效
    QSoundEffect * backSound1 = new QSoundEffect(this);
    backSound1->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    backSound1->setLoopCount(QSoundEffect::Infinite);
    backSound1->setVolume(0.25f);
    backSound1->setLoopCount(1);
    //添加返回上一页按钮
    backBtn = new MyButton(this, ":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->move(this->width()-backBtn->width(), this->height()-backBtn->height());
    connect(backBtn, &QPushButton::clicked, [=](){
        backSound1->play();
        QTimer::singleShot(200, this, [=](){
            emit this->backToMainScene();
        });
    });
    //选择关卡音效
    QSoundEffect * selectSound = new QSoundEffect(this);
    selectSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    selectSound->setLoopCount(QSoundEffect::Infinite);
    selectSound->setVolume(0.25f);
    selectSound->setLoopCount(1);
    //关卡按钮
    for(int i=0;i<20;i++)
    {
        MyButton * menubtn = new MyButton(this, ":/res/LevelIcon.png");
        menubtn->move(25+(i%4)*70, 130+(i/4)*70);
        //添加数字标签
        QLabel * label = new QLabel(QString::number(i+1), this);
        label->setFixedSize(menubtn->width(), menubtn->height());
        label->move(25+(i%4)*70, 130+(i/4)*70);
        label->setAlignment(Qt::AlignCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        connect(menubtn, &MyButton::clicked, [=](){
            selectSound->play();
            this->hide();
            playScene = new PlayScene(this, i+1);
            playScene->setGeometry(this->geometry());
            playScene->show();

            connect(playScene, &PlayScene::backToSelecScene, [=](){
                playScene->close();
                this->setGeometry(playScene->geometry());
                delete playScene;
                this->show();
            });
        });


    }
}

void SelecScene::paintEvent(QPaintEvent *)
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
