#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H
#include <QWidget>

#include "Markov_Plot/GraphView.h"

namespace Markov_IO {
  class YfitLikelihoodEvaluation;
}

namespace Markov_Plot
{
class GraphWindow: public QWidget
{
   Q_OBJECT

public:
    GraphWindow(QWidget* parent=0);


    virtual ~GraphWindow();


    friend GraphWindow* plot(QWidget* parent, const Markov_LA::M_Matrix<double>& x);
    friend GraphWindow* plot(QWidget* parent, const Markov_LA::M_Matrix<double>& x,
                             const Markov_LA::M_Matrix<double>& y);

    friend GraphWindow* plot(QWidget* parent, const Markov_IO::ABC_trace& trace);
    friend GraphWindow* plot(QWidget* parent, const Markov_IO::ABC_Experiment& experiment);

    friend GraphWindow* plot(QWidget* parent, const Markov_IO::YfitLikelihoodEvaluation& experiment);

};

 GraphWindow* plot(QWidget* parent, const Markov_LA::M_Matrix<double>& x);
 GraphWindow* plot(QWidget* parent, const Markov_LA::M_Matrix<double>& x,
                         const Markov_LA::M_Matrix<double>& y);

 GraphWindow* plot(QWidget* parent, const Markov_IO::ABC_trace& trace);
 GraphWindow* plot(QWidget* parent, const Markov_IO::ABC_Experiment& experiment);

 GraphWindow* plot(QWidget* parent, const Markov_IO::YfitLikelihoodEvaluation& experiment);

}



#endif // GRAPHWINDOW_H
