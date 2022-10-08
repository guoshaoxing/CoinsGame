#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QPixmap>
#include "mybutton.h"
#include "selecscene.h"
#include <QDebug>
#include <QTimer>
#include <QSoundEffect>


MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //创建开始按钮（注意，要一直显示，所有要建在堆上）
    MyButton * startButton = new MyButton(this, ":/res/MenuSceneStartButton.png");
    startButton->move(this->width()*0.5-startButton->width()*0.5, this->height()*0.7);
    //创建音效
    QSoundEffect *startSound = new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    startSound->setLoopCount(QSoundEffect::Infinite);
    startSound->setVolume(0.25f);
    startSound->setLoopCount(1);

    //创建选关页面
    selectionScene = new SelecScene(this);

    connect(startButton, &MyButton::clicked, [=](){
        startButton->pressAnimation();
        startSound->play();
        startButton->releaseAnimation();

        QTimer::singleShot(400, this, [=](){
            //延时进入下一场景
            this->hide();
            selectionScene->setGeometry(this->geometry());
            selectionScene->show();
        });
    });

    connect(selectionScene, &SelecScene::backToMainScene, [=](){
        selectionScene->hide();
        this->setGeometry(selectionScene->geometry());
        this->show();
    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    //画画需要有画家
    //1、画背景
    QPainter painter(this);
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    //2、画标题，开始
    pix.load(":/res/Title.png");
//    pix.scaled(pix.width()*0.5, pix.height()*0.5);
    painter.drawPixmap(10, 30, pix.width()*0.5, pix.height()*0.5, pix);
}
