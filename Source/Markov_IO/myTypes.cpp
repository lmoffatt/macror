#include "Markov_IO/myTypes.h"
#include "Markov_Mol/QMarkovModel.h"

namespace Markov_IO_New {

  namespace _private {

    template class Implements_Data_Type_class<ABC_Markov_Model*>;


    namespace _model {




    }

    void push_Types(Markov_CommandManagerVar *cm)
    {

      cm->pushType(_model::agonist_vector_type::varType(cm));
      cm->pushType(_model::conductance_vector_Type::varType(cm));
      cm->pushType(_model::Q_matrix_Type::varType(cm));
      cm->pushType(new Implements_Data_Type_New<ABC_Markov_Model*>(cm));

      cm->pushType(new Implements_Data_Type_New<Q_Markov_Model*>(cm));
    }

  }

}
