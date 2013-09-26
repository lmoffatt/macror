#ifndef SCALE_H
#define SCALE_H
#include "Markov_Plot/ABC_PlotData.h"

#include <QString>
#include <QVector>
#include <QGraphicsObject>
#include <QPainter>

#include "Markov_IO/ABC_Experiment.h"


namespace Markov_Plot

{
class Scale: public QGraphicsObject
{
    Q_OBJECT
public:
    enum Type
    {
        LinearScale,
        LogScale
    };

    enum RangeCalculation
    {
        ExactRange=0x0,
        Pad5PercentRange=0x1,
        NearestTickRange=0x2
    };

    enum AxisType
    {
        xAxis,
        yAxis
    };


    virtual double valueToPos(double x)const;

    virtual double posToValue(double pos)const;
    virtual qreal posToValue(QGraphicsSceneMouseEvent *event)const;
    virtual qreal posToValue(QGraphicsSceneHoverEvent *event)const;

    virtual void reScale(double min, double max);

    virtual double min()const;
    virtual double max()const;



    virtual  QString Title()const;

    virtual void  Title(const QString& newTitle);

    Type getType()const;
    void setType(Type scaleType);

    Scale(double min,
          double max,
          AxisType axis,
          QString title,
          QString units,
          double length,
          double width,
          Type scaletype
          );



    AxisType getAxisType()const;

    qreal Length()const;
    qreal Width()const;


    QRectF boundingRect() const;


    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);


 signals:
    void rescaled();



 protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);



 private:
    void reset();
    void PadForRange(double percentPadded);
    void buildLinearTicks();
    void buildLogTicks();
    void buildLines();


    void buildLabelPos(QPainter *painter);
    void drawTitle(QPainter* painter);
    void drawLabels(QPainter* painter);


    AxisType axis_;
    Type type_;
    RangeCalculation rangeCalc_;

    qreal length_;
    qreal width_;
    qreal tickLength_;
    qreal penWidth_;

    QString title_;
    QString units_;

    double min_;
    double max_;

    double b_;

    double tickInterval_;
    double minTick_;
    double maxTick_;
    int ticksCount_;

    QVector<double> ticksValue_;
    QVector<qreal> ticksPosition_;

    QVector<QString> labels_;

    QVector<QRectF> labelsPos_;

    QVector<QLineF> tickLines_;
    QLineF axisLine_;

    double nextMin_;
    QPoint nextMinMaxPos_;
};


}
#endif // SCALE_H
