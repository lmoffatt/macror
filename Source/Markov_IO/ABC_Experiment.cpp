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

namespace Markov_IO
{
using Markov_LA::NaN;

std::string ABC_Experiment::mySuperClass()const
{
    return ClassName();
}

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




ClassDescription ABC_Experiment::GetState()const{

    ClassDescription desc=GetDescription();

    for (std::size_t i=0; i<this->num_traces(); i++)
    {
	this->trace(i);
        desc.push_back("input_"+ToString(i),this->toTx());
	    if (!Markov_LA::isNaN(y()))
        desc.push_back("output_"+ToString(i),this->toTy());
    }
    return desc;
}



std::ostream& ABC_Experiment::put(std::ostream& s) const
{
    s<<GetDescription();
    return s;
}

std::ostream& operator<<(std::ostream& stream, const ABC_Experiment&  E )
{
   E.put(stream);
   return stream;
}



/// returns true if it is a class name descendent of ABC_Experiment
bool  create(ABC_Experiment*& experiment,const std::string& childClass)

{
 if (childClass==Random_Pulses::ClassName())
   {
       Random_Pulses* rp;
       rp=new Random_Pulses();
       experiment=rp;
       return true;
   }
    else if (childClass==Single_Pulses::ClassName())
    {
	Single_Pulses* rp;
	rp=new Single_Pulses();
	experiment=rp;
       return true;
    }
     else if (childClass==Single_Pulses2::ClassName())
       {
	   Single_Pulses2* rp;
	   rp=new Single_Pulses2();
	   experiment=rp;
       return true;
       }
    else if (childClass==Pulses_program::ClassName())
      {
	  Pulses_program* rp;
	  rp=new Pulses_program();
	  experiment=rp;
       return true;
      }
    else if (childClass==Experiment::ClassName())
      {
	  Experiment* rp;
	  rp=new Experiment();
	  experiment=rp;
       return true;
      }
    else if (childClass==Experiment_Average::ClassName())
      {
	  Experiment_Average* rp;
	  rp=new Experiment_Average();
	  experiment=rp;
       return true;
      }
  else if (childClass==ExperimentalData::ClassName())
   {
       ExperimentalData* rp;
       rp=new ExperimentalData();
       experiment=rp;
    return true;
   }
    else if (childClass==Markov_Mol::Experiment_simulation::ClassName())
      {
	  Markov_Mol::Experiment_simulation* rp;
	  rp=new Markov_Mol::Experiment_simulation();
	  experiment=rp;
       return true;
      }
    else return false;

}




bool LoadFromDescription(ABC_Experiment*& experiment,
			 const Markov_IO::ClassDescription& classDes)
{
    if (create(experiment,classDes.ClassName()))
	return experiment->LoadFromDescription(classDes);
    return false;
}

std::istream& operator>> (std::istream& stream,ABC_Experiment*& x)
{
    ClassDescription classDes;
    stream>>classDes;
    if (stream.good())
	if(!LoadFromDescription(x,classDes))
	    stream.setstate(stream.rdstate() | std::ios_base::failbit);
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


namespace Markov_Test
{
namespace Markov_IO_Test
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
    MultipleTests results("ABC_Experiment ",
                          "Class Invariant");

    results.push_back(ABC_Saveable_Test::classInvariant());

    MultipleTests pGD("GetDescription()",
                      "conform invariant and class");

    ClassDescription des=experiment_->GetDescription();
    pGD.push_back(ClassDescription_Test(des).classInvariant());
    pGD.push_back(ElementaryTest("myClass()",
                                 "right in GetDescription",
                                 des.ClassName()==experiment_->myClass()));
    pGD.push_back(ElementaryTest("mySuperClass()",
                                 "right in GetDescription",
                                 des.SuperClass()==experiment_->mySuperClass()));
    pGD.push_back(ElementaryTest("myName()",
                                 "right in GetDescription",
                                 des.ElementValue(des.NameIndex("name"))==
                                 experiment_->myName()));

    results.push_back(pGD);
    MultipleTests pGS("GetState()",
                      "conform invariant and class");

    ClassDescription st=experiment_->GetState();
    pGS.push_back(ClassDescription_Test(st).classInvariant());
    pGS.push_back(ElementaryTest("myClass()",
                                 "right in GetDescription",
                                 st.ClassName()==experiment_->myClass()));
    pGS.push_back(ElementaryTest("mySuperClass()",
                                 "right in GetDescription",
                                 st.SuperClass()==experiment_->mySuperClass()));
    pGS.push_back(ElementaryTest("myName()",
                                 "right in GetDescription",
                                 st.ElementValue(des.NameIndex("name"))==
                                 experiment_->myName()));


    results.push_back(pGS);
    MultipleTests pLD("LoadFromDescription()",
                      "recover rigth object");

    ABC_Experiment *empty=experiment_->create();

    pLD.push_back(ElementaryTest(
                      "GetDescription()",
                      "fill an empty object",
                      empty->LoadFromDescription(des)));

  /*  pLD.push_back(ElementaryTest(
                      "GetDescription()",
                      "recover the same object",
                      *empty==*saveable_));
    results.push_back(pLD);
*/
// test on those is not implemented since nobody uses them
    // bool Save(const std::string& path);

//     bool Load(const std::string& path);



    return results;


}

ABC_Experiment_Test::ABC_Experiment_Test(const ABC_Experiment& experiment):
    ABC_Saveable_Test(experiment),
    experiment_(dynamic_cast<const ABC_Experiment*>(saveable_))
{

}

ABC_Experiment_Test::~ABC_Experiment_Test()
{

}

}
}


#endif //MACRO_TEST


