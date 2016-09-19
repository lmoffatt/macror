#include "Markov_IO/ABC_Experiment.h"

#include "Markov_IO/RandomPulses.h"
#include "Markov_IO/SinglePulses.h"
#include "Markov_IO/SinglePulses2.h"
#include "Markov_IO/ExperimentAverage.h"
#include "Markov_IO/PulsesProgram.h"
#include "Markov_IO/Experiment.h"
#include "Markov_IO/ExperimentalData.h"
#include "Markov_IO/auxiliarIO.h"


#include "Markov_Mol/ExperimentSimulation.h"

//#include "Forms/macror.h"

namespace Markov_IO_New
{
using Markov_LA::NaN;


std::string ABC_Experiment::ClassName()
{
    return "Experiment";
}




const ABC_Experiment& ABC_Experiment::trace_interval()const
    {return (*this)[num_measures()];}


/*

Markov_LA::M_Matrix<double> ABC_Experiment::t_y()const
{
    Markov_LA::M_Matrix<double>  ty(this->num_measures()+1,this->num_replicates()+1);
    for (std::size_t i=0; i<=num_measures(); i++)
    {
	ty(i,0)=(*this)[i].t();
	for (std::size_t j=0;j<num_replicates(); j++)
	ty(i,j+1)=(*this).replicate(j).y();
    }
    return ty;
}

*/


 const ABC_Experiment& ABC_Experiment::selectPatch(std::string )const
{
  return *this;
}

 std::vector<std::string> ABC_Experiment::getPatchs()const
{
  return std::vector<std::string>();
}

 std::string ABC_Experiment::currentPatch()const
{
  return std::string();
}





std::ostream& operator<<(std::ostream& stream, const ABC_Experiment&  E )
{
   E.put(stream);
   return stream;
}




/*
void ABC_Experiment::Plot_Save(std::string path,
                               double xMin,
                               double xMax,
                               double yMin,
                               double yMax)
{

    Markov_Plot::Plotter p_;

    std::vector<double> x_V;
    std::vector<double> y_V;
    std::vector<double> t_V;

    for(std::size_t k=0; k<num_traces(); k++)
    {
         trace(k);
         for (std::size_t j=0; j<num_measures(); j++)
         {
             if (t() != NaN() &&
                     x() != NaN() &&
                     y() != NaN())
             {
                 t_V.push_back(t());
                 x_V.push_back(x());
                 y_V.push_back(y());
             }
         }


         p_.addCurve(y_V, "y", LINE_SOLID, "1", DOT_NONE, COLOR_BLUE);
         p_.addCurve(x_V, "x", LINE_SOLID, "1", DOT_NONE, COLOR_BLACK);
         p_.defineSteps(t_V);
         if (xMin != -1 && xMax != -1) p_.setXLimits(xMin, xMax);
         if (yMin != -1 && yMax != -1) p_.setYLimits(yMin,yMax);
    }

    p_.save(path);
}

*/

}

#ifdef MACRO_TEST



#include "Tests/ElementaryTest.h"
#include "Tests/Markov_IO/ClassDescription_Test.h"


namespace Markov_Test_New
{
namespace Markov_IO_New_Test
{
  std::string ABC_Experiment_Test::TestName()
  {
    return "Experiment_Test";
  }

   std::string ABC_Experiment_Test::myTest()const
  {
    return TestName();
  }


MultipleTests ABC_Experiment_Test::classInvariant()const
{



  /*  pLD.push_back(ElementaryTest(
                      "GetDescription()",
                      "recover the same object",
                      *empty==*saveable_));
    results.push_back(pLD);
*/
// test on those is not implemented since nobody uses them
    // bool Save(const std::string& path);

//     bool Load(const std::string& path);





}

ABC_Experiment_Test::ABC_Experiment_Test(const ABC_Experiment& experiment)
{

}

ABC_Experiment_Test::~ABC_Experiment_Test()
{

}

}
}


#endif //MACRO_TEST





#endif //MACRO_TEST


