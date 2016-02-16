#include "Markov_IO/buildByToken.h"
#include "Markov_Console/Markov_CommandManager.h"

namespace Markov_IO {

  std::string ABC_BuildByToken::ClassName()
  {
    return "ABC_BuildByToken";
  }

  std::set<std::string> ABC_BuildByToken::SuperClasses()
  {
    return ABC_Base::SuperClasses()+ClassName();
  }

  std::string ABC_BuildByToken::myClass() const
  {
    return ClassName();

  }

  std::set<std::string> ABC_BuildByToken::mySuperClasses() const
  {
    return SuperClasses();
  }

  std::string ABC_BuildByToken::errorMessage() const
  {
    return error_;
  }

  ABC_BuildByToken::~ABC_BuildByToken(){}

  ABC_Value *ABC_BuildByToken::parent()
  {
    return parent_;
  }

  const ABC_Value *ABC_BuildByToken::parent() const
  {
    return parent_;
  }

  ABC_BuildByToken::ABC_BuildByToken(ABC_Value *p):parent_(p), error_(){}

  void ABC_BuildByToken::setErrorMessage(std::string err)
  {
    error_=err;
  }

  void ABC_BuildByToken::setErrorMessage(ABC_BuildByToken *child)
  {
    error_="Error in "+myClass()+" : "+child->errorMessage();
  }

  void ABC_BuildByToken::setErrorMessage(Token_New::Value expected, Token_New found)
  {
    error_="Error in "+myClass()+" : expected: "
        +Token_New::toString(expected)+"; found: "
        +found.str();
  }

  void ABC_BuildByToken::setErrorMessage(std::string expected, Token_New found)
  {
    error_="Error in "+myClass()+" : expected: "
        +expected+"; found: "
        +found.str();
  }

  void ABC_BuildByToken::setErrorMessage(const Markov_Console::ABC_CommandVar* cmd,
                                         const ABC_Value* input, const std::string& error)
  {
    std::string err="Error in command: "+cmd->id() +", field: "+input->id()+" "+error;
    error_=err;
  }

  void ABC_BuildByToken::setErrorMessage(const Markov_Console::ABC_CommandVar* cmd,const std::string& error)
  {
    std::string err="Error in "+myClass()+" for command "+cmd->id() +" "+error;
    error_=err;
  }


  void ABC_BuildByToken::setErrorMessage(const Markov_Console::ABC_CommandVar* cmd,
                                         const ABC_Value* input, Token_New found)
  {
    std::string err="Error in "+myClass()+" for command "+cmd->id() +"  : expected: ";
    for (unsigned i=0; i<input->numChilds(); ++i)
      {
        std::string idith=input->ith_ChildName(i);
        auto oith=input->idToValue(idith);
        if (oith->empty())
          err+=oith->id()+" ("+oith->myVar()+")"+ " or ";
      }
    err.substr(0,err.size()-3);
    err+="; found: " +found.str();
    error_=err;
  }



  void ABC_BuildByToken::setErrorsMessage(std::vector<Token_New::Value> expected, Token_New found)
  {
    std::string estr="Error in "+myClass()+" : expected: ";
    for (auto ex:expected)
      estr+=Token_New::toString(ex)+" or ";
    estr.substr(0,estr.size()-3);
    estr+="; found: " +found.str();
    error_=estr;
  }

  void ABC_BuildByToken::clearErrorMessage()
  {
    error_.clear();
  }



  template class buildByToken<double>;
  template class buildByToken<std::vector<double>>;


  template class buildByToken<int>;
  template class buildByToken<std::vector<int>>;

  template class buildByToken<std::size_t>;
  template class buildByToken<std::vector<std::size_t>>;

  template class buildByToken<std::string>;
  template class buildByToken<std::vector<std::string>>;



  template class buildByToken<std::set<double>>;



  template class buildByToken<Markov_LA::M_Matrix<double>>;

  std::string build_ABC_Value::ClassName()
  {
    return "build_ABC_Value";
  }

  std::set<std::string> build_ABC_Value::SuperClasses()
  {
    return ABC_Value_ByToken::SuperClasses()+ClassName();
  }

  std::string build_ABC_Value::myClass() const
  {
    return ClassName();

  }

  build_ABC_Value::build_ABC_Value(ABC_Var *p):
    ABC_Value_ByToken(p),
    mystate{S_Init}
  ,x_(nullptr)
  ,id_(p)
  ,var_(nullptr)
  ,previousTok_{}
  , prevTokens_{}{}

  void build_ABC_Value::clear()
  {
    ABClass_buildByToken::clear();
    delete x_;
    mystate=S_Init;
    x_=nullptr;


  }

  ABC_Value *build_ABC_Value::unloadVar()
  {
    if (isFinal())
      {
        auto out=x_;
        mystate=S_Init;
        x_=nullptr;

        return out;
      }
    else return nullptr;
  }

