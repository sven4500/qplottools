#pragma once
#ifndef QPLOTTOOLS_AXES2D_H_
#define QPLOTTOOLS_AXES2D_H_

#include <cmath> // floor, pow, abs, ...

#include <QMouseEvent>
#include <QPoint>
#include <QPointF>
#include <QRect>

#include "abstractpainter.h"
#include "viewregion2d.h"

class Axes2D: public AbstractPainter
{
    Q_OBJECT

signals:
    void pixelClicked(int x, int y);

public:
    Axes2D(QWidget* parent = nullptr)
        : AbstractPainter(parent)
        , m_numTicks(10)
    {
        makeNiceStep();
        setMouseTracking(true);
    }

    bool setLimX(double min, double max)
    {
        if(max <= min)
            return false;

        m_viewRegion.minX = min;
        m_viewRegion.maxX = max;

        makeNiceStep();
        update();

        return true;
    }

    bool setLimY(double min, double max)
    {
        if(max <= min)
            return false;

        m_viewRegion.minY = min;
        m_viewRegion.maxY = max;

        makeNiceStep();
        update();

        return true;
    }

    static double niceNumber(double number, bool round)
    {
        // note: Graphic Gems Vol.1 p.62
        int exp = std::floor(std::log10(number));
        double f = number / std::pow(10.0, exp);
        double nf;

        if(round)
        {
            if(f < 1.5)
                nf = 1.0;
            else if(f < 3.0)
                nf = 2.0;
            else if(f < 7.0)
                nf = 5.0;
            else
                nf = 10.0;
        }
        else
        {
            if(f <= 1.0)
                nf = 1.0;
            else if(f <= 2.0)
                nf = 2.0;
            else if(f <= 5.0)
                nf = 5.0;
            else
                nf = 10.0;
        }

        return nf * std::pow(10.0, exp);
    }

protected:
    virtual void mousePressEvent(QMouseEvent* event)
    {
        if(event->button() == Qt::LeftButton)
        {
            setCursor(Qt::CrossCursor);
            m_rubberband.setTopLeft(event->pos());
            m_rubberband.setBottomRight(event->pos());
        }
        else
        if(event->button() == Qt::RightButton)
        {
            setCursor(Qt::ClosedHandCursor);
            m_dragPoint = toPoint(event->pos());
        }
    }

    virtual void mouseReleaseEvent(QMouseEvent* event)
    {
        if(event->button() == Qt::LeftButton)
        {
            unsetCursor();

            QPointF const topLeft = toPoint(m_rubberband.topLeft());
            QPointF const bottomRight = toPoint(m_rubberband.bottomRight());

            m_viewRegion.minX = std::min(topLeft.x(), bottomRight.x());
            m_viewRegion.maxX = std::max(topLeft.x(), bottomRight.x());

            m_viewRegion.minY = std::min(topLeft.y(), bottomRight.y());
            m_viewRegion.maxY = std::max(topLeft.y(), bottomRight.y());

            // Выделяющий прямоугольник больше не будет отрисован.
            m_rubberband.setTopLeft(event->pos());
            m_rubberband.setBottomRight(event->pos());

            makeNiceStep();
            update();

            emit pixelClicked(event->pos().x(), event->pos().y());
        }
        else if(event->button() == Qt::RightButton)
        {
            unsetCursor();
            update();
        }
    }

    virtual void mouseMoveEvent(QMouseEvent* event)
    {
        if(event->buttons() == Qt::LeftButton)
        {
            if(contentsRect().adjusted(-1, -1, -1, -1).contains(event->pos()))
            {
                m_rubberband.setBottomRight(event->pos());
            }

            update();
        }
        else
        if(event->buttons() == Qt::RightButton)
        {
            QPointF const distance = toPoint(event->pos()) - m_dragPoint;

            if((event->modifiers() & Qt::ShiftModifier) == 0)
            {
                m_viewRegion.minX -= distance.x();
                m_viewRegion.maxX -= distance.x();
            }

            if((event->modifiers() & Qt::ControlModifier) == 0)
            {
                m_viewRegion.minY -= distance.y();
                m_viewRegion.maxY -= distance.y();
            }

            update();
        }
    }

    virtual void wheelEvent(QWheelEvent* event)
    {
        if(!event->angleDelta().isNull())
        {
            QPointF const point = toPoint(event->pos());

            // note: angleDelta returns 1/8 of a degree
            auto const angle = event->angleDelta().y() / 8;

            double const factor = std::abs(angle > 0.0 ? angle / 30.0 : angle / 10.0);

            if((event->modifiers() & Qt::ShiftModifier) == 0)
            {
                double const deltaSpanX = m_viewRegion.spanX() - m_viewRegion.spanX() * factor;

                double const x1 = (point.x() - m_viewRegion.minX) / m_viewRegion.spanX();
                double const x2 = 1.0 - x1;

                m_viewRegion.minX += deltaSpanX * x1;
                m_viewRegion.maxX -= deltaSpanX * x2;
            }

            if((event->modifiers() & Qt::ControlModifier) == 0)
            {
                double const deltaSpanY = m_viewRegion.spanY() - m_viewRegion.spanY() * factor;

                double const y1 = (point.y() - m_viewRegion.minY) / m_viewRegion.spanY();
                double const y2 = 1.0 - y1;

                m_viewRegion.minY += deltaSpanY * y1;
                m_viewRegion.maxY -= deltaSpanY * y2;
            }

            makeNiceStep();
            update();
        }
    }

    double minX()const
    {
        return m_viewRegion.minX;
    }

    double maxX()const
    {
        return m_viewRegion.maxX;
    }

    double minY()const
    {
        return m_viewRegion.minY;
    }

    double maxY()const
    {
        return m_viewRegion.maxY;
    }

    void drawRubberband(QPainter& painter)
    {
        if(std::abs(m_rubberband.width()) > 4 && std::abs(m_rubberband.height()) > 4)
        {
            painter.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
            painter.setPen(Qt::white);
            painter.drawRect(m_rubberband);
        }
    }

    QPoint toPixel(QPointF const& point)const
    {
        QRect const& rect = contentsRect();

        double const kX = m_viewRegion.spanX() / rect.width();
        double const kY = m_viewRegion.spanY() / rect.height();

        int const x = rect.left() + int((point.x() - m_viewRegion.minX) / kX);
        int const y = rect.bottom() - int((point.y() - m_viewRegion.minY) / kY);

        return QPoint(x, y);
    }

    QPointF toPoint(QPoint const& pixel)const
    {
        QRect const& rect = contentsRect();

        double const kX = m_viewRegion.spanX() / rect.width();
        double const kY = m_viewRegion.spanY() / rect.height();

        double const x = (pixel.x() - rect.left()) * kX + m_viewRegion.minX;
        double const y = (rect.bottom() - pixel.y()) * kY + m_viewRegion.minY;

        return QPointF(x, y);
    }

    ViewRegion2D m_viewRegion;

    double m_stepX;
    double m_stepY;

    int m_numTicks;

private:
    void makeNiceStep()
    {
        double const rangeX = niceNumber(m_viewRegion.spanX(), false);
        double const rangeY = niceNumber(m_viewRegion.spanY(), false);

        m_stepX = niceNumber(rangeX / (m_numTicks - 1), true);
        m_stepY = niceNumber(rangeY / (m_numTicks - 1), true);
    }

    QRect m_rubberband;

    QPointF m_dragPoint;

};

#endif
