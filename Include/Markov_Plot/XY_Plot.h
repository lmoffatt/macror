#ifndef XY_PLOT_H
#define XY_PLOT_H
#include <QString>
#include <QVector>
#include <QGraphicsObject>
#include <QPainter>

#include "Markov_Plot/Scale.h"

namespace Markov_Plot

{
class XY_Plot: public QGraphicsObject, public Markov_IO::Implements_Complex_Var
{
    Q_OBJECT
public:

    virtual  QString Title()const;

    virtual void  Title(const QString& newTitle);


    enum Symbol{NoSymbol,
                TriangleUp,
                TriangleDown,
                Star,
                Circle,
                Square,
                Diamond};


    Qt::PenStyle getLineStyle()const;
    void setLineStyle(Qt::PenStyle lineStyle);

    Symbol getSymbol()const;
    void setSymbol(Symbol symbol);


    XY_Plot(Markov_IO::ABC_Data* e,
            const Markov_LA::M_Matrix<double>* x,
                     const Markov_LA::M_Matrix<double>* y,
                     QString title,
                     Scale* xAxis,
                     Scale* yAxis, int col=0);


    qreal Length()const;
    qreal Width()const;


    Scale* xAxis();
    Scale* yAxis();
    const Scale* xAxis()const;
    const Scale* yAxis()const;




    QRectF boundingRect() const;


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

 protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

 protected slots:
    void reset();

 private:
    void computexyPos();
    //void computexyPosTrace();
    void drawSymbols(QPainter* painter);
    void drawLines(QPainter* painter);


    Scale* xAxis_; //not owned
    Scale* yAxis_; //not owned

    qreal penWidth_;

    QString title_;

    const Markov_LA::M_Matrix<double>* x_;//not  owned
    const Markov_LA::M_Matrix<double>* y_;//not  owned

    int icol;
    //const Markov_IO::ABC_trace* trace_; //not owned




    QVector<QPointF> points_;
    QVector<QLineF> pointLines_;
    Symbol symbol_;
    qreal symbolSize_;
    Qt::PenStyle lineStyle_;
    QVector<QColor> lineColors_;


};


}



#endif // XY_PLOT_H
