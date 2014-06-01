#ifndef SCALE_H
#define SCALE_H
#include "Markov_Plot/ABC_PlotData.h"

#include <QString>
#include <QVector>
#include <QGraphicsObject>
#include <QPainter>

#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/ABC_Var.h"


namespace Markov_Plot

{
class Scale: public QGraphicsObject, public Markov_IO::Implements_Complex_Var
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
        ExactRange,
        Pad5PercentRange,
        NearestTickRange
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

    Scale(Markov_IO::ABC_Var* e,
          double min,
          double max,
          AxisType axis,
          QString title,
          QString units,
          double length,
          double width,
          Type scaletype);

    Scale():
      Implements_Complex_Var(0,"","Scale",{},"",""){}



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

    static AxisType toAxisType(std::string a);

    static std::string toString(AxisType a);
    static Type toType(std::string a);

    static std::string toString(Type a);


    static RangeCalculation toRangeCalculation(std::string a);

    static std::string toString(RangeCalculation a);




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


    // ABC_Object interface
public:
    virtual std::string myClass() const;

    virtual std::string mySuperClass()const;
    static std::string ClassName();



    virtual ABC_Var*  load_ABC_Var() override
    {
      addVar(new Markov_IO::Implements_Simple_Var<double>(this,"min",min_));
      addVar(new Markov_IO::Implements_Simple_Var<double>(this,"max",max_));
      addVar(new Markov_IO::Implements_Simple_Var<double>(this,"length",length_));
      addVar(new Markov_IO::Implements_Simple_Var<double>(this,"width",width_));
      addVar(new Markov_IO::Implements_Simple_Var<std::string>(
               this,"title",title_.toStdString()));
      addVar(new Markov_IO::Implements_Simple_Var<std::string>(
               this,"units",units_.toStdString()));
      addVar(new Markov_IO::Implements_Categorical_Class(this,"AxisType",{{"xaxis"},{"yaxis"}},"xaxis"));
      addVar(new Markov_IO::Implements_Categorical_Class(
               this,"ScaleType",{{"LinearScale"},{"LogScale"}},"LinearScale"));
      addVar(new Markov_IO::Implements_Categorical(
               this,"axis",static_cast<int>(axis_),"AxisType"));
      addVar(new Markov_IO::Implements_Categorical(
               this,"saletype",static_cast<int>(type_),"ScaleType"));
      return this;

    }

    virtual bool unload_ABC_Var()override
    {
      std::string newtitle;
      std::string newUnits;
      int newaxis;
      int newscaletye;

      if (!getValue("min",min_)) return false;
      if (!getValue("max",max_)) return false;
      if (!getValue("length",length_)) return false;
      if (!getValue("width",width_)) return false;
      if (!getValue("title",newtitle)) return false;
      if (!getValue("units",newUnits)) return false;
      if (!getValue("axis",newaxis)) return false;
      if (!getValue("ScaleType",newscaletye)) return false;

      title_=newtitle.c_str();
      units_=newUnits.c_str();
      axis_=static_cast<Scale::AxisType>(newaxis);
      type_=static_cast<Scale::Type>(newscaletye);
      return true;


    }

};


}
#endif // SCALE_H
