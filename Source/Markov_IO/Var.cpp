#include "Markov_IO/Var.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/buildByToken.h"
#include "Markov_IO/VarTempl.h"
#include "Markov_IO/StructureEnv_templ.h"
namespace Markov_IO_New {

  //  template class Implements_Value_New<double>;

  //  template class Implements_Value_New<int>;

  //  template class Implements_Value_New<std::size_t>;


  //  template class Implements_Value_New<std::vector<double>>;

  //  template class Implements_Value_New<std::set<double>>;

  //  template class Implements_Value_New<Markov_LA::M_Matrix<double>>;

  //  template class Implements_Value_New<Markov_LA::M_Matrix<std::size_t>>;

  //  template class Implements_Value_New<std::vector<int>>;

  //  template class Implements_Value_New<std::map<std::size_t,double>>;

  //  template class Implements_Value_New<ABC_Data_New*>;

  //  template class Implements_Value_New<Implements_Var>;


  namespace
  _private{


    template class Implements_Data_Type_New_regular<double>;

    template class Implements_Data_Type_New_vector<double> ;


    template class Implements_Data_Type_New_M_Matrix<double>;

    template class Implements_Data_Type_New_map<std::string,double> ;

    const ABC_Type_of_Value *Implements_Value_Base_New<void>::myType() const
    {
      return varType_;
    }





  }

  bool StructureEnv_New::hasNameofType(const std::string &name, const std::string &type, bool recursive, std::string *whyNot, const std::string &masterObjective) const
  {
    auto it=vars_.find(name);
    if (it==vars_.end())
      {
        if(!recursive||(parent()==nullptr))
          {
            if (whyNot!=nullptr)
              *whyNot=masterObjective+": "+name+" is not a name in ";
            return false;
          }
        else return parent()->hasNameofType(name, type,recursive,whyNot,masterObjective);
      }
    else
      {
        auto t=idToType(type,whyNot,masterObjective);
        if (t==nullptr)
          return false;
        else
          {
            const ABC_Data_New* v=it->second;
            return t->isDataInDomain(this,v,whyNot,masterObjective);
          }
      }

  }





  bool StructureEnv_New::hasTypeofType(const std::string &name, const std::string &type, std::string *whyNot, const std::string &masterObjective, bool recursive) const
  {
    auto it=types_.find(name);
    if (it==types_.end())
      {
        if(!recursive||(parent()==nullptr))
          {
            *whyNot=masterObjective+": "+name+" is not a type in ";
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
            return t->includesThisType(this,name,whyNot,masterObjective);
          }
      }

  }

  bool StructureEnv_New::hasFunction_returningType(const std::string &name, const std::string &type, std::string *whyNot, const std::string &masterObjective, bool recursive) const
  {
    auto it=R_funcs_.find(type);
    if (it==R_funcs_.end())
      {
        if(!recursive||(parent()==nullptr))
          {
            *whyNot=masterObjective+": "+type+" is not returned by any function ";
            return false;
          }
        else
          return parent()->hasFunction_returningType(name, type,whyNot,masterObjective,recursive);
      }

    else
      {
        auto it2=it->second.find(name);
        if (it2==it->second.end())
          {
            if(!recursive||(parent()==nullptr))
              {
                *whyNot=masterObjective+": "+name+" does not returned a "+type;
                return false;
              }
            else
              return parent()->hasFunction_returningType
                  (name, type,whyNot,masterObjective,recursive);
          }
        else
          {

                return true;
          }
      }
  }





  std::vector<std::string> StructureEnv_New::getIdsOfVarType(const std::string &varType,bool recursive) const
  {
    std::vector<std::string> o;
    if (varType.empty())
      {
        o=idVars_;
      }
    else
      {
        for (const auto &id:idVars_)
          if (hasNameofType(id,varType,false))
            o.push_back(id);
      }
    if (recursive&& parent()!=nullptr)
      {
        o+=parent()->getIdsOfVarType(varType,recursive);
      }
    return o;
  }


  std::set<std::string> StructureEnv_New::getIdsOfCmds(bool recursive) const
  {
    std::set<std::string> o;
    if (recursive&& parent()!=nullptr)
      {
        o=parent()->getIdsOfCmds(recursive);
      }
        auto s=getMapKeys(cmds_);
        s.insert(o.begin(),o.end());
        return s;
    }




  std::set<std::string> StructureEnv_New::getIdsOfFncType(const std::string &fucnType,bool recursive) const
  {
    std::set<std::string> o;
    if (recursive&& parent()!=nullptr)
      {
        o=parent()->getIdsOfFncType(fucnType,recursive);
      }
    if (fucnType.empty())
      {
        auto s=getMapKeys(funcs_);
        s.insert(o.begin(),o.end());
        return s;
      }
    else
      {
        auto it=R_funcs_.find(fucnType);
        if (it!=R_funcs_.end())
          {
            auto s=getMapKeys(it->second);
            s.insert(o.begin(),o.end());
            return s;
          }
        else return {};
      }
  }


  std::string StructureEnv_New::defaultIdOfVarType(const std::string &varType,bool recursive) const
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
            ABC_Data_New* var=p.second;
            std::string why;
            if (t->isDataInDomain(this,var,&why,objective))
              return p.first;
          }
        if (!recursive || parent()==nullptr)
          return {};
        else return parent()->defaultIdOfVarType(varType,recursive);

      }
  }





  std::string StructureEnv_New::defaultIdOfTypeType(const std::string &typeType,bool recursive) const
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
            std::string why;
            if (t->includesThisType(this,p.first,&why,objective))
              return p.first;
          }
        if (!recursive || parent()==nullptr)
          return {};
        else return parent()->defaultIdOfTypeType(typeType,recursive);

      }
  }




  std::set<std::string> StructureEnv_New::getIdsOfTypeType(const std::string &typeType, bool recursive) const
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
            std::string why;
            if (t->includesThisType(this,p.first,&why,objective))
              s.insert(p.first);
          }
        s.insert(o.begin(),o.end());
        return s;
      }
  }














}
