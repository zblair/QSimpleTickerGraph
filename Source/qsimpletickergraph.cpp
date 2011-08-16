#include <QtGui/QPainter>
#include "qsimpletickergraph.h"

const int GRAPH_GRID_PITCH = 10;
const int LABEL_MARGIN = 2;
const int DEFAULT_FONT_SIZE = 12;

QSimpleTickerGraph::QSimpleTickerGraph(QWidget *parent) : QWidget(parent),
    mDataCount(0),
    mMin(0),
    mMax(100),
    mBackgroundBrush(QBrush(Qt::white)),
    mGridPen(QColor(0, 128, 64)),
    mDataLinePen(QColor(0, 255, 0)),
    mLabelFont("Arial", DEFAULT_FONT_SIZE)
{
}

void QSimpleTickerGraph::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // Draw the background
    painter.setBrush(mBackgroundBrush);
    painter.fillRect(rect(), Qt::SolidPattern);

    // Draw the grid lines
    painter.setPen(mGridPen);
    for (int x = -mDataCount % GRAPH_GRID_PITCH;
         x < width();
         x += GRAPH_GRID_PITCH)
        painter.drawLine(QPointF(x, 0), QPoint(x, height()));

    for (int y = 0;
         y < height();
         y += GRAPH_GRID_PITCH)
        painter.drawLine(QPointF(0, y), QPoint(width(), y));

    double scale = height() / (mMax - mMin);

    // Draw the data lines
    painter.setPen(mDataLinePen);
    for (int i = 1;
         i < mData.size();
         i++)
    {
        double prev = height() - scale * (mData.at(i-1) - mMin);
        double val = height() - scale * (mData.at(i) - mMin);
        painter.drawLine(QPointF(width() - mData.size() + i-1, prev), QPointF(width() - mData.size() + i, val));
    }

    // Draw the current value as text
    if (!mData.isEmpty())
    {
        QString current = QString("%1 %2")
                          .arg(mData.last(), 3, 'f', 3)
                          .arg(mUnits);
        painter.setPen(Qt::white);
        painter.setFont(mLabelFont);
        painter.drawText(rect().adjusted(LABEL_MARGIN, LABEL_MARGIN, -LABEL_MARGIN, -LABEL_MARGIN), Qt::AlignTop | Qt::AlignLeft, current);
    }
}

void QSimpleTickerGraph::appendPoint(double point)
{
    mData.enqueue(point);
    if (mData.size() > width())
        mData.dequeue();
    mDataCount ++;

    update();
}

void QSimpleTickerGraph::clear()
{
    mData.clear();
    mDataCount = 0;
    update();
}

void QSimpleTickerGraph::setUnits(const QString& units)
{
    if (units != mUnits)
    {
        mUnits = units;
        if (!mData.isEmpty())
            update();
    }
}

QString QSimpleTickerGraph::units() const
{
    return mUnits;
}

void QSimpleTickerGraph::setRange(double min, double max)
{
    if (min != mMin || max != mMax)
    {
        mMin = min;
        mMax = max;
        if (!mData.isEmpty())
            update();
    }
}

QPair<double, double> QSimpleTickerGraph::range() const
{
    return QPair<double, double>(mMin, mMax);
}

void QSimpleTickerGraph::setBackgroundBrush(const QBrush& brush)
{
    if (brush != mBackgroundBrush)
    {
        mBackgroundBrush = brush;
        update();
    }
}
QBrush QSimpleTickerGraph::backgroundBrush() const
{
    return mBackgroundBrush;
}

void QSimpleTickerGraph::setGridPen(const QPen& pen)
{
    if (pen != mGridPen)
    {
        mGridPen = pen;
        update();
    }
}
QPen QSimpleTickerGraph::gridPen() const
{
    return mGridPen;
}
void QSimpleTickerGraph::setDataLinePen(const QPen& pen)
{
    if (pen != mDataLinePen)
    {
        mDataLinePen = pen;
        if (!mData.isEmpty())
            update();
    }
}
QPen QSimpleTickerGraph::dataLinePen() const
{
    return mDataLinePen;
}
void QSimpleTickerGraph::setLabelFont(const QFont& font)
{
    if (font != mLabelFont)
    {
        mLabelFont = font;
        if (!mData.isEmpty())
            update();
    }
}
QFont QSimpleTickerGraph::labelFont() const
{
    return mLabelFont;
}
