#include "Markov_LA/matrixMaxMin.h"
#include <QResizeEvent>
#include <QToolTip>

#include <QtDebug>
#include "Markov_Plot/GraphView.h"
#include "Markov_Bay/YfitLikelihoodEvaluation.h"
#include "Markov_GUI/ABC_Var_GUI.h"

namespace Markov_Plot
{
  GraphView::GraphView(QWidget* parent,
                       Markov_IO::ABC_Data* e,
                       qreal width,
                       qreal height):
    QGraphicsView(parent),
    Markov_IO::Implements_Complex_Var(e,"","GraphView","",""),
    gscene_(new QGraphicsScene(0.0,0.0,width,height,parent)),
    height_(height),
    width_(width),
    xAxes_(),
    yAxes_(),
    plot_(),
    lineColors_()
  {
    lineColors_<<QColor(Qt::black)
              <<QColor(Qt::green)<<QColor(Qt::blue)<<QColor(Qt::red)
             <<QColor(Qt::cyan)<<QColor(Qt::magenta)<<QColor(Qt::yellow)
            <<QColor(Qt::gray)<<QColor(Qt::lightGray)<<QColor(Qt::darkGray)
           <<QColor(Qt::darkGreen)<<QColor(Qt::darkBlue)<<QColor(Qt::darkRed)
          <<QColor(Qt::darkCyan)<<QColor(Qt::darkMagenta)<<QColor(Qt::darkYellow);

    setScene(gscene_);
    gscene_->setFont(QFont ("Arial", 30));

    setMouseTracking(true);
  }

  GraphView::GraphView(QWidget* parent):
    QGraphicsView(parent),
    height_(),
    width_(),
    xAxes_(),
    yAxes_(),
    plot_()
  {
    gscene_=new QGraphicsScene(parent);
    setScene(gscene_);
    setMouseTracking(true);

  }


  GraphView::~GraphView()
  {
  }


  GraphView* aplot(QWidget* parent,Markov_IO::ABC_Data* e,
                   const Markov_LA::M_Matrix<double>& x)
  {
    GraphView* g=  new GraphView(parent,e,
                                 1000,1000);

    Scale* xAxis=new Scale(e,
                           Markov_LA::min(x(":",0)),
                           Markov_LA::max(x(":",0)),
                           Scale::xAxis,
                           "x",
                           "units",
                           1000,
                           200,
                           Scale::LinearScale);


    Scale* yAxis=new Scale(e,
                           Markov_LA::min(x(":",1)),
                           Markov_LA::max(x(":",1)),
                           Scale::yAxis,
                           "x",
                           "units",
                           1000,
                           200,
                           Scale::LinearScale);

    XY_Plot* p=new XY_Plot(e,
                           new Markov_LA::M_Matrix<double> (x),
                           0,
                           "Plot",xAxis,yAxis);

    g->xAxes_.push_back(xAxis);
    g->yAxes_.push_back(yAxis);
    g->plot_.push_back(p);


    g->gscene_->addItem(xAxis);
    g->gscene_->addItem(yAxis);
    g->gscene_->addItem(p);

    // xAxis->moveBy();
    g->redraw();
    return g;

  }


  GraphView* aplot(QWidget* parent, Markov_IO::ABC_Data *e,
                   const Markov_LA::M_Matrix<double>& x,
                   const Markov_LA::M_Matrix<double>& y)
  {
    GraphView* g=  new GraphView(parent,e,
                                 1000,1000);

    Scale* xAxis=new Scale(g,Markov_LA::min(x),
                           Markov_LA::max(x),
                           Scale::xAxis,
                           "x",
                           "units",
                           1000,
                           200,
                           Scale::LinearScale);


    Scale* yAxis=new Scale(g,Markov_LA::min(y),
                           Markov_LA::max(y),
                           Scale::yAxis,
                           "x",
                           "units",
                           1000,
                           200,
                           Scale::LinearScale);

    XY_Plot* p=new XY_Plot(g,new Markov_LA::M_Matrix<double> (x),
                           new Markov_LA::M_Matrix<double> (y),
                           "Plot",xAxis,yAxis);

    g->xAxes_.push_back(xAxis);
    g->yAxes_.push_back(yAxis);
    g->plot_.push_back(p);


    g->gscene_->addItem(xAxis);
    g->gscene_->addItem(yAxis);
    g->gscene_->addItem(p);

    // xAxis->moveBy();
    g->gscene_->setSceneRect(g->gscene_->itemsBoundingRect());

    g->redraw();
    return g;



  }


