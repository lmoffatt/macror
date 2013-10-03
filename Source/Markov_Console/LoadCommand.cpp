#include "Markov_Console/LoadCommand.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_Mol/ABC_PatchModel.h"
#include "Markov_IO/ExperimentalData.h"

namespace Markov_Console
{
  ///  destructor
  LoadCommand::~LoadCommand(){}



  LoadCommand::LoadCommand(Markov_CommandManager* cm)
  {
    cm_=cm;
  }


  /// hint about of the class nature
  std::string LoadCommand::Tip()const
  {
    return "Displays help on subject";
  }

  /// a short description of the class
  std::string LoadCommand::WhatThis()const
  {
    return "Help command\n"
        " returns help on subject\n"
        " subject can be either a command";
  }




  std::string LoadCommand::commandName()const
  {
    return "load";
  }
  /// runs the command on the command manager and returns true if succeeds
  bool LoadCommand::run(std::deque<Token> & tokenList)
  {
    std::string loadFileName;
    std::vector<std::string> varnames;
    if (tokenList.empty())
      {
        loadFileName="macror.txt";
      }
    else if (tokenList[0].get_token()==Token::STRING)
      {
        loadFileName=tokenList.front().Path();
        tokenList.pop_front();

      }
    else if(tokenList[0].get_token()==Token::IDENTIFIER)

      {
        loadFileName=tokenList.front().Name();
        tokenList.pop_front();

      }
    else
      {
        output_.clear();
        errorMessage_="unexpected Token; expected Name, found other";
        return false;
      }
    if (tokenList.empty())
      {
        return run(loadFileName,varnames);
      }
    else while (!tokenList.empty())
      {
        switch(tokenList.front().get_token())
          {
          case Token::IDENTIFIER:
            varnames.push_back(tokenList.front().Name());
            tokenList.pop_front();
            break;
          default:
            std::string tokenString=tokenList.front().get_tokenString();
            output_.clear();
            errorMessage_="wrong token; expected NAME or NUMBER one number, found : "+
                tokenString;
            return false;
          }
      }
    return run(loadFileName,varnames);

  }


