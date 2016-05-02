#include "Markov_IO/Var.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/buildByToken.h"

namespace Markov_IO_New {

  template class Implements_Var_New<double>;

  template class Implements_Var_New<std::vector<double>>;

  template class Implements_Var_New<std::set<double>>;

  template class Implements_Var_New<Markov_LA::M_Matrix<double>>;


  namespace
  _private{


    template class Implements_Data_Type_New_regular<double>;

    template class Implements_Data_Type_New_vector<double> ;


    template class Implements_Data_Type_New_M_Matrix<double>;

    template class Implements_Data_Type_New_map<std::string,double> ;

  }

  bool Implements_ComplexVar_New::hasNameofType(const std::string &name, const std::string &type, std::string *whyNot, const std::string &masterObjective, bool recursive) const
  {
    auto it=vars_.find(name);
    if (it==vars_.end())
      {
        if(!recursive||(parent()==nullptr))
          {
            *whyNot=masterObjective+": "+name+" is not a name in "+this->id();
            return false;
          }
        else return parent()->hasNameofType(name, type,whyNot,masterObjective,recursive);
      }
    else
      {
        auto t=parent()->idToType(type,whyNot,masterObjective);
        if (t==nullptr)
          return false;
        else
          {
            const ABC_Var_New* v=it->second;
            return t->isVarInDomain(parent(),v->value(),whyNot,masterObjective);
          }
      }

  }


  bool Implements_ComplexVar_New::hasCmdofType(const std::string &name, const std::string &type, std::string *whyNot, const std::string &masterObjective, bool recursive) const
  {
    auto it=cmds_.find(name);
    if (it==cmds_.end())
      {
        if(!recursive||(parent()==nullptr))
          {
            *whyNot=masterObjective+": "+name+" is not a name in "+this->id();
            return false;
          }
        else return parent()->hasCmdofType(name, type,whyNot,masterObjective,recursive);
      }
    else
      {
        auto t=parent()->idToCommand(type,whyNot,masterObjective);
        if (t==nullptr)
          return false;
        else
          {
            const Implements_Command_Type_New* v=it->second;
            return t->isTypeInDomain(parent(),v,whyNot,masterObjective);
          }
      }

  }




  bool Implements_ComplexVar_New::hasTypeofType(const std::string &name, const std::string &type, std::string *whyNot, const std::string &masterObjective, bool recursive) const
  {
    auto it=types_.find(name);
    if (it==types_.end())
      {
        if(!recursive||(parent()==nullptr))
          {
            *whyNot=masterObjective+": "+name+" is not a type in "+this->id();
            return false;
          }
        else
          return parent()->hasTypeofType(name, type,whyNot,masterObjective,recursive);
      }
    else
      {
        auto t=idToType(type,whyNot,masterObjective);
        if (t==nullptr)
          return false;
        else
          {
            const ABC_Type_of_Value* subt=it->second;
            return t->isTypeInDomain(this,subt,whyNot,masterObjective);
          }
      }

  }





  std::set<std::string> Implements_ComplexVar_New::getIdsOfVarType(const std::string &varType,bool recursive) const
  {
    std::set<std::string> o;
    if (recursive&& parent()!=nullptr)
      {
        o=parent()->getIdsOfVarType(varType,recursive);
      }
    std::string whyNot;
    std::string objective;
    if (varType.empty())
      {
        auto s=alternatives::getIdofVar(vars_);
        s.insert(o.begin(),o.end());
        return s;
      }
    else
      {
        const ABC_Type_of_Value* t=idToType(varType,&whyNot,objective);
        std::set<std::string> s;
        for (const auto &p:vars_)
          {
            ABC_Var_New* var=p.second;
            std::string why;
            if (t->isVarInDomain(this,var->value(),&why,objective))
              alternatives::insert(s,var);
          }
        s.insert(o.begin(),o.end());
        return s;
      }
  }


  std::set<std::string> Implements_ComplexVar_New::getIdsOfCmdType(const std::string &cmdType,bool recursive) const
  {
    std::set<std::string> o;
    if (recursive&& parent()!=nullptr)
      {
        o=parent()->getIdsOfCmdType(cmdType,recursive);
      }
    std::string whyNot;
    std::string objective;
    if (cmdType.empty())
      {
        auto s=getMapKeys(cmds_);
        s.insert(o.begin(),o.end());
        return s;
      }
    else
      {
        const Implements_Command_Type_New* t=
            idToCommand(cmdType,&whyNot,objective);
        std::set<std::string> s;
        for (const auto &p:cmds_)
          {
            Implements_Command_Type_New* cmd=p.second;
            std::string why;
            if (t->isTypeInDomain(this,cmd,&why,objective))
              s.insert(cmd->id());
          }
        s.insert(o.begin(),o.end());
        return s;
      }
  }



  std::string Implements_ComplexVar_New::defaultIdOfVarType(const std::string &varType,bool recursive) const
  {
    std::string whyNot;
    std::string objective;
    if (varType.empty())
      {
        if (!vars_.empty())
          {
            return vars_.begin()->first;
          }
        else if (!recursive || parent()==nullptr)
          return {};
        else return parent()->defaultIdOfVarType(varType,recursive);


      }
    else
      {
        const ABC_Type_of_Value* t=idToType(varType,&whyNot,objective);
        for (const auto &p:vars_)
          {
            ABC_Var_New* var=p.second;
            std::string why;
            if (t->isVarInDomain(this,var->value(),&why,objective))
              return var->id();
          }
        if (!recursive || parent()==nullptr)
          return {};
        else return parent()->defaultIdOfVarType(varType,recursive);

      }
  }


