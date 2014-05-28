#include "Markov_Plot/Scale.h"
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/auxiliarMath.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneHoverEvent>
#include <QToolTip>

namespace Markov_Plot
{

QString Scale::Title()const
{
    return title_ + " ["+ units_+"]";
}

void Scale::Title(const QString &newTitle)
{
    title_=newTitle;
}

qreal Scale::Length()const
{
    return length_;
}

qreal Scale::Width()const
{
    return width_;
}



double Scale::valueToPos(double x)const
{
    switch (type_)
    {
    case LinearScale:
        switch (axis_)
        {
        case xAxis:
            return (x-min_)*b_;
        case yAxis:
            return (max_-x)*b_;

        }

    case LogScale:
        switch (axis_)
        {
        case xAxis:
            return log10(x/min_)*b_;
        case yAxis:
            return log10(max_/x)*b_;

        }
    }
}


double Scale::posToValue(double pos)const
{
    switch (type_)
    {
    case LinearScale:
        switch (axis_)
        {
        case xAxis:
            return pos/b_+min_;
        case yAxis:
            return max_-pos/b_;

        }

    case LogScale:
        switch (axis_)
        {
        case xAxis:
            return pow(10,pos/b_)*min_;
        case yAxis:
            return max_/pow(10,pos/b_);

        }
    }
}



void Scale::reScale(double min,double max)
{
    min_=min;
    max_=max;
    reset();
    update();
    emit rescaled();

}




Scale::Type Scale::getType()const
{
    return type_;
}

void Scale::setType(Type scaleType)
{
    type_=scaleType;
}


Scale::AxisType Scale::getAxisType()const
{
    return axis_;
}




void Scale::PadForRange(double percentPadded)
{
    double d,r;
    switch(type_)
    {
    case LinearScale:
        d=percentPadded/100.0*(max_-min_);
        max_+=d;
        min_-=d;
        break;
    case LogScale:
        r=percentPadded/100.0*max_/min_;
        max_*=r;
        min_/=r;
        break;
    }
}

void Scale::buildLinearTicks()
{
    double minUnit=pow(10.0,Markov_LA::floorSafe(log10(std::abs(max_-min_)))-1);
    double rangeU=std::abs(max_-min_)/minUnit;
    if (rangeU<16)
        tickInterval_=2.0*minUnit;
    else if (rangeU<32)
        tickInterval_=5.0*minUnit;
    else if (rangeU<64)
        tickInterval_=10.0*minUnit;
    else
        tickInterval_=20.0*minUnit;


    if((rangeCalc_&NearestTickRange)==NearestTickRange)
    {
        minTick_=Markov_LA::floorSafe(min_/tickInterval_)*tickInterval_;
        maxTick_=Markov_LA::ceilSafe(max_/tickInterval_)*tickInterval_;

        ticksCount_=(maxTick_-minTick_)/tickInterval_;
        min_=minTick_;
        max_=maxTick_;
        b_=Length()/(max_-min_);

    }
    else
    {
        minTick_=Markov_LA::ceilSafe(min_/tickInterval_)*tickInterval_;
        maxTick_=Markov_LA::floorSafe(max_/tickInterval_)*tickInterval_;

        ticksCount_=(maxTick_-minTick_)/tickInterval_;
        b_=Length()/(max_-min_);

    }

    int nprec=Markov_LA::ceilSafe(log10(max_/tickInterval_));


    ticksValue_=QVector<double>(ticksCount_+1);
    ticksPosition_=QVector<qreal> (ticksCount_+1);

    labels_=QVector<QString>(ticksCount_+1);


    for (int i=0; i<=ticksCount_;++i)
    {
        double currTick=minTick_+i*tickInterval_;
        ticksValue_[i]=currTick;
        ticksPosition_[i]=valueToPos(currTick);
        labels_[i]=QString::number(currTick,'G',nprec+1);
    }
}




void Scale::buildLogTicks()
{
    double minE10=pow(10.0,Markov_LA::floorSafe(log10(min_)));
    double maxE10=pow(10.0,Markov_LA::floorSafe(log10(max_)));

    if((rangeCalc_&NearestTickRange)==NearestTickRange)
    {
        minTick_=Markov_LA::floorSafe(min_/minE10)*minE10;
        maxTick_=Markov_LA::ceilSafe(max_/maxE10)*maxE10;

        min_=minTick_;
        max_=maxTick_;
        b_=Length()/log10(max_/min_);

    }
    else
    {
        minTick_=Markov_LA::ceilSafe(min_/minE10)*minE10;
        maxTick_=Markov_LA::floorSafe(max_/maxE10)*maxE10;
        b_=Length()/log10(max_/min_);

    }
    ticksValue_.clear();
    ticksPosition_.clear();


    double currTick=minTick_;
    double currE10=minE10;
    while (currTick<maxTick_*1.01)
    {
        ticksValue_.push_back(currTick);
        ticksPosition_.push_back(valueToPos(currTick));

        labels_.push_back(QString::number(currTick,'G'));
        if (currTick/currE10>9.8)
        {
            currE10*=10.0;
        }
        currTick+=currE10;
    }
    ticksCount_=ticksValue_.size();

}



void Scale::buildLabelPos(QPainter* painter)
{
    labelsPos_.clear();
    switch (axis_)
    {
    case Scale::xAxis:

        for (int i=0; i<labels_.size(); i++)
        {
            QRectF rect=painter->fontMetrics().boundingRect(labels_.at(i));
            QSizeF s=rect.size()*1.2;
            rect.setSize(s);
            rect.moveTo(ticksPosition_.at(i)-rect.width()/2,
                        tickLength_*1.2+rect.height());
            labelsPos_.push_back(rect);

        }
        break;
    case Scale::yAxis:

        for (int i=0; i<labels_.size(); i++)
        {
            QRectF rect=painter->fontMetrics().boundingRect(labels_.at(i));
            QSizeF s=rect.size()*1.2;
            rect.setSize(s);
            rect.moveTo(Width()-tickLength_*1.2-rect.width(),
                        ticksPosition_.at(i)-rect.height()/2);
            labelsPos_.push_back(rect);
        }
        break;
    }

}




void Scale::drawTitle(QPainter *painter)
{
    QRectF rect;
    qreal w;
    qreal h;
    QSizeF s(1,1);
    switch(axis_)
    {
    case Scale::xAxis:
        qDebug()<<painter->fontInfo().pointSize();

        rect=painter->fontMetrics().boundingRect(Title());
        s+=rect.size();
        rect.setSize(s);
        w=rect.width();
        h=rect.height();
        rect.moveTo(Length()/2-w/2,Width()-h);
        painter->drawText(rect,Qt::AlignCenter,Title());
        break;
    case Scale::yAxis:
        rect=painter->fontMetrics().boundingRect(Title());
        s+=rect.size();
        rect.setSize(s);
        w=rect.width();
        h=rect.height();
        rect.moveTo(-Length()/2-w/2,0);
        painter->rotate(-90);

        painter->drawText(rect,Qt::AlignCenter,Title());
        painter->rotate(90);

        break;
    }
}

void Scale::drawLabels(QPainter *painter)
{
    for (int i=0; i<labels_.size(); ++i)
    {
        painter->drawText(labelsPos_.at(i),Qt::AlignCenter,labels_.at(i));

    }
}

Scale::AxisType Scale::toAxisType(std::string a)
{
  if (a=="xAxis")
    return xAxis;
  else if (a=="yAxis")
    return yAxis;
  else return xAxis;

}

std::string Scale::toString(Scale::AxisType a)
{
  switch (a) {
    case xAxis:
      return "xAxis";
      break;
    case yAxis:
      return "yAxis";
      break;
    }
}

Scale::Type Scale::toType(std::string a)
{
  if (a=="LogScale")
    return LogScale;
  else if (a=="LinearScale")
    return LinearScale;
  else return LinearScale;

}

std::string Scale::toString(Scale::Type a)
{
  switch (a) {
    case LogScale:
      return "LogScale";
      break;
    case LinearScale:
      return "LinearScale";
      break;
    default:
      return "LinearScale";
    }
}

Scale::RangeCalculation Scale::toRangeCalculation(std::string a)
{
  if (a=="ExactRange")
    return ExactRange;
  else if (a=="Pad5PercentRange")
    return Pad5PercentRange;
  else if (a=="NearestTickRange")
    return NearestTickRange;
  else return ExactRange;

}

std::string Scale::toString(Scale::RangeCalculation a){
  switch (a) {
    case Pad5PercentRange:
      return "Pad5PercentRange";
      break;
    case NearestTickRange:
      return "NearestTickRange";
      break;
    case ExactRange:
      return "ExactRange";
      break;
    default:
      return "ExactRange";
    }
}

std::string Scale::myClass() const
{
  return ClassName();
}

std::string Scale::mySuperClass() const
{
  return ClassName();
}

std::string Scale::ClassName()
{
  return "Scale";
}

Markov_IO::ClassDescription Scale::GetDescription() const

{
  Markov_IO::ClassDescription desc(myClass(),mySuperClass());
  double max;
  AxisType axis;
  QString title;
  QString units;
  double length;
  double width;
  Type scaletype;

  desc.push_back("name",this->myName());
  desc.push_back("min",
                 this->min(),
                 "[mininum]",
                 "minimum value of the scale");
  desc.push_back("max",
                 this->max(),
                 "[maximum]",
                 "maximum value of the scale");
  desc.push_back("Axis_Type",
                 this->toString(axis_),
                 "[axisType]",
                 "x axis or y axis ");
  desc.push_back("Title",
                 this->Title().toStdString(),
                 "[title]",
                 "axis title");
  desc.push_back("Units",
                 this->units_.toStdString(),
                 "[units]",
                 "units");



  return desc;
}

bool Scale::LoadFromDescription(const Markov_IO::ClassDescription &classDes)
{

}

std::string Scale::myName() const
{
  return name_;
}

void Scale::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{

  painter->setFont(scene()->font());

  penWidth_=painter->pen().widthF();
  buildLabelPos(painter);
  painter->drawLine(axisLine_);
  painter->drawLines(tickLines_);
  drawTitle(painter);
  drawLabels(painter);
  //painter->drawRect(this->boundingRect());

}

void Scale::buildLines()
{
  tickLines_.clear();
  switch(getAxisType())
    {
    case Scale::xAxis:
      axisLine_ =QLineF(0.0,0.0,Length(),0.0);
      for (int i=0;i<ticksPosition_.size();++i )
        {
          tickLines_.push_back(QLineF(ticksPosition_.at(i),0.0,
                                      ticksPosition_.at(i),tickLength_));
        }
      break;
    case Scale::yAxis:
      axisLine_=QLineF(Width(),0.0,Width(),Length());
      for (int i=0;i<ticksPosition_.size();++i )
        {
            tickLines_.push_back(QLineF(Width(),ticksPosition_.at(i),
                                        Width()-tickLength_,ticksPosition_.at(i)));
        }
        break;
    }

}



Scale::Scale(ABC_Complex_Var *e,
             double min,
             double max,
             AxisType axis,
             QString title,
             QString units,
             double length,
             double width,
             Type scaletype
             ):
  Markov_IO::Implements_Complex_Var(e,title.toStdString(),"scale",{}),
  axis_(axis),
    type_(scaletype),
    rangeCalc_(Scale::Pad5PercentRange),
    length_(length),
    width_(width),
    tickLength_(width*0.1),
    penWidth_(1.0),
     title_(title),
     units_(units),
    min_(min),
    max_(max),
    b_(),
    tickInterval_(),
    minTick_(),
    maxTick_(),
    ticksCount_(),
    ticksValue_(),
    labels_(),
    labelsPos_(),
    tickLines_(),
    axisLine_()
   {
    reset();
    setAcceptHoverEvents(true);

    addVar(new Markov_IO::Implements_Simple_Var<double>(this,"min",min));
    addVar(new Markov_IO::Implements_Simple_Var<double>(this,"max",max));
    addVar(new Markov_IO::Implements_Simple_Var<double>(this,"length",length));
    addVar(new Markov_IO::Implements_Simple_Var<double>(this,"width",width));
    addVar(new Markov_IO::Implements_Simple_Var<std::string>(
             this,"title",title.toStdString()));
    addVar(new Markov_IO::Implements_Simple_Var<std::string>(
             this,"units",units.toStdString()));
    addVar(new Markov_IO::Categorical_Options(this,"AxisType",{{"xaxis"},{"yaxis"}}));
    addVar(new Markov_IO::Categorical_Options(
             this,"ScaleType",{{"LinearScale"},{"LogScale"}}));
    addVar(new Markov_IO::Categorical_Data(
             this,"axis",static_cast<int>(axis),"AxisType"));
    addVar(new Markov_IO::Categorical_Data(
             this,"saletype",static_cast<int>(scaletype),"ScaleType"));

    std::string out=Implements_Complex_Var::toString();

    getEnvironment()->addClass(new Markov_IO::Implements_Simple_Var<double>,
                               Markov_IO::Implements_Simple_Var<double>::ClassName());

    getEnvironment()->addClass(new Markov_IO::Implements_Simple_Var<std::string>,
                               Markov_IO::Implements_Simple_Var<std::string>::ClassName());

    getEnvironment()->addClass(new Markov_IO::Implements_Simple_Var<std::vector<std::string>>,
                               Markov_IO::Implements_Simple_Var<std::vector<std::string>>::ClassName());

    getEnvironment()->addClass(new Markov_IO::Implements_Simple_Var<int>,
                               Markov_IO::Implements_Simple_Var<int>::ClassName());

    getEnvironment()->addClass(new Markov_IO::Categorical_Options,
                               Markov_IO::Categorical_Options::ClassName());

    getEnvironment()->addClass(new Markov_IO::Categorical_Data,
                               Markov_IO::Categorical_Data::ClassName());
    getEnvironment()->addClass(new Scale,
                               Scale::ClassName());

    std::cerr<<out;


    std::deque<Markov_IO::Token_New> t;
    t<<out;
    std::size_t pos=0;
    auto d =Markov_IO::ABC_Var::getFromTokens(this,t,pos);

    std::cerr<<d->toString();



}

void Scale::reset()
{
    if((rangeCalc_ & Pad5PercentRange)==Pad5PercentRange)
    {
        PadForRange(5.0);
    };
    switch(type_)
    {
    case LogScale:
        this->buildLogTicks();
        break;
    case LinearScale:
        this->buildLinearTicks();
        break;
    }
    buildLines();

}


double Scale::min()const
{
    return min_;
}
 double Scale::max()const
 {
     return max_;
 }



QRectF Scale::boundingRect() const
{

    switch(getAxisType())
    {
    case Scale::xAxis:
        return QRectF(- penWidth_ / 2, - penWidth_ / 2,
                      Length(), Width());
        break;
    case Scale::yAxis:

        return QRectF(- penWidth_ / 2, - penWidth_ / 2
                      , Width(),Length());

    }
}


void Scale::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QString label;
    switch(getAxisType())
    {
    case Scale::xAxis:
        label=QString("x:%1").arg(posToValue(event));
        break;
    case Scale::yAxis:
        label=QString("y:%1").arg(posToValue(event));
    }
        QToolTip::showText(event->screenPos(),label);

}


