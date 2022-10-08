#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mybutton.h"
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr, int idx=1);
    //绘图事件用来绘制背景等
    void paintEvent(QPaintEvent *);
private:
        MyButton * backBtn;
        int levelIdx;
        int rows, cols;
        bool isWin;
        QVector<QVector<MyCoin*>> coins;
signals:
        void backToSelecScene();
};

#endif // PLAYSCENE_H
