#include "Markov_IO/myTypes.h"
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_IO/VarTempl.h"


namespace Markov_IO_New {

  namespace _private {

    template class Implements_Data_Type_class<ABC_Markov_Model*>;


    namespace _model {




    }

    void push_Types(Markov_CommandManagerVar *cm)
    {
      //cm->pushType<std::size_t>();

      //cm->pushType<double>();
      //cm->pushType<std::string>();
    // cm->pushType(new Implements_Data_Type_New<int> (cm));
    //  cm->pushType(new Implements_Data_Type_New<bool> (cm));


        //   cm->pushType<ABC_Markov_Model*>();

     Implements_Data_Type_New<Q_Markov_Model*>::push_Types(cm);
    }

  }

}
