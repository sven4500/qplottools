#include "widget.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent)
{
    m_graph = new Graph2D<float>(this);
    //m_graph->setLimX(-M_PI, M_PI * 2);

    auto const id1 = addSine(m_graph, 200);
    m_graph->setStyle(id1, Qt::DashLine);
    m_graph->setWidth(id1, 2);

    addCurve2(m_graph);
    addCurve3(m_graph);

    QGridLayout* const layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_graph, 0, 0);

    setLayout(layout);
    resize(640, 480);
}

int Widget::addSine(Graph2D<float> *graph, int points)
{
    QVector<float> y(points);

    for(auto i = 0; i < points; ++i)
    {
        y[i] = std::sin((M_PI / points) * i);
    }

    auto const id = graph->addCurve(y, Qt::red);
    return id;
}

void Widget::addCurve2(Graph2D<float> *graph)
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
}

void Widget::addCurve3(Graph2D<float> *graph)
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
}
