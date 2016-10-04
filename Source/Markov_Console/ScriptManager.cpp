#include "Markov_Console/ScriptManager.h"
#include "Markov_IO/StructureEnv.h"

#include "Markov_IO/StructureEnv_templ.h"
#include "Markov_Console/Markov_CommandManager.h"

namespace Markov_IO_New {



  bool ScriptManager::run(Markov_CommandManagerVar *cm, ABC_Input *istream,ABC_Output * ostream,bool checkErrors)
  {
    const Implements_Data_Type_New<Implements_Var> *varType=cm->getVarType();
    const Implements_Data_Type_New<Implements_Var_Closure> *varClosureType=cm->getFnType();
    const Implements_Closure_Type<void *> *cmdType=cm->getCmdType();
    std::string* whyNot=nullptr;
    if (checkErrors)
      whyNot=new std::string;
     while (!istream->eof())
       {

         Implements_Var v;
          Implements_Var_Closure ic;
          ABC_Closure* c;


          if (cmdType->getClosure(cm,c,istream,whyNot,""))
            {
              if (ostream!=nullptr)
                 c->putMe(cm,ostream,whyNot,"");
              c->evalData(cm);
              }
          else if(varClosureType->getValue(cm,ic,istream,whyNot,""))
            {
              if (ostream!=nullptr)
                 varClosureType->putValue(cm,ic,ostream,whyNot,"");
              cm->pushVar({ic.id,ic.closure->evalData(cm),ic.Tip,ic.WhatThis});

            }
          else if (varType->getValue(cm,v,istream,whyNot,""))
            {
              if (ostream!=nullptr)
                 varClosureType->putValue(cm,ic,ostream,whyNot,"");
              cm->pushVar(v);
            }
    }
     return true;
  }


}
