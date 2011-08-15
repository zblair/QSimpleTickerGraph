#ifndef Q_SIMPLE_TICKET_GRAPH_H
#define Q_SIMPLE_TICKET_GRAPH_H

#include <QtCore/QQueue>
#include <QtGui/QWidget>

class QSimpleTickerGraph : public QWidget
{
    Q_OBJECT

public:
    explicit QSimpleTickerGraph(QWidget *parent = 0);
    void paintEvent(QPaintEvent* pEvent);

    void setUnits(const QString& unit);
    QString units() const;
    void setFontSize(int size);
    int fontSize() const;
    void setRange(double min, double max);

    void appendPoint(double point);
    void clear();

private:
    QQueue<double> mData;
    int mDataCount;

    int mFontSize;
    QString mUnits;

    double mMin;
    double mMax;
};

#endif // Q_SIMPLE_TICKET_GRAPH_H
