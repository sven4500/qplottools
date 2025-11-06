#pragma once
#ifndef WIDGET_H
#define WIDGET_H

#define _USE_MATH_DEFINES

#include <cmath>

#include <QGridLayout>
#include <QObject>
#include <QPointF>
#include <QWidget>

#include <graph2d.h>

class Widget: public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructs new widget class.
     * \param parent widgets parent.
     */
    Widget(QWidget* parent = nullptr);

private:
    /*!
     * \brief addSine
     * \param graph
     */
    static int addSine(Graph2D<float>* graph, int points = 100);

    static void addCurve2(Graph2D<float>* graph);

    static void addCurve3(Graph2D<float>* graph);

    Graph2D<float>* m_graph;

};

#endif
