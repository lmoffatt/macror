#ifndef MYTYPES_H
#define MYTYPES_H
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Console/Markov_CommandManager.h"

namespace Markov_IO_New {

  using Markov_Mol_New::Q_Markov_Model;
  using Markov_Mol_New::ABC_Markov_Model;
  namespace _private {

    class Implements_Data_Type_class_ABC_Markov_Model
        :public _private::Implements_Data_Type_class<ABC_Markov_Model*>
    {

      Implements_Data_Type_class_ABC_Markov_Model
      (const Implements_ComplexVar_New* parent,
                                       const std::string& id
                                       ,const std::string& var
                                       ,const std::string& tip
                                       ,const std::string& whatthis
                                       ,typePredicate complyPred
                                       ,plainPredicate mapComply
                                       ,getEmptyObject  defaultValue
                                       ,getEmptyMap eMap
                                       ,getCVMap map
                                       ,getObject obj):
        Implements_Data_Type_class<ABC_Markov_Model*>(parent,
          id,var,tip,whatthis,complyPred,mapComply,defaultValue,eMap,map,obj,nullptr,nullptr)
      {}

      virtual bool put(const Implements_ComplexVar_New* cm,
                       const ABC_Markov_Model* v,ABC_Output* ostream,std::string* error, const std::string& masterObjective)const
      {

      }

      virtual bool get(const Implements_ComplexVar_New* cm,
                       ABC_Markov_Model*& v, ABC_Input* istream,std::string* whyNot,
                       const std::string& masterObjective)const
      {

      }


      virtual ABC_Markov_Model* getDefault_Valued(const Implements_ComplexVar_New* cm)const
      {

      }


      virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,
                                 const ABC_Markov_Model *val, std::string *whyNot
                                 ,const std::string &masterObjective ) const
      {

      }



      virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm
                                  ,const Implements_Data_Type_New<ABC_Markov_Model*>* val
                                  , std::string *whyNot
                                  ,const std::string& masterObjective ) const
      {

      }


      virtual bool includesThisType(const Implements_ComplexVar_New* cm
                                    ,const std::string& childType
                                    ,std::string *whyNot
                                    , const std::string &masterObjective)const
      {

      }


    };





    void push_Model_Types(Markov_CommandManagerVar* cm)
    {
      //cm->pushType( new Implements_Data_Type_New<ABC_Markov_Model*>(cm));

    }


  }

}

#endif // MYTYPES_H
