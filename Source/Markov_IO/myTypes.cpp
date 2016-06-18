#include "Markov_IO/myTypes.h"
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_IO/VarTempl.h"


namespace Markov_IO_New {

  namespace _private {

    template class Implements_Data_Type_class<ABC_Markov_Model*>;


    namespace _model {




      void push_Types(StructureEnv_New *cm)
      {
       Q_Markov_Model_type::push_Types(cm);
      }


    }


  }

}
