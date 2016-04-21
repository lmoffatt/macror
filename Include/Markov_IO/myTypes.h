#ifndef MYTYPES_H
#define MYTYPES_H
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_Console/Markov_CommandManager.h"

#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixAritmetic.h"
namespace Markov_IO_New {
  
  using Markov_Mol_New::Q_Markov_Model;
  using Markov_Mol_New::ABC_Markov_Model;
  namespace _private
  {
  namespace _model {
    template<class C>
    void push_var(std::map<std::string,ABC_Var_New*>& m
                  ,typename C::myC val={}
                  , const std::string idVar=C::idVar()
                  , const std::string& tip=C::Tip()
                  , const std::string& whatthis=C::WhatThis()  )
    {
       m[idVar]=new Implements_Var_New<typename C::myC>
           (nullptr,idVar,C::idType(),val,tip,whatthis);
    }

    template <class Field>
    bool get_var(const std::map<std::string,ABC_Var_New*>& m, typename Field::myC& val
             ,std::string* whyNot,const std::string& masterObjective )
    {
        auto it=m.find(Field::idVar());
        if (it==m.end())
          {
            *whyNot=masterObjective+": field "+Field::idVar()+" not found";
            return false;
          }
        else
          {
            ABC_Var_New* o=it->second;
            if (o==nullptr)
              {
                *whyNot=masterObjective+": field "+Field::idVar()+" is null";
                return false;
              }
            else
              {
                auto v=dynamic_cast<Implements_Var_New<typename Field::myC>*>(o);
                if (v==nullptr)
                  {
                    *whyNot=masterObjective+": field "+Field::idVar()+" is of wrong type: "
                        +o->myType()+" instead of "+ Field::idType();
                    return false;
                  }
                else
                  {
                    val=v->value()->getValued();
                    return true;
                  }

              }
          }
    }




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


    struct numStates_Field
    {
      typedef std::size_t myC;
      static std::string idVar(){return "numStates";}
      static std::string idType(){return Cls<myC>::name();}
      static std::string Tip(){return "number of channel states";}
      static std::string WhatThis() {return "number of different states in the model";}
   };
    
    struct Q_matrix_Type{
      typedef Markov_LA::M_Matrix<double> myC;
      static std::string idVar(){return "Q_matrix_type";}
      static std::string idType(){return Cls<myC>::name();}
      static std::string Tip(){return " state transition probability rates or  Q matrices";}
      static std::string WhatThis() {return "";}

      static bool comply(const Implements_ComplexVar_New* cm
                         ,const myC& x
                         ,const Implements_ComplexVar_New*
                         ,std::string *WhyNot
                         , const std::string& objective)
      {
        std::size_t numstates;
        if (!cm->getValueFromId(numStates_Field::idVar(),numstates,WhyNot,objective))
          return false;
        if (!Matrix<double>::Comply::Size(x,numstates,numstates,WhyNot,objective))
          return false;
        if (!Matrix<double>::Comply::OffDiagPositive(x,WhyNot,objective))
          return false;
        if (!Matrix<double>::Comply::RowSumIsZero(x,WhyNot,objective))
          return false;
        if (!Matrix<double>::Comply::FiniteEquilibrium(x,WhyNot,objective))
          return false;
        return true;
      }

      static bool typeElementComply
      (const Implements_ComplexVar_New* cm
       ,const myC & m
       ,typename myC::const_iterator it
       ,const double& x
       ,const _private::Implements_Container_Type_New<double,Markov_LA::M_Matrix>* v
       , std::string *WhyNot, const std::string& objective)
      {
        std::size_t i=it.iRow();
        std::size_t j=it.jCol();
        if (i==j)
          {
            if (x==0)
              return true;
            else
              {
                *WhyNot=objective+": nonzero value at i="+std::to_string(i)
                    +" j="+std::to_string(j);
                return false;
              }
          }
        else if (x<0)
          {
            *WhyNot=objective+": negative value at i="+std::to_string(i)
                +" j="+std::to_string(j);
            return false;
          }
        else if (j>i) {return true;}
        else  {
            if (m(j,i)==0)
              {
                if (x>0)
                  {
                    *WhyNot=objective
                        +": forward rate zero and backward positive at i="
                        +std::to_string(i)
                        +" j="+std::to_string(j);
                    return false;
                  }
                else return true;
              }
            else {
                if (x==0)
                  {
                    *WhyNot=objective
                        +": forward rate positive and backward zero at i="
                        +std::to_string(i)
                        +" j="+std::to_string(j);
                    return false;
                  }
                else
                  return true;
              }}
      }