  bool build_ABC_Value::unPop(ABC_Value *var)
  {
    if (x_!=var)
      {
        auto v=createBuild_Value(parent(),var);
        if (v!=nullptr)
          {
            delete x_;
            x_=var;
            delete var_;
            var_=v;
            mystate=S_Final;
            return true;
          }
        else return false;
      }
    else
      return true;
  }

  bool build_ABC_Value::pushToken(Token_New t)
  {
    switch (mystate)
      {
      case S_Init:
      case S_ID_Partial:
        if (!id_.pushToken(t))
          {
            ABC_BuildByToken::setErrorMessage(&id_);
            return false;
          }
        else if (id_.isFinal())
          {

            mystate=S_ID_Final;
            return true;
          }
        else
          {
            mystate=S_ID_Partial;
            return true;
          }
        break;
      case S_ID_Final:
        if (t.tok()==Token_New::BEGIN)
          {
            var_=new build_Implements_Complex_Value(id_.unloadVar());
            var_->pushToken(t);
            mystate=S_Var_Partial;
            return true;
          }
        else if (t.tok()==Token_New::ASSIGN)
          {
            prevTokens_.push_back(t);
            mystate=S_NOT_Complex_Und;
            return true;
          }
        else
          {
            ABC_BuildByToken::setErrorsMessage({Token_New::BEGIN,Token_New::ASSIGN},t);
            return false;
          }
        break;
      case S_Var_Partial:
        if(!var_->pushToken(t))
          {
            ABC_BuildByToken::setErrorMessage(var_);
            return false;
          }
        else if (var_->isFinal())
          {
            mystate=S_Final;
            x_=var_->unloadVar();
            return true;
          }
        else
          {
            mystate=S_Var_Partial;
            return true;
          }
        break;
      case S_NOT_Complex_Und:
        if (t.tok()==Token_New::MUL)
          {
            var_=new build_Implements_Refer_Var(id_.unloadVar());
          }
        else if (t.tok()==Token_New::REAL)
          {
            var_=new build_Implements_Simple_Value<double>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::INTEGER)
          {
            var_=new build_Implements_Simple_Value<int>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::UNSIGNED)
          {
            var_=new build_Implements_Simple_Value<std::size_t>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::IDENTIFIER)
          {
            var_=new build_Implements_Simple_Value<std::string>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::EOL)
          {
            prevTokens_.push_back(t);
            mystate=S_SimpMult_Und;
            return true;
          }
        else
          {
            ABC_BuildByToken::setErrorsMessage({Token_New::MUL
                                                ,Token_New::REAL
                                                ,Token_New::UNSIGNED
                                                ,Token_New::INTEGER
                                                ,Token_New::IDENTIFIER
                                                ,Token_New::EOL}
                                               ,t);
            return false;
          }
        prevTokens_.push_back(t);
        for (auto to:prevTokens_)
          if (var_->pushToken(to))
            {
              ABC_BuildByToken::setErrorMessage(var_);
              return false;
            }

        mystate=S_Var_Partial;
        return true;
        break;
      case S_SimpMult_Und:
        if (t.tok()==Token_New::LSB)
          {
            prevTokens_.push_back(t);
            mystate=S_Vec_Und;
            return true;
          }
        else if (t.tok()==Token_New::LCB)
          {
            prevTokens_.push_back(t);
            mystate=S_Set_or_Map;
            return true;
          }
        else if (t.tok()==Token_New::REAL)
          {
            var_=new build_Implements_Simple_Value<Markov_LA::M_Matrix<double>>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::INTEGER)
          {
            var_=new build_Implements_Simple_Value<Markov_LA::M_Matrix<int>>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::UNSIGNED)
          {
            var_=new build_Implements_Simple_Value<Markov_LA::M_Matrix<std::size_t>>(id_.unloadVar());
          }
        else
          {
            ABC_BuildByToken::setErrorsMessage({Token_New::LCB
                                                ,Token_New::LSB
                                                ,Token_New::REAL
                                                ,Token_New::UNSIGNED
                                                ,Token_New::INTEGER
                                               }
                                               ,t);
            return false;
          }

        prevTokens_.push_back(t);

        for (auto to:prevTokens_)
          if (var_->pushToken(to))
            {
              ABC_BuildByToken::setErrorMessage(var_);
              return false;
            }

        mystate=S_Var_Partial;
        return true;
        break;
      case S_Vec_Und:
        if (t.tok()==Token_New::REAL)
          {
            var_=new build_Implements_Simple_Value<std::vector<double>>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::INTEGER)
          {

            var_=new build_Implements_Simple_Value<std::vector<int>>(id_.unloadVar());
          }

        else if (t.tok()==Token_New::UNSIGNED)
          {

            var_=new build_Implements_Simple_Value<std::vector<std::size_t>>(id_.unloadVar());
          }
        else if ((t.tok()==Token_New::IDENTIFIER)||(t.tok()==Token_New::STRING))
          {

            var_=new build_Implements_Simple_Value<std::vector<std::string>>(id_.unloadVar());
          }
        else
          {
            ABC_BuildByToken::setErrorsMessage({Token_New::MUL
                                                ,Token_New::REAL
                                                ,Token_New::UNSIGNED
                                                ,Token_New::INTEGER
                                                ,Token_New::IDENTIFIER
                                                ,Token_New::STRING}
                                               ,t);
            return false;
          }

        // update var_ processing also all the tokens in buffer
        prevTokens_.push_back(t);

        for (auto to:prevTokens_)
          if (var_->pushToken(to))
            {
              ABC_BuildByToken::setErrorMessage(var_);
              return false;
            }
        mystate=S_Var_Partial;
        return true;
        break;
      case S_Set_or_Map:
        // does not allow set of vectors nor maps with vectors as keys
        // we can include those by including the [ token
        if (t.isReal()||t.tok()==Token_New::IDENTIFIER
            ||t.tok()==Token_New::STRING)
          {
            prevTokens_.push_back(t);
            previousTok_=t;
            mystate=S_Set_or_Map2;
            return true;
          }
        else
          {
            ABC_BuildByToken::setErrorsMessage({Token_New::REAL
                                                ,Token_New::UNSIGNED
                                                ,Token_New::INTEGER
                                                ,Token_New::IDENTIFIER
                                                ,Token_New::STRING}
                                               ,t);
            return false;
          }
      case S_Set_or_Map2:
        if (t.tok()==Token_New::COLON)
          {
            prevTokens_.push_back(t);
            mystate=S_Map_Und;
            return true;
          }
        // else it is a set or nothing
        else if (previousTok_.tok()==Token_New::REAL&&t.isReal())
          {
            var_=new build_Implements_Simple_Value<std::set<double>>(id_.unloadVar());
          }
        else if (previousTok_.tok()==Token_New::INTEGER&&t.isInteger())    {
            var_=new build_Implements_Simple_Value<std::set<int>>(id_.unloadVar());
          }
        else if (previousTok_.tok()==Token_New::UNSIGNED&&t.isCount())    {
            var_=new build_Implements_Simple_Value<std::set<std::size_t>>(id_.unloadVar());
          }
        else if ((previousTok_.tok()==Token_New::IDENTIFIER
                  ||previousTok_.tok()==Token_New::STRING)
                 &&(t.tok()==Token_New::IDENTIFIER
                    ||t.tok()==Token_New::STRING))
          {
            var_=new build_Implements_Simple_Value<std::set<std::string>>(id_.unloadVar());
          }
        else
          {
            ABC_BuildByToken::setErrorMessage({Token_New::COLON,previousTok_.tok()},t);
            return false;
          }
        prevTokens_.push_back(t);

        for (auto to:prevTokens_)
          if (var_->pushToken(to))
            {
              ABC_BuildByToken::setErrorMessage(var_);
              return false;
            }
        mystate=S_Var_Partial;
        return true;

        break;
      case S_Map_Und:
        if (previousTok_.tok()==Token_New::REAL)
          {
            if (t.tok()==Token_New::REAL)
              {
                var_=new build_Implements_Simple_Value<std::map<double,double>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::INTEGER)
              {
                var_=new build_Implements_Simple_Value<std::map<double,int>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::UNSIGNED) {
                var_=new build_Implements_Simple_Value<std::map<double,std::size_t>>(id_.unloadVar());
              }
            else   if ((t.tok()==Token_New::IDENTIFIER||t.tok()==Token_New::STRING)) {
                var_=new build_Implements_Simple_Value<std::map<double,std::string>>(id_.unloadVar());
              }
          }
        if (previousTok_.tok()==Token_New::INTEGER)
          {
            if (t.tok()==Token_New::REAL)
              {
                var_=new build_Implements_Simple_Value<std::map<int,double>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::INTEGER)
              {
                var_=new build_Implements_Simple_Value<std::map<int,int>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::UNSIGNED) {
                var_=new build_Implements_Simple_Value<std::map<int,std::size_t>>(id_.unloadVar());
              }
            else   if ((t.tok()==Token_New::IDENTIFIER||t.tok()==Token_New::STRING)) {
                var_=new build_Implements_Simple_Value<std::map<int,std::string>>(id_.unloadVar());
              }
          }
        if (previousTok_.tok()==Token_New::UNSIGNED)
          {
            if (t.tok()==Token_New::REAL)
              {
                var_=new build_Implements_Simple_Value<std::map<std::size_t,double>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::INTEGER)
              {
                var_=new build_Implements_Simple_Value<std::map<std::size_t,int>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::UNSIGNED) {
                var_=new build_Implements_Simple_Value<std::map<std::size_t,std::size_t>>(id_.unloadVar());
              }
            else   if ((t.tok()==Token_New::IDENTIFIER||t.tok()==Token_New::STRING)) {
                var_=new build_Implements_Simple_Value<std::map<std::size_t,std::string>>(id_.unloadVar());
              }
          }
        if ((previousTok_.tok()==Token_New::IDENTIFIER
             ||previousTok_.tok()==Token_New::STRING))

          {
            if (t.tok()==Token_New::REAL)
              {
                var_=new build_Implements_Simple_Value<
                    std::map<std::string,double>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::INTEGER)
              {
                var_=new build_Implements_Simple_Value<
                    std::map<std::string,int>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::UNSIGNED) {
                var_=new build_Implements_Simple_Value
                    <std::map<std::string,std::size_t>>(id_.unloadVar());
              }
            else   if ((t.tok()==Token_New::IDENTIFIER||t.tok()==Token_New::STRING)) {
                var_=new build_Implements_Simple_Value<
                    std::map<std::string,std::string>>(id_.unloadVar());
              }
          }
        else
          {
            ABC_BuildByToken::setErrorsMessage({Token_New::MUL
                                                ,Token_New::REAL
                                                ,Token_New::UNSIGNED
                                                ,Token_New::INTEGER
                                                ,Token_New::IDENTIFIER
                                                ,Token_New::EOL}
                                               ,t);
            return false;
          }
        prevTokens_.push_back(t);

        for (auto to:prevTokens_)
          if (var_->pushToken(to))
            {
              ABC_BuildByToken::setErrorMessage(var_);
              return false;
            }
        mystate=S_Var_Partial;
        return true;
        break;

      case S_Final:
      default:
        return false;
        break;

      }

  }

