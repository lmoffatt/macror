#include "Markov_IO/Token_New.h"

#include <iomanip>
#include <cmath>


namespace Markov_IO_New {
  bool Token_New::isNameChar(char ch)
  {
    const std::string NameChar="abcdefghijklmnopqrstuvwxyz"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "1234567890_"; return
        NameChar.find_first_of(ch)!=std::string::npos;

  }

  bool Token_New::isSpaceChar(char ch)
  {
    const std::string spaceChar=" \t"; return
        spaceChar.find_first_of(ch)!=std::string::npos;

  }

  bool Token_New::isRealNumberChar(char ch)
  { const std::string NumberChar="1234567890.eE+-";
    return NumberChar.find_first_of(ch)!=std::string::npos;


  }

  std::string Token_New::toString(double number)
  {
    std::stringstream ss;
    ss<<std::setprecision(std::numeric_limits<double>::digits10)<<number;
    return ss.str();
  }

  std::string Token_New::toString(int number)
  {
    std::stringstream ss;
    ss<<number;
    return ss.str();
  }

  std::string Token_New::toString(std::size_t number)
  {
    std::stringstream ss;
    ss<<number;
    return ss.str();
  }

  bool Token_New::oneCharIsEnough(Token_New::Value v)
  {
    switch (v) {
      case EOL:
      case PLUS:
      case MUL:
      case DIV:
      case EXPONENT:
      case COMMA:
      case SEMICOLON:
      case LP:
      case RP:
      case LSB:
      case RSB:
      case LCB:
      case RCB:
      case AND:
      case OR:
      case HASH:
        return true;
        break;
      case EMPTY:
      case ANY:
      case IDENTIFIER:
      case STRING:
      case INTEGER:
      case UNSIGNED:
      case REAL:
      case INVALID:
      case DCOLON://::
      case  LEQ:// <=
      case  EQ: //==
      case  NEQ: //~=
      case  GEQ: // >=
      case  WHILE: //while
      case  DO:  //do
      case  IF: //if
      case  THEN: // then
      case  BEGIN: //begin
      case  END: // end
      case  ELSE: // else
      case  SWITCH: //switch
      case  CASE:// case

      default:
        return false;
        break;
      }
  }





  bool Token_New::canBePartial(Token_New::Value v)
  {
    switch (v) {
      case EOL:
      case PLUS:
      case MUL:
      case DIV:
      case EXPONENT:
      case COMMA:
      case SEMICOLON:
      case LP:
      case RP:
      case LSB:
      case RSB:
      case LCB:
      case RCB:
      case AND:
      case OR:
      case HASH:
      case  DCOLON:
      case  LEQ:
      case  EQ:
      case  NEQ:
      case  GEQ:
        return false;
      case EMPTY:
      case COLON:
      case ASSIGN:
      case NOT:
      case LSS:
      case GTR:
      case DOT:
      case MINUS:
      case UNSIGNED:
      case REAL:
      case INTEGER:
      case STRING:
      case IDENTIFIER:
      case INVALID:
      case  WHILE:
      case  DO:
      case  IF:
      case  THEN:
      case  BEGIN:
      case  END:
      case  ELSE:
      case  SWITCH:
      case  CASE:
        return true;


      }

  }

