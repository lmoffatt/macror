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



      struct numStates_Field
      {
        typedef std::size_t myC;
        static std::string myId(){return "numStates";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "number of channel states";}
        static std::string myWhatThis() {return "number of different states in the model";}
      };

      struct Q_matrix_Type{
        typedef Markov_LA::M_Matrix<double> myC;
        static std::string myId(){return "Q_matrix_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return " state transition probability rates or  Q matrices";}
        static std::string myWhatThis() {return "";}

        static bool comply(const Implements_ComplexVar_New* cm
                           ,const myC& x
                           ,const Implements_ComplexVar_New*
                           ,std::string *WhyNot
                           , const std::string& objective)
        {
          std::size_t numstates;
          if (!cm->getValueFromId(numStates_Field::myId(),numstates,WhyNot,objective))
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
              (cm,myId(),myIdType(),myTip(),myWhatThis(),
               Cls<double>::name(),&comply,nullptr,&typeElementComply
               ,nullptr,nullptr,nullptr);
        }

      };
      struct Q_matrix_Field  {
        typedef Markov_LA::M_Matrix<double> myC;

        static std::string myId(){return "Q_matrix";}
        static std::string myIdType(){return Q_matrix_Type::myId();}
        static std::string myTip(){return "a transition probability rate matrix";}
        static std::string myWhatThis() {return "";}
      };


      struct conductance_vector_Type
      {

        typedef  Markov_LA::M_Matrix<double> myC;
        static std::string myId(){return "conductance_vector_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "the class of relative conductance by state";}
        static std::string myWhatThis() {return "";}

        static bool comply
        (const Implements_ComplexVar_New* cm
         ,const Markov_LA::M_Matrix<double>& x
         ,const Implements_ComplexVar_New* self,
         std::string *WhyNot
         , const std::string& objective)
        {
          std::size_t numstates;
          if (!cm->getValueFromId(numStates_Field::myId(),numstates,WhyNot,objective))
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
              (cm,myIdType(),"","transition probability rate"," more exp",
               Cls<double>::name(),&comply,nullptr,nullptr
               ,nullptr,nullptr,nullptr);
        }
      };


      struct conductance_vector_Field
      {

        typedef  Markov_LA::M_Matrix<double> myC;
        static std::string myId(){return "conductance_vector";}
        static std::string myIdType(){return conductance_vector_Type::myId();}
        static std::string myTip(){return "relative conductance by state";}
        static std::string myWhatThis() {return "";}
      };



      struct agonist_vector_type
      {
        typedef  Markov_LA::M_Matrix<std::size_t> myC;
        static std::string myId(){return "agonist_vector_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "number of bound agonist at each states";}
        static std::string myWhatThis() {return "";}

        static bool comply
        (const Implements_ComplexVar_New* cm
         ,const myC& x
         ,const Implements_ComplexVar_New* self,
         std::string *WhyNot
         , const std::string& objective)
        {
          std::size_t numstates;
          if (!cm->getValueFromId(numStates_Field::myId(),numstates,WhyNot,objective))
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
              (cm,myId(),myIdType(),myTip(),myWhatThis(),
               Cls<double>::name(),&comply,nullptr,nullptr
               ,nullptr,nullptr,nullptr);
        }
      };

      struct agonist_vector_field
      {
        typedef  Markov_LA::M_Matrix<std::size_t> myC;
        static std::string myId(){return "agonist_vector";}
        static std::string myIdType(){return agonist_vector_type::myId();}
        static std::string myTip(){return "number of bound agonist at each states";}
        static std::string myWhatThis() {return "";}
      };

      struct unitary_conductance_field
      {
        typedef  double myC;
        static std::string myId(){return "unitary_conductance";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "number of bound agonist at each states";}
        static std::string myWhatThis() {return "";}
      };

      struct Q_Markov_Model_type {
        typedef Markov_Mol_New::ABC_Markov_Model myB;
        typedef Markov_Mol_New::Q_Markov_Model myC;

        static std::string myId(){return "my"+Cls<myC>::name();}
        static std::string myIdType(){return "a"+Cls<myC>::name();}
        static std::string myTip(){return "model of channel kinetics";}
        static std::string myWhatThis(){return "";}


        static Implements_Data_Type_New<myC*>*
        varType(const Implements_ComplexVar_New* cm);
};

      class Implements_Data_Type_class_ABC_Markov_Model
          :public _private::Implements_Data_Type_class<ABC_Markov_Model*>
      {
      public:
        typedef ABC_Markov_Model myC;

       Implements_Data_Type_class_ABC_Markov_Model
        (const Implements_ComplexVar_New* parent,
         const std::string& id
         ,const std::string& var
         ,const std::string& myTip
         ,const std::string& myWhatThis
         , const std::map<std::string,ABC_Var_New*> fields
         ,typePredicate complyPred
         ,typetypePredicate typeComply
         ,getEmptyObject  defaultValue
         ):
          Implements_Data_Type_class<ABC_Markov_Model*>(
            parent,id,var,myTip,myWhatThis,fields,complyPred,typeComply,defaultValue,nullptr,nullptr)
        {}

       Implements_Data_Type_class_ABC_Markov_Model
        (const Implements_ComplexVar_New* parent)
          :Implements_Data_Type_class<ABC_Markov_Model*>
           (parent,Cls<myC*>::name(),Cls<myC*>::name(),"","",
       {},nullptr,nullptr,nullptr,nullptr,nullptr)
        {}
       };



      class Implements_Data_Type_class_Q_Markov_Model
          :public Implements_Data_Type_class_ABC_Markov_Model
      {
      public:
        typedef Q_Markov_Model myC;
        typedef ABC_Markov_Model myB;

private:
        static myC* map2obj(const Implements_ComplexVar_New* cm,
                            const std::map<std::string,ABC_Var_New*>& m
                            ,const Implements_ComplexVar_New* v
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



        static  std::map<std::string,ABC_Var_New*> objB2map
        (const Implements_ComplexVar_New* cm,
         const myB* Q
         ,const Implements_ComplexVar_New* v
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


        static  std::map<std::string,ABC_Var_New*> obj2map
        (const Implements_ComplexVar_New* cm,
         const myC* Q
         ,const Implements_ComplexVar_New* v
         , std::string* WhyNot, const std::string& masterObjective)
        {
          std::map<std::string,ABC_Var_New*> f;
          push_var<numStates_Field>(f,Q->k());
          push_var<Q_matrix_Field>(f,Q->Q());

          Markov_LA::M_Matrix<double> g=Q->g();
          double gamma=Q->gamma();
          g=g/gamma;

          push_var<conductance_vector_Field>(f,g);
          push_var<agonist_vector_field>(f,Q->n_bound_agonists());
          push_var<unitary_conductance_field>(f,gamma);

          return f;
        }

      static std::map<std::string,ABC_Var_New*> getFields()
      {
        std::map<std::string,ABC_Var_New*> f;
        push_var<numStates_Field>(f);
        push_var<Q_matrix_Field>(f);
        push_var<conductance_vector_Field>(f);
        push_var<agonist_vector_field>(f);
        push_var<unitary_conductance_field>(f);
        return f;
      }



      public:
        using getClass_type=  myC* (*)(const Implements_ComplexVar_New *cm, const std::map<std::string, ABC_Var_New *>& m,
        const Implements_ComplexVar_New* self,
        std::string *WhyNot, const std::string &masterObjective);

        using getCVFromBase_type=   std::map<std::string, ABC_Var_New *> (*)(const Implements_ComplexVar_New *cm, const myB *v,
        const Implements_ComplexVar_New* self,
        std::string *WhyNot, const std::string &masterObjective);

        using getCV_type=   std::map<std::string, ABC_Var_New *> (*)(const Implements_ComplexVar_New *cm, const myC *v,
        const Implements_ComplexVar_New* self,
        std::string *WhyNot, const std::string &masterObjective);





        Implements_Data_Type_class_Q_Markov_Model
        (const Implements_ComplexVar_New* parent,
         const std::string& id
         ,const std::string& var
         ,const std::string& myTip
         ,const std::string& myWhatThis
         ,const std::map<std::string,ABC_Var_New*>& fields
         ,typePredicate complyPred
         ,typetypePredicate typeComply
         ,getEmptyObject  defaultValue
         ,getCVFromBase_type getCVB
         ,getCV_type getCV
         ,getClass_type getObj
         ):
          Implements_Data_Type_class_ABC_Markov_Model(
            parent,id,var,myTip,myWhatThis,fields,complyPred,typeComply,defaultValue)
        ,getCVB_(getCVB),getCV_(getCV),getObj_(getObj)
        {}

        Implements_Data_Type_class_Q_Markov_Model
        (const Implements_ComplexVar_New* parent):
          Implements_Data_Type_class_ABC_Markov_Model(
            parent,Cls<myC>::name(),ClassName()
            ,"basic model representation","",getFields(),nullptr,nullptr,nullptr)
        ,getCVB_(&objB2map),getCV_(&obj2map),getObj_(&map2obj)
        {}


        // Implements_Data_Type_class<T *> interface
      public:
        virtual Q_Markov_Model *getClass(const Implements_ComplexVar_New *cm, std::map<std::string, ABC_Var_New *> m, std::string *WhyNot, const std::string &masterObjective) const override
        {
          return (*getObj_)(cm,m,this,WhyNot,masterObjective);
        }




        virtual std::map<std::string, ABC_Var_New *> getComplexMap(const Implements_ComplexVar_New *cm, const ABC_Markov_Model *v, std::string *WhyNot, const std::string &masterObjective) const override
        {
          return (*getCVB_)(cm,v,this,WhyNot,masterObjective);
        }


        virtual std::map<std::string, ABC_Var_New *> getComplexMap(const Implements_ComplexVar_New *cm, const Q_Markov_Model *v, std::string *WhyNot, const std::string &masterObjective) const
        {
          return (*getCV_)(cm,v,this,WhyNot,masterObjective);

        }


      private:
        getCVFromBase_type getCVB_;
        getCV_type getCV_;
        getClass_type getObj_;


      };


    }
    

    void push_Types(Markov_CommandManagerVar* cm);
    
  }
}



#endif // MYTYPES_H