  std::pair<std::string, std::set<std::string>> build_ABC_Value::alternativesNext(Markov_Console::Markov_CommandManagerVar *cm) const
  {
    switch (mystate)
      {
      case S_Init:
      case S_ID_Partial:
        return id_.alternativesNext(cm);
        break;
      case S_ID_Final:
        return {"class or object",{Token_New::toString(Token_New::BEGIN)
                , Token_New::toString(Token_New::ASSIGN)}};
        break;
      case S_NOT_Complex_Und:
        return {"simple object",{Token_New::toString(Token_New::EOL)
                ,Token_New::toString(Token_New::MUL)
                ,Implements_Simple_Value<double>::ClassName()
                ,Implements_Simple_Value<std::size_t>::ClassName()
                ,Implements_Simple_Value<int>::ClassName()
                ,Implements_Simple_Value<std::string>::ClassName()}};
        break;
      case S_SimpMult_Und:
        return {"complex object",{Token_New::toString(Token_New::LSB)  //map or set
                ,Token_New::toString(Token_New::LCB)  //vector
                ,Implements_Simple_Value<double>::ClassName()   //matrix of doubles
                ,Implements_Simple_Value<std::size_t>::ClassName()  // matrix of counts
                ,Implements_Simple_Value<int>::ClassName()}};  //matrix of integers
        break;
      case S_Vec_Und:
        return {"Vector of",{Implements_Simple_Value<double>::ClassName()
                ,Implements_Simple_Value<std::size_t>::ClassName()
                ,Implements_Simple_Value<int>::ClassName()
                ,Implements_Simple_Value<std::string>::ClassName()}};
        break;
      case S_Set_or_Map:
        return {"set or map",{Implements_Simple_Value<double>::ClassName()
                ,Implements_Simple_Value<std::size_t>::ClassName()
                ,Implements_Simple_Value<int>::ClassName()
                ,Implements_Simple_Value<std::string>::ClassName()}};
        break;
      case S_Set_or_Map2:
        switch (previousTok_.tok()) {
          case Token_New::REAL:
            return {"map or set",{Token_New::toString(Token_New::COLON)  //map
                    ,Implements_Simple_Value<double>::ClassName()}}; //set of doubles
            break;
          case Token_New::INTEGER:
            return {"map or set",{Token_New::toString(Token_New::COLON)  //map
                    ,Implements_Simple_Value<int>::ClassName()}}; //set of doubles
            break;
          case Token_New::UNSIGNED:
            return {"map or set",{Token_New::toString(Token_New::COLON)  //map
                    ,Implements_Simple_Value<std::size_t>::ClassName()}}; //set of doubles
            break;
          case Token_New::IDENTIFIER:
          case Token_New::STRING:

            return {"map or set",{Token_New::toString(Token_New::COLON)  //map
                    ,Implements_Simple_Value<std::string>::ClassName()}}; //set of doubles
            break;

          default:
            return {};
            break;
          }
        break;
      case S_Map_Und:
        return {"map ",{Implements_Simple_Value<double>::ClassName()
                ,Implements_Simple_Value<std::size_t>::ClassName()
                ,Implements_Simple_Value<int>::ClassName()
                ,Implements_Simple_Value<std::string>::ClassName()}};
        break;
      case S_Var_Partial:
        return var_->alternativesNext(cm);
        break;
      case S_Final:
      default:
        return {};
        break;
      }

  }