  ///
  /// \brief Token_New::get
  /// \param stream input stream
  /// \return valid stream if a token was successfully read
  /// \post if successfull, the read token is stored.
  /// \post if fails, previous value is wiped out
  /// \post if the stream is invalid, token value is set to Token_New::END
  ///
  /// whitespaces are skipped
  ///
  std::istream &Token_New::get(std::istream &stream)
  {
    str_.clear();
    int_=0;
    size_=0;
    number_=0;
    myState_=S_Init;
    char ch;

    do {	// skip whitespace except '\en'
        if(!stream.get(ch))
          {
            curr_tok = END;
            myState_=S_Final;
            return stream;
          }
      } while (isSpaceChar(ch));

    switch (ch) {
      case '\n':
        str_=ch;
        curr_tok=EOL;
        myState_=S_Final;
        return stream;
        break;
      case '+':
      case '*':
      case '/':
      case '^':

      case ';':

      case '(':
      case ')':
      case '[':
      case ']':
      case '&':
      case '|':
        str_=ch;
        curr_tok=Value(ch);
        myState_=S_Final;

        return stream;

      case '#':
        str_=ch;
        curr_tok=HASH;
        myState_=S_Final;
        return stream;

      case ':':
        if(!stream.get(ch))
          {
            str_=ch;
            curr_tok = COLON;
            myState_=S_Final;

            stream.clear();
            return stream;
          }
        else if (ch==':')
          {
            str_="::";
            curr_tok=DCOLON;
            myState_=S_Final;
            return stream;
          }
        else
          {
            str_=":";
            stream.putback(ch);
            curr_tok=COLON;
            myState_=S_Final;

            return stream;
          }

      case '=':
        if(!stream.get(ch))
          {
            str_="=";
            curr_tok = ASSIGN;
            myState_=S_Final;

            stream.clear();
            return stream;
          }
        else if (ch=='=')
          {
            str_="==";
            curr_tok=EQ;
            myState_=S_Final;
            return stream;
          }
        else
          {
            str_="=";
            stream.putback(ch);
            curr_tok=ASSIGN;
            myState_=S_Final;
            return stream;
          }
      case '~':
        if(!stream.get(ch))
          {
            curr_tok = NOT;
            myState_=S_Final;
            stream.clear();
            return stream;
          }
        else if (ch=='=')
          {
            str_="~=";
            curr_tok=NEQ;
            myState_=S_Final;
            return stream;
          }
        else
          {
            stream.putback(ch);
            str_="~";
            curr_tok=NOT;
            myState_=S_Final;
            return stream;
          }
      case '<':
        if(!stream.get(ch))
          {
            curr_tok = LSS;
            myState_=S_Final;
            stream.clear();
            return stream;
          }
        else if (ch=='=')
          {
            str_="<=";
            curr_tok=LEQ;
            myState_=S_Final;

            return stream;
          }
        else
          {
            str_="<";
            stream.putback(ch);
            curr_tok=LSS;
            return stream;
          }
      case '>':
        if(!stream.get(ch))
          {
            curr_tok = GTR;
            myState_=S_Final;

            stream.clear();
            return stream;
          }
        else if (ch=='=')
          {
            str_=">=";
            curr_tok=GEQ;
            myState_=S_Final;

            return stream;
          }
        else
          {
            stream.putback(ch);
            str_=">";
            curr_tok=GTR;
            myState_=S_Final;
            return stream;
          }

      case '.':
        if(!stream.get(ch))
          {
            curr_tok = DOT;
            myState_=S_Final;

            stream.clear();
            return stream;
          }
        else if (ch=='.')
          {
            str_="..";
            curr_tok=STRING;
            myState_=S_Final;

            return stream;
          }
        else
          {
            stream.putback(ch);
            str_=".";
            curr_tok=DOT;
            return stream;
          }
      case '-':
        str_=ch;
        if(!stream.get(ch))
          {
            curr_tok = MINUS;
            myState_=S_Final;

            stream.clear();
            return stream;
          }
        else if (!isdigit(ch))
          {
            stream.putback(ch);
            curr_tok=MINUS;
            myState_=S_Final;
            return stream;
          }

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        if (str_=="-")
          {
            curr_tok=INTEGER;
            str_+= ch;
          }
        else
          {
            curr_tok=UNSIGNED;
            str_= ch;
          }
        while (stream.get(ch) && std::isdigit(ch))
          str_.push_back(ch);
        if (ch=='.')
          {
            str_.push_back(ch);
            while (stream.get(ch) && std::isdigit(ch))
              str_.push_back(ch);
            if ((ch=='e')||(ch=='E'))
              {
                str_.push_back(ch);
                if ((stream.get(ch)) && ((std::isdigit(ch)||(ch=='-')||(ch=='+'))))
                  str_.push_back(ch);
                while (stream.get(ch) && std::isdigit(ch))
                  str_.push_back(ch);
              }
            curr_tok=REAL;
            std::stringstream ss(str_);
            ss>>number_;
            if (!std::isdigit(ch))
              stream.putback(ch);
            myState_=S_Final;

            return stream;

          }
        else if ((ch=='e')||(ch=='E'))
          {
            str_.push_back(ch);
            if ((stream.get(ch)) && ((std::isdigit(ch)||(ch=='-')||(ch=='+'))))
              str_.push_back(ch);
            while (stream.get(ch) && std::isdigit(ch))
              str_.push_back(ch);
            curr_tok=REAL;
            try{
              number_=std::stod(str_);

            }
            catch (...)
            {
              curr_tok=INVALID;
              myState_=S_Final;

              return stream;
            }

            if (!isdigit(ch))
              stream.putback(ch);
            myState_=S_Final;

            return stream;
          }
        if (curr_tok==INTEGER)
          try{
            int_=std::stoi(str_);} catch(...){ curr_tok=INVALID;}
        else if (curr_tok==UNSIGNED)
          try{
            size_=std::stoul(str_);
          }
        catch(...){ curr_tok=INVALID;}
        if (!isdigit(ch))
          stream.putback(ch);
        myState_=S_Final;

        return stream;
      case '"':
        str_.push_back(ch);
        while (stream.get(ch)&& (ch!='"'))
          str_.push_back(ch);

        if (ch!='"')
          {
            //error("missing `""` ");
            curr_tok=STRING;
            stream.setstate(stream.rdstate() | std::ios_base::failbit);
            myState_=S_Final;

            return stream;
          }
        else
          {
            curr_tok=STRING;
            str_.push_back(ch);
          }
        myState_=S_Final;

        return stream;

      default:			// NAME, NAME=, or error
        if (isalpha(ch))
          {
            str_ = ch;
            while (stream.get(ch) && isNameChar(ch))
              str_.push_back(ch);
            if (!isNameChar(ch))
              stream.putback(ch);

            curr_tok=toKeyword(str_);
            str_.push_back(' ');
            stream.clear();
            myState_=S_Final;

            return stream;
          }
        else
          {
            //error("bad token");
            curr_tok=INVALID;
            stream.setstate(stream.rdstate() | std::ios_base::failbit);
            return stream;
          }

      }
  }

  std::string Token_New::str() const
  {
    return str_;
  }

  std::string Token_New::identifier() const
  {
    return identifier(str_);
  }

  std::string Token_New::identifier(const std::string idWithSPace)
  {
    return  idWithSPace.substr(0,idWithSPace.find_first_of(" "));
  }

  double Token_New::realValue() const
  {
    if (isFinal())
      switch (curr_tok) {
        case UNSIGNED:
          return size_;
        case INTEGER:
          return int_;
        case REAL:
          return number_;
        default:
          return {};
        }
    else return {};

  }

  int Token_New::intval() const
  {
    if (!isFinal()) return {};
    switch (curr_tok) {
      case UNSIGNED:
        return size_;
      case INTEGER:
        return int_;
      case REAL:
        return number_;
      default:
        return {};
      }
  }


  std::size_t Token_New::count() const
  {
    if (!isFinal()) return {};
    switch (curr_tok) {
      case UNSIGNED:
        return size_;
      case INTEGER:
        return int_;
      case REAL:
        return number_;
      default:
        return {};
      }
  }

  Token_New::Value Token_New::tok() const
  {
    return curr_tok;
  }

  std::string Token_New::toString() const
  {
    if (tok()==REAL)
      return toString(number_)+" ";
    else  if (tok()==INTEGER)
      return toString(int_)+" ";
    else  if (tok()==UNSIGNED)
      return toString(size_)+" ";
    else if (tok()==IDENTIFIER)
      return str_+" ";
    else if (tok()==STRING)
      return "\""+str_+"\" ";
    else return toString(tok());
  }

