#include "Markov_Console/ABC_Command.h"
#include "Markov_Console/Markov_CommandManager.h"














namespace Markov_Console


{

  std::vector<std::string> slice0 (const std::vector<ABC_Command::variable > data)
  {
    std::vector<std::string> out;
    for (auto t:data)
      out.push_back(t.name);
    return out;
  }

  std::vector<std::string> slice1 (const std::vector<ABC_Command::variable > data)
  {
    std::vector<std::string> out;
    for (auto t:data)
      out.push_back(t.type);
    return out;
  }
  std::vector<bool> slice2 (const std::vector<ABC_Command::variable > data)
  {
    std::vector<bool> out;
    for (auto t:data)
      out.push_back(t.mandatory );
    return out;
  }


  ABC_Command::ABC_Command(Markov_CommandManager* cm,
                           const std::string &commandName,
                           const std::vector<std::string>& inputNames,
                           const std::vector<std::string>& inputTypes,
                           const std::vector<bool>& inputIsMandatory,
                           const std::vector<std::string>& outputNames,
                           const std::vector<std::string>& outputTypes,
                           const std::vector<bool>& outputIsMandatory):
    cm_(cm),
    commandName_(commandName),
    inputNames_(inputNames),
    inputTypes_(inputTypes),
    inputMandatory_(inputIsMandatory),
    outputNames_(outputNames),
    outputTypes_(outputTypes),
    outputMandatory_(outputIsMandatory)
  {}


  ABC_Command::ABC_Command(Markov_CommandManager* cm,
              const std::string& commandName,
              const std::vector<variable> &inputs,
              const std::vector<variable> &outputs)
:  cm_(cm),
    commandName_(commandName),
    inputNames_(slice0(inputs)),
    inputTypes_(slice1(inputs)),
    inputMandatory_(slice2(inputs)),
    outputNames_(slice0(outputs)),
    outputTypes_(slice1(outputs)),
    outputMandatory_(slice2(outputs))

  {

  }








  ABC_Command::~ABC_Command(){}
  ///  formated output

  ///  formated output
  std::ostream& ABC_Command::put(std::ostream& s) const
  {
    s<<this->commandName();
    return s;
  }

  bool ABC_Command::operator==(const ABC_Command& other)const
  {
    return this->commandName()==other.commandName();
  }



  // TODO: implement with help files
  /// hint about of the class nature
  std::string ABC_Command::Tip()const
  {
    return "Some command";
  }


  std::string ABC_Command::commandName()const
  {
    return commandName_;
  }

  // TODO: implement from help files
  /// a short description of the class
  std::string ABC_Command::WhatThis()const
  {
    return "Base class of all console commands\n"
        "This commands are also used in scripts\n";

  }

  /// error message, empty string if succeeded
  std::string ABC_Command::errorMessage()const
  {
    return errorMessage_;
  }

  void ABC_Command::errorMessage(const std::string& errmsg)
  {
    errorMessage_=errmsg;
  }



  /// printed output, empty string if command fails
  std::string ABC_Command::output()const
  {
    return output_;
  }

  Markov_CommandManager* ABC_Command::getCommandManager()
  {
    return cm_;
  }

  const Markov_CommandManager* ABC_Command::getCommandManager()const
  {
    return cm_;
  }



  std::size_t ABC_Command::numInputs()const
  {
    return this->inputTypes_.size();
  }

  std::string ABC_Command::InputType(std::size_t i)const
  {
    return inputTypes_[i];
  }
  std::string ABC_Command::InputName(std::size_t i)const
  {
    return inputNames_[i];
  }

  bool ABC_Command::isMandatoryInput(std::size_t i)const
  {
    return inputMandatory_[i];
  }
  bool ABC_Command::isMandatoryOutput(std::size_t i)const
  {
    return outputMandatory_[i];
  }



  std::size_t ABC_Command::numOutputs()const
  {
    return this->outputTypes_.size();
  }

  std::string ABC_Command::OutputType(std::size_t i)const
  {
    return outputTypes_[i];
  }
  std::string ABC_Command::OutputName(std::size_t i)const
  {
    return outputNames_[i];
  }


