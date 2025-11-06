#pragma once
#ifndef ABSTRACTPAINTER_H
#define ABSTRACTPAINTER_H

#include <QPainter>
#include <QVector>
#include <QWidget>

/*!
 * \brief The AbstractPainter class implements painter queue. Children should
 * not override paintEvent and should add painting stages to queue by calling
 * addToPaintQueue instead.
 */
class AbstractPainter: public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Stops painter queue by setting skip flag to true.
     */
    void stopPainter()
    {
        m_skipPainter = true;
    }

    /*!
     * \brief Resumes painter queue by setting skip flag to false.
     */
    void resumePainter()
    {
        m_skipPainter = false;
        update();
    }

protected:
    typedef void (AbstractPainter::*PaintFunc)(QPainter& painter);

    /*!
     * \brief Builds default AbstractPainter class.
     * \param parent widgets parent.
     */
    AbstractPainter(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        auto pal = palette();
        pal.setColor(QPalette::Window, Qt::white);

        setPalette(pal);
    }

    /*!
     * \brief Runs painter queue by calling consequently each PaintFunc in
     * queue.
     * \param event unused QPaintEvent argument.
     */
    virtual void paintEvent(QPaintEvent* event) final
    {
        Q_UNUSED(event);

        if(m_skipPainter)
            return;

        QPainter painter(this);

        paintBackground(painter);

        if(contentsRect().isValid())
        {
            for(auto paintFunc : m_paintQueue)
            {
                painter.save();
                (this->*paintFunc)(painter);
                painter.restore();
            }
        }
    }

    /*!
     * \brief Adds PaintFunc to queue. This function is called by children to
     * build a painter queue.
     * \param func painter stage function.
     */
    void addToPaintQueue(PaintFunc func)
    {
        m_paintQueue.append(func);
    }

    /*!
     * \brief Removes all ocurences of painter function from queue.
     * \param func painter stage function to remove.
     */
    void removeFromPaintQueue(PaintFunc func)
    {
        m_paintQueue.removeAll(func);
    }

    /*!
     * \brief Clears painter queue.
     */
    void clearPaintQueue()
    {
        m_paintQueue.clear();
        //update();
    }

    void paintBackground(QPainter& painter)
    {
        // todo: add customizable background color
        painter.fillRect(0, 0, width(), height(), palette().window());
    }

private:
    QVector<PaintFunc> m_paintQueue;
    bool m_skipPainter = false;

};

#endif
