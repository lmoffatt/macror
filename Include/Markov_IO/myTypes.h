#ifndef MYTYPES_H
#define MYTYPES_H
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Console/Markov_CommandManager.h"

#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
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

      inline
      std::size_t getNumStates(const StructureEnv_New* cm)
      {
        std::size_t numstates;
        std::string WhyNot;
        if (!cm->getValueFromId(numStates_Field::myId(),numstates,&WhyNot,""))
          return 0;
        else return numstates;

      }
      inline
      std::size_t oneDim(const StructureEnv_New*)
      {
        return 1;
      }

      struct Q_matrix_Type{

        typedef Q_matrix_Type selfType;
        typedef double elem;

        typedef ::Markov_LA::M_Matrix<elem> myC;
        typedef Implements_Data_Type_New<myC>  vType;

        static std::string myId(){return "Q_matrix_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return " state transition probability rates or  Q matrices";}
        static std::string myWhatThis() {return "";}

        static bool comply(const StructureEnv_New* cm
                           ,const myC& x
                           ,const vType* self
                           ,std::string *WhyNot
                           , const std::string& objective)
        {
          std::size_t numstates;
          if (!cm->getValueFromId(numStates_Field::myId(),numstates,WhyNot,objective))
            return false;
          if (!Matrix::Comply::Size<elem>(x,numstates,numstates,WhyNot,objective))
            return false;
          if (!Matrix::Comply::OffDiagPositive<elem>(x,WhyNot,objective))
            return false;
          //  if (!Matrix::Comply::RowSumIsZero<elem>(x,WhyNot,objective))
          //    return false;
          if (!Matrix::Comply::FiniteEquilibrium<elem>(x,WhyNot,objective))
            return false;
          return true;
        }
        static const Implements_Data_Type_New<elem>* elementType
        (const StructureEnv_New* cm, std::string *whyNot,const std::string& masterObjective)
        {
          return cm->idToTyped<elem>(Cls<elem>::name(),whyNot,masterObjective);
        }



        static Implements_Data_Type_New<elem>* nextElement (
            const StructureEnv_New* cm
            ,const std::vector<elem>& val,
            std::size_t ncol, std::size_t nrow
            ,std::size_t i, std::size_t j
            ,const Implements_Data_Type_New<myC>* self
            , std::string * whyNot, const std::string& masterObjective,
            Implements_Data_Type_New<elem>* source)
        {
          if (i==j)
            {
              return Real::types::Zero::varType(source);
            }
          else if (j>i)
            {
              return Real::types::nonZero::varType(source);
            }
          else
            {
              if (val[j+i*ncol]==elem(0))
                {
                  return Real::types::Zero::varType(source);
                }
              else {
                  return Real::types::nonZero::varType(source);
                }
            }
        }



        static std::size_t getColsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return getNumStates(cm);
        }

        static std::size_t getRowsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return getNumStates(cm);
        }

        static constexpr bool areColsFixed=true;
        static constexpr bool areRowsFixed=true;


        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm
                ,std::string* whyNot,const std::string& masterObjective)
        {
          auto d=elementType(cm,whyNot,masterObjective);
          if (d==nullptr)
            return nullptr;
          else
            {
              return new Implements_Data_Type_New<myC>
                  (d,&comply,&nextElement,&getColsNumber,&getRowsNumber
                   ,areColsFixed,areRowsFixed);
            }
        }

        static void push_Types(Markov_CommandManagerVar *cm)
        {
          cm->pushType<selfType>();
        }


      };


      struct Q_matrix_Field  {
        typedef ::Markov_LA::M_Matrix<double> myC;
        typedef Implements_Data_Type_New<myC> vType;


        static std::string myId(){return "Q_matrix";}
        static std::string myIdType(){return Q_matrix_Type::myId();}
        static std::string myTip(){return "a transition probability rate matrix";}
        static std::string myWhatThis() {return "";}
      };



      struct conductance_vector_Type
      {
        typedef conductance_vector_Type selfType;
        typedef double elem;

        typedef typename ::Markov_LA::M_Matrix<elem> myC;

        typedef Implements_Data_Type_New<myC> vType;
        static std::string myId(){return "conductance_vector_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "the class of relative conductance by state";}
        static std::string myWhatThis() {return "";}

        static bool comply
        (const StructureEnv_New* cm
         ,const myC & x
         ,const vType* self,
         std::string *WhyNot
         , const std::string& objective)
        {
          std::size_t numstates;
          if (!cm->getValueFromId(numStates_Field::myId(),numstates,WhyNot,objective))
            return false;
          if (!Matrix::Comply::Size<elem>(x,numstates,1,WhyNot,objective))
            return false;
          if (!Matrix::Comply::notAllZero<elem>(x,WhyNot,objective))
            return false;

          return true;
        }

        static const Implements_Data_Type_New<elem>* elementType
        (const StructureEnv_New* cm, std::string *whyNot,const std::string& masterObjective)
        {
          return cm->idToTyped<elem>(Cls<elem>::name(),whyNot,masterObjective);
        }

        static Implements_Data_Type_New<elem>* nextElement (
            const StructureEnv_New* cm
            ,const std::vector<elem>& val,
            std::size_t ncol, std::size_t nrow
            ,std::size_t i, std::size_t j
            ,const vType* self, std::string * whyNot, const std::string& masterObjective,
            Implements_Data_Type_New<elem>* source)
        {
          return source;
        }

        static std::size_t getColsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return oneDim(cm);
        }

        static std::size_t getRowsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return getNumStates(cm);
        }

        static constexpr bool areColsFixed=false;
        static constexpr bool areRowsFixed=false;


        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm
                ,std::string* whyNot,const std::string& masterObjective)
        {
          auto d=elementType(cm,whyNot,masterObjective);
          if (d==nullptr)
            return nullptr;
          else
            {
              return new Implements_Data_Type_New<myC>
                  (d,&comply,&nextElement,&getColsNumber,&getRowsNumber
                   ,areColsFixed,areRowsFixed);
            }
        }
        static void push_Types(Markov_CommandManagerVar *cm)
        {
          cm->pushType<selfType>();
        }

      };


      struct conductance_vector_Field
      {

        typedef  ::Markov_LA::M_Matrix<double> myC;
        typedef Implements_Data_Type_New<myC> vType;
        static std::string myId(){return "conductance_vector";}
        static std::string myIdType(){return conductance_vector_Type::myId();}
        static std::string myTip(){return "relative conductance by state";}
        static std::string myWhatThis() {return "";}
      };



      struct agonist_vector_type

      {
        typedef agonist_vector_type selfType;

        typedef std::size_t elem;
        typedef  ::Markov_LA::M_Matrix<elem> myC;
        typedef Implements_Data_Type_New<myC> vType;

        static std::string myId(){return "agonist_vector_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "number of bound agonist at each states";}
        static std::string myWhatThis() {return "";}


        static bool comply
        (const StructureEnv_New* cm
         ,const myC & x
         ,const vType* self,
         std::string *WhyNot
         , const std::string& objective)
        {
            std::size_t numstates;
            if (!cm->getValueFromId(numStates_Field::myId(),numstates,WhyNot,objective))
              return false;
            if (!Matrix::Comply::Size<elem>(x,numstates,1,WhyNot,objective))
              return false;

            return true;
          }

        static const Implements_Data_Type_New<elem>* elementType
        (const StructureEnv_New* cm, std::string *whyNot,const std::string& masterObjective)
        {
          return cm->idToTyped<elem>(Cls<elem>::name(),whyNot,masterObjective);
        }

        static std::size_t getColsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return oneDim(cm);
        }

        static std::size_t getRowsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return getNumStates(cm);
        }

        static constexpr bool areColsFixed=true;
        static constexpr bool areRowsFixed=true;


        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm
                ,std::string* whyNot=nullptr,const std::string& masterObjective="")
        {
          auto d=elementType(cm,whyNot,masterObjective);
          if (d==nullptr)
            return nullptr;
          else
            {
              return new Implements_Data_Type_New<myC>
                  (d,&comply,nullptr,&getColsNumber,&getRowsNumber
                   ,areColsFixed,areRowsFixed);
            }
        }


        static void push_Types(Markov_CommandManagerVar *cm)
        {
          cm->pushType<selfType>();
        }

      };

      struct agonist_vector_field
      {
        typedef  ::Markov_LA::M_Matrix<std::size_t> myC;
        typedef Implements_Data_Type_New<myC> vType;
        typedef agonist_vector_type myType;

        static std::string myId(){return "agonist_vector";}
        static std::string myIdType(){return myType::myId();}
        static std::string myTip(){return "number of bound agonist at each states";}
        static std::string myWhatThis() {return "";}
      };

      struct unitary_conductance_field
      {
        typedef  double myC;
        typedef Implements_Data_Type_New<myC> vType;

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
        varType(const StructureEnv_New* cm);
      };

      class Implements_Data_Type_class_ABC_Markov_Model
          :public ::Markov_IO_New::_private::Implements_Data_Type_class<ABC_Markov_Model*>
      {
      public:
        typedef ABC_Markov_Model myC;

        Implements_Data_Type_class_ABC_Markov_Model
        ( const std::vector<std::pair<Implements_Var,bool>> fields={}
            ,typePredicate complyPred=nullptr
            ):
          Implements_Data_Type_class<ABC_Markov_Model*>(fields,complyPred)
        {}

      };



      class Implements_Data_Type_class_Q_Markov_Model
          :public Implements_Data_Type_class_ABC_Markov_Model
      {
      public:
        typedef Q_Markov_Model myC;
        typedef ABC_Markov_Model myB;
        typedef Implements_Data_Type_class_Q_Markov_Model vType;

      private:
        static myC* map2obj(const StructureEnv_New* cm,
                            const StructureEnv_New* m
                            ,const vType* v
                            ,std::string* WhyNot,
                            const std::string& masterObjective)
        {
          numStates_Field::myC numSt;
          Q_matrix_Field::myC Q;
          conductance_vector_Field::myC g;
          agonist_vector_field::myC a;
          unitary_conductance_field::myC gamma;

          if (!m->getDataValue<numStates_Field>(numSt,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<Q_matrix_Field>(Q,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<conductance_vector_Field>(g,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<agonist_vector_field>(a,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<unitary_conductance_field>(gamma,WhyNot,masterObjective))
            return nullptr;
          else return new Markov_Mol_New::Q_Markov_Model(Q,g,a,gamma);

        }



        static  StructureEnv_New* objB2map
        (const StructureEnv_New* cm,
         const myB* Q
         ,const vType* v
         , std::string* WhyNot, const std::string& masterObjective)
        {
          auto f=new StructureEnv_New(cm,Cls<myB>::name());
          f->pushVar<numStates_Field>(Q->k());
          f->pushVar<Q_matrix_Field>(Q->Q());

          ::Markov_LA::M_Matrix<double> g=Q->g();
          double gamma=::Markov_LA::maxAbs(g);
          g=g/gamma;

          f->pushVar<conductance_vector_Field>(g);
          f->pushVar<agonist_vector_field>(Q->n_bound_agonists());
          f->pushVar<unitary_conductance_field>(gamma);

          return f;
        }


        static  StructureEnv_New* obj2map
        (const StructureEnv_New* cm,
         const myC* Q
         ,const vType* v
         , std::string* WhyNot, const std::string& masterObjective)
        {
          auto f=new StructureEnv_New(cm,Cls<myB>::name());
          f->pushVar<numStates_Field>(Q->k());
          f->pushVar<Q_matrix_Field>(Q->Q());

          ::Markov_LA::M_Matrix<double> g=Q->g();
          double gamma=Q->gamma();
          g=g/gamma;

          f->pushVar<conductance_vector_Field>(g);
          f->pushVar<agonist_vector_field>(Q->n_bound_agonists());
          f->pushVar<unitary_conductance_field>(gamma);
          return f;
        }

        static std::vector<std::pair<Implements_Var,bool>> getFields()
        {
          std::vector<std::pair<Implements_Var,bool>> f;
          f.push_back({getMyVar<numStates_Field>(),true});
          f.push_back({getMyVar<Q_matrix_Field>(),true});
          f.push_back({getMyVar<conductance_vector_Field>(),true});
          f.push_back({getMyVar<agonist_vector_field>(),true});
          f.push_back({getMyVar<unitary_conductance_field>(),true});
          return f;
        }



      public:
        using getClass_type=  myC* (*)
        (const StructureEnv_New *cm
        , const StructureEnv_New * m,
        const vType* self,
        std::string *WhyNot, const std::string &masterObjective);

        using getCVFromBase_type=   StructureEnv_New* (*)
        (const StructureEnv_New *cm, const myB *v,
        const vType* self,
        std::string *WhyNot, const std::string &masterObjective);

        using getCV_type=   StructureEnv_New* (*)
        (const StructureEnv_New *cm, const myC *v,
        const vType* self,
        std::string *WhyNot, const std::string &masterObjective);

        Implements_Data_Type_class_Q_Markov_Model
        (const std::vector<std::pair<Implements_Var,bool>>& fields
         ,typePredicate complyPred
         ,getCVFromBase_type getCVB
         ,getCV_type getCV
         ,getClass_type getObj
         ):
          Implements_Data_Type_class_ABC_Markov_Model(fields,complyPred)
        ,getCVB_(getCVB),getCV_(getCV),getObj_(getObj)
        {}

        Implements_Data_Type_class_Q_Markov_Model
        ():
          Implements_Data_Type_class_ABC_Markov_Model(getFields(),nullptr)
        ,getCVB_(&objB2map),getCV_(&obj2map),getObj_(&map2obj)
        {}


        // Implements_Data_Type_class<T *> interface
      public:
        virtual Q_Markov_Model *getClass(const StructureEnv_New *cm, const StructureEnv_New * m, std::string *WhyNot, const std::string &masterObjective) const
        {
          return (*getObj_)(cm,m,this,WhyNot,masterObjective);
        }




        virtual StructureEnv_New* getComplexMap(const StructureEnv_New *cm, const ABC_Markov_Model *v, std::string *WhyNot, const std::string &masterObjective) const
        {
          return (*getCVB_)(cm,v,this,WhyNot,masterObjective);
        }


        virtual StructureEnv_New* getComplexMap(const StructureEnv_New *cm, const Q_Markov_Model *v, std::string *WhyNot, const std::string &masterObjective) const
        {
          return (*getCV_)(cm,v,this,WhyNot,masterObjective);

        }


        static void push_Types(Markov_CommandManagerVar *cm)
        {
          cm->pushRegularType<std::size_t>();
          agonist_vector_type::push_Types(cm);
          conductance_vector_Type::push_Types(cm);
          Q_matrix_Type::push_Types(cm);
          cm->pushRegularType<Q_Markov_Model>();

        }


      private:
        getCVFromBase_type getCVB_;
        getCV_type getCV_;
        getClass_type getObj_;
      };




    }


    void push_Types(Markov_CommandManagerVar* cm);

  };



}



#endif // MYTYPES_H