  std::vector<std::string> ABC_Command::complete(const std::string& hint,const std::deque<Token>& tokenList)

  {
    auto n=tokenList.size();
    std::vector<bool> hasInput(numInputs(),false);
    std::vector<bool> hasOutput(numOutputs(),false);

    for (std::size_t i=1; i<n; i++)
      {
        auto name=tokenList.at(i).Name();
        std::size_t j=0;
        while ((j<numInputs())&&
               (hasInput[j]||
                (!getCommandManager()->checkVariable(name,InputType(j)))))
          {
            if ((isMandatoryInput(j))&&(!hasInput[j]))
              {
                return {name+" is wrong; Mandatory input <"+InputName(j)+ "> expected"};
              }
            else
              j++;
          }
        if (j<numInputs())
          {
            hasInput[j]=true;
          }
        else
          {
            std::size_t k=0;
            while (k<numOutputs()&&
                   (hasOutput[k]||
                    !getCommandManager()->checkVariable(name,OutputType(k))
                    ))
              {
                if (isMandatoryOutput(k))
                  {
                    return {name+" is wrong; Mandatory output "+OutputName(k)+ "expected"};
                  }
                else
                  k++;
              }
            if (k<numOutputs())
              {
                hasOutput[k]=true;
              }
            else
              {
                std::string msg;
                for (std::size_t jj=0; jj<numInputs(); jj++)
                  if (!hasInput[jj])
                    msg+="<"+InputName(jj)+"> is missing; ";
                for (std::size_t kk=0; k<numOutputs(); kk++)
                  if (!hasOutput[kk])
                    msg+="<"+OutputName(kk)+"> is missing; ";

                return {name + "is wrong "+msg};
              }
          }
      }



    std::vector<std::string> res;
    for (std::size_t jj=0; jj<numInputs(); jj++)
      if ((!hasInput[jj])&&isMandatoryInput(jj))
        {
          res=getCommandManager()->complete(hint,InputType(jj));
          if (res.size()!=1)
            {
              res.insert(res.begin(),"<"+InputName(jj)+">");
            }
          return res;
        }
    for (std::size_t kk=0; kk<numOutputs(); kk++)
      if ((!hasOutput[kk])&& isMandatoryOutput(kk))
        {
          res=getCommandManager()->complete(hint,OutputType(kk));
          if (res.size()!=1)
            {
              res.insert(res.begin(),"<"+OutputName(kk)+">");
            }
          return res;
        }

    std::size_t numIOleft=0;
    for (std::size_t jj=0; jj<numInputs(); jj++)
      if ((!hasInput[jj]))
        {
          numIOleft++;
        }

    for (std::size_t kk=0; kk<numOutputs(); kk++)
      if ((!hasOutput[kk]))
        {
          numIOleft++;
        }



    for (std::size_t jj=0; jj<numInputs(); jj++)
      if ((!hasInput[jj]))
        {
          auto res2=getCommandManager()->complete(hint,InputType(jj));
          if ((res2.size()==1) && (numIOleft==1))
            return res2;
          res.insert(res.end(),"["+InputName(jj)+"]");
          res.insert(res.end(),res2.begin(),res2.end());
        }

    for (std::size_t kk=0; kk<numOutputs(); kk++)
      if ((!hasOutput[kk]))
        {
          auto res2= getCommandManager()->complete(hint,OutputType(kk));
          if ((res2.size()==1) && (numIOleft==1))
            return res2;
              res.insert(res.end(),"["+OutputName(kk)+"]");
              res.insert(res.end(),res2.begin(),res2.end());

        }
    if (res.empty())
      return {"Error", "too many parameters"};
    else
      return res;

  }




