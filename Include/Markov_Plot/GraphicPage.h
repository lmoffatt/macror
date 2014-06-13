#ifndef GRAPHICPAGE_H
#define GRAPHICPAGE_H

#include "Markov_Plot/GraphView.h"
#include "Markov_IO/ABC_Var.h"

namespace Markov_IO {
  class YfitLikelihoodEvaluation;
}
/*
namespace Markov_Plot
{




class GraphicPage: public QWidget, public Markov_IO::Implements_Complex_Var
{
   Q_OBJECT

public:
    static void addDefinitions(Markov_IO::ABC_Var* e)
    {
      e->addChildVar(new Markov_IO::Implements_Simple_Class<double>(
                       nullptr,"widthSize","mm",210,26,841));
      e->addChildVar(new Markov_IO::Implements_Simple_Class<double>(
                       nullptr,"heightSize","mm",297,37,1189));

      e->addChildVar(new Markov_IO::Implements_Simple_Class<double>(
                       nullptr,"graphResolution","dpi",300,50,1200));

    }

    GraphicPage(QWidget* parent, Markov_IO::ABC_Var* e,std::string id, ):
      QWidget(parent),
      Implements_Complex_Var(e,id,className,tip,whathis,
    {{"width","widthSize"},
    {"height","heightSize"},
{"resolution","graphResolution"}}){}

    virtual ~GraphicPage();


    friend GraphicPage* plot(QWidget* parent,Markov_IO::ABC_Var* e,
                             const Markov_LA::M_Matrix<double>& x);
    friend GraphicPage* plot(QWidget* parent,Markov_IO::ABC_Var* e,
                             const Markov_LA::M_Matrix<double>& x,
                             const Markov_LA::M_Matrix<double>& y);

    friend GraphicPage* plot(QWidget* parent,
                             Markov_IO::ABC_Var* e,
                             const Markov_IO::ABC_trace& trace);
    friend GraphicPage* plot(QWidget* parent,
                             Markov_IO::ABC_Var* e,
                             const Markov_IO::ABC_Experiment& experiment);

    friend GraphicPage* plot(QWidget* parent, Markov_IO::ABC_Var* e,

                             const Markov_IO::YfitLikelihoodEvaluation& experiment);

 private:



};

 GraphicPage* plot(QWidget* parent, Markov_IO::ABC_Var* e,
                   const Markov_LA::M_Matrix<double>& x);
 GraphicPage* plot(QWidget* parent, Markov_IO::ABC_Var* e,
                   const Markov_LA::M_Matrix<double>& x,
                         const Markov_LA::M_Matrix<double>& y);

 GraphicPage* plot(QWidget* parent, Markov_IO::ABC_Var* e,
                   const Markov_IO::ABC_trace& trace);
 GraphicPage* plot(QWidget* parent, Markov_IO::ABC_Var* e,
                   const Markov_IO::ABC_Experiment& experiment);

 GraphicPage* plot(QWidget*, Markov_IO::ABC_Var*, const Markov_IO::YfitLikelihoodEvaluation&);

}


*/


#endif // GRAPHICPAGE_H
