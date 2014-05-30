#include "Markov_Plot/XY_Plot.h"
#include <QGraphicsSceneMouseEvent>
#include <QToolTip>

namespace Markov_Plot
{

QString XY_Plot::Title()const
{
    return title_;
}

void  XY_Plot::Title(const QString& newTitle)
{
    title_=newTitle;
}




Qt::PenStyle XY_Plot::getLineStyle()const
{
    return this->lineStyle_;
}
void XY_Plot::setLineStyle(Qt::PenStyle lineStyle)
{
    lineStyle_=lineStyle;
}


XY_Plot::Symbol XY_Plot::getSymbol()const
{
    return symbol_;
}
void XY_Plot::setSymbol(XY_Plot::Symbol symbol)
{
    symbol_=symbol;
}



XY_Plot::XY_Plot(Markov_IO::ABC_Var* e,
                 const Markov_LA::M_Matrix<double>* x,
                 const Markov_LA::M_Matrix<double>* y,
                 QString title,
                 Scale* xAxis,
                 Scale* yAxis,
                 int col):
  Implements_Complex_Var(e,"","XY_plot",{}),
  xAxis_(xAxis),
    yAxis_(yAxis),

    penWidth_(0),

    title_(title),

    x_(x),
    y_(y),
    icol(col),
    points_(),
    pointLines_(),
    symbol_(XY_Plot::Circle),
    symbolSize_(1),
    lineStyle_(Qt::SolidLine)
    //lineStyle_(Qt::NoPen)
{
    lineColors_<<QColor(Qt::black)
              <<QColor(Qt::green)<<QColor(Qt::blue)<<QColor(Qt::red)
             <<QColor(Qt::cyan)<<QColor(Qt::magenta)<<QColor(Qt::yellow)
             <<QColor(Qt::gray)<<QColor(Qt::lightGray)<<QColor(Qt::darkGray)
            <<QColor(Qt::darkGreen)<<QColor(Qt::darkBlue)<<QColor(Qt::darkRed)
           <<QColor(Qt::darkCyan)<<QColor(Qt::darkMagenta)<<QColor(Qt::darkYellow);

  computexyPos();
  setAcceptHoverEvents(true);
  connect(xAxis_,SIGNAL(rescaled()),this,SLOT(reset()));
  connect(yAxis_,SIGNAL(rescaled()),this,SLOT(reset()));


}



qreal XY_Plot::Length()const
{
    return xAxis_->Length();
}
qreal XY_Plot::Width()const
{
    return yAxis_->Length();
}


QRectF XY_Plot::boundingRect() const
{
    return xAxis_->boundingRect()|yAxis_->boundingRect();
}


void XY_Plot::paint(QPainter *painter,
                    const QStyleOptionGraphicsItem *option,
                    QWidget *widget)
{
    painter->setClipRect(this->boundingRect());
    drawSymbols(painter);
    drawLines(painter);
}


Scale* XY_Plot::xAxis(){
    return xAxis_;
}

Scale* XY_Plot::yAxis(){
    return yAxis_;
}

const Scale* XY_Plot::xAxis()const{
    return xAxis_;
}
const Scale* XY_Plot::yAxis()const{
    return yAxis_;
}




void XY_Plot::computexyPos()
{
    points_.clear();
    pointLines_.clear();
    if (y_!=0)
    {
    for (int i=0; i<Markov_LA::nrows(*x_);i++)
        points_.push_back(QPointF(xAxis_->valueToPos((*x_)(i,0)),
                                  yAxis_->valueToPos((*y_)(i,icol))));
    }
    else
    {
        for (int i=0; i<Markov_LA::nrows(*x_);i++)
            points_.push_back(QPointF(xAxis_->valueToPos((*x_)(i,0)),
                                      yAxis_->valueToPos((*x_)(i,1+icol))));
     }

    for (int i=1; i<points_.size();i++)
        pointLines_.push_back(QLineF(points_.at(i-1),points_.at(i)));

}




void XY_Plot::drawSymbols(QPainter* painter)
{
    switch (symbol_)
    {
    case XY_Plot::NoSymbol:
        break;
    case XY_Plot::Circle:
        for (int i=0; i<points_.size(); i++)
        {
            painter->drawEllipse(points_.at(i),symbolSize_,symbolSize_);
        }
        break;
    case XY_Plot::Square:
        for (int i=0; i<points_.size(); i++)
        {
            painter->drawRect(points_.at(i).x()-symbolSize_,
                              points_.at(i).y()-symbolSize_,
                              points_.at(i).x()+symbolSize_,
                              points_.at(i).y()+symbolSize_);
        }
        break;

    }
}
void XY_Plot::drawLines(QPainter* painter)
{    if (lineStyle_!=Qt::NoPen)
    {
        painter->setPen(lineStyle_);
        painter->setPen(lineColors_[icol%lineColors_.size()]);
        painter->drawLines(pointLines_);
        painter->setPen(lineStyle_);
    }
}



void XY_Plot::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{

    double x=xAxis_->posToValue(event->pos().x());
    double y=yAxis_->posToValue(event->pos().y());

    QString label=QString("x:%1\ny:%2").arg(x).arg(y);
    QToolTip::showText(event->screenPos(),label);

}

void XY_Plot::reset()
{
    computexyPos();
    update();
}

}
