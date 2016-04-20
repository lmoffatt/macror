#include "Markov_IO/myTypes.h"
#include "Markov_Mol/QMarkovModel.h"

namespace Markov_IO_New {

  namespace _private {

    template class Implements_Data_Type_class<ABC_Markov_Model*>;


    namespace _model {


    Implements_Data_Type_New<Q_Markov_Model_type::myC *> *Q_Markov_Model_type::varType(const Implements_ComplexVar_New *cm)
    {
      std::map<std::string,ABC_Var_New*> f;
      push_var<numStates_Field>(f);
      push_var<Q_matrix_Field>(f);
      push_var<conductance_vector_Field>(f);
      push_var<agonist_vector_field>(f);
      push_var<unitary_conductance_field>(f);
      return new Implements_Data_Type_New<myC*>
          (cm,idVar(),idType()
           ,Tip(),WhatThis()
           ,f,nullptr,nullptr
           ,nullptr,&obj2map,&map2obj);
    }

  }
  }

}
