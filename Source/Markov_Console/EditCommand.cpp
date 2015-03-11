#include "Markov_Console/EditCommand.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/Markov_CommandManager.h"
namespace Markov_Console
{
  ///  destructor
  EditCommand::~EditCommand(){}



  EditCommand::EditCommand(Markov_CommandManager* cm)
  {
    cm_=cm;
  }


  /// hint about of the class nature
  std::string EditCommand::Tip()const
  {
    return "Displays help on subject";
  }

  /// a short description of the class
  std::string EditCommand::WhatThis()const
  {
    return "Help command\n"
           " returns help on subject\n"
           " subject can be either a command";
  }




  std::string EditCommand::commandName()const
  {
    return "edit";
  }
  /// runs the command on the command manager and returns true if succeeds
  bool EditCommand::run(std::deque<Token> & tokenList)
  {
    std::string  varname;
    if (tokenList.empty())
      {
        output_.clear();
        errorMessage_="missing parameter; expected variable to be edited";
        return false;
      }
    else if (tokenList[0].get_token()!=Token::IDENTIFIER)
      {
        output_.clear();
        errorMessage_="unexpected Token; expected Name, found other";
        return false;
      }
    else
      {
        varname=tokenList.front().Name();
        tokenList.pop_front();

      }
    return run(varname);

  }
  /// runs the command for a list of parameters
  bool EditCommand::run(Markov_IO::ClassDescription& classDes)
  {
//    Markov_IO::ClassDescription desc=classDes;
//    std::stringstream ss;
//    while (true)
//      {

//        ss<<"Enter either:\n"
//            "(0) a current variable name of the corresponding superClass \n"
//            "(1) ""all"" for editing all the items one by one or \n";
//        ss<<" (2) the name or (number) of an item of the variable or\n";
//        ss<<" (3) ""save"" for saving the variable"<<std::endl;
//        ss<<" (4) ""exit"" for exit without saving changes"<<std::endl;
//        cm_->getIO()->put(ss.str());
//        ss.str().clear();
//        std::string resp=cm_->getIO()->getline();
//        std::size_t first=0;
//        std::size_t last=0;
//        if (cm_->checkVariable(resp,desc.SuperClass()))
//          {
//            ss<<"use variable?"<<resp<<"\n"<<*cm_->getVar(resp)<<std::endl;
//            ss<<"enter ""yes"" or ""no""";
//            cm_->getIO()->put(ss.str());
//            ss.str().clear();
//            std::string resp2=cm_->getIO()->getline();
//            if (resp2=="yes")
//              {
//                Markov_IO::ABC_Saveable* s=cm_->getVar(resp);
//                classDes=s->GetDescription();
//                return true;
//              }
//          }
//        else if (resp=="all")
//          {
//            first=0; last=desc.size();
//          }
//        else if (Markov_IO::ToValue(resp,first)&&(first<desc.size()))
//          {
//            last=first+1;
//          }
//        else if (desc.HasElementName(resp))
//          {
//            first=desc.NameIndex(resp);last=first+1;
//          }
//        else {
//            first=0; last=0;
//          }
//        for (std::size_t i=first; i<last; i++)
//          {
//            std::string name=desc.ElementName(i);
//            ss<<name<<" current value"<<std::endl;
//            ss<<ToString(*desc[name])<<std::endl;
//            if (desc[name]->mySuperClass()==Markov_IO::ABC_Object::ClassName())
//              {
//                ss<<"enter "<<name<< " new value [end with blank line]"<<std::endl;
//                std::string value;
//                cm_->getIO()->put(ss.str());
//                ss.str().clear();
//                std::string line=cm_->getIO()->getline();

//                value=value+line+"\n";
//                while (!line.empty())
//                  {
//                    line=cm_->getIO()->getline();
//                    value=value+line+"\n";
//                  }
//                desc.ReplaceElement(name,value);
//              }
//            else
//              {
//                Markov_IO::ABC_Saveable* os=
//                    dynamic_cast<const Markov_IO::ABC_Saveable*>(desc[name])->clone();
//                Markov_IO::ClassDescription fieldDes=os->GetDescription();

//                run(fieldDes);
//                os->LoadFromDescription(fieldDes);
//                desc.ReplaceElement(name,*os);
//                delete os;
//              }

//          }
//        if (resp=="save")
//          {
//            ss<<"Class Description"<<"\n"<<desc<<"\n";

//            classDes=desc;
//            ss<<"Saving successfull. New value"<<std::endl;

//            cm_->getIO()->put(ss.str());
//            ss.str().clear();

//            return true;
//          }
//        else if (resp=="exit")
//          return false;
//      }
}


  bool EditCommand::run(const std::string& varname)

  {

    if (cm_->has_var(varname))
      {
        Markov_IO::ABC_Saveable* v=cm_->getVar(varname);
        Markov_IO::ClassDescription desc=v->GetDescription();
        std::cout<<"Current value of ";
        std::cout<<varname<<", alias of "<<v->id();
        std::cout<<" a "<<v->myClass()<<"  "<<v->mySuperClass()<<std::endl;
        for (std::size_t i=0; i<desc.size(); i++)
          {
            std::cout<<"("<<i<<")"<<desc.ElementName(i)<<std::endl;
            std::cout<<desc.ElementValue(i)<<std::endl;
          }
        bool isEdited=run(desc);
        bool desValid=false;
        if (isEdited)
          desValid=v->LoadFromDescription(desc);
        if (isEdited && desValid)
          {
            std::cout<<"Saving successfull. New value"<<std::endl;
            std::cout<<*cm_->getVar(varname);
            return true;
          }
        else
          {
            std::cout<<"Saving unsuccessfull."<<std::endl;
            return false;
          }

      }
    else
      {
        auto v=cm_->getChild(varname);
        if (v!=nullptr)
          {
            std::string s="current value of "+v->id();
            s+="a "+v->myVar()+"\n"+v->toString();
            cm_->putOut(s);



          }
        else

          return false;
      }


  }
}

