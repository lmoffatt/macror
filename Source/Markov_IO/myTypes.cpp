#include "Markov_IO/myTypes.h"
#include "Markov_Mol/QMarkovModel.h"

namespace Markov_IO_New {

  namespace _private {

    template class Implements_Data_Type_class<ABC_Markov_Model*>;


    namespace _model {




    }

    void push_Types(Markov_CommandManagerVar *cm)
    {
      cm->pushType(new Implements_Data_Type_New<std::size_t> (cm));
      cm->pushType(new Implements_Data_Type_New<double> (cm));
      //cm->pushType(new Implements_Data_Type_New<int> (cm));
     // cm->pushType(new Implements_Data_Type_New<bool> (cm));


           cm->pushType(new Implements_Data_Type_New<ABC_Markov_Model*>(cm));

     Implements_Data_Type_New<Q_Markov_Model*>::push_Types(cm);
    }

  }

}