  bool Token_New::isReal(std::string *whyNot, const std::string& masterObjective) const
  {
    if (!isFinal())
      {
        *whyNot=masterObjective+": Not a real number",str()," is not final";
        return false;
      }

    else
      {
        return (tok()==REAL)||(tok()==INTEGER)||(tok()==UNSIGNED);
        *whyNot=masterObjective+": Not a real number";
        }
  }

  bool Token_New::isInteger(std::string *whyNot, const std::string& masterObjective) const
  {
    const std::string objective=masterObjective+": "+str()+" is not an integer";
    if (!isFinal())
      {
        *whyNot=objective+": is not final";
        return false;
      }
    else
      if ((tok()==INTEGER)||(tok()==UNSIGNED))
        return true;
      else if (tok()==REAL){
          if (number_-std::floor(number_)==0)
            return true;
          else
            {
              *whyNot=objective+" has fractional component";
              return false;
            }
        }
      else
        {
          *whyNot=objective+" not a number";
          return false;
        }
  }

  bool Token_New::isCount(std::string *whyNot, const std::string &masterObjective) const
  {
    const std::string objective=masterObjective+": Token "+str()+" is not count";

    if (!isFinal()) return false;
    else

      if (tok()==UNSIGNED)
        return true;
      else if ((tok()==INTEGER))
        {
          if (int_>=0) return true;
          else
            {
              *whyNot=objective+" is negative";
              return false;
            }
        }
      else if (tok()==REAL){
          if (number_<0)
            {
              *whyNot=objective+" is negative";
              return false;
            }
          else if (number_-floor(number_)!=0)
            {
              *whyNot=objective+" has fractional component";
              return false;

            }
          else return true;
           }
      else
        {
          *whyNot=objective+" is not a number";

          return false;
        }

  }


  Token_New::Value Token_New::toKeyword(std::string identifier)
  {
    if (identifier.empty())
      return EMPTY;
    if (identifier.back()==' ')
      identifier.pop_back();
    if ((identifier.front()=='"')||(identifier==".."))
      return STRING;
    else if (isalpha(identifier.front()))
      {
        if(identifier=="do")
          {
            return DO;
          }
        else if(identifier=="then")
          {
            return THEN;
          }
        else if(identifier=="while")
          {
            return WHILE;
          }
        else if(identifier=="if")
          {
            return IF;
          }
        else if(identifier=="else")
          {
            return ELSE;
          }
        else if(identifier=="begin")
          {
            return BEGIN;
          }
        else if(identifier=="end")
          {
            return END;
          }
        else if(identifier=="switch")
          {
            return SWITCH;
          }
        else if(identifier=="case")
          {
            return CASE;
          }
        else
          return IDENTIFIER;
      }
    else if (std::isdigit(identifier.front()))
      {
        if (identifier.find_first_not_of("0123456789")!=identifier.npos)
          return UNSIGNED;
        else if  (identifier.find_first_not_of("0123456789.eE+-")!=identifier.npos)
          return REAL;
      }
    else if (std::isdigit(identifier.front()=='-')
             &&(identifier.find_first_not_of("0123456789",1)!=identifier.npos))
      return INTEGER;
    else if (identifier=="\n") return EOL;

    else if (identifier=="+") return PLUS;
    else if (identifier=="-") return MINUS;
    else if (identifier=="*") return MUL;
    else if (identifier=="/") return DIV;
    else if (identifier=="^") return EXPONENT;
    else if (identifier==".") return DOT;
    else if (identifier==":") return COLON;
    else if (identifier==",") return COMMA;
    else if (identifier==";") return SEMICOLON;
    else if (identifier=="=") return ASSIGN;
    else if (identifier=="(") return LP;
    else if (identifier==")") return RP;
    else if (identifier=="[") return LSB;
    else if (identifier=="]") return RSB;
    else if (identifier=="{") return LCB;
    else if (identifier=="}") return RCB;
    else if (identifier=="~") return NOT;
    else if (identifier=="&") return AND;
    else if (identifier=="|") return OR;
    else if (identifier=="<") return LSS;
    else if (identifier==">") return GTR;
    else if (identifier=="#") return HASH;
    else if (identifier=="::") return DCOLON;
    else if (identifier=="<=") return LEQ;
    else if (identifier=="==") return EQ;
    else if (identifier=="~=") return NEQ;
    else if (identifier==">=") return GEQ;
    else return INVALID;


  }

  Token_New::Value Token_New::toToken(char ch)
  {
    switch (ch) {
      case '\n':
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
      case '.':
      case ':':
      case ',':
      case ';':
      case '=':
      case '(':
      case ')':
      case '[':
      case ']':
      case '{':
      case '}':
      case '~':
      case '&':
      case '#':
      case '|':
      case '>':
      case '<':
        return static_cast<Value>(ch);
        break;
      case '"':
        return STRING;
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        return UNSIGNED;
        break;

      default:
        if (isalpha(ch)||ch=='_')
          return IDENTIFIER;
        else if (isSpaceChar(ch))
          return EMPTY;
        else
          return INVALID;
      }
  }


  ///
  /// \brief Token_New::toString string representation of an operator or keyword Token_New::Value
  /// \param identifier the category of token
  /// \return string representation of the keyword or operator token
  ///  \return empty string otherwise (number, identifier, string,path)
  ///
  std::string Token_New::toString(Token_New::Value identifier)
  {
    switch (identifier) {
      case EMPTY:
      case IDENTIFIER:
      case STRING:
      case INTEGER:
      case UNSIGNED:
      case REAL:
      case INVALID:
        return{};
      case EOL: return "\n";
      case PLUS: return "+";
      case MINUS: return "-";
      case MUL:   return "*";
      case DIV:   return "/";
      case EXPONENT:   return "^";
      case DOT:   return ".";
      case COLON:   return ":";
      case COMMA:   return ",";
      case SEMICOLON:   return ";";
      case ASSIGN:   return  "=";
      case LP:   return "(" ;
      case RP:   return  ")";
      case LSB:   return  "[";
      case RSB:   return  "]";
      case LCB: return "{";
      case RCB: return "}";
      case NOT:   return  "~";
      case AND:   return  "&";
      case OR:   return  "|";
      case LSS:   return  "<";
      case GTR:   return  ">";
      case HASH:   return "#";
      case DCOLON:  return  "::";
      case LEQ:   return  "<=";
      case EQ:   return  "==";
      case NEQ:   return  "~=";
      case GEQ:   return  ">=";

      case WHILE:   return  "while ";
      case DO:   return  "do ";
      case IF:   return  "if ";
      case THEN:   return  "then ";
      case BEGIN:   return  "begin ";
      case END:   return  "end ";
      case ELSE:   return  "else ";
      case SWITCH:   return "switch ";
      case CASE:    return "case ";
      }



  }

