#include "Markov_IO/FunctionCommand.h"
#include "Markov_Console/Markov_CommandManager.h"

#include "Markov_IO/FileLoadSave.h"

#include "Markov_Mol/PatchModel.h"

#include "Markov_IO/Experiment.h"



namespace Markov_IO_New
{
  namespace funct
  {

    void pushAllFunctions(Markov_CommandManagerVar *cm)
    {
      cm->pushFunction<Save>();
      cm->pushFunction<Load>();
      cm->pushFunction<Who>();
      cm->pushFunction<Exit>();
      cm->pushFunction<Simulate>();




    }


    void Save::save_cm::save(Markov_CommandManagerVar *cm, const std::__cxx11::string &pathfileName)
    {
      fd::FileOut f(pathfileName);
      std::string whyNot;
      auto eType=cm->idToTyped<StructureEnv_New*>(ComplexVar::types::Var::myId());
      if (!eType->putValue(cm,cm,&f,&whyNot,""))
          cm->getIO()->put(whyNot);

    }






    void Load::load_cm::load(Markov_CommandManagerVar *cm, const std::__cxx11::string &path)
    {
      fd::FileIn f(path);
      std::size_t numVar=0;
      std::string whyNot;
      auto eType=cm->idToTyped<StructureEnv_New*>(ComplexVar::types::Var::myId());
      auto loadedEnv=new StructureEnv_New (cm,"load");
      if (eType->getValue(cm,loadedEnv,&f,&whyNot,""))
        {
          auto out=cm->loadVars(std::move(*loadedEnv),&whyNot,"",true);

          for (auto& e:out)
            cm->getIO()->put(e+"\t");
        }
      delete loadedEnv;
      //      getCommandManager()->putOut(Markov_IO::ToString(numVar)+" variables loaded from file "+ path+"\n");
    }

    ABC_Type_of_Closure *Load::load_cm::varType(Markov_CommandManagerVar *cm)
    {

      return new Implements_Data_Type_FnClosure<
          functionType,returnType,Markov_CommandManagerVar*,std::string>
          (cm,&load
           ,getReturnFnType(cm), getArgumentTypes(cm));
    }

    void Who::who_cm::who(Markov_CommandManagerVar *cm, const std::__cxx11::string &typeName)
    {
      std::vector<std::string> out=cm->getIdsOfVarType(typeName,false);
      for (auto& e:out)
        {
          cm->getIO()->put(e);
          cm->getIO()->put("\t");
          cm->getIO()->putNewLine();
        }
    }

    ABC_Type_of_Closure *Who::who_cm::varType(Markov_CommandManagerVar *cm)
    {
      return new Implements_Data_Type_FnClosure<
          functionType,returnType,Markov_CommandManagerVar*,std::string>
          (cm,&who
           ,getReturnFnType(cm), getArgumentTypes(cm));

    }

    void Exit::exit_cm::exitProgram(Markov_CommandManagerVar *cm, const std::__cxx11::string &pathfileName)
    {
      exit(0);
    }

    void Simulate::simulate_cm::simulate(Markov_CommandManagerVar *cm, Markov_Mol_New::ABC_PatchModel *p, ABC_Experiment *e, std::__cxx11::string experiment_out, double time_step, std::size_t num_steps, std::size_t n_replicates, std::size_t seed)
    {


      Experiment* sim =new
         Experiment(p->run(*e,n_replicates,time_step,num_steps, cm->sto()));

      cm->pushData(experiment_out,sim,"simulation");

    }

  }
}
