#include <QtGui/QPainter>
#include "qsimpletickergraph.h"

const int GRAPH_GRID_PITCH = 10;
const int LABEL_MARGIN = 2;
const int DEFAULT_FONT_SIZE = 12;

QSimpleTickerGraph::QSimpleTickerGraph(QWidget *parent) : QWidget(parent),
    mDataCount(0),
    mFontSize(DEFAULT_FONT_SIZE),
    mMin(0),
    mMax(100)
{
}

void QSimpleTickerGraph::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // Draw the background
    painter.setBrush(QBrush(Qt::white));
    painter.fillRect(rect(), Qt::SolidPattern);

    // Draw the graph lines
    painter.setPen(QColor(0, 128, 64));
    for (int x = -mDataCount % GRAPH_GRID_PITCH; x < width(); x += GRAPH_GRID_PITCH)
        painter.drawLine(QPointF(x, 0), QPoint(x, height()));

    for (int y = 0; y < height(); y += GRAPH_GRID_PITCH)
        painter.drawLine(QPointF(0, y), QPoint(width(), y));

    double scale = height() / (mMax - mMin);

    // Draw the data
    painter.setPen(QColor(0, 255, 0));
    for (int i = 1; i < mData.size(); i++)
    {
        double prev = height() - scale * (mData.at(i-1) - mMin);
        double val = height() - scale * (mData.at(i) - mMin);
        painter.drawLine(QPointF(width() - mData.size() + i-1, prev), QPointF(width() - mData.size() + i, val));
    }

    // Draw the value
    if (!mData.isEmpty())
    {
        QString current = QString("%1 %2")
                          .arg(mData.last(), 3, 'f', 3)
                          .arg(mUnits);
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", mFontSize));
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

void QSimpleTickerGraph::setFontSize(int size)
{
    if (size != mFontSize)
    {
        mFontSize = size;
        if (!mData.isEmpty())
            update();
    }
}

int QSimpleTickerGraph::fontSize() const
{
    return mFontSize;
}

void QSimpleTickerGraph::setRange(double min, double max)
{
    mMin = min;
    mMax = max;
}