  char Token_New::popLastChar()
  {
    if (str_.empty())
      return {};
    char r=str_.back();
    str_.pop_back();
    curr_tok=toKeyword(str_);
    if (curr_tok==EMPTY)
      myState_=S_Init;
    else if (!canBePartial(curr_tok))
      myState_=S_Final;
    else
      myState_=S_Partial;
    return r;
  }
  bool Token_New::CharIsSuccesfullyFeed(char ch)
  {
    if (myState_==S_Final)
      return false;
    else if (myState_==S_Init)
      {
        curr_tok=toToken(ch);
        if (curr_tok==INVALID)
          {
            return false;
          }
        else if (curr_tok==EMPTY)
          {
            return true;
          }
        else
          {
            str_.push_back(ch);
            if (oneCharIsEnough(curr_tok))
              myState_=S_Final;
            else
              myState_=S_Partial;
            return true;
          }
      }
    else if (!canBePartial(curr_tok))
      {
        myState_=S_Final;  // there is a logical error if we ever get here, since
        // myState could not be S_Partial to begin with
        return false;
      }
    else
      switch (curr_tok) {
        case COLON:
          if (ch==':')
            {
              curr_tok=DCOLON;
              str_.push_back(ch);
              myState_=S_Final;
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }
        case ASSIGN:
          if (ch=='=')
            {
              curr_tok=EQ;
              str_.push_back(ch);
              myState_=S_Final;
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }
        case NOT:
          if (ch=='=')
            {
              curr_tok=NEQ;
              str_.push_back(ch);
              myState_=S_Final;

              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }

        case LSS:
          if (ch=='=')
            {
              curr_tok=LEQ;
              str_.push_back(ch);
              myState_=S_Final;
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }

        case GTR:
          if (ch=='=')
            {
              curr_tok=GEQ;
              str_.push_back(ch);
              myState_=S_Final;
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }
        case DOT:
          if (ch=='.')
            {
              curr_tok=STRING;
              str_.push_back(ch);
              myState_=S_Final;
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }
        case MINUS:
          if (isdigit(ch))
            {
              curr_tok=INTEGER;
              str_.push_back(ch);
              myState_=S_Partial;  // it is already S_Partial, just for clarity
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }
        case UNSIGNED:
          if (isdigit(ch))
            {
              str_.push_back(ch);
              myState_=S_Partial;
              return true;
            }
          else if ((ch=='.')||(ch=='e')||(ch=='E'))
            {
              str_.push_back(ch);
              curr_tok=REAL;
              myState_=S_Partial;
              return true;
            }
          else
            {
              try {
                size_=std::stoul(str_);
              } catch (...) {
                curr_tok=INVALID;
              }
              myState_=S_Final;
              return false;
            }
        case REAL:
          if (isdigit(ch)||ch=='E'||ch=='e'||ch=='.'
              ||(((ch=='+')||(ch=='-'))&&((str_.back()=='e')||(str_.back()=='E'))))
            {
              str_.push_back(ch);
              myState_=S_Partial;
              return true;
            }
          else
            {
              try {
                number_=std::stod(str_);
              } catch (...) {
                curr_tok=INVALID;
              }
              myState_=S_Final;
              return false;
            }
        case INTEGER:
          if (isdigit(ch))
            {
              str_.push_back(ch);
              myState_=S_Partial;
              return true;
            }
          else if ((ch=='.')||(ch=='e')||(ch=='E'))
            {
              curr_tok=REAL;
              str_.push_back(ch);
              myState_=S_Partial;
              return true;
            }
          else
            {
              try {
                int_=std::stoi(str_);
              } catch (...) {
                curr_tok=INVALID;
              }
              myState_=S_Final;
              return false;
            }
        case STRING:
          if ((str_.size()==1)||(str_.back()!='"'))
            {
              str_.push_back(ch);
              myState_=S_Partial;
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }
        case IDENTIFIER:
          if (isNameChar(ch))
            {
              str_.push_back(ch);
              myState_=S_Partial;
              return true;
            }
          else
            {
              myState_=S_Final;
              if (isSpaceChar(ch))
                {
                  str_.push_back(ch);
                  return true;
                }
              else
                return false;
            }
        case INVALID:
          {
            myState_=S_Partial;
            return false;
          }
        }

  }



  Token_New::Token_New():
    curr_tok(EMPTY),
    myState_(S_Init),
    number_(),
    int_(),
    size_(),
    str_(){}

  Token_New::Token_New(double d):
    curr_tok{REAL},
    myState_(S_Final),
    number_(d),
    int_{},
    size_{},
    str_{std::to_string(d)}{}

  Token_New::Token_New(int n):
    curr_tok{INTEGER},
    myState_(S_Final),
    number_{},
    int_{n},
    size_{},
    str_{std::to_string(n)}{}

  Token_New::Token_New(std::size_t s):
    curr_tok{UNSIGNED},
    myState_(S_Final),
    number_{},
    int_{},
    size_{s},
    str_{std::to_string(s)}{}

  Token_New::Token_New(const std::string& d):
    curr_tok{},
    myState_(S_Final),
    number_{},
    str_{}{
    std::stringstream ss(d);
    get(ss);
  }

  Token_New::Token_New(Token_New::Value v):
    curr_tok{v},
    myState_(S_Final),
    number_{},
    int_{},
    size_{},
    str_{toString(v)}{ }

