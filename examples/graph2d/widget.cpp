#include "widget.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent)
{
    m_graph = new Graph2D<float>(this);
    m_graph->setLimX(-M_PI, M_PI * 2);
    m_graph->setLimY(-0.5, 1.5);

    addSine1(m_graph);
    addSine2(m_graph);
    addSine3(m_graph);

    QGridLayout* const layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_graph, 0, 0);

    setLayout(layout);
    resize(640, 480);
}

int Widget::addSine1(Graph2D<float> *graph)
{
    auto const numPoints = 10;
    QVector<float> y(numPoints);

    for(auto i = 0; i < numPoints; ++i)
    {
        y[i] = std::sin((M_PI / numPoints) * i);
    }

    auto const id = graph->addCurve(y, Qt::red);
    graph->setStyle(id, Qt::DashLine);
    graph->setWidth(id, 2);

    return id;
}

int Widget::addSine2(Graph2D<float> *graph)
{
    auto const numPoints = 200;
    QVector<float> x(numPoints), y(numPoints);

    for(auto i = 0; i < numPoints; ++i)
    {
        x[i] = (M_PI / numPoints) * i;
        y[i] = std::sin(x[i]);
    }

    auto const id = graph->addCurve(x, y);
    graph->setWidth(id, 3);

    return id;
}

int Widget::addSine3(Graph2D<float> *graph)
{
    auto const numPoints = 200;
    QVector<QPointF> xy(numPoints);

    for(auto i = 0; i < numPoints; ++i)
    {
        xy[i].setX((M_PI / numPoints) * i);
        xy[i].setY(std::cos(xy[i].x()));
    }

    auto const id = graph->addCurve(xy, Qt::blue);
    graph->setColor(id, Qt::green);

    return id;
}
