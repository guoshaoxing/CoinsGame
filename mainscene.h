#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "selecscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //绘图事件用来绘制背景等
    void paintEvent(QPaintEvent *);
private:
    Ui::MainScene *ui;
    SelecScene * selectionScene;
};
#endif // MAINSCENE_H