  Token_New::Token_New(char ch):
    curr_tok(toToken(ch)),
    myState_(S_Final),
    number_(),
    int_(),
    size_(),
    str_()
  {
    if (curr_tok!=STRING&&curr_tok!=EMPTY)
      str_.push_back(ch);
  }

  void Token_New::clear()
  {
    curr_tok=EMPTY;
    myState_=S_Init;
    number_={};
    int_={};
    size_={};
    str_={};
  }



  bool Token_New::pushChar(char c)
  {

  }


}



namespace Markov_IO {
  bool Token_New::isNameChar(char ch)
  {
    const std::string NameChar="abcdefghijklmnopqrstuvwxyz"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "1234567890_"; return
        NameChar.find_first_of(ch)!=std::string::npos;

  }

  bool Token_New::isSpaceChar(char ch)
  {
    const std::string spaceChar=" \t"; return
        spaceChar.find_first_of(ch)!=std::string::npos;

  }

  bool Token_New::isRealNumberChar(char ch)
  { const std::string NumberChar="1234567890.eE+-";
    return NumberChar.find_first_of(ch)!=std::string::npos;


  }

  std::string Token_New::toString(double number)
  {
    std::stringstream ss;
    ss<<std::setprecision(std::numeric_limits<double>::digits10)<<number;
    return ss.str();
  }

  std::string Token_New::toString(int number)
  {
    std::stringstream ss;
    ss<<number;
    return ss.str();
  }

  std::string Token_New::toString(std::size_t number)
  {
    std::stringstream ss;
    ss<<number;
    return ss.str();
  }

  bool Token_New::oneCharIsEnough(Token_New::Value v)
  {
    switch (v) {
      case EOL:
      case PLUS:
      case MUL:
      case DIV:
      case EXPONENT:
      case COMMA:
      case SEMICOLON:
      case LP:
      case RP:
      case LSB:
      case RSB:
      case LCB:
      case RCB:
      case AND:
      case OR:
      case HASH:
        return true;
        break;
      case EMPTY:
      case ANY:
      case IDENTIFIER:
      case STRING:
      case INTEGER:
      case UNSIGNED:
      case REAL:
      case INVALID:
      case DCOLON://::
      case  LEQ:// <=
      case  EQ: //==
      case  NEQ: //~=
      case  GEQ: // >=
      case  WHILE: //while
      case  DO:  //do
      case  IF: //if
      case  THEN: // then
      case  BEGIN: //begin
      case  END: // end
      case  ELSE: // else
      case  SWITCH: //switch
      case  CASE:// case

      default:
        return false;
        break;
      }
  }





  bool Token_New::canBePartial(Token_New::Value v)
  {
    switch (v) {
      case EOL:
      case PLUS:
      case MUL:
      case DIV:
      case EXPONENT:
      case COMMA:
      case SEMICOLON:
      case LP:
      case RP:
      case LSB:
      case RSB:
      case LCB:
      case RCB:
      case AND:
      case OR:
      case HASH:
      case  DCOLON:
      case  LEQ:
      case  EQ:
      case  NEQ:
      case  GEQ:
        return false;
      case EMPTY:
      case COLON:
      case ASSIGN:
      case NOT:
      case LSS:
      case GTR:
      case DOT:
      case MINUS:
      case UNSIGNED:
      case REAL:
      case INTEGER:
      case STRING:
      case IDENTIFIER:
      case INVALID:
      case  WHILE:
      case  DO:
      case  IF:
      case  THEN:
      case  BEGIN:
      case  END:
      case  ELSE:
      case  SWITCH:
      case  CASE:
        return true;


      }

  }

