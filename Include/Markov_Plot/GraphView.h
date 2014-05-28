#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H
#include <QGraphicsView>

#include "Markov_Plot/ABC_PlotData.h"
#include "Markov_Plot/Scale.h"
#include "Markov_Plot/XY_Plot.h"

#include "Markov_LA/Matrix.h"
#include "Markov_IO/ABC_Experiment.h"
#include "Markov_Bay/YfitLikelihoodEvaluation.h"

namespace Markov_Plot
{
  class GraphView: public QGraphicsView, public Markov_IO::Implements_Complex_Var
  {
    Q_OBJECT

  public:
    GraphView(QWidget* parent=0);

    GraphView(QWidget *parent,
              Markov_IO::ABC_Complex_Class *e,
              qreal width,
              qreal height);

    virtual ~GraphView();


    friend GraphView* aplot(QWidget* parent, Markov_IO::ABC_Complex_Class* e,
                            const Markov_LA::M_Matrix<double>& x);
    friend GraphView* aplot(QWidget* parent, Markov_IO::ABC_Complex_Class* e,
                            const Markov_LA::M_Matrix<double>& x,
                            const Markov_LA::M_Matrix<double>& y);

    friend GraphView* aplot(QWidget* parent, Markov_IO::ABC_Complex_Class* e,
                            const Markov_IO::ABC_trace& trace);
    friend GraphView* aplot(QWidget* parent, Markov_IO::ABC_Complex_Class* e,
                            const Markov_IO::ABC_Experiment& experiment);

    friend GraphView* aplot(QWidget* parent,Markov_IO::ABC_Complex_Class* e,
                            const Markov_Bay::YfitLikelihoodEvaluation& yfit,
                            std::size_t itrace);


  public slots:
    void redraw();

  protected:
    void resizeEvent(QResizeEvent *event);




  private:

    QGraphicsScene* gscene_;

    qreal height_;
    qreal width_;

    std::vector<Scale*> xAxes_;
    std::vector<Scale*> yAxes_;
    std::vector<XY_Plot*> plot_;

    QVector<QColor> lineColors_;


  };

  GraphView* aplot(QWidget* parent, Markov_IO::ABC_Complex_Class *e,
                   const Markov_LA::M_Matrix<double>& x);
  GraphView* aplot(QWidget* parent, Markov_IO::ABC_Complex_Class* e,
                   const Markov_LA::M_Matrix<double>& x,
                   const Markov_LA::M_Matrix<double>& y);

  GraphView* aplot(QWidget* parent,
                   Markov_IO::ABC_Complex_Class* e,
                   const Markov_IO::ABC_trace& trace);


 GraphView* aplot(QWidget* parent,Markov_IO::ABC_Complex_Class* e,
                          const Markov_Bay::YfitLikelihoodEvaluation& yfit,
                          std::size_t itrace);


}

#endif // GRAPHVIEW_H
