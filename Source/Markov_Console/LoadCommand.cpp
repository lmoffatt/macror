#include "Markov_Console/LoadCommand.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_Mol/ABC_PatchModel.h"
#include "Markov_IO/ExperimentalData.h"

#include <fstream>


namespace Markov_Console
{
  ///  destructor
  LoadCommandVar::~LoadCommandVar(){}



  LoadCommandVar::LoadCommandVar(Markov_CommandManagerVar* cm)
    : Markov_IO::Implements_ValueId("load"
                                    , ""
                                    ,"Displays help on subject"
                                    ,"Help command\n"
                                     " returns help on subject\n"
                                     " subject can be either a command"
                                    )
      ,ABC_CommandVar(cm
                    ,"load"
                    , ""
                    ,"Displays help on subject"
                    ,"Help command\n"
                     " returns help on subject\n"
                     " subject can be either a command"
                    ,{{"filename","","",""}},0)
  {}

  /// runs the command on the command manager and returns true if succeeds
  bool LoadCommandVar::processTokens(Markov_IO::Token_Stream &t)
  {
    if (t.currToken().str()!=id())
      return false;
    t.advance(1);

    std::string loadFileName;
    std::vector<std::string> varnames;
    if (t.eof()||t.currToken().tok()==Markov_IO::Token_New::EOL)
      {
        loadFileName="macror.txt";
      }
    else if (t.currToken().tok()==Markov_IO::Token_New::STRING)
      {
        loadFileName=t.currToken().str();
        t.advance(1);

      }
    else if (t.currToken().tok()==Markov_IO::Token_New::IDENTIFIER)

      {
        loadFileName=t.currToken().str();
        t.advance(1);
      }
    else
      {
        cm_->getIO()->putError("unexpected Token; expected Name, found other");
        return false;
      }
    if (t.eof()||t.currToken().tok()==Markov_IO::Token_New::EOL)
      {
        if (!t.eof())
          t.advance(1);
        return run(loadFileName,varnames);
      }
    else while (!(t.eof()||t.currToken().tok()==Markov_IO::Token_New::EOL))
      {
        switch(t.currToken().tok())
          {
          case Markov_IO::Token_New::IDENTIFIER:
            varnames.push_back(t.currToken().str());
            t.advance(1);
            break;
          default:
            std::string tokenString=t.currToken().str();

            cm_->getIO()->putError("unexpected Token; expected Name, found other"
                                   +tokenString);
            return false;
          }
      }
    return run(loadFileName,varnames);

  }

  bool LoadCommandVar::run(const std::string &fname
                           ,const std::vector<std::string> &varnames)

  {
    std::string filename=fname;
    // is filename or dirname?
    if (!Markov_IO::IsDir(filename))
      {
        if (filename.find(".")==std::string::npos)
          {
            filename+=".txt";
          }
        std::string path;
        Markov_IO::FileDir d(cm_->getDir());
        if (!Markov_IO::IsFile(filename))
          path=d.DirName()+"/"+filename;
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
                  cm_->putErrorOut("invalid name "+path);
                  return false;
                }
            }
          std::size_t numVar=0;
          std::string varname;
          //safeGetline allow loading windows files in linux
          //TODO: check if it loads linux files in windows

          Markov_IO::Token_Stream tok(&f);


          while (true)
            {
              auto v=getValueFromStream(tok);
              if (v!=nullptr)
                {
                  numVar++;
                  auto w=cm_->getMeasureFromValue(v);
                  if (w!=nullptr)
                    cm_->pushChild(w);
                  else
                    cm_->pushChild(v);

                }
              else if (!f.eof())
                {

                  std::string m="unrecognized variable; read text ";
                  m+=tok.putTokenBuffer();
                  cm_->putErrorOut(m);
                  f.close();
                  return false;
                }
              if (f.eof())
                break;
              tok.cleanRead();
            }
          cm_->putOut(Markov_IO::ToString(numVar)+" variables loaded from file "+ path+"\n");
        return true;
        }

      }
   // else  is a dirname
  }



}


namespace Markov_Console
{
  ///  destructor
  LoadCommand::~LoadCommand(){}



  LoadCommand::LoadCommand(Markov_CommandManager* cm)
    :ABC_Command(cm,
                 "load",{{
                 "filename",ABC_Command::fileName(),false}},{}){}


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
    std::string filename=fname;
    // is filename or dirname?
    if (!Markov_IO::IsDir(filename))
      {
        if (filename.find(".")==std::string::npos)
          {
            filename+=".txt";
          }
        std::string path;
        Markov_IO::FileDir d(getCommandManager()->getDir());
        if (!Markov_IO::IsFile(filename))
          path=d.DirName()+"/"+filename;
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
                  getCommandManager()->putErrorOut("invalid name "+path);
                  return false;
                }
            }
          std::size_t numVar=0;
          std::string varname;
          //safeGetline allow loading windows files in linux
          //TODO: check if it loads linux files in windows

          Markov_IO::Token_Stream tok(&f);

          if (Markov_IO::safeGetline(f,varname))
            {
              MacroVersion_=getCommandManager()->getVersion(varname);
              if (MacroVersion_>0)
                {
                  output_="Format of version "+varname+"\n";
                  varname.clear();
                }
              varname.clear();

            }
          else
            return false;

          while (true)
            {
              auto v=getValueFromStream(tok);
              if (v!=nullptr)
                {
                  numVar++;
                  auto w=getCommandManager()->getMeasureFromValue(v);
                  if (w!=nullptr)
                    getCommandManager()->pushChild(w);
                  else
                    getCommandManager()->pushChild(v);

                }
              else if (!f.eof())
                {

                  std::string m="unrecognized variable; read text ";
                  m+=tok.putTokenBuffer();
                  getCommandManager()->putErrorOut(m);
                  f.close();
                  return false;
                }
              if (f.eof())
                break;
              tok.cleanRead();
            }
          getCommandManager()->putOut(Markov_IO::ToString(numVar)+" variables loaded from file "+ path+"\n");
        }

      }
    else   // it is a dirname
      {
        // tries one by one all the files in the directory
        std::string fileName;
        Markov_IO::FileDir f(filename);
        f.begin();
        std::size_t numVar=0;
        // std::size_t numfiles=0;

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
                          des.setEnvironment(getCommandManager());

                          if (f>>des)
                            {
                              Markov_IO::ABC_Saveable* s;


                              numVar++;
                              bool isVar=false;
                              for (auto tname:cm_->getTypesList())
                                {
                                  s=cm_->getType(tname)->create();
                                  if (s->LoadFromDescription(des))
                                    {
                                      cm_->add_var(varname,s);
                                      isVar=true;
                                      break;
                                    }
                                }
                              if (!isVar)
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
    return true;

  }
}

