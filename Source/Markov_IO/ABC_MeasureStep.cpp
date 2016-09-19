#include "Markov_IO/ABC_MeasureStep.h"

namespace Markov_IO_New
{

ABC_measure_step::~ABC_measure_step() {}

std::ostream& ABC_measure_step::put(std::ostream& s) const
{
  return printSelf(s);
  }

std::ostream& ABC_measure_step::printSelf(std::ostream& s)const
{
  for (std::size_t i=0; i<num_steps(); i++)
  {
      s<<"("<<i<<")"<<sub_step(i).dt()<<"  "<<x()<<"  "<<y()<<"\t";
  };
  s<<"\n";
  return s;

}


}