  Token_New build_ABC_Value::popBackToken()
  {

    switch (mystate)
      {
      case S_Init:
        return {};
        break;

      case S_ID_Final:
        id_.unPop(var_->unloadVar()); // intended followthrough
      case S_ID_Partial:
        {
          auto out=id_.popBackToken();
          if (id_.isInitial())
            mystate=S_Init;
          else
            mystate= S_ID_Partial;
          return out;
        }

      case S_Final:
        var_->unPop(x_);  // intended followthrough
      case S_Var_Partial:
        {
          auto out=var_->popBackToken();
          if (var_->isHollow())
            {
              prevTokens_=definingState(var_,mystate);
            }
          else
            mystate=S_Var_Partial;
          return out;
        }
        break;
      case S_NOT_Complex_Und:
        {
          prevTokens_.pop_back();
          mystate=S_ID_Final;
          return Token_New(Token_New::ASSIGN);
        }
        break;

      case S_SimpMult_Und:
        {
          prevTokens_.pop_back();
          mystate=S_ID_Final;
          return Token_New(Token_New::EOL);
        }
        break;
      case  S_Vec_Und:

        prevTokens_.pop_back();
        mystate=S_SimpMult_Und;
        return Token_New(Token_New::LSB);
        break;


      case  S_Set_or_Map:
        prevTokens_.pop_back();
        mystate=S_SimpMult_Und;
        return Token_New(Token_New::LCB);
        break;
      default:
        return{};
        break;
      }
  }