  ///
  /// \brief Token_New::get
  /// \param stream input stream
  /// \return valid stream if a token was successfully read
  /// \post if successfull, the read token is stored.
  /// \post if fails, previous value is wiped out
  /// \post if the stream is invalid, token value is set to Token_New::END
  ///
  /// whitespaces are skipped
  ///
  std::istream &Token_New::get(std::istream &stream)
  {
    str_.clear();
    int_=0;
    size_=0;
    number_=0;
    myState_=S_Init;
    char ch;

    do {	// skip whitespace except '\en'
        if(!stream.get(ch))
          {
            curr_tok = END;
            myState_=S_Final;
            return stream;
          }
      } while (isSpaceChar(ch));

    switch (ch) {
      case '\n':
        str_=ch;
        curr_tok=EOL;
        myState_=S_Final;
        return stream;
        break;
      case '+':
      case '*':
      case '/':
      case '^':

      case ';':

      case '(':
      case ')':
      case '[':
      case ']':
      case '&':
      case '|':
        str_=ch;
        curr_tok=Value(ch);
        myState_=S_Final;

        return stream;

      case '#':
        str_=ch;
        curr_tok=HASH;
        myState_=S_Final;
        return stream;

      case ':':
        if(!stream.get(ch))
          {
            str_=ch;
            curr_tok = COLON;
            myState_=S_Final;

            stream.clear();
            return stream;
          }
        else if (ch==':')
          {
            str_="::";
            curr_tok=DCOLON;
            myState_=S_Final;
            return stream;
          }
        else
          {
            str_=":";
            stream.putback(ch);
            curr_tok=COLON;
            myState_=S_Final;

            return stream;
          }

      case '=':
        if(!stream.get(ch))
          {
            str_="=";
            curr_tok = ASSIGN;
            myState_=S_Final;

            stream.clear();
            return stream;
          }
        else if (ch=='=')
          {
            str_="==";
            curr_tok=EQ;
            myState_=S_Final;
            return stream;
          }
        else
          {
            str_="=";
            stream.putback(ch);
            curr_tok=ASSIGN;
            myState_=S_Final;
            return stream;
          }
      case '~':
        if(!stream.get(ch))
          {
            curr_tok = NOT;
            myState_=S_Final;
            stream.clear();
            return stream;
          }
        else if (ch=='=')
          {
            str_="~=";
            curr_tok=NEQ;
            myState_=S_Final;
            return stream;
          }
        else
          {
            stream.putback(ch);
            str_="~";
            curr_tok=NOT;
            myState_=S_Final;
            return stream;
          }
      case '<':
        if(!stream.get(ch))
          {
            curr_tok = LSS;
            myState_=S_Final;
            stream.clear();
            return stream;
          }
        else if (ch=='=')
          {
            str_="<=";
            curr_tok=LEQ;
            myState_=S_Final;

            return stream;
          }
        else
          {
            str_="<";
            stream.putback(ch);
            curr_tok=LSS;
            return stream;
          }
      case '>':
        if(!stream.get(ch))
          {
            curr_tok = GTR;
            myState_=S_Final;

            stream.clear();
            return stream;
          }
        else if (ch=='=')
          {
            str_=">=";
            curr_tok=GEQ;
            myState_=S_Final;

            return stream;
          }
        else
          {
            stream.putback(ch);
            str_=">";
            curr_tok=GTR;
            myState_=S_Final;
            return stream;
          }

      case '.':
        if(!stream.get(ch))
          {
            curr_tok = DOT;
            myState_=S_Final;

            stream.clear();
            return stream;
          }
        else if (ch=='.')
          {
            str_="..";
            curr_tok=STRING;
            myState_=S_Final;

            return stream;
          }
        else
          {
            stream.putback(ch);
            str_=".";
            curr_tok=DOT;
            return stream;
          }
      case '-':
        str_=ch;
        if(!stream.get(ch))
          {
            curr_tok = MINUS;
            myState_=S_Final;

            stream.clear();
            return stream;
          }
        else if (!isdigit(ch))
          {
            stream.putback(ch);
            curr_tok=MINUS;
            myState_=S_Final;
            return stream;
          }

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        if (str_=="-")
          {
            curr_tok=INTEGER;
            str_+= ch;
          }
        else
          {
            curr_tok=UNSIGNED;
            str_= ch;
          }
        while (stream.get(ch) && std::isdigit(ch))
          str_.push_back(ch);
        if (ch=='.')
          {
            str_.push_back(ch);
            while (stream.get(ch) && std::isdigit(ch))
              str_.push_back(ch);
            if ((ch=='e')||(ch=='E'))
              {
                str_.push_back(ch);
                if ((stream.get(ch)) && ((std::isdigit(ch)||(ch=='-')||(ch=='+'))))
                  str_.push_back(ch);
                while (stream.get(ch) && std::isdigit(ch))
                  str_.push_back(ch);
              }
            curr_tok=REAL;
            std::stringstream ss(str_);
            ss>>number_;
            if (!std::isdigit(ch))
              stream.putback(ch);
            myState_=S_Final;

            return stream;

          }
        else if ((ch=='e')||(ch=='E'))
          {
            str_.push_back(ch);
            if ((stream.get(ch)) && ((std::isdigit(ch)||(ch=='-')||(ch=='+'))))
              str_.push_back(ch);
            while (stream.get(ch) && std::isdigit(ch))
              str_.push_back(ch);
            curr_tok=REAL;
            try{
              number_=std::stod(str_);

            }
            catch (...)
            {
              curr_tok=INVALID;
              myState_=S_Final;

              return stream;
            }

            if (!isdigit(ch))
              stream.putback(ch);
            myState_=S_Final;

            return stream;
          }
        if (curr_tok==INTEGER)
          try{
            int_=std::stoi(str_);} catch(...){ curr_tok=INVALID;}
        else if (curr_tok==UNSIGNED)
          try{
            size_=std::stoul(str_);
          }
        catch(...){ curr_tok=INVALID;}
        if (!isdigit(ch))
          stream.putback(ch);
        myState_=S_Final;

        return stream;
      case '"':
        str_.push_back(ch);
        while (stream.get(ch)&& (ch!='"'))
          str_.push_back(ch);

        if (ch!='"')
          {
            //error("missing `""` ");
            curr_tok=STRING;
            stream.setstate(stream.rdstate() | std::ios_base::failbit);
            myState_=S_Final;

            return stream;
          }
        else
          {
            curr_tok=STRING;
            str_.push_back(ch);
          }
        myState_=S_Final;

        return stream;

      default:			// NAME, NAME=, or error
        if (isalpha(ch))
          {
            str_ = ch;
            while (stream.get(ch) && isNameChar(ch))
              str_.push_back(ch);
            if (!isNameChar(ch))
              stream.putback(ch);

            curr_tok=toKeyword(str_);
            str_.push_back(' ');
            stream.clear();
            myState_=S_Final;

            return stream;
          }
        else
          {
            //error("bad token");
            curr_tok=INVALID;
            stream.setstate(stream.rdstate() | std::ios_base::failbit);
            return stream;
          }

      }
  }

  std::string Token_New::str() const
  {
    return str_;
  }

  std::string Token_New::identifier() const
  {
    return identifier(str_);
  }

  std::string Token_New::identifier(const std::string idWithSPace)
  {
    return  idWithSPace.substr(0,idWithSPace.find_first_of(" "));
  }

  double Token_New::realValue() const
  {
    if (isFinal())
      switch (curr_tok) {
        case UNSIGNED:
          return size_;
        case INTEGER:
          return int_;
        case REAL:
          return number_;
        default:
          return {};
        }
    else return {};

  }

  int Token_New::intval() const
  {
    if (!isFinal()) return {};
    switch (curr_tok) {
      case UNSIGNED:
        return size_;
      case INTEGER:
        return int_;
      case REAL:
        return number_;
      default:
        return {};
      }
  }


  std::size_t Token_New::count() const
  {
    if (!isFinal()) return {};
    switch (curr_tok) {
      case UNSIGNED:
        return size_;
      case INTEGER:
        return int_;
      case REAL:
        return number_;
      default:
        return {};
      }
  }

  Token_New::Value Token_New::tok() const
  {
    return curr_tok;
  }

