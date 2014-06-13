#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H
#include <QWidget>

#include "Markov_Plot/GraphView.h"
#include "Markov_IO/ABC_Var.h"

namespace Markov_IO {
  class YfitLikelihoodEvaluation;
}

namespace Markov_Plot
{
class GraphWindow: public QWidget, public Markov_IO::Implements_Complex_Var
{
   Q_OBJECT

public:
    GraphWindow(QWidget* parent=0);


    virtual ~GraphWindow();


    friend GraphWindow* plot(QWidget* parent,Markov_IO::ABC_Var* e,
                             const Markov_LA::M_Matrix<double>& x);
    friend GraphWindow* plot(QWidget* parent,Markov_IO::ABC_Var* e,
                             const Markov_LA::M_Matrix<double>& x,
                             const Markov_LA::M_Matrix<double>& y);

    friend GraphWindow* plot(QWidget* parent,
                             Markov_IO::ABC_Var* e,
                             const Markov_IO::ABC_trace& trace);
    friend GraphWindow* plot(QWidget* parent,
                             Markov_IO::ABC_Var* e,
                             const Markov_IO::ABC_Experiment& experiment);

    friend GraphWindow* plot(QWidget* parent, Markov_IO::ABC_Var* e,
                             const Markov_IO::YfitLikelihoodEvaluation& experiment);

};

 GraphWindow* plot(QWidget* parent, Markov_IO::ABC_Var* e,
                   const Markov_LA::M_Matrix<double>& x);
 GraphWindow* plot(QWidget* parent, Markov_IO::ABC_Var* e,
                   const Markov_LA::M_Matrix<double>& x,
                         const Markov_LA::M_Matrix<double>& y);

 GraphWindow* plot(QWidget* parent, Markov_IO::ABC_Var* e,
                   const Markov_IO::ABC_trace& trace);
 GraphWindow* plot(QWidget* parent, Markov_IO::ABC_Var* e,
                   const Markov_IO::ABC_Experiment& experiment);

 GraphWindow* plot(QWidget*, Markov_IO::ABC_Var*, const Markov_IO::YfitLikelihoodEvaluation&);

}



#endif // GRAPHWINDOW_H