      static Implements_Data_Type_New<myC>*
      varType(const Implements_ComplexVar_New* cm)
      {
        return new Implements_Data_Type_New<myC>
            (cm,idVar(),idType(),Tip(),WhatThis(),
               Cls<double>::name(),&comply,nullptr,&typeElementComply
               ,nullptr,nullptr,nullptr);
      }

    };
    struct Q_matrix_Field  {
      typedef Markov_LA::M_Matrix<double> myC;

      static std::string idVar(){return "Q_matrix";}
      static std::string idType(){return Q_matrix_Type::idVar();}
      static std::string Tip(){return "a transition probability rate matrix";}
      static std::string WhatThis() {return "";}
    };

    
    struct conductance_vector_Type
    {

      typedef  Markov_LA::M_Matrix<double> myC;
      static std::string idVar(){return "conductance_vector_type";}
      static std::string idType(){return Cls<myC>::name();}
      static std::string Tip(){return "the class of relative conductance by state";}
      static std::string WhatThis() {return "";}

      static bool comply
      (const Implements_ComplexVar_New* cm
       ,const Markov_LA::M_Matrix<double>& x
       ,const Implements_ComplexVar_New* self,
       std::string *WhyNot
       , const std::string& objective)
      {
        std::size_t numstates;
        if (!cm->getValueFromId(numStates_Field::idVar(),numstates,WhyNot,objective))
          return false;
        if (!Matrix<double>::Comply::Size(x,numstates,1,WhyNot,objective))
          return false;
        if (!Matrix<double>::Comply::notAllZero(x,WhyNot,objective))
          return false;
        
        return true;
      }
      
      static Implements_Data_Type_New<myC>*
      varType(const Implements_ComplexVar_New* cm)
      {
        return new Implements_Data_Type_New<myC>
            (cm,idType(),"","transition probability rate"," more exp",
               Cls<double>::name(),&comply,nullptr,nullptr
               ,nullptr,nullptr,nullptr);
      }
    };
    

    struct conductance_vector_Field
    {

      typedef  Markov_LA::M_Matrix<double> myC;
      static std::string idVar(){return "conductance_vector";}
      static std::string idType(){return conductance_vector_Type::idVar();}
      static std::string Tip(){return "relative conductance by state";}
      static std::string WhatThis() {return "";}
    };



    struct agonist_vector_type
    {
      typedef  Markov_LA::M_Matrix<std::size_t> myC;
      static std::string idVar(){return "agonist_vector_type";}
      static std::string idType(){return Cls<myC>::name();}
      static std::string Tip(){return "number of bound agonist at each states";}
      static std::string WhatThis() {return "";}

      static bool comply
      (const Implements_ComplexVar_New* cm
       ,const myC& x
       ,const Implements_ComplexVar_New* self,
       std::string *WhyNot
       , const std::string& objective)
      {
        std::size_t numstates;
        if (!cm->getValueFromId(numStates_Field::idVar(),numstates,WhyNot,objective))
          return false;
        if (!Matrix<double>::Comply::Size(x,numstates,1,WhyNot,objective))
          return false;
        if (!Matrix<double>::Comply::notAllZero(x,WhyNot,objective))
          return false;

        return true;
      }

