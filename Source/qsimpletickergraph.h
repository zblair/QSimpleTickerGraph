#ifndef Q_SIMPLE_TICKET_GRAPH_H
#define Q_SIMPLE_TICKET_GRAPH_H

#include <QtCore/QPair>
#include <QtCore/QQueue>
#include <QtGui/QBrush>
#include <QtGui/QFont>
#include <QtGui/QPen>
#include <QtGui/QWidget>

class QSimpleTickerGraph : public QWidget
{
    Q_OBJECT

public:
    explicit QSimpleTickerGraph(QWidget *parent = 0);
    void paintEvent(QPaintEvent* pEvent);

    // Data-related parameters
    void setUnits(const QString& unit);
    QString units() const;
    void setRange(double min, double max);
    QPair<double, double> range() const;

    // Style-related parameters
    void setBackgroundBrush(const QBrush& brush);
    QBrush backgroundBrush() const;
    void setGridPen(const QPen& pen);
    QPen gridPen() const;
    void setDataLinePen(const QPen& pen);
    QPen dataLinePen() const;
    void setLabelFont(const QFont& font);
    QFont labelFont() const;

    // Adding/clearing data points
    void appendPoint(double point);
    void clear();

private:
    // Data points
    QQueue<double> mData;
    int mDataCount;
    QString mUnits;

    // Data range visible in graph
    double mMin;
    double mMax;

    // Style
    QBrush mBackgroundBrush;
    QPen mGridPen;
    QPen mDataLinePen;
    QFont mLabelFont;
};

#endif // Q_SIMPLE_TICKET_GRAPH_H