  bool build_ABC_Value::isFinal() const
  {
    return mystate==S_Final;

  }

  bool build_ABC_Value::isInitial() const
  {
    return mystate==S_Init;
  }

  bool build_ABC_Value::isHollow() const
  {
    switch (mystate) {
      case       S_Init:
      case     S_ID_Partial:
      case     S_ID_Final:
        return true;
      case  S_Var_Partial:
      case     S_Final:
      case     S_NOT_Complex_Und:
      case   S_SimpMult_Und:
      case  S_Vec_Und:
      case   S_Set_or_Map:
      case     S_Set_or_Map2:
      case S_Map_Und:
      default:
        return false;

      }
  }

  build_Implements_ValueId *build_ABC_Value::createBuild_Value(ABC_Value * parent,
                                                               ABC_Value *var)
  {
    //TODO: this seems to be very uneficient.
    // I can think later of a better way..Like figuring out first all the superclasses of var and
    // then look in a table which classname it belongs to.

    if (var->complyClass(Implements_Complex_Value::ClassName()))
      {
        return new build_Implements_Complex_Value(parent);
      }
    else if (var->complyClass(Implements_Refer_Var::ClassName()))
      {
        return new build_Implements_Refer_Var(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<double>::ClassName()))
      {
        return new build_Implements_Simple_Value<double>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<int>::ClassName()))
      {
        return new build_Implements_Simple_Value<int>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::size_t>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::size_t>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::string>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::string>(parent);
      }

