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
    public:

      static Implements_Data_Type_class_ABC_Markov_Model* create_ABCModel(
          const Implements_ComplexVar_New* cm)
      {
        return new Implements_Data_Type_class_ABC_Markov_Model
            (cm,ClassName(),ClassName()
             , "abstract kinetic model"
             ,""
             ,{},nullptr,nullptr,nullptr,nullptr,nullptr);

      }


      Implements_Data_Type_class_ABC_Markov_Model
      (const Implements_ComplexVar_New* parent,
       const std::string& id
       ,const std::string& var
       ,const std::string& tip
       ,const std::string& whatthis
       , const std::map<std::string,ABC_Var_New*> fields
       ,typePredicate complyPred
       ,typetypePredicate typeComply
       ,getEmptyObject  defaultValue
       ,getCVMap map
       ,getObject obj):
        Implements_Data_Type_class<ABC_Markov_Model*>(
          parent,id,var,tip,whatthis,fields,complyPred,typeComply,defaultValue,map,obj,nullptr,nullptr)
      {}
};



    class Implements_Data_Type_class_Q_Markov_Model
        :public Implements_Data_Type_class_ABC_Markov_Model
    {
    public:

      Implements_Data_Type_class_Q_Markov_Model
      (const Implements_ComplexVar_New* parent,
       const std::string& id
       ,const std::string& var
       ,const std::string& tip
       ,const std::string& whatthis
       ,const std::map<std::string,ABC_Var_New*>& fields
       ,typePredicate complyPred
       ,typetypePredicate typeComply
       ,getEmptyObject  defaultValue
       ,getCVMap map
       ,getObject obj):
        Implements_Data_Type_class_ABC_Markov_Model(
          parent,id,var,tip,whatthis,fields,complyPred,typeComply,defaultValue,map,obj)
      {}









    };






    void push_Model_Types(Markov_CommandManagerVar* cm)
    {


    }


  }

}

#endif // MYTYPES_H
