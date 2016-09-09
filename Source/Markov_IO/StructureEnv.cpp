#include "Markov_IO/StructureEnv.h"
#include"Markov_IO/Implements_ComplexVar_New.h"

namespace Markov_IO_New
{

  StructureEnv_New::StructureEnv_New(const StructureEnv_New *parent, const std::__cxx11::string &idType):
    StructureEnv_New(parent,parent->idToTyped<StructureEnv_New*>(idType)){}

}