    // vectors
    else if (var->complyClass(Implements_Simple_Value<std::vector<double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::vector<double>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::vector<int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::vector<int>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::vector<std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::vector<std::size_t>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::vector<std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::vector<std::string>>(parent);
      }
    //sets
    else if (var->complyClass(Implements_Simple_Value<std::set<double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::set<double>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::set<int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::set<int>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::set<std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::set<std::size_t>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::set<std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::set<std::string>>(parent);
      }

    // matrix

    else if (var->complyClass(Implements_Simple_Value<Markov_LA::M_Matrix<double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<Markov_LA::M_Matrix<double>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<Markov_LA::M_Matrix<int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<Markov_LA::M_Matrix<int>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<Markov_LA::M_Matrix<std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<Markov_LA::M_Matrix<std::size_t>>(parent);
      }

    //maps

    else if (var->complyClass(Implements_Simple_Value<std::map<double,double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<double,double>>(parent);

      }
    else if (var->complyClass(Implements_Simple_Value<std::map<double,int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<double,int>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::map<double,std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<double,std::size_t>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::map<double,std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<double,std::string>>(parent);


      }



    else if (var->complyClass(Implements_Simple_Value<std::map<int,double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<int,double>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<int,int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<int,int>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<int,std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<int,std::size_t>>(parent);

      }
    else if (var->complyClass(Implements_Simple_Value<std::map<int,std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<int,std::string>>(parent);


      }





    else if (var->complyClass(Implements_Simple_Value<std::map<std::size_t,double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::size_t,double>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<std::size_t,int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::size_t,int>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<std::size_t,std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::size_t,std::size_t>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<std::size_t,std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::size_t,std::string>>(parent);


      }



    else if (var->complyClass(Implements_Simple_Value<std::map<std::string,double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::string,double>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<std::string,int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::string,int>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<
                              std::map<std::string,std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::string,std::size_t>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<
                              std::map<std::string,std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::string,std::string>>(parent);


      }
    else return nullptr;
  }



  std::vector<Token_New> build_ABC_Value::definingState(build_Implements_ValueId *var, build_ABC_Value::DFA &mystate)
  {
    if (var->myClass()==build_Implements_Complex_Value::ClassName())
      {
        mystate=S_ID_Final;
        return {};
      }
    else if ((var->myClass()==build_Implements_Refer_Var::ClassName())
             ||(var->myClass()==build_Implements_Simple_Value<double>::ClassName())
             ||(var->myClass()==build_Implements_Simple_Value<int>::ClassName())
             ||(var->myClass()==build_Implements_Simple_Value<std::size_t>::ClassName())
             ||(var->myClass()==build_Implements_Simple_Value<std::string>::ClassName()))
      {
        mystate=S_NOT_Complex_Und;
        return {{Token_New::ASSIGN}};
      }
    else if  (var->myClass()==build_Implements_Simple_Value<
              Markov_LA::M_Matrix<double>>::ClassName())
      {
        mystate=S_SimpMult_Und;
        return {{Token_New::ASSIGN},{Token_New::EOL}};

      }
    else if  (var->myClass()==build_Implements_Simple_Value<
              std::vector<double>>::ClassName())
      {
        mystate=S_Vec_Und;
        return {{Token_New::ASSIGN},{Token_New::EOL},{Token_New::LSB}};

      }
    else if  ((var->myClass()==build_Implements_Simple_Value<
               std::set<double>>::ClassName())
              ||(var->myClass()==build_Implements_Simple_Value<
                 std::map<double,double>>::ClassName()))
      {
        mystate=S_Set_or_Map;
        return {{Token_New::ASSIGN},{Token_New::EOL},{Token_New::LCB}};

      }
    else
      {
        mystate=S_Final;
        return {};
      }

  }

  bool build_Command_Input::pushToken(Token_New t)
  {
    switch (mystate)
      {
      case S_Init:
        if (t.tok()==Token_New::IDENTIFIER)
          {

            if (cm_->has_command(t.identifier()))
              {
                cmd_=cm_->getCommand(t.identifier())->clone();
                if (hasAllInputs(cmd_))
                  mystate=S_Input_Final;
                else if (hasAllMandatoryInputs(cmd_))
                  mystate=S_Mandatory_Final;
                return true;
              }
            else
              {
                setErrorMessage("a valid command",t);
                return false;
              }
          }
        else
          {
            setErrorMessage("a valid command",t);

            return false;
          }
        break;
      case  S_Mandatory_Final:
        if (t.tok()==Token_New::EOL)
          {
            mystate=S_Final;
            return true;
          }
        else if (processVariableInput(t))
          {
            if (hasAllInputs(cmd_))
              mystate=S_Input_Final;
            else mystate=S_Mandatory_Final;
            return true;

          }
        else return false;

        break;
      case S_ID_Final:
      case S_Input_Partial:
        if (processVariableInput(t))
          {
            if (hasAllInputs(cmd_))
              mystate=S_Input_Final;
            else if (hasAllMandatoryInputs(cmd_))
              mystate=S_Mandatory_Final;
            else
              mystate=S_Input_Partial;
            return true;

          }
        else return false;
        break;

      case S_Input_Final:
        if (t.tok()==Token_New::EOL)
          {
            mystate=S_Final;
            return true;
          }
      case S_Final:
      default:
        return false;
        break;

      }

  }

  std::pair<std::string, std::set<std::string>> build_Command_Input::alternativesNext(Markov_Console::Markov_CommandManagerVar *cm) const
  {
    switch (mystate)
      {
      case S_Init:
        return {"command",cm_->getCommandList()};
        break;
      case S_ID_Final:
      case S_Input_Partial:
      case S_Mandatory_Final:
        return inputAlternativeNext(cm_);
        break;
      case S_Final:
        return {cmd_->id(),{Token_New::toString(Token_New::EOL)}};
      default:
        return {};
        break;
      }
  }




  Token_New build_Command_Input::popBackToken()
  {
    switch (mystate)
      {
      case S_Init:
        return {};
        break;
      case S_ID_Final:
        {
          mystate=S_Init;
          Token_New out(cmd_->id());
          return out;
        }
        break;
      case S_Input_Final:
      case S_Input_Partial:
      case S_Mandatory_Final:
        if (hasNoInput(cmd_))
          {
            mystate=S_Init;
            Token_New out(cmd_->id());
            return out;
          }
        else
          {
            Token_New out=popLastInput(cmd_);
            if (hasNoInput(cmd_))
              mystate=S_ID_Final;
            else if (hasAllMandatoryInputs(cmd_))
              mystate=S_Mandatory_Final;
            else
              mystate=S_Input_Partial;
            return out;
          }
        break;
      case S_Final:
        if (hasAllInputs(cmd_))
          mystate=S_Input_Final;
        else
          mystate=S_Mandatory_Final;
        return Token_New(Token_New::EOL);
        break;
      default:
        return {};
      }
  }



  build_Command_Input::build_Command_Input(Markov_Console::Markov_CommandManagerVar *cm):
    ABC_Value_ByToken(cm),
    mystate(S_Init)
  ,cm_(cm)
  , cmd_(nullptr)

  ,iInputField_(0){}
  Markov_Console::ABC_CommandVar *build_Command_Input::unloadVar()
  {
    ABClass_buildByToken::clear();
    Markov_Console::ABC_CommandVar* out=cmd_;
    mystate=S_Init;
    cmd_=nullptr;
    return out;
  }

  void build_Command_Input::clear()
  {
    ABClass_buildByToken::clear();
    delete cmd_;
    mystate=S_Init;
    cmd_=nullptr;
  }

  bool build_Command_Input::unPop(ABC_Value *var)
  {
    /// do some checking later
    ///
    ///
    Markov_Console::ABC_CommandVar* cmd=dynamic_cast<Markov_Console::ABC_CommandVar*>(var);

    if ((cmd!=nullptr)&&(hasAllInputs(cmd)))
      {
        mystate=S_Final;
        cmd_=cmd;
        return true;

      }
    else
      return false;


  }



  bool build_Command_Input::hasAllInputs(const Markov_Console::ABC_CommandVar *v)
  {
    if (v==nullptr)
      return true;
    else
      {
        for (unsigned i=0; i<v->numChilds(); ++i)
          {
            auto o=v->idToValue(v->ith_ChildName(i));
            if ((o==nullptr)||(o->empty()))
              return false;
          }
        return true;
      }
  }


  bool build_Command_Input::hasNoInput(const ABC_Value *v)
  {
    if (v==nullptr)
      return true;
    else
      {
        for (unsigned i=0; i<v->numChilds(); ++i)
          {
            auto o=v->idToValue(v->ith_ChildName(i));
            if ((o!=nullptr)&&(!o->empty()))
              return false;
          }
        return true;
      }
  }


  Token_New build_Command_Input::popLastInput(ABC_Value *v)
  {
    std::size_t i=v->numChilds();
    std::string idith=v->ith_ChildName(i);
    auto oith=v->idToValue(idith);
    while ((i>0)&&((oith==nullptr)||(oith->empty())))
      {
        --i;
        idith=v->ith_ChildName(i);
        oith=v->idToValue(idith);

      }
    if (oith->empty())
      return {};
    else
      {
        if (oith->myClass()==Implements_Refer_Var::ClassName())
          {
            Token_New o(oith->refId());
            oith->clear();
            return o;
          }
        else if (oith->myClass()==Implements_Simple_Value<std::string>::ClassName())
          {
            auto sv=dynamic_cast<Implements_Simple_Value<std::string>*> (oith);
            Token_New o(sv->value());
            oith->clear();
            return o;
          }
        else if (oith->myClass()==Implements_Simple_Value<double>::ClassName())
          {
            auto sv=dynamic_cast<Implements_Simple_Value<double>*> (oith);
            Token_New o(sv->value());
            oith->clear();
            return o;
          }
        else if (oith->myClass()==Implements_Simple_Value<std::size_t>::ClassName())
          {
            auto sv=dynamic_cast<Implements_Simple_Value<std::size_t>*> (oith);
            Token_New o(sv->value());
            oith->clear();
            return o;
          }
        else return {};

      }
  }






  ABC_Value* build_Command_Input::nextInput(Markov_Console::ABC_CommandVar *v,std::size_t& iInputField)
  {

    std::string idith=v->ith_ChildName(iInputField);
    auto oith=v->idToValue(idith);
    while ((iInputField<v->numChilds())&&((oith==nullptr)||(!oith->empty())))
          {
              ++iInputField;
            idith=v->ith_ChildName(iInputField);
            oith=v->idToValue(idith);
          }
    if (iInputField<v->numChilds())
      return oith;
    else return nullptr;


  }


  std::__cxx11::string build_Command_Input::ClassName()
  {
    return "build_Command_Input";
  }

  std::set<std::__cxx11::string> build_Command_Input::SuperClasses()
  {
    return ABC_Value_ByToken::SuperClasses()+ClassName();
  }

  std::__cxx11::string build_Command_Input::myClass() const
  {
    return ClassName();
  }

  std::set<std::__cxx11::string> build_Command_Input::mySuperClasses() const
  {
    return SuperClasses();
  }




  bool build_Command_Input::hasAllMandatoryInputs(const Markov_Console::ABC_CommandVar *cmd)
  {
    if (cmd==nullptr)
      return true;
    else
      {
        for (unsigned i=0; i<cmd->numMandatoryInputs(); ++i)
          {
            auto o=cmd->idToValue(cmd->ith_ChildName(i));
            if ((o==nullptr)||(o->refId().empty()))
              return false;
          }
        return true;
      }

  }


  bool build_Command_Input::hasNoOptionalInput(Markov_Console::ABC_CommandVar *cmd
                                               , const ABC_Value *v)
  {
    if (v==nullptr)
      return true;
    else
      {
        for (unsigned i=cmd->numMandatoryInputs();i<v->numChilds(); ++i)
          {
            auto o=v->idToValue(v->ith_ChildName(i));
            if ((o!=nullptr)&&(!o->refId().empty()))
              return false;
          }
        return true;
      }

  }



  bool build_Command_Input::processVariableInput( Token_New input)
  {

    ABC_Value* oith=nextInput(cmd_,iInputField_);

    if (oith==nullptr)
      {
        ABC_BuildByToken::setErrorMessage(cmd_,"no inputs left");
        return false;
      }
    else if (iInputField_<cmd_->numMandatoryInputs())
      {
        std::string error;
        if (oith->setThisValue(input,&error))
          return true;
        else
          {
            setErrorMessage(cmd_,oith,error);
            return false;
          }
      }
    else
      {
        std::string errorF;
        bool res=oith->setThisValue(input,&errorF);

        std::size_t iend=iInputField_;
        std::string errorTotal;

        while (!res)
          {
            errorTotal+=errorF;
            errorF.clear();
            ++iInputField_;
            if (iInputField_>=cmd_->numChilds())
              iInputField_=cmd_->numMandatoryInputs();
            if (iInputField_==iend)
              break;
            oith=nextInput(cmd_,iInputField_);
            res=oith->setThisValue(input,&errorF);
          }
        if (res)
          return true;
        else
          {
            setErrorMessage(cmd_,errorTotal);
            return false;
          }

      }
  }

  std::pair<std::string, std::set<std::string>> build_Command_Input::inputAlternativeNext(Markov_Console::Markov_CommandManagerVar*cm) const
  {
    ABC_Value* oith=nextInput(cmd_,iInputField_);

    if (oith==nullptr)
      {
        return {"full",{}};
      }
    else
      {
        return {oith->id(),oith->alternativeValues(cm)};
      }


    }

  build_Statement::build_Statement(Markov_Console::Markov_CommandManagerVar *p):
    ABC_Value_ByToken(p),
    mystate{S_Init}
  ,x_(nullptr)
  ,cmv_(nullptr)
  ,v_(p)
  ,c_(p){}

  bool build_Statement::pushToken(Token_New t)
  {
    switch (mystate)
      {
      case S_Init:
        if (c_.pushToken(t))
          {
            if (c_.isFinal())
              {
                cmv_=c_.unloadVar();
                x_=cmv_;
                mystate=S_Command_Final;
                return true;
              }
            else
              {
                mystate=S_Command_Partial;
                return true;
              }
          }
        else if (v_.pushToken(t))
          {
            mystate=S_Expression_Partial;
            return true;
          }
        else
          {
            if (t.tok()==Token_New::EOL)
              return true;
            else
              setErrorMessage(t.str()+": unknown command or variable");

            return false;
          }
        break;
      case S_Command_Partial:
        if (!c_.pushToken(t))
          {
            ABClass_buildByToken::setErrorMessage(c_.errorMessage());
            return false;
          }
        else
          {
            if (c_.isFinal())
              {
                cmv_=c_.unloadVar();
                x_=cmv_;
                mystate=S_Command_Final;
              }
            else
              mystate=S_Command_Partial;
            return true;
          }
        break;
      case S_Expression_Partial:
        if (!v_.pushToken(t))
          {
            ABClass_buildByToken::setErrorMessage(v_.errorMessage());
            return false;
          }
        else
          {
            if (v_.isFinal())
              {
                mystate=S_Expression_Final;
                x_=v_.unloadVar();

              }
            else
              mystate=S_Expression_Partial;
            return true;
          }
        break;
      case S_Command_Final:
      case S_Expression_Final:
      default:
        return false;
        break;
      }

  }

  std::pair<std::string, std::set<std::string>> build_Statement::alternativesNext(Markov_Console::Markov_CommandManagerVar *cm) const
  {
    switch (mystate)
      {
      case S_Init:
        return  {"comands or variables",c_.alternativesNext(cm).second+v_.alternativesNext(cm).second};
        break;
      case S_Command_Partial:
        return c_.alternativesNext(cm);
        break;
      case S_Expression_Partial:
        return c_.alternativesNext(cm);
        break;
      case S_Command_Final:
      case S_Expression_Final:
      default:
        return {};
        break;
      }

  }

  Token_New build_Statement::popBackToken()
  {
    switch (mystate)
      {

      case S_Command_Final:
        c_.unPop(cmv_);  // intended followthrough

      case S_Command_Partial:
        {
          auto out=c_.popBackToken();
          if (c_.isInitial())
            mystate=S_Init;
          else
            mystate=S_Command_Partial;
          return out;
        }
        break;

      case S_Expression_Final:
        v_.unPop(x_);  // intended followthrough

      case S_Expression_Partial:
        {
          auto out=v_.popBackToken();
          if (v_.isInitial())
            mystate=S_Init;
          else
            mystate=S_Expression_Partial;
          return out;
        }
        break;
      case S_Init:
      default:
        return {};
        break;

      }

  }


}