  /// runs the command for a list of parameters
  bool LoadCommand::run(const std::string& fname,
                        const std::vector<std::string>& varnames)
  {
    output_.clear();
    errorMessage_.clear();

    std::string filename=fname;
    // is filename or dirname?
    if (!Markov_IO::IsDir(filename))
      {
        if (filename.find(".")==std::string::npos)
          {
            filename+=".txt";
          }
        std::string path;
        if (!Markov_IO::IsFile(filename))
          path=cm_->getDir().DirName()+"/"+filename;
        else
          path=filename;
        {
          std::ifstream f(path.c_str());
          if(!f)
            {
              //path+=".txt";
              f.close();
              f.open(path.c_str());
              if (!f)
                {
                  output_.clear();
                  errorMessage_="invalid name "+path;
                  return false;
                }
            }



          std::size_t numVar=0;
          std::string varname;
          //safeGetline allow loading windows files in linux
          //TODO: check if it loads linux files in windows


          while (Markov_IO::safeGetline(f,varname))
            {

              if (numVar==0)
                {
                  MacroVersion_=getCommandManager()->getVersion(varname);
                  if (MacroVersion_>0)
                    {
                      output_="Format of version "+varname+"\n";
                      varname.clear();
                    }
                }

              while (varname.empty())
                if (!Markov_IO::safeGetline(f,varname))
                  break;
              if (varnames.empty()||
                  (std::find(varnames.begin(),varnames.end(),varname)!=
                   varnames.end()))
                {
                  Markov_IO::ClassDescription des;
                  if (f>>des)
                    {
                      Markov_IO::ABC_Saveable* s;

                      Markov_IO::ABC_Experiment* exp;
                      Markov_Mol::ABC_Markov_Model* mod;
                      Markov_Mol::ABC_noise* noise;
                      Markov_Mol::ABC_PatchModel* p;
                      Markov_IO::ABC_Options* o;
                      Markov_Bay::ABC_Result* r;

                      numVar++;
                      if (Markov_IO::LoadFromDescription(exp,des))
                        {
                          cm_->add_experiment(varname,exp);
                        }
                      else if (Markov_Mol::LoadFromDescription(mod,des))
                        {
                          cm_->add_channel(varname,mod);
                        }
                      else if (Markov_Mol::LoadFromDescription(noise,des))
                        {
                          cm_->add_var(varname,noise);
                        }
                      else if (Markov_Mol::LoadFromDescription(p,des))
                        {
                          cm_->add_patch(varname,p);
                        }
                      else if (LoadFromDescription(o,des))
                        {
                          cm_->add_option(varname,o);
                        }
                      else if (LoadFromDescription(r,des))
                        {
                          cm_->add_result(varname,r);
                        }
                      else
                        {
                          std::stringstream ss;
                          ss<<"unrecognized variable: "<<des;
                          errorMessage_=ss.str();
                          output_.clear();

                          numVar--;
                        }

                    }
                  else
                    {
                      if (!des.ClassName().empty())
                        {
                          std::stringstream ss;
                          ss<<"unrecognized variable: "<<des;
                          errorMessage_=ss.str();
                          output_.clear();
                        }
                    }
                }
            }
          if (errorMessage_.empty())
            {
              output_+=Markov_IO::ToString(numVar)+" variables loaded from file "+
                  path;
              return true;
            }
          else
            {

              errorMessage_=Markov_IO::ToString(numVar)+" variables loaded from file "+
                  path+"; \nbut the following variables were not recognized "+errorMessage_;
              return false;
            }

          f.close();
        }
      }

    else
      {
        // tries one by one all the files in the directory
        std::string fileName;
        Markov_IO::FileDir f(filename);
        f.begin();
        std::size_t numVar=0;
        std::size_t numfiles=0;

        do
          {
            fileName=f.FileName();
            std::string path=f.DirName()+"/"+fileName;
            if (Markov_IO::IsFile(path))
              {
                {
                  std::ifstream f(path.c_str());
                  if(!f)
                    {
                      //path+=".txt";
                      f.close();
                      f.open(path.c_str());
                      if (!f)
                        {
                          output_.clear();
                          errorMessage_="invalid name "+path;
                        }
                    }


                  std::string varname;
                  //safeGetline allow loading windows files in linux
                  //TODO: check if it loads linux files in windows
                  while (Markov_IO::safeGetline(f,varname))
                    {
                      while (varname.empty())
                        if (!Markov_IO::safeGetline(f,varname))
                          break;
                      if (varnames.empty()||
                          (std::find(varnames.begin(),varnames.end(),varname)!=
                           varnames.end()))
                        {
                          Markov_IO::ClassDescription des;
                          if (f>>des)
                            {
                              Markov_IO::ABC_Experiment* exp;
                              Markov_Mol::ABC_Markov_Model* mod;
                              Markov_Mol::ABC_noise* noise;
                              Markov_Mol::ABC_PatchModel* p;
                              Markov_IO::ABC_Options* o;
                              Markov_Bay::ABC_Result* r;

                              numVar++;
                              if (Markov_IO::LoadFromDescription(exp,des))
                                {
                                  cm_->add_experiment(varname,exp);
                                }
                              else if (Markov_Mol::LoadFromDescription(mod,des))
                                {
                                  cm_->add_channel(varname,mod);
                                }
                              else if (Markov_Mol::LoadFromDescription(noise,des))
                                {
                                  cm_->add_var(varname,noise);
                                }
                              else if (Markov_Mol::LoadFromDescription(p,des))
                                {
                                  cm_->add_patch(varname,p);
                                }
                              else if (LoadFromDescription(o,des))
                                {
                                  cm_->add_option(varname,o);
                                }
                              else if (LoadFromDescription(r,des))
                                {
                                  cm_->add_result(varname,r);
                                }
                              else
                                {
                                  std::stringstream ss;
                                  ss<<"unrecognized variable: "<<des;
                                  errorMessage_=ss.str();
                                  output_.clear();
                                  numVar--;
                                }

                            }

                        }
                    }

                  f.close();
                }

              }
          }
        while (f.next());
        if (errorMessage_.empty())
          {
            output_=Markov_IO::ToString(numVar)+" variables loaded from directory "+
                filename;
            return true;
          }
        else
          {
            errorMessage_=Markov_IO::ToString(numVar)+" variables loaded from directory "+
                filename;
            +"; but the following variables were not recognized "+errorMessage_;
            return false;
          }


      }

  }
}

