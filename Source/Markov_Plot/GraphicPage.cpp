#include "Markov_Plot/GraphicPage.h"
#include <QHBoxLayout>
#include <QTabWidget>


namespace Markov_IO {
  using Markov_Plot::GraphicPage;



  template<>
  std::string
  Implements_EnumMethod_Var<GraphicPage,GraphicPage::zoomScale>::ClassName()
  {
    return "graph_Zoom_Scale";
  }

  template<>
  std::map<std::string,GraphicPage::zoomScale>        Implements_EnumMethod_Var<GraphicPage,GraphicPage::zoomScale>::strToEnum=
  {
   {"actual_Pixels",GraphicPage::BYPIXEL},{"actual_size",GraphicPage::BYCM}
  };


}

namespace Markov_Plot
{








  GraphicPage* plot(QWidget* parent,
                    Markov_IO::ABC_Var* e,
                    const std::string &id,
                    const Markov_LA::M_Matrix<double>& x)
  {
    GraphicPage* gw=new  GraphicPage(parent,e,id,"xplot","","");

    GraphView* g=  aplot(parent,e,x);

    QHBoxLayout* mainLayout=new QHBoxLayout;
    mainLayout->addWidget(g);
    gw->setLayout(mainLayout);
    return gw;
  }


  GraphicPage* plot(QWidget* parent,
                    Markov_IO::ABC_Var* e,
                    const std::string &id,
                    const Markov_LA::M_Matrix<double>& x,
                    const Markov_LA::M_Matrix<double>& y)
  {
    GraphicPage* gw=new  GraphicPage(parent,e,id,"xyplot","","");

    GraphView* g=  aplot(parent,e,x,y);

    QHBoxLayout* mainLayout=new QHBoxLayout;
    mainLayout->addWidget(g);
    gw->setLayout(mainLayout);
    return gw;



  }

  GraphicPage* plot(QWidget* parent,
                    Markov_IO::ABC_Var *e,
                    const std::string &id,
                    const Markov_IO::ABC_trace& trace)
  {

    GraphicPage* gw=new  GraphicPage(parent,e,id,"xplot","","");

    GraphView* g=  aplot(parent,e,trace);

    QHBoxLayout* mainLayout=new QHBoxLayout;
    mainLayout->addWidget(g);
    gw->setLayout(mainLayout);
    return gw;



  }
  GraphicPage* plot(QWidget* parent,
                    Markov_IO::ABC_Var *e,
                    const std::string &id,
                    const Markov_IO::ABC_Experiment& experiment)
  {
    GraphicPage* gw=new  GraphicPage(parent,e,id,"experimentplot","","");



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
            //Markov_Plot::GraphView* g=aplot(gw,e,experiment.trace(i));
            tab->addTab(patchtab,QString(patch.c_str()));

          }

        mainLayout->addWidget(tab);
        gw->setLayout(mainLayout);
        return gw;

      }


  }







}

