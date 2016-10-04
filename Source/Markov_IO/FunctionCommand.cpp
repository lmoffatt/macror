#include "Markov_IO/FunctionCommand.h"
#include "Markov_Console/Markov_CommandManager.h"

#include "Markov_IO/FileLoadSave.h"

#include "Markov_Mol/PatchModel.h"

#include "Markov_IO/Experiment.h"

#include "Markov_Bay/MarkovLikelihood.h"
#include "Markov_IO/StructureEnv_templ.h"


namespace Markov_IO_New
{
  namespace funct
  {

    void pushAllFunctions(Markov_CommandManagerVar *cm)
    {

      cm->pushCommand<Save>();

      cm->pushCommand<Load>();
      cm->pushCommand<Run>();

      cm->pushCommand<Who>();
      cm->pushCommand<Exit>();
      cm->pushFunction<Simulate>();
      cm->pushFunction<Likelihood>();



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


    void Run::run_cm::run(Markov_CommandManagerVar *cm, const std::__cxx11::string &pathfileNameIn, const std::__cxx11::string &pathfileLog,bool withError)
    {
      fd::FileIn f_in(pathfileNameIn);
      fd::FileOut f_out(pathfileLog);
      cm->run(&f_in,&f_out,withError);

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


    void Exit::exit_cm::exitProgram(Markov_CommandManagerVar *cm, const std::__cxx11::string &pathfileName)
    {
      exit(0);
    }

    Experiment* Simulate::simulate_cm::simulate
    (Markov_CommandManagerVar *cm
     , Markov_Mol_New::ABC_PatchModel *p
     , ABC_Experiment *e
     , double time_step
     , std::size_t num_steps
     , std::size_t n_replicates)
    {
      return new
          Experiment(p->run(*e,n_replicates,time_step,num_steps, cm->sto()));
    }

    Markov_Bay_New::LikelihoodEvaluation
    *Likelihood::likelihood_::likelihood(
        const Markov_Mol_New::ABC_PatchModel *patch,
        const ABC_Experiment *experiment,
        const std::__cxx11::string& algorithm
        , bool isaveraging
        , bool zeroGuard)
    {
      return Markov_Bay_New::Markov_Likelihood::run
          (patch,experiment,algorithm
           ,isaveraging, zeroGuard);

    }



  }
}
