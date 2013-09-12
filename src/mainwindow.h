#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Game* gm;
    void setupGame();
    QLabel* scoreOne;
    QLabel* scoreTwo;
    QPushButton* endGame;
protected:
    void timerEvent(QTimerEvent *event);
public slots:
    void changeScore(int score, PrPlayer* player);
    void newTurn();
private slots:
    void on_opttionsBtn_clicked();
    void on_playBtn_clicked();
    void on_playBtn_2_clicked();
    void on_playBtn_3_clicked();
    void on_pushButton_clicked();
    void endGameSlot();
    void on_highscores_clicked();
    void on_closeHigh_clicked();

private:
    Ui::MainWindow *ui;
    int timerId;
    int fragileProb;
    int morphProb;
    int multiProb;
    void getProbs();
};

#endif // MAINWINDOW_H
