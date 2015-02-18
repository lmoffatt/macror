#ifndef GRAPHICPAGE_H
#define GRAPHICPAGE_H

#include "Markov_Plot/GraphView.h"
#include "Markov_IO/ABC_Var.h"

namespace Markov_IO {
  class YfitLikelihoodEvaluation;

  }

namespace Markov_Plot
{

  class GraphicPage: public QWidget, public Markov_IO::Implements_Class_Reflection<GraphicPage>
  {
    Q_OBJECT

  public:

    static void addDefinitions(Markov_IO::ABC_Data* e)
    {
      e->pushChildVar(new Markov_IO::Implements_Simple_Class<double>(
                       nullptr,"widthSize","mm",{},210,26,841));
      e->pushChildVar(new Markov_IO::Implements_Simple_Class<double>(
                       nullptr,"heightSize","mm",{},297,37,1189));

      e->pushChildVar(new Markov_IO::Implements_Simple_Class<double>(
                       nullptr,"graphResolution","dpi",{},300,50,1200));

      e->pushChildVar(new Markov_IO::Implements_Simple_Class<double>(
                       nullptr,"graphZoom","%",{},100,6.75,1600));



    }
    typedef GraphicPage C;


    GraphicPage()=default;
    GraphicPage(QWidget* parent,
                Markov_IO::ABC_Data* e,
                const std::string& id,
                const std::string& className,
                const std::string & tip,
                const std::string& whatthis):
      QWidget(parent),
      Implements_Class_Reflection<GraphicPage>(e,id,this,className,tip,whatthis)
    {

      addDefinitions(e);
      this->push_backValMethod("width",&C::getWidth,&C::setWidth,"widthSize",
                               "width of the page",
                               "width value for the printed page");
      this->push_backValMethod("height",&C::getHeigth,&C::setHeight,"heightSize",
                               "heigth of the page",
                               "heigth value for the printed page");
      this->push_backValMethod("resolution",&C::getResolution,&C::setResolution,"graphResolution",
                               "resolution of the graph in pixels per inch",
                               "resolution for the printed page");

       this->push_backEnumValMethod("zoomScale",&C::getZoomScale,&C::setZoomScale,"zoomScales",
                                "100% zoom means actual resolution or actual size",
                                "it represent the graph in its final physical size or in its final "
                                "resolution ");







    }

    enum zoomScale {BYPIXEL,BYCM};

    zoomScale getZoomScale()const{return zs_;}

    void setZoomScale(zoomScale z){zs_=z;}

    double getResolution()const{ return resolution_;}
    double getWidth()const{return width_;}
    double getHeigth()const    { return height_;}



    void setHeight(double height){ height_=height;}
    void setWidth(double width){ width_=width;}
    void setResolution(double resolution){ resolution_=resolution;}


    virtual ~GraphicPage()
    {
    }


    friend GraphicPage* plot(QWidget* parent,Markov_IO::ABC_Data* e,
                             const std::string& id,
                             const Markov_LA::M_Matrix<double>& x);
    friend GraphicPage* plot(QWidget* parent,Markov_IO::ABC_Data* e,
                             const std::string& id,
                             const Markov_LA::M_Matrix<double>& x,
                             const Markov_LA::M_Matrix<double>& y);

    friend GraphicPage* plot(QWidget* parent,
                             Markov_IO::ABC_Data* e,
                             const std::string& id,
                             const Markov_IO::ABC_trace& trace);
    friend GraphicPage* plot(QWidget* parent,
                             Markov_IO::ABC_Data* e,
                             const std::string& id,
                             const Markov_IO::ABC_Experiment& experiment);




  private:
    double resolution_;
    double width_;
    double height_;
    double zoom_;
    zoomScale zs_;

  };






  GraphicPage* plot(QWidget* parent, Markov_IO::ABC_Data* e,
                    const std::string& id,
                    const Markov_LA::M_Matrix<double>& x);
  GraphicPage* plot(QWidget* parent, Markov_IO::ABC_Data* e, const std::string &id,
                    const Markov_LA::M_Matrix<double>& x,
                    const Markov_LA::M_Matrix<double>& y);

  GraphicPage* plot(QWidget* parent, Markov_IO::ABC_Data* e, const std::string &id,
                    const Markov_IO::ABC_trace& trace);
  GraphicPage* plot(QWidget* parent, Markov_IO::ABC_Data* e, const std::string &id,
                    const Markov_IO::ABC_Experiment& experiment);

  //GraphicPage* plot(QWidget*, Markov_IO::ABC_Var*, const Markov_IO::YfitLikelihoodEvaluation&);

}




#endif // GRAPHICPAGE_H
