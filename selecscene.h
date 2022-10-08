#ifndef SELECSCENE_H
#define SELECSCENE_H

#include <QMainWindow>
#include "mybutton.h"
#include "playscene.h"

class SelecScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit SelecScene(QWidget *parent = nullptr);
    //绘图事件用来绘制背景等
    void paintEvent(QPaintEvent *);

private:
    MyButton * backBtn;
    //维护游戏场景的指针
    PlayScene * playScene;
signals:
    void backToMainScene();
};

#endif // SELECSCENE_H
