#include "Markov_Plot/GraphWindow.h"
#include <QHBoxLayout>
#include <QTabWidget>
namespace Markov_Plot
{

  GraphWindow::GraphWindow(QWidget* parent):
    QWidget(parent)
  {
  }


  GraphWindow::~GraphWindow()
  {
  }



  GraphWindow* plot(QWidget* parent,
                    Markov_IO::ABC_Complex_Var* e,
                    const Markov_LA::M_Matrix<double>& x)
  {
    GraphWindow* gw=new  GraphWindow(parent);

    GraphView* g=  aplot(parent,e,x);

    QHBoxLayout* mainLayout=new QHBoxLayout;
    mainLayout->addWidget(g);
    gw->setLayout(mainLayout);
    return gw;
  }


  GraphWindow* plot(QWidget* parent,
                    Markov_IO::ABC_Complex_Var* e,
                    const Markov_LA::M_Matrix<double>& x,
                    const Markov_LA::M_Matrix<double>& y)
  {
    GraphWindow* gw=new  GraphWindow(parent);

    GraphView* g=  aplot(parent,e,x,y);

    QHBoxLayout* mainLayout=new QHBoxLayout;
    mainLayout->addWidget(g);
    gw->setLayout(mainLayout);
    return gw;



  }

  GraphWindow* plot(QWidget* parent,
                    Markov_IO::ABC_Complex_Var *e,
                    const Markov_IO::ABC_trace& trace)
  {

    GraphWindow* gw=new  GraphWindow(parent);

    GraphView* g=  aplot(parent,e,trace);

    QHBoxLayout* mainLayout=new QHBoxLayout;
    mainLayout->addWidget(g);
    gw->setLayout(mainLayout);
    return gw;



  }
  GraphWindow* plot(QWidget* parent,
                    Markov_IO::ABC_Complex_Var *e,
                    const Markov_IO::ABC_Experiment& experiment)
  {
    GraphWindow* gw=new  GraphWindow(parent);

    QHBoxLayout* mainLayout= new QHBoxLayout;

    QTabWidget* tab=new QTabWidget;
    std::vector<std::string> patchs=experiment.getPatchs();
    if (patchs.empty())
      {
        for (std::size_t i=0; i<experiment.num_traces(); ++i)
          {
            Markov_Plot::GraphView* g=aplot(gw,e,experiment.trace(i));
            tab->addTab(g,QString::number(i));
          }

        mainLayout->addWidget(tab);
        gw->setLayout(mainLayout);
        return gw;



      }
    else
      {
        for (std::size_t i=0; i<patchs.size(); ++i)
          {
            std::string patch=patchs[i];
            experiment.selectPatch(patch);
            QTabWidget* patchtab=new QTabWidget;
            for (std::size_t i=0; i<experiment.num_traces(); ++i)
              {
                Markov_Plot::GraphView* g=aplot(gw,e,experiment.trace(i));
                tab->addTab(g,QString::number(i));
              }
            Markov_Plot::GraphView* g=aplot(gw,e,experiment.trace(i));
            tab->addTab(patchtab,QString(patch.c_str()));

          }

        mainLayout->addWidget(tab);
        gw->setLayout(mainLayout);
        return gw;

      }


  }



  GraphWindow *plot(QWidget *parent, Markov_IO::ABC_Complex_Var *e, const Markov_IO::YfitLikelihoodEvaluation &experiment)
  {

  }




}


