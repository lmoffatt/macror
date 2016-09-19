#ifndef TOKEN_NEW
#define TOKEN_NEW

#include <string>
#include <set>
#include <map>
#include <vector>

namespace Markov_IO_New {



  class Token_New
  {
  public:
    ///
    /// \brief isNameChar check if a char is allowed on identifiers
    /// \param ch inspected char
    /// \return true if is a char allowed in identifiers
    ///
    static bool isNameChar(char ch);
    static bool isSpaceChar(char ch);
    static bool isRealNumberChar(char ch);

    static std::string toString(double number);
    static std::string toString(int number);
    static std::string toString(std::size_t number);
    enum  Value {
      EMPTY,
      ANY,
      IDENTIFIER,
      STRING,
      INTEGER,
      UNSIGNED,
      REAL,
      INVALID,

      EOL='\n',
      HASH='#',
      PLUS='+',
      MINUS='-',
      MUL='*',
      DIV='/',
      EXPONENT='^',

      DOT='.',
      COLON=':',
      COMMA=',',
      SEMICOLON=';',
      ASSIGN='=',

      LP='(',
      RP=')',
      LSB='[',
      RSB=']',
      LCB='{',
      RCB='}',
      NOT='~',
      AND='&',
      OR='|',
      LSS='<',
      GTR='>',

      DCOLON,//::
      LEQ,// <=
      EQ, //==
      NEQ, //~=
      GEQ, // >=

      WHILE, //while
      DO,  //do
      IF, //if
      THEN, // then
      BEGIN, //begin
      END, // end
      ELSE, // else
      SWITCH, //switch
      CASE   // case
    };




    static bool oneCharIsEnough(Value v);

    std::istream& get(std::istream& stream);
    std::string str()const;

    std::string identifier()const;
    static std::string identifier(const std::string idWithSPace);

    double realValue()const;
    int  intval()const;

    std::size_t count()const;

    Value tok()const;

    std::string toString()const;

    template<typename T>
    bool toValue(T& val, std::string *whyNot, const std::string& masterObjective)const;

    bool isReal(std::string *whyNot, const std::string &masterObjective)const;
    bool isInteger(std::string *whyNot, const std::string& masterObjective)const;
    bool isCount(std::string *whyNot, const std::string& masterObjective)const;



    ///
    /// \brief toKeyword convert a string to the corresponding token value, a keyword, an identifier or a string
    /// \param identifier a string to be checked
    /// \return the identified keyword or the value IDENTIFIER
    ///
    static Value toKeyword(std::string identifier);
    static Value toToken(char ch);

    static std::string toString(Value identifier);




    Token_New();

    explicit Token_New(double d);

    explicit Token_New(int n);

    explicit Token_New(std::size_t s);

    Token_New(const std::string &d);

    static Token_New toToken(const std::string &d, std::size_t& pos)
    {
      pos=0;
      Token_New t;
      while ((pos<d.size()) && t.CharIsSuccesfullyFeed(d[pos])) ++pos;
      return t;
    }

    Token_New(Value v);

    explicit Token_New(char ch);

    friend class Token_Stream;

    enum DAF{
      S_Init, S_Partial, S_Final, S_PostFinal
    };


    void clear();

    bool pushChar(char c);

    char popLastChar();


    bool CharIsSuccesfullyFeed(char ch);



    bool isFinal()const
    {
      return myState_==S_Final;
    }
    bool isInitial()const
    {
      return myState_==S_Init;
    }

    bool isValid(std::string *whyNot,const std::string &masterObjective)const
    {
      const std::string objective="Token "+str()+ " is not valid";
      if (curr_tok==INVALID)
        {
          *whyNot=masterObjective+": "+objective;
          return false;
        }
      else
        return true;
    }

    static bool canBePartial(Value v);
  private:
    Value curr_tok;
    DAF myState_;
    double number_;
    int int_;
    std::size_t size_;
    std::string str_;

  };



  template<>
  inline
  bool Token_New::toValue(double& val, std::string *whyNot, const std::string& masterObjective)const
  {
    if (!isReal(whyNot,masterObjective))
      return false;
    else
      {
        val=realValue();
        return true;
      }
  }

  template<>
  inline
  bool Token_New::toValue(
      std::size_t& val, std::string *whyNot,const std::string &masterObjective)const
  {
    if (!isCount(whyNot,masterObjective))
      return false;
    else
      {
        val=count();
        return true;
      }
  }

  template<>
  inline
  bool Token_New::toValue(int& val, std::string *whyNot,const std::string &masterObjective)const
  {
    if (!isInteger(whyNot,masterObjective))
      return false;
    else
      {
        val=intval();
        return true;
      }
  }

  template<>
  inline
  bool Token_New::toValue(std::string& val, std::string *whyNot,const std::string &masterObjective)const
  {
    if (!isValid(whyNot,masterObjective))
      return false;
    if (tok()==IDENTIFIER)
      {
        val=identifier();
        return true;
      }
    else
      {
        val=str();
        return true;
      }
  }


}








#endif // TOKEN_NEW