  std::string Token_New::toString() const
  {
    if (tok()==REAL)
      return toString(number_)+" ";
    else  if (tok()==INTEGER)
      return toString(int_)+" ";
    else  if (tok()==UNSIGNED)
      return toString(size_)+" ";
    else if (tok()==IDENTIFIER)
      return str_+" ";
    else if (tok()==STRING)
      return "\""+str_+"\" ";
    else return toString(tok());
  }

  bool Token_New::isReal() const
  {
    if (!isFinal()) return false;
    else
      return (tok()==REAL)||(tok()==INTEGER)||(tok()==UNSIGNED);
  }

  bool Token_New::isInteger() const
  {
    if (!isFinal()) return false;
    else
      if ((tok()==INTEGER)||(tok()==UNSIGNED))
        return true;
      else if (tok()==REAL){
          if (number_-std::floor(number_)==0)
            return true;
          else return false;}
      else return false;
  }

  bool Token_New::isCount() const
  {
    if (!isFinal()) return false;
    else

      if (tok()==UNSIGNED)
        return true;
      else if ((tok()==INTEGER)){
          if (int_>=0) return true;
          else return false;}
      else if (tok()==REAL){
          if ((number_>=0)&&(number_-floor(number_)==0))
            return true;
          else return false;}
      else return false;

  }


  Token_New::Value Token_New::toKeyword(std::string identifier)
  {
    if (identifier.empty())
      return EMPTY;
    if (identifier.back()==' ')
      identifier.pop_back();
    if ((identifier.front()=='"')||(identifier==".."))
      return STRING;
    else if (isalpha(identifier.front()))
      {
        if(identifier=="do")
          {
            return DO;
          }
        else if(identifier=="then")
          {
            return THEN;
          }
        else if(identifier=="while")
          {
            return WHILE;
          }
        else if(identifier=="if")
          {
            return IF;
          }
        else if(identifier=="else")
          {
            return ELSE;
          }
        else if(identifier=="begin")
          {
            return BEGIN;
          }
        else if(identifier=="end")
          {
            return END;
          }
        else if(identifier=="switch")
          {
            return SWITCH;
          }
        else if(identifier=="case")
          {
            return CASE;
          }
        else
          return IDENTIFIER;
      }
    else if (std::isdigit(identifier.front()))
      {
        if (identifier.find_first_not_of("0123456789")!=identifier.npos)
          return UNSIGNED;
        else if  (identifier.find_first_not_of("0123456789.eE+-")!=identifier.npos)
          return REAL;
      }
    else if (std::isdigit(identifier.front()=='-')
             &&(identifier.find_first_not_of("0123456789",1)!=identifier.npos))
      return INTEGER;
    else if (identifier=="\n") return EOL;

    else if (identifier=="+") return PLUS;
    else if (identifier=="-") return MINUS;
    else if (identifier=="*") return MUL;
    else if (identifier=="/") return DIV;
    else if (identifier=="^") return EXPONENT;
    else if (identifier==".") return DOT;
    else if (identifier==":") return COLON;
    else if (identifier==",") return COMMA;
    else if (identifier==";") return SEMICOLON;
    else if (identifier=="=") return ASSIGN;
    else if (identifier=="(") return LP;
    else if (identifier==")") return RP;
    else if (identifier=="[") return LSB;
    else if (identifier=="]") return RSB;
    else if (identifier=="{") return LCB;
    else if (identifier=="}") return RCB;
    else if (identifier=="~") return NOT;
    else if (identifier=="&") return AND;
    else if (identifier=="|") return OR;
    else if (identifier=="<") return LSS;
    else if (identifier==">") return GTR;
    else if (identifier=="#") return HASH;
    else if (identifier=="::") return DCOLON;
    else if (identifier=="<=") return LEQ;
    else if (identifier=="==") return EQ;
    else if (identifier=="~=") return NEQ;
    else if (identifier==">=") return GEQ;
    else return INVALID;


  }

  Token_New::Value Token_New::toToken(char ch)
  {
    switch (ch) {
      case '\n':
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
      case '.':
      case ':':
      case ',':
      case ';':
      case '=':
      case '(':
      case ')':
      case '[':
      case ']':
      case '{':
      case '}':
      case '~':
      case '&':
      case '#':
      case '|':
      case '>':
      case '<':
        return static_cast<Value>(ch);
        break;
      case '"':
        return STRING;
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        return UNSIGNED;
        break;

      default:
        if (isalpha(ch)||ch=='_')
          return IDENTIFIER;
        else if (isSpaceChar(ch))
          return EMPTY;
        else
          return INVALID;
      }
  }


  ///
  /// \brief Token_New::toString string representation of an operator or keyword Token_New::Value
  /// \param identifier the category of token
  /// \return string representation of the keyword or operator token
  ///  \return empty string otherwise (number, identifier, string,path)
  ///
  std::string Token_New::toString(Token_New::Value identifier)
  {
    switch (identifier) {
      case EMPTY:
      case IDENTIFIER:
      case STRING:
      case INTEGER:
      case UNSIGNED:
      case REAL:
      case INVALID:
        return{};
      case EOL: return "\n";
      case PLUS: return "+";
      case MINUS: return "-";
      case MUL:   return "*";
      case DIV:   return "/";
      case EXPONENT:   return "^";
      case DOT:   return ".";
      case COLON:   return ":";
      case COMMA:   return ",";
      case SEMICOLON:   return ";";
      case ASSIGN:   return  "=";
      case LP:   return "(" ;
      case RP:   return  ")";
      case LSB:   return  "[";
      case RSB:   return  "]";
      case LCB: return "{";
      case RCB: return "}";
      case NOT:   return  "~";
      case AND:   return  "&";
      case OR:   return  "|";
      case LSS:   return  "<";
      case GTR:   return  ">";
      case HASH:   return "#";
      case DCOLON:  return  "::";
      case LEQ:   return  "<=";
      case EQ:   return  "==";
      case NEQ:   return  "~=";
      case GEQ:   return  ">=";

      case WHILE:   return  "while ";
      case DO:   return  "do ";
      case IF:   return  "if ";
      case THEN:   return  "then ";
      case BEGIN:   return  "begin ";
      case END:   return  "end ";
      case ELSE:   return  "else ";
      case SWITCH:   return "switch ";
      case CASE:    return "case ";
      }



  }

