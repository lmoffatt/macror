#ifndef TOKEN_NEW
#define TOKEN_NEW


#include "Markov_LA/Matrix.h"


#include <string>
#include <istream>
#include <deque>
#include <sstream>
#include <set>


namespace Markov_IO {

  ///
  /// \brief The Token_New class
  ///  This class describe a token element of macror. It could be a number, a string, an identifier or an operator

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
    enum  Value: char {
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
    bool toValue(T& val)const;

    bool isReal()const;
    bool isInteger()const;
    bool isCount()const;



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
      S_Init, S_Partial, S_Final
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

    bool isValid()const
    {
      return curr_tok!=INVALID;
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
  bool Token_New::toValue(double& val)const
  {
    if (!isReal())
      return false;
    else
      {
        val=realValue();
        return true;
      }
  }

  template<>
  inline
  bool Token_New::toValue(std::size_t& val)const
  {
    if (!isCount())
      return false;
    else
      {
        val=count();
        return true;
      }
  }

  template<>
  inline
  bool Token_New::toValue(int& val)const
  {
    if (!isInteger())
      return false;
    else
      {
        val=intval();
        return true;
      }
  }

  template<>
  inline
  bool Token_New::toValue(std::string& val)const
  {
    if (!isValid())
      return false;
    if (this->tok()==IDENTIFIER)
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


  class ABC_Value;









  class streamLike
  {
  public:
    virtual bool good()const
    {
      return !bad() && ! eof();
    }
    virtual bool eof()const=0;
    virtual bool bad()const=0;
    virtual void clear()=0;
    virtual ~streamLike(){}
  };


  class Token_Stream: public streamLike
  {
  public:
    Token_Stream(std::istream *s):
      t_{},
      posParserTok_(0),
      s_(s)
    {}



    Token_Stream():
      t_{},posParserTok_(0),s_(nullptr){}



    Token_Stream(const std::deque<Token_New>& t):
      t_{t},posParserTok_(0),s_(nullptr){}


    virtual ~Token_Stream(){}


    std::deque<Token_New>const & getToken()const
    {
      return t_;
    }


    std::deque<Token_New>& getToken()
    {
      return t_;
    }


    void feedChar(char ch)
    {
      if (!t_.back().CharIsSuccesfullyFeed(ch))
        t_.push_back(Token_New(ch));

    }

    std::size_t pos()const
    {
      return posParserTok_;
    }

    void setPos(std::size_t p)
    {
      posParserTok_=p;
    }

    //    void setPosEnd()
    //    {
    //      if (!t_.empty())
    //        posParserTok_=t_.size()-1;
    //      else posParserTok_=0;
    //    }
    //    void setPosHome()
    //    {
    //      setPos(0);
    //    }


    Token_New& currToken()
    {
      return t_.at(posParserTok_);

    }

    Token_New const & currToken()const

    {
      return t_.at(posParserTok_);
    }

    Token_New const & nextToken(int i)const
    {
      return t_.at(posParserTok_+i);
    }

    Token_Stream& operator ++()
    {

      posParserTok_++;
      return *this;
    }

    Token_Stream& advance(int i)
    {
      posParserTok_+=i;
      return *this;
    }

    std::size_t size()const
    {
      return t_.size();
    }

    bool empty()const
    {
      return t_.empty();
    }
    ///
    /// \brief tokenAdvance
    /// \param  t [in, out]buffer of tokens
    /// \param pos [in] position of the current token in the buffer
    /// \param s  [in, out] if not nullptr, it points to a stream to read new tokens
    /// \param n  [in] desired number of tokens from position
    ///
    /// \retval true if there are at least the desired number of tokens begining at the indicated position
    /// \retval false if it failed to complete the buffer up to the desired number of tokens
    /// \post    if successful the buffer will contain at least n more tokens starting from the position

    inline bool tokenAdvance(std::size_t n)
    {
      if (s_!=nullptr)
        {
          Token_New to;
          while (posParserTok_+n>t_.size())
            {
              if (to.get(*s_))
                t_.push_back(to);
              else
                return false;
            }
          return true;
        }
      else
        return posParserTok_+n<=t_.size();
    }

    inline void advanceEmptyLines()
    {
      while ((posParserTok_<t_.size())&&(t_.at(posParserTok_).tok()==Token_New::EOL))
        ++posParserTok_;
    }

    template<typename T>
    static Token_Stream toToken(const T& val)
    {
      Token_Stream out;
      out<<val;
      return out;
    }


    bool toTip(std::string&  tip)
    {
      tokenAdvance(2);
      if (!(posParserTok_<t_.size()))
        return false;
      else if(t_.at(posParserTok_).tok()!=Token_New::HASH)
        return false;
      else if (!(posParserTok_+1<t_.size()))
        return false;
      else if ((t_.at(posParserTok_+1).tok()==Token_New::STRING)) // tip is present
        {
          ++posParserTok_;
          tip=t_.at(posParserTok_).str();
          ++posParserTok_;
          return false;
        }
      else
        return false;
    }


    bool toWhatThis(std::string& whatthis)
    {
      tokenAdvance(3);
      if (!(posParserTok_<t_.size()))
        return false;
      else if(currToken().tok()!=Token_New::HASH)
        return false;
      else if (!(posParserTok_+1<t_.size()))
        return false;
      else if(t_.at(posParserTok_+1).tok()!=Token_New::HASH)
        return false;
      else if (!(posParserTok_+2<t_.size()))
        return false;
      else if ((t_.at(posParserTok_+2).tok()==Token_New::STRING)) // whatthis is present
        {
          posParserTok_+=2;
          whatthis=t_.at(posParserTok_).str();
          ++posParserTok_;
          return false;
        }
      else
        return false;
    }

    bool toIdClass(std::string& id, std::string& idclass)
    {
      tokenAdvance(3);
      if (!(posParserTok_<t_.size()))
        return false;
      else if(currToken().tok()!=Token_New::IDENTIFIER)
        return false;
      else if (!(posParserTok_+1<t_.size()))
        return false;
      else if(t_.at(posParserTok_+1).tok()!=Token_New::COLON)
        return false;
      else if (!(posParserTok_+2<t_.size()))
        return false;
      else if(nextToken(2).tok()==Token_New::IDENTIFIER)
        {
          id=t_.at(posParserTok_).str();
          idclass=t_.at(posParserTok_+2).str();
          posParserTok_+=3;
          return true;
        }
      else
        return false;

    }


    void cleanRead()
    {
      t_.erase(t_.begin(),t_.begin()+posParserTok_);
      posParserTok_=0;
    }


    std::string putTokenBuffer() const
    {
      std::string out;
      for (std::size_t i=0; i<std::min(posParserTok_,t_.size()); i++)
        out+=t_.at(i).toString();
      return out;
    }
    //    bool feedChar(char ch);



  private:

    std::deque<Token_New> t_;
    std::size_t posParserTok_;
    std::istream *s_;

    // streamLike interface
  public:
    virtual bool eof() const
    {
      if (s_==nullptr)
        return !(posParserTok_<t_.size());
      else
        return !(posParserTok_<t_.size())&&(s_->eof());
    }
    virtual bool bad() const
    {
      return (s_!=nullptr)&&(s_->bad());
    }
    virtual void clear(){
      if (s_!=nullptr)
        s_->clear();
    }
  };





  inline std::deque<Token_New>&operator<<(std::deque<Token_New>&t,const std::string &text)
  {
    std::stringstream ss(text);
    Token_New to;
    while (to.get(ss))
      {
        t.push_back(to);
      }

    return t;
  }


  inline std::deque<Token_New>&operator<<(std::deque<Token_New>&t,const char* text)
  {
    std::stringstream ss(text);
    Token_New to;
    while (to.get(ss))
      {
        t.push_back(to);
      }

    return t;
  }



  inline std::deque<Token_New>& operator<<(std::deque<Token_New>&t,const Token_Stream &tok2)
  {
    t.insert(t.end(),tok2.getToken().begin(),tok2.getToken().end());
    return t;
  }



  inline std::deque<Token_New>&operator<<(std::deque<Token_New>&t,double d)
  {
    t.push_back(Token_New(d));
    return t;
  }

  inline std::deque<Token_New>&operator<<(std::deque<Token_New>&t,int d)
  {
    t.push_back(Token_New(d));
    return t;
  }

  inline std::deque<Token_New>&operator<<(std::deque<Token_New>&t,std::size_t s)
  {
    t.push_back(Token_New(s));
    return t;
  }

  template<typename T>
  std::deque<Token_New>&operator<<(std::deque<Token_New>&t,std::vector<T> v)
  {
    t<<"\n [ ";
    for (const T& e:v)
      t<<e;
    t<<" ] "<<"\n";
    return t;
  }

  template<typename T>
  std::deque<Token_New>&operator<<(std::deque<Token_New>&t,Markov_LA::M_Matrix<T> m)
  {
    t<<"\n";
    for (std::size_t i=0; i<Markov_LA::nrows(m); ++i)
      {
        for(std::size_t j=0; j<Markov_LA::ncols(m); ++j)
          {
            t<<m(i,j);
          }
        t<<"\n";
      }
    return t;
  }


  template<typename K,typename T>
  std::deque<Token_New>&operator<<(std::deque<Token_New>&t,std::pair<K,T> e)
  {
    t<<e.first<<":"<<e.second;
    return t;
  }

  template<typename K,typename T>
  std::deque<Token_New>&operator<<(std::deque<Token_New>&t, std::map<K,T> m)
  {
    t<<"\n { ";
    for (auto& e:m)
      t<<e;
    t<<" } "<<"\n";
    return t;
  }

  template<typename T>
  std::deque<Token_New>&operator<<(std::deque<Token_New>&t, std::set<T> m)
  {
    t<<"\n { ";
    for (auto& e:m)
      t<<e;
    t<<" } "<<"\n";
    return t;
  }



  inline bool toValue(Token_Stream& t,double &val)
  {
    t.tokenAdvance(1);
    if (!(t.pos()<t.size())) return false;
    Token_New to=t.currToken();
    if (!to.isReal())
      return false;
    else
      {
        val=to.realValue();
        ++t;
        return true;
      }
  }

  inline bool toValue(Token_Stream& t,int &val)
  {
    t.tokenAdvance(1);
    if (!(t.pos()<t.size())) return false;
    Token_New to=t.currToken();
    if (!to.isInteger())
      return false;
    else
      {
        val=to.intval();
        ++t;
        return true;
      }
  }

  inline bool toValue(Token_Stream& t,std::size_t &val)
  {
    t.tokenAdvance(1);
    if (!(t.pos()<t.size())) return false;
    Token_New to=t.currToken();
    if (to.isCount())
      {
        val=to.count();
        ++t;
        return true;
      }
    else
      return false;
  }

  inline bool toValue(Token_Stream& to,std::string &val)
  {
    to.tokenAdvance(2);
    if (!(to.pos()<to.size())) return false;
    if (to.currToken().tok()!=Token_New::IDENTIFIER)
      return false;
    else
      {
        val=to.currToken().str();
        ++to;
        return true;
      }
  }


  inline bool toValue(Token_Stream& t,bool &val)
  {
    t.tokenAdvance(1);
    if (!(t.pos()<t.size())) return false;
    if (t.currToken().tok()==Token_New::IDENTIFIER)
      {
        std::string s=t.currToken().str();
        if ((s=="false")||(s=="false"))
          {
            val=false;
            ++t;
            return true;
          }
        else if ((s=="true")||(s=="TRUE"))
          {
            val=true;
            ++t;
            return true;
          }
        else return false;
      }
    else if (t.currToken().isCount())
      {
        if (t.currToken().count()==0)
          {
            val=false;
            ++t;
            return true;
          }
        else if(t.currToken().count()==1)
          {
            val=true;
            ++t;
            return true;
          }
        else
          return false;
      }
    else
      return false;
  }


  template<typename T>
  bool toValue(Token_Stream& t, std::vector<T> &vec)
  {
    // checks the initial squarebracket
    t.tokenAdvance(3);
    if ((!(t.pos()+1<t.size()))||
        (t.currToken().tok()!=Token_New::EOL)||
        (t.nextToken(1).tok()!=Token_New::LSB))
      return false;
    t.advance(2);
    T val;
    if (!toValue(t,val))
      return false;
    else
      {
        vec.push_back(val);
        while (toValue(t,val))
          {
            vec.push_back(val);
          }
        t.tokenAdvance(1);
        if ((!(t.pos()<t.size()))||(t.currToken().tok()!=Token_New::RSB))
          return false;
        ++t;
        return true;
      }
  }


  template<typename T>
  bool toValue(Token_Stream& t, std::set<T> &myset)
  {
    // checks the initial squarebracket
    t.tokenAdvance(3);
    if ((!(t.pos()+1<t.size()))||
        (t.currToken().tok()!=Token_New::EOL)||
        (t.nextToken(1).tok()!=Token_New::LCB))
      return false;
    t.advance(2);
    T val;
    if (!toValue(t,val))
      return false;
    else
      {
        myset.insert(val);
        while (toValue(t,val))
          {
            myset.insert(val);
          }
        t.tokenAdvance(1);
        if ((!(t.pos()<t.size()))||(t.currToken().tok()!=Token_New::RCB))
          return false;
        ++t;
        return true;
      }
  }











  template<typename T>
  inline bool toValue(Token_Stream& t, Markov_LA::M_Matrix<T> &m)
  {
    t.tokenAdvance(2);
    if ((!(t.pos()<t.size()))||
        (t.currToken().tok()!=Token_New::EOL))
      return false;
    ++t;
    std::vector<T> v;
    T val;
    if (Markov_LA::size(m)==0)// we have to determine the size ourselves
      {
        std::size_t ncols=0;
        std::size_t icol=0;
        std::size_t irow=0;
        while (toValue(t,val))
          {
            ++irow;
            ++icol;
            v.push_back(val);
            while (toValue(t,val)) // advances only on success
              {
                icol++;
                v.push_back(val);
              }
            // we consider as candidates all the things until there is and end of line
            if (ncols==0)
              ncols=icol;
            else if (ncols!=icol)
              return false;
            icol=0;
            ++t;
          }
        m=Markov_LA::M_Matrix<T>(irow,ncols,v);
        return true;
        // lets see if there are more things
      }
    else
      {
        for (std::size_t ii=0; ii<Markov_LA::nrows(m); ++ii)
          {
            for (std::size_t j=0; j<Markov_LA::ncols(m); ++j)
              {
                if (toValue(t,val))
                  m(ii,j)=val;
                else
                  return false;
              }
            if ((t.pos()>=t.size())||(t.currToken().tok()!=Token_New::EOL))
              return false;
            else
              ++t;
          }
        return true;
      }
  }


  template<typename K,typename T>
  inline bool toValue(Token_Stream& to, std::pair<K,T>& p)
  {
    to.tokenAdvance(4);
    if (!(to.pos()+2<to.size()))
      return false;
    auto pos0=to.pos();

    K k;
    T t;
    if (to.nextToken(1).tok()!=Token_New::COLON)
      return false;
    if (!toValue(to,k))
      return false;
    ++to;
    if (!toValue(to,t))
      {
        to.setPos(pos0);
        return false;
      }
    else
      {
        p.first=k;
        p.second=t;
        return true;
      }
  }





  template<typename K,typename T>
  inline bool toValue(Token_Stream& to, std::map<K,T> &map)
  {
    to.tokenAdvance(4);
    // checks the initial squarebracket
    if ((!(to.pos()+1<to.size()))||
        (to.currToken().tok()!=Token_New::EOL)||
        (to.nextToken(1).tok()!=Token_New::LCB))
      return false;
    to.advance(2);
    std::pair<K,T> val;
    if (!toValue(to,val))
      return false;
    else
      {
        map.insert(val);
        while (toValue(to,val))
          {
            map.insert(val);
          }
        if ((!(to.pos()<to.size()))||(to.currToken().tok()!=Token_New::RCB))
          return false;
        ++to;
        return true;
      }
  }




}

#endif // TOKEN_NEW