  std::string ABC_Command::check(const std::deque<Token>& tokenList)const
  {
    auto n=tokenList.size();
    std::vector<bool> hasInput(numInputs(),false);
    std::vector<bool> hasOutput(numOutputs(),false);

    for (std::size_t i=1; i<n; i++)
      {
        auto name=tokenList.at(i).Name();
        std::size_t j=0;
        while ((j<numInputs())&&
               (hasInput[j]||
                (!getCommandManager()->checkVariable(name,InputType(j)))))
          {
            if ((isMandatoryInput(j))&&(!hasInput[j]))
              {
                return name+" is wrong; Mandatory input <"+InputName(j)+ "> expected";
              }
            else
              j++;
          }
        if (j<numInputs())
          {
            hasInput[j]=true;
          }
        else
          {
            std::size_t k=0;
            while (k<numOutputs()&&
                   (hasOutput[k]||
                    !getCommandManager()->checkVariable(name,OutputType(k))
                    ))
              {
                if (isMandatoryOutput(k))
                  {
                    return name+" is wrong; Mandatory output "+OutputName(k)+ "expected";
                  }
                else
                  k++;
              }
            if (k<numOutputs())
              {
                hasOutput[k]=true;
              }
            else
              {
                std::string msg;
                for (std::size_t jj=0; jj<numInputs(); jj++)
                  if (!hasInput[jj])
                    msg+="<"+InputName(jj)+"> is missing; ";
                for (std::size_t kk=0; k<numOutputs(); kk++)
                  if (!hasOutput[kk])
                    msg+="<"+OutputName(kk)+"> is missing; ";

                return name + "is wrong "+msg;
              }
          }
      }
    return "";

  }



  bool ABC_Command::run(std::deque<Token> &tokenList)
  {
    auto n=tokenList.size();
    std::vector<std::string> InputValue(numInputs(),"");
    std::vector<std::string> OutputValue(numOutputs(),"");

    for (std::size_t i=0; i<n; i++)
      {
        auto name=tokenList.at(i).Name();
        std::size_t j=0;
        while ((j<numInputs())&&
               (!InputValue[j].empty()||
                (!getCommandManager()->checkVariable(name,InputType(j)))))
          {
            if ((isMandatoryInput(j))&&(InputValue[j].empty()))
              {
                getCommandManager()->printErrorMessage(
                      name+" is wrong; Mandatory input <"+InputName(j)+ "> expected", this);
                return false;
              }
            else
              j++;
          }
        if (j<numInputs())
          {
            InputValue[j]=name;
          }
        else
          {
            std::size_t k=0;
            while (k<numOutputs()&&
                   (!OutputValue[k].empty()||
                    !getCommandManager()->checkVariable(name,OutputType(k))
                    ))
              {
                if ( isMandatoryOutput(k) && OutputValue[k].empty())
                  {
                    getCommandManager()->printErrorMessage(
                          name+" is wrong; Mandatory output <"+OutputName(k)+ "> expected",this);
                    return false;
                  }
                else
                  k++;
              }
            if (k<numOutputs())
              {
                OutputValue[k]=name;
              }
            else
              {
                std::string msg;
                for (std::size_t jj=0; jj<numInputs(); jj++)
                  if (InputValue[jj].empty())
                    msg+=InputName(jj)+" is missing; ";
                for (std::size_t kk=0; k<numOutputs(); kk++)
                  if (OutputValue[kk].empty())
                    msg+=OutputName(kk)+" is missing; ";

                getCommandManager()->printErrorMessage(
                      name + " is wrong "+msg,this);
                return false;
              }
          }
      }
    for  (std::size_t i=0; i<numInputs(); i++)
      if (isMandatoryInput(i)&& InputValue[i].empty())
        {
        getCommandManager()->printErrorMessage(
              "Mandatory input <"+ InputName(i)+"> is missing",this);
        return false;
        }

    for  (std::size_t i=0; i<numOutputs(); i++)
      if (isMandatoryOutput(i)&& OutputValue[i].empty())
        {
        getCommandManager()->printErrorMessage(
              "Mandatory output <"+ OutputName(i)+"> is missing",this);
        return false;
        }
    tokenList.clear();

    return run(InputValue,OutputValue);

  }


   std::string ABC_Command::directory()
  {
    return "directory";
  }







}