  void GraphView::redraw(){

    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);


  }





  GraphView* aplot(QWidget* parent, Markov_IO::ABC_Data *e, const Markov_IO::ABC_trace& trace)
  {



    GraphView* g=  new GraphView(parent,e,
                                 900,900);

    double axisLength=900;
    double axisWidth=300;


    Scale* tAxis=new Scale(g,trace[0].t(),
        trace[trace.num_measures()-1].t(),
        Scale::xAxis,
        "t",
        "s",
        axisLength,
        axisWidth,
        Scale::LinearScale);

    Markov_LA::M_Matrix<double> tx=trace.t_x();

    Markov_LA::M_Matrix<double> ty=trace.t_y();
    bool hasY=trace.num_replicates()>0;


    Scale* xAxis=new Scale(g,Markov_LA::min(tx(":",1)),
                           Markov_LA::max(tx(":",1)),
                           Scale::yAxis,
                           "x",
                           "units",
                           axisLength/3.0,
                           axisWidth,
                           Scale::LinearScale);



    Scale* yAxis;


    XY_Plot* px=new XY_Plot(g,new Markov_LA::M_Matrix<double> (tx),
                            0,
                            "Plot",tAxis,xAxis);
    g->xAxes_.push_back(tAxis);
    g->plot_.push_back(px);


    g->gscene_->addItem(tAxis);
    g->gscene_->addItem(xAxis);
    g->gscene_->addItem(px);

    tAxis->setPos(axisWidth,(1./3)*axisLength);
    xAxis->setPos(0,0);

    px->setPos(axisWidth,0);

    if (hasY)
      {

        int numtraces=Markov_LA::ncols(ty)-1;

        double miny=Markov_LA::min(ty(":",1));
        double maxy=Markov_LA::max(ty(":",1));

        for (int itrace=1; itrace<numtraces; itrace++)
          {
            miny=std::min(miny,Markov_LA::min(ty(":",itrace+1)));
            maxy=std::max(maxy,Markov_LA::max(ty(":",itrace+1)));
          }

        yAxis=new Scale(g,miny,
                        maxy,
                        Scale::yAxis,
                        "y",
                        "units",
                        axisLength,
                        axisWidth,
                        Scale::LinearScale);


        for (int itrace=0; itrace<numtraces; itrace++)
          {

            XY_Plot* py=new XY_Plot(g,new Markov_LA::M_Matrix<double> (ty),
                                    0,
                                    "Plot",tAxis,yAxis,itrace);
            g->plot_.push_back(py);
            g->gscene_->addItem(py);
            py->setPos(axisWidth,axisLength/3+0.05*axisLength);

          }
        g->yAxes_.push_back(yAxis);
        g->gscene_->addItem(yAxis);
        yAxis->setPos(0,axisLength/3+0.05*axisLength);
        tAxis->setPos(axisWidth,(1.+1./3)*axisLength+0.05*axisLength);


      }

    g->gscene_->setSceneRect(QRectF());

    g->redraw();
    return g;
  }
  GraphView* aplot(const Markov_IO::ABC_Experiment& )
  {
 return nullptr;


  }

  void GraphView::resizeEvent(QResizeEvent *event)
  {
    QGraphicsView::resizeEvent(event);
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
  }

  GraphView* aplot(QWidget* parent, Markov_IO::ABC_Data *e,
                   const Markov_Bay::YfitLikelihoodEvaluation& yfit,
                   std::size_t itrace)
  {

    qreal graphheight=900;
    qreal graphWidth=900;

    GraphView* g=  new GraphView(parent,e,
                                 graphWidth,graphheight);

    double axisLength=900;
    double axisWidth=300;

    const Markov_IO::ABC_trace& trace=yfit.experiment()->trace(itrace);
    double tmin=trace[0].t();
    double tmax=trace[trace.num_measures()-1].t();


    Scale* tAxis=new Scale(g,tmin,
                           tmax,
                           Scale::xAxis,
                           "t",
                           "s",
                           axisLength,
                           axisWidth,
                           Scale::LinearScale);

    Markov_LA::M_Matrix<double> tx=trace.t_x();

    Markov_LA::M_Matrix<double> ty=trace.t_y();
    bool hasY=trace.num_replicates()>0;


    Scale* xAxis=new Scale(g,Markov_LA::min(tx(":",1)),
                           Markov_LA::max(tx(":",1)),
                           Scale::yAxis,
                           "x",
                           "units",
                           axisLength/3.0,
                           axisWidth,
                           Scale::LinearScale);



    Scale* yAxis;


    XY_Plot* px=new XY_Plot(g,new Markov_LA::M_Matrix<double> (tx),
                            0,
                            "Plot",tAxis,xAxis);
    g->xAxes_.push_back(tAxis);
    g->plot_.push_back(px);


    g->gscene_->addItem(tAxis);
    g->gscene_->addItem(xAxis);
    g->gscene_->addItem(px);

    tAxis->setPos(axisWidth,(1./3)*axisLength);
    xAxis->setPos(0,0);

    px->setPos(axisWidth,0);

    if (hasY)
      {

        int numtraces=Markov_LA::ncols(ty)-1;

        double miny=Markov_LA::min(ty(":",1));
        double maxy=Markov_LA::max(ty(":",1));

        for (int itrace=1; itrace<numtraces; itrace++)
          {
            miny=std::min(miny,Markov_LA::min(ty(":",itrace+1)));
            maxy=std::max(maxy,Markov_LA::max(ty(":",itrace+1)));
          }

        yAxis=new Scale(g,miny,
                        maxy,
                        Scale::yAxis,
                        "y",
                        "units",
                        axisLength,
                        axisWidth,
                        Scale::LinearScale);


        for (int itrace=0; itrace<numtraces; itrace++)
          {

            XY_Plot* py=new XY_Plot(g,new Markov_LA::M_Matrix<double> (ty),
                                    0,
                                    "Plot",tAxis,yAxis,itrace);
            g->plot_.push_back(py);
            g->gscene_->addItem(py);
            py->setPos(axisWidth,axisLength/3+0.05*axisLength);

          }
        g->yAxes_.push_back(yAxis);
        g->gscene_->addItem(yAxis);
        yAxis->setPos(0,axisLength/3+0.05*axisLength);
        tAxis->setPos(axisWidth,(1.+1./3)*axisLength+0.05*axisLength);


      }

    g->gscene_->setSceneRect(QRectF());

    g->redraw();
    return g;
  }



}