      static Implements_Data_Type_New<myC>*
      varType(const Implements_ComplexVar_New* cm)
      {
        return new Implements_Data_Type_New<myC>
            (cm,idVar(),idType(),Tip(),WhatThis(),
               Cls<double>::name(),&comply,nullptr,nullptr
               ,nullptr,nullptr,nullptr);
      }
    };

    struct agonist_vector_field
    {
      typedef  Markov_LA::M_Matrix<std::size_t> myC;
      static std::string idVar(){return "agonist_vector";}
      static std::string idType(){return agonist_vector_type::idVar();}
      static std::string Tip(){return "number of bound agonist at each states";}
      static std::string WhatThis() {return "";}
    };

    struct unitary_conductance_field
    {
      typedef  double myC;
      static std::string idVar(){return "unitary_conductance";}
      static std::string idType(){return Cls<myC>::name();}
      static std::string Tip(){return "number of bound agonist at each states";}
      static std::string WhatThis() {return "";}
    };
    
    struct Q_Markov_Model_type {
      typedef Markov_Mol_New::ABC_Markov_Model myB;
      typedef Markov_Mol_New::Q_Markov_Model myC;
      
      static std::string idVar(){return "my"+Cls<myC>::name();}
      static std::string idType(){return "a"+Cls<myC>::name();}
      static std::string Tip(){return "model of channel kinetics";}
      static std::string WhatThis(){return "";}

      static  std::map<std::string,ABC_Var_New*> obj2map
      (const Implements_ComplexVar_New* cm,
      const Markov_Mol_New::ABC_Markov_Model* Q
       ,const Implements_Data_Type_class<Markov_Mol_New::ABC_Markov_Model*>* v
      , std::string* WhyNot, const std::string& masterObjective)
      {
        std::map<std::string,ABC_Var_New*> f;
        push_var<numStates_Field>(f,Q->k());
        push_var<Q_matrix_Field>(f,Q->Q());

        Markov_LA::M_Matrix<double> g=Q->g();
        double gamma=Markov_LA::maxAbs(g);
        g=g/gamma;

        push_var<conductance_vector_Field>(f,g);
        push_var<agonist_vector_field>(f,Q->n_bound_agonists());
        push_var<unitary_conductance_field>(f,gamma);

        return f;
       }

      static myB* map2obj(const Implements_ComplexVar_New* cm,
      const std::map<std::string,ABC_Var_New*>& m
      ,const Implements_Data_Type_class<Markov_Mol_New::ABC_Markov_Model*>* v
      ,std::string* WhyNot,
      const std::string& masterObjective)
      {
         numStates_Field::myC numSt;
         Q_matrix_Field::myC Q;
         conductance_vector_Field::myC g;
         agonist_vector_field::myC a;
         unitary_conductance_field::myC gamma;

         if (!get_var<numStates_Field>(m,numSt,WhyNot,masterObjective))
           return nullptr;
         else if (!get_var<Q_matrix_Field>(m,Q,WhyNot,masterObjective))
           return nullptr;
         else if (!get_var<conductance_vector_Field>(m,g,WhyNot,masterObjective))
           return nullptr;
         else if (!get_var<agonist_vector_field>(m,a,WhyNot,masterObjective))
           return nullptr;
         else if (!get_var<unitary_conductance_field>(m,gamma,WhyNot,masterObjective))
           return nullptr;
         else return new Markov_Mol_New::Q_Markov_Model(Q,g,a,gamma);

      }

      static Implements_Data_Type_New<myC*>*
      varType(const Implements_ComplexVar_New* cm);
      
      
    };
}
    

    void push_Types(Markov_CommandManagerVar* cm)
    {

      cm->pushType(_model::agonist_vector_type::varType(cm));
      cm->pushType(_model::conductance_vector_Type::varType(cm));
      cm->pushType(_model::Q_matrix_Type::varType(cm));
      cm->pushType(_model::Q_Markov_Model_type::varType(cm));
    }
    
  }
  }
  


#endif // MYTYPES_H
