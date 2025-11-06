#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <vector>
#include <gradientmap.h>

class Widget: public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    virtual ~Widget();

private slots:
    void updateFps();
    void catchPoint(int x, int y);

private:
    virtual void keyPressEvent(QKeyEvent* event);

    //std::vector<float*> _fvect;
    std::vector<int*> _ivect;

    //GradientMap<float>* _gmap;
    GradientMap<int>* _gmap;

    QTimer* _timer;

    QLabel* _FPSlabel;
    QLabel* _pointLabel;

    int _frames;

};

#endif
