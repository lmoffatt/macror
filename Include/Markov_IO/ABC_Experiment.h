#ifndef ABC_EXPERIMENT_H
#define ABC_EXPERIMENT_H
#include <cstddef>

#include "Markov_IO/ABC_Trace.h"
#include "Markov_IO/ABC_Saveable.h"

#include "Markov_Plot/XY_PlotData.h"
//#include "Forms/plotscreen.h"
//#include <Markov_Plot/Experiment_PlotData.h>

namespace Markov_IO
{

class ABC_Experiment:public ABC_trace
        //, public Markov_Plot::ABC_Plotable
{
public:
    virtual ABC_Experiment* clone() const=0;
    ///virtual default constructors
    virtual ABC_Experiment* create() const=0;
    virtual ~ABC_Experiment() {}

    //virtual bool operator==(const ABC_Experiment& other)const;

    static std::string ClassName();

    virtual std::string myName()const=0;
    virtual std::string myClass()const=0;
    virtual std::string mySuperClass()const;

    virtual std::size_t total_samples()const=0;

    virtual std::size_t num_replicates()const=0;

    virtual const ABC_Experiment& replicate(std::size_t i)const=0;


    virtual const ABC_Experiment& selectPatch(std::string)const;
    virtual std::vector<std::string> getPatchs()const;
    virtual std::string currentPatch()const;



    virtual const ABC_Experiment& trace(std::size_t i)const=0;
    virtual std::size_t i_trace()const=0;

    virtual const ABC_Experiment& trace_interval()const;

    virtual std::size_t num_traces() const=0;

    virtual const ABC_Experiment& operator[](std::size_t i)const=0;
    virtual const ABC_Experiment& operator++()const=0;
    //    virtual const ABC_Experiment& raw_sample(std::size_t i)const=0;
    virtual std::size_t i_sample()const=0;

    virtual std::size_t num_measures()const=0;

    virtual double t()const=0;
    virtual double dt()const=0;
    virtual double x()const=0;
    virtual std::size_t num_steps()const=0;
    virtual const ABC_measure_point&  sub_step(std::size_t i)const=0;

    /// gives NaN() if there are no measures
    virtual double y()const=0;
    //    virtual ABC_Experiment& y(double new_value)=0;

  //  virtual Markov_LA::M_Matrix<double> t_y()const;

//    virtual Markov_Plot::XY_PlotData *plotY()const;
//    virtual Markov_Plot::XY_PlotData *plotX()const;


    virtual ClassDescription GetState()const;

   virtual std::ostream& put(std::ostream& s) const;


    //virtual Markov_Plot::Experiment_PlotData* Get_PlotData();
    /*
    virtual void Plot_Screen(QWidget* parent);
    virtual void Plot_Save(std::string path,
                           double xMin=-1,
                           double xMax=-1,
                           double yMin=-1,
                           double yMax=-1);
*/

};


std::ostream& operator<<(std::ostream& stream, const ABC_Experiment&  E );

bool LoadFromDescription(ABC_Experiment*& e,
			 const Markov_IO::ClassDescription& classDes);



bool  create(ABC_Experiment*& e,const std::string& childClass);

std::istream& operator>> (std::istream& stream,ABC_Experiment*& e);

}


#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"
#include "Tests/Markov_IO/ABC_Put_Test.h"
namespace Markov_Test
{
namespace Markov_IO_Test
{

using namespace Markov_IO;

class ABC_Experiment_Test:public ABC_Saveable_Test
{
public:

    virtual MultipleTests classInvariant()const;

    ABC_Experiment_Test(const ABC_Experiment& experiment);

    virtual~ABC_Experiment_Test();
    static std::string TestName();

    virtual std::string myTest()const;


protected:
    const ABC_Experiment* experiment_;
};

}
}

#endif //MACRO_TEST


#endif // ABC_EXPERIMENT_H