  std::string Implements_ComplexVar_New::defaultIdOfCmdType(const std::string &cmdType,bool recursive) const
  {
    std::string whyNot;
    std::string objective;
    if (cmdType.empty())
      {
        if (!cmds_.empty())
          {
            return cmds_.begin()->first;
          }
        else if (!recursive || parent()==nullptr)
          return {};
        else return parent()->defaultIdOfCmdType(cmdType,recursive);


      }
    else
      {
        const Implements_Command_Type_New* t=
            idToCommand(cmdType,&whyNot,objective);
        for (const auto &p:cmds_)
          {
            Implements_Command_Type_New* cmd=p.second;
            std::string why;
            if (t->isTypeInDomain(this,cmd,&why,objective))
              return cmd->id();
          }
        if (!recursive || parent()==nullptr)
          return {};
        else return parent()->defaultIdOfCmdType(cmdType,recursive);

      }
  }




  std::string Implements_ComplexVar_New::defaultIdOfTypeType(const std::string &typeType,bool recursive) const
  {
    std::string whyNot;
    std::string objective;
    if (typeType.empty())
      {
        if (!types_.empty())
          {
            return types_.begin()->first;
          }
        else if (!recursive || parent()==nullptr)
          return {};
        else return parent()->defaultIdOfTypeType(typeType,recursive);
      }
    else
      {
        const ABC_Type_of_Value* t=idToType(typeType,&whyNot,objective);
        for (const auto &p:types_)
          {
            ABC_Type_of_Value* var=p.second;
            std::string why;
            if (t->isTypeInDomain(this,var,&why,objective))
              return var->id();
          }
        if (!recursive || parent()==nullptr)
          return {};
        else return parent()->defaultIdOfTypeType(typeType,recursive);

      }
  }



  std::string Implements_ComplexVar_New::defaultIdOfCommand(const std::string &idCmd,bool recursive) const
  {
    std::string whyNot;
    std::string objective;
    if (idCmd.empty())
      {
        if (!cmds_.empty())
          {
            return cmds_.begin()->first;
          }
        else if (!recursive || parent()==nullptr)
          return {};
        else return parent()->defaultIdOfCommand(idCmd,recursive);
      }
    else
      {
        const Implements_Command_Type_New* t=idToCommand(idCmd,&whyNot,objective);
        for (const auto &p:cmds_)
          {
            const Implements_Command_Type_New* var=p.second;
            std::string why;
            if (t->isTypeInDomain(this,var,&why,objective))
              return var->id();
          }
        if (!recursive || parent()==nullptr)
          return {};
        else return parent()->defaultIdOfTypeType(idCmd,recursive);

      }
  }


  std::set<std::string> Implements_ComplexVar_New::getIdsOfTypeType(const std::string &typeType, bool recursive) const
  {
    std::set<std::string> o;
    if (recursive&& parent()!=nullptr)
      {
        o=parent()->getIdsOfTypeType(typeType,recursive);
      }
    std::string whyNot;
    std::string objective;
    if (typeType.empty())
      {
        auto s=getMapKeys(types_);
        s.insert(o.begin(),o.end());
        return s;
      }
    else
      {
        const ABC_Type_of_Value* t=idToType(typeType,&whyNot,objective);
        std::set<std::string> s;
        for (const auto &p:types_)
          {
            const ABC_Type_of_Value* var=p.second;
            std::string why;
            if (t->isTypeInDomain(this,var,&why,objective))
              s.insert(var->id());
          }
        s.insert(o.begin(),o.end());
        return s;
      }
  }












  //  const Implements_Field_Data_Type * Implements_Data_Type_New<Implements_ComplexVar_New *>::nextField(const Implements_ComplexVar_New *cm, const std::map<std::string, ABC_Var_New *> &m)const
  //  {
  //    return (*nextField_)(cm,m,this);
  //  }

  //  template<>
  //  buildByToken<ABC_Var_New *> Implements_Data_Type_New<Implements_ComplexVar_New *>::getFieldBuildByToken(const Implements_ComplexVar_New *cm, std::map<std::string, ABC_Var_New *> m) const
  //  {
  //    const Implements_Field_Data_Type* f=nextField(cm,m);
  //    return buildByToken<ABC_Var_New*>(cm,f);
  //  }

  bool ABC_Var_New::isOfThisType(const Implements_ComplexVar_New* cm,
                                 const std::string& generalType,
                                 std::string* whyNot
                                 ,const std::string &masterObjective)const
  {
    if (myType()==generalType)
      return true;
    else
      {
        const ABC_Type_of_Value* mytype=cm->idToType(myType(),whyNot,masterObjective);
        if ((mytype==nullptr)||(mytype->myType()==mytype->id()))
          return false;
        else
          return mytype->isOfThisType(cm,generalType,whyNot,masterObjective);
      }
  }






}
