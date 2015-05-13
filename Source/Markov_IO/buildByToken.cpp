#include "Markov_IO/buildByToken.h"

namespace Markov_IO {

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

  bool build_ABC_Value::unPop(ABC_Value *var)
  {
    if (x_!=var)
      {
        auto v=createBuild_Value(var);
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
    switch (mystate) {
      case S_Init:
      case S_ID_Partial:
        if (!id_.pushToken(t))
          {
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
        else return false;
        break;
      case S_Var_Partial:
        if(!var_->pushToken(t))
          {
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
        else return false;
        prevTokens_.push_back(t);
        for (auto to:prevTokens_)
          if (var_->pushToken(to)) return false;
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
        else return false;
        prevTokens_.push_back(t);

        for (auto to:prevTokens_)
          if (var_->pushToken(to)) return false;
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
        else return false;
        // update var_ processing also all the tokens in buffer
        prevTokens_.push_back(t);

        for (auto to:prevTokens_)
          if (var_->pushToken(to)) return false;
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
        else return false;
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
                    ||t.tok()==Token_New::STRING))    {
            var_=new build_Implements_Simple_Value<std::set<std::string>>(id_.unloadVar());
          }
        else return false;
        prevTokens_.push_back(t);

        for (auto to:prevTokens_)
          if (var_->pushToken(to)) return false;
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
        else return false;
        prevTokens_.push_back(t);

        for (auto to:prevTokens_)
          if (var_->pushToken(to)) return false;
        mystate=S_Var_Partial;
        return true;
        break;

      case S_Final:
      default:
        return false;
        break;

      }

  }

  std::set<std::string> build_ABC_Value::alternativesNext() const
  {
    switch (mystate)
      {
      case S_Init:
      case S_ID_Partial:
        return id_.alternativesNext();
        break;
      case S_ID_Final:
        return {Token_New::toString(Token_New::BEGIN)
                , Token_New::toString(Token_New::ASSIGN)};
        break;
      case S_NOT_Complex_Und:
        return {Token_New::toString(Token_New::EOL)
                ,Token_New::toString(Token_New::MUL)
                ,Implements_Simple_Value<double>::ClassName()
                ,Implements_Simple_Value<std::size_t>::ClassName()
                ,Implements_Simple_Value<int>::ClassName()
                ,Implements_Simple_Value<std::string>::ClassName()};
        break;
      case S_SimpMult_Und:
        return {Token_New::toString(Token_New::LSB)  //map or set
                ,Token_New::toString(Token_New::LCB)  //vector
                ,Implements_Simple_Value<double>::ClassName()   //matrix of doubles
                ,Implements_Simple_Value<std::size_t>::ClassName()  // matrix of counts
                ,Implements_Simple_Value<int>::ClassName()};  //matrix of integers
        break;
      case S_Vec_Und:
        return {Implements_Simple_Value<double>::ClassName()
                ,Implements_Simple_Value<std::size_t>::ClassName()
                ,Implements_Simple_Value<int>::ClassName()
                ,Implements_Simple_Value<std::string>::ClassName()};
        break;
      case S_Set_or_Map:
        return {Implements_Simple_Value<double>::ClassName()
                ,Implements_Simple_Value<std::size_t>::ClassName()
                ,Implements_Simple_Value<int>::ClassName()
                ,Implements_Simple_Value<std::string>::ClassName()};
        break;
      case S_Set_or_Map2:
        switch (previousTok_.tok()) {
          case Token_New::REAL:
            return {Token_New::toString(Token_New::COLON)  //map
                    ,Implements_Simple_Value<double>::ClassName()}; //set of doubles
            break;
          case Token_New::INTEGER:
            return {Token_New::toString(Token_New::COLON)  //map
                    ,Implements_Simple_Value<int>::ClassName()}; //set of doubles
            break;
          case Token_New::UNSIGNED:
            return {Token_New::toString(Token_New::COLON)  //map
                    ,Implements_Simple_Value<std::size_t>::ClassName()}; //set of doubles
            break;
          case Token_New::IDENTIFIER:
          case Token_New::STRING:

            return {Token_New::toString(Token_New::COLON)  //map
                    ,Implements_Simple_Value<std::string>::ClassName()}; //set of doubles
            break;

          default:
            return {};
            break;
          }
        break;
      case S_Map_Und:
        return {Implements_Simple_Value<double>::ClassName()
                ,Implements_Simple_Value<std::size_t>::ClassName()
                ,Implements_Simple_Value<int>::ClassName()
                ,Implements_Simple_Value<std::string>::ClassName()};
        break;
      case S_Var_Partial:
        return var_->alternativesNext();
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

  build_Implements_ValueId *build_ABC_Value::createBuild_Value(ABC_Value *var)
  {
    //TODO: this seems to be very uneficient.
    // I can think later of a better way..Like figuring out first all the superclasses of var and
    // then look in a table which classname it belongs to.

    if (var->complyClass(Implements_Complex_Value::ClassName()))
      {
        return new build_Implements_Complex_Value;
      }
    else if (var->complyClass(Implements_Refer_Var::ClassName()))
      {
        return new build_Implements_Refer_Var;
      }
    else if (var->complyClass(Implements_Simple_Value<double>::ClassName()))
      {
        return new build_Implements_Simple_Value<double>;
      }
    else if (var->complyClass(Implements_Simple_Value<int>::ClassName()))
      {
        return new build_Implements_Simple_Value<int>;
      }
    else if (var->complyClass(Implements_Simple_Value<std::size_t>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::size_t>;
      }
    else if (var->complyClass(Implements_Simple_Value<std::string>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::string>;
      }

    // vectors
    else if (var->complyClass(Implements_Simple_Value<std::vector<double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::vector<double>>;
      }
    else if (var->complyClass(Implements_Simple_Value<std::vector<int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::vector<int>>;
      }
    else if (var->complyClass(Implements_Simple_Value<std::vector<std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::vector<std::size_t>>;
      }
    else if (var->complyClass(Implements_Simple_Value<std::vector<std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::vector<std::string>>;
      }
    //sets
    else if (var->complyClass(Implements_Simple_Value<std::set<double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::set<double>>;
      }
    else if (var->complyClass(Implements_Simple_Value<std::set<int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::set<int>>;
      }
    else if (var->complyClass(Implements_Simple_Value<std::set<std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::set<std::size_t>>;
      }
    else if (var->complyClass(Implements_Simple_Value<std::set<std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::set<std::string>>;
      }

    // matrix

    else if (var->complyClass(Implements_Simple_Value<Markov_LA::M_Matrix<double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<Markov_LA::M_Matrix<double>>;
      }
    else if (var->complyClass(Implements_Simple_Value<Markov_LA::M_Matrix<int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<Markov_LA::M_Matrix<int>>;
      }
    else if (var->complyClass(Implements_Simple_Value<Markov_LA::M_Matrix<std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<Markov_LA::M_Matrix<std::size_t>>;
      }

    //maps

    else if (var->complyClass(Implements_Simple_Value<std::map<double,double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<double,double>>;

      }
    else if (var->complyClass(Implements_Simple_Value<std::map<double,int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<double,int>>;
      }
    else if (var->complyClass(Implements_Simple_Value<std::map<double,std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<double,std::size_t>>;
      }
    else if (var->complyClass(Implements_Simple_Value<std::map<double,std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<double,std::string>>;


      }



    else if (var->complyClass(Implements_Simple_Value<std::map<int,double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<int,double>>;


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<int,int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<int,int>>;


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<int,std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<int,std::size_t>>;

      }
    else if (var->complyClass(Implements_Simple_Value<std::map<int,std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<int,std::string>>;


      }





    else if (var->complyClass(Implements_Simple_Value<std::map<std::size_t,double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::size_t,double>>;


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<std::size_t,int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::size_t,int>>;


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<std::size_t,std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::size_t,std::size_t>>;


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<std::size_t,std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::size_t,std::string>>;


      }



    else if (var->complyClass(Implements_Simple_Value<std::map<std::string,double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::string,double>>;


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<std::string,int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::string,int>>;


      }
    else if (var->complyClass(Implements_Simple_Value<
                              std::map<std::string,std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::string,std::size_t>>;


      }
    else if (var->complyClass(Implements_Simple_Value<
                              std::map<std::string,std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::string,std::string>>;


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
















}