  char Token_New::popLastChar()
  {
    if (str_.empty())
      return {};
    char r=str_.back();
    str_.pop_back();
    curr_tok=toKeyword(str_);
    if (curr_tok==EMPTY)
      myState_=S_Init;
    else if (!canBePartial(curr_tok))
      myState_=S_Final;
    else
      myState_=S_Partial;
    return r;
  }
  bool Token_New::CharIsSuccesfullyFeed(char ch)
  {
    if (myState_==S_Final)
      return false;
    else if (myState_==S_Init)
      {
        curr_tok=toToken(ch);
        if (curr_tok==INVALID)
          {
            return false;
          }
        else
          {
            str_.push_back(ch);
            if (oneCharIsEnough(curr_tok))
              myState_=S_Final;
            else
              myState_=S_Partial;
            return true;
          }
      }
    else if (!canBePartial(curr_tok))
      {
        myState_=S_Final;  // there is a logical error if we ever get here, since
        // myState could not be S_Partial to begin with
        return false;
      }
    else
      switch (curr_tok) {
        case COLON:
          if (ch==':')
            {
              curr_tok=DCOLON;
              str_.push_back(ch);
              myState_=S_Final;
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }
        case ASSIGN:
          if (ch=='=')
            {
              curr_tok=EQ;
              str_.push_back(ch);
              myState_=S_Final;
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }
        case NOT:
          if (ch=='=')
            {
              curr_tok=NEQ;
              str_.push_back(ch);
              myState_=S_Final;

              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }

        case LSS:
          if (ch=='=')
            {
              curr_tok=LEQ;
              str_.push_back(ch);
              myState_=S_Final;
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }

        case GTR:
          if (ch=='=')
            {
              curr_tok=GEQ;
              str_.push_back(ch);
              myState_=S_Final;
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }
        case DOT:
          if (ch=='.')
            {
              curr_tok=STRING;
              str_.push_back(ch);
              myState_=S_Final;
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }
        case MINUS:
          if (isdigit(ch))
            {
              curr_tok=INTEGER;
              str_.push_back(ch);
              myState_=S_Partial;  // it is already S_Partial, just for clarity
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }
        case UNSIGNED:
          if (isdigit(ch))
            {
              str_.push_back(ch);
              myState_=S_Partial;
              return true;
            }
          else if ((ch=='.')||(ch=='e')||(ch=='E'))
            {
              str_.push_back(ch);
              curr_tok=REAL;
              myState_=S_Partial;
              return true;
            }
          else
            {
              try {
                size_=std::stoul(str_);
              } catch (...) {
                curr_tok=INVALID;
              }
              myState_=S_Final;
              return false;
            }
        case REAL:
          if (isdigit(ch)||ch=='E'||ch=='e'||ch=='.'
              ||(((ch=='+')||(ch=='-'))&&((str_.back()=='e')||(str_.back()=='E'))))
            {
              str_.push_back(ch);
              myState_=S_Partial;
              return true;
            }
          else
            {
              try {
                number_=std::stod(str_);
              } catch (...) {
                curr_tok=INVALID;
              }
              myState_=S_Final;
              return false;
            }
        case INTEGER:
          if (isdigit(ch))
            {
              str_.push_back(ch);
              myState_=S_Partial;
              return true;
            }
          else if ((ch=='.')||(ch=='e')||(ch=='E'))
            {
              curr_tok=REAL;
              str_.push_back(ch);
              myState_=S_Partial;
              return true;
            }
          else
            {
              try {
                int_=std::stoi(str_);
              } catch (...) {
                curr_tok=INVALID;
              }
              myState_=S_Final;
              return false;
            }
        case STRING:
          if ((str_.size()==1)||(str_.back()!='"'))
            {
              str_.push_back(ch);
              myState_=S_Partial;
              return true;
            }
          else
            {
              myState_=S_Final;
              return false;
            }
        case IDENTIFIER:
          if (isNameChar(ch))
            {
              str_.push_back(ch);
              myState_=S_Partial;
              return true;
            }
          else
            {
              myState_=S_Final;
              if (isSpaceChar(ch))
                {
                  str_.push_back(ch);
                  return true;
                }
              else
                return false;
            }
        case INVALID:
          {
            myState_=S_Partial;
            return false;
          }
        }

  }



  Token_New::Token_New():
    curr_tok(EMPTY),
    myState_(S_Init),
    number_(),
    int_(),
    size_(),
    str_(){}

  Token_New::Token_New(double d):
    curr_tok{REAL},
    myState_(S_Final),
    number_(d),
    int_{},
    size_{},
    str_{std::to_string(d)}{}

  Token_New::Token_New(int n):
    curr_tok{INTEGER},
    myState_(S_Final),
    number_{},
    int_{n},
    size_{},
    str_{std::to_string(n)}{}

  Token_New::Token_New(std::size_t s):
    curr_tok{UNSIGNED},
    myState_(S_Final),
    number_{},
    int_{},
    size_{s},
    str_{std::to_string(s)}{}

  Token_New::Token_New(const std::string& d):
    curr_tok{},
    myState_(S_Final),
    number_{},
    str_{}{
    std::stringstream ss(d);
    get(ss);
  }

  Token_New::Token_New(Token_New::Value v):
    curr_tok{v},
    myState_(S_Final),
    number_{},
    int_{},
    size_{},
    str_{toString(v)}{ }

  Token_New::Token_New(char ch):
    curr_tok(toToken(ch)),
    myState_(S_Final),
    number_(),
    int_(),
    size_(),
    str_()
  {
    if (curr_tok!=STRING&&curr_tok!=EMPTY)
      str_.push_back(ch);
  }

  void Token_New::clear()
  {
    curr_tok=EMPTY;
    myState_=S_Init;
    number_={};
    int_={};
    size_={};
    str_={};
  }



  bool Token_New::pushChar(char c)
  {

  }


}
