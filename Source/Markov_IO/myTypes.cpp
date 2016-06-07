#include "Markov_IO/myTypes.h"
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_IO/VarTempl.h"


namespace Markov_IO_New {

  namespace _private {

    template class Implements_Data_Type_class<ABC_Markov_Model*>;


    namespace _model {

      Implements_Data_Type_New<Q_Markov_Model_type::myC *> *Q_Markov_Model_type::varType(const StructureEnv_New *cm)
      {
        return new Implements_Data_Type_New<myC*>();
      }

      void Q_Markov_Model_type::push_Types(Markov_CommandManagerVar *cm)
      {
        cm->pushType(myId(),varType(cm),myTip(),myWhatThis());
        Implements_Data_Type_New<myC *>::push_Types(cm);

      }


      void push_Types(Markov_CommandManagerVar *cm)
      {
       Q_Markov_Model_type::push_Types(cm);
      }


    }


  }

}
