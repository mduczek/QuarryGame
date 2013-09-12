#ifndef STSTONE_H
#define STSTONE_H

#include <QWidget>
#include <QtGui>

struct StColor{
    QString path;
    int value;
};

class StStone : public QWidget
{
    Q_OBJECT
public:
    explicit StStone(QWidget *parent = 0);
    static void initialise();
    static StColor colors [6];
    static int colorNum;
    virtual bool matches(StStone*);
    virtual int multiplyer();
    static const int size = 50;
    virtual void setColor(StColor);
    virtual int getValue();
    virtual void changeColor();
    StColor color;
    virtual bool toBeDeleted(){return false;}
protected:
    QPixmap* pict;
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
signals:
    void clicked(StStone* me);
public slots:
    virtual void newTurn(){return;}
};

enum StTypes{
    Multi, Morph, Gold, Mud, Fragile, Normal
};



#endif // STSTONE_H