qreal Scale::posToValue(QGraphicsSceneMouseEvent *event)const
{
    switch(getAxisType())
    {
    case Scale::xAxis:
        return posToValue(event->pos().x());
        break;
    case Scale::yAxis:
        return posToValue(event->pos().y());
    }

}



qreal Scale::posToValue(QGraphicsSceneHoverEvent *event)const
{
    switch(getAxisType())
    {
    case Scale::xAxis:
        return posToValue(event->pos().x());
        break;
    case Scale::yAxis:
        return posToValue(event->pos().y());
    }

}


void Scale::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    nextMin_=posToValue(event);
    nextMinMaxPos_=event->screenPos();
    QString label;
    switch(getAxisType())
    {
    case Scale::xAxis:
        label=QString("zoom\n x0:%1").arg(nextMin_);
        QToolTip::showText(event->screenPos(),label);
        break;
    case Scale::yAxis:
        label=QString("zoom\n y0:%1").arg(nextMin_);
        QToolTip::showText(event->screenPos(),label);
    }
}
void Scale::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal nextMax=posToValue(event);
    qreal min,max;
    bool zoomout;
    QString label;
    if (nextMax>nextMin_)
    {
        zoomout=false;
        min=nextMin_;
        max=nextMax;
        label=QString("ZOOM IN\nmin:%1\nmax:%2").arg(min).arg(max);
    }
    else
    {
        zoomout=true;
        double range=(max_-min_)*(max_-min_)/(nextMin_-nextMax);
        min=min_-(nextMax-min_)/(max_-min_)*range;
        max=min+range;
        label=QString("ZOOM OUT\nmin:%1\nmax:%2").arg(min).arg(max);
    }

    QToolTip::showText(nextMinMaxPos_,label);
}

void Scale::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qreal nextMax=posToValue(event);
    qreal min,max;
    if (nextMax>nextMin_)
    {
        min=nextMin_;
        max=nextMax;
    }
    else
    {
        double range=(max_-min_)*(max_-min_)/(nextMin_-nextMax);
        min=min_-(nextMax-min_)/(max_-min_)*range;
        max=min+range;
    }
    if (max>min)
        reScale(min,max);



}




}

