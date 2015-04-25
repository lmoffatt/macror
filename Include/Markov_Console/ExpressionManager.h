#ifndef EXPRESSIONMANAGER
#define EXPRESSIONMANAGER


#include "Markov_Console/MacorCoreApplication.h"
#include"Markov_Console/Markov_CommandManager.h"
#include "Markov_IO/ABC_Var.h"

#include "Markov_Console/CommandHistory.h"
#include "Markov_IO/ABC_IO.h"


namespace Markov_Console {



   
   /**
   * @brief The ExpressionParser class
   * 
   *  a middleman between the maker and the view
   *  the Maker accepts tokens
   *  the view deals with chars and strings
   *  so the ExpressionParser translates chars and strings 
   *  into tokens
   *  it also ask the maker for the next category
   *  
   *  one question is how is it different from a tokenstream
   *  the stream is continuos 
   *  the idea of the ExpressionParser is that it deals with the expression
   *  of a single maker. 
   *  if that is the case, it should have a pointer to the Token_Parser
   *  
   */
   
  class ExpressionParser: public Markov_IO::Temporary
  {
  public:
    void push_back(char c)
    {
      Markov_IO::Token_New t=t_.getToken().back();
      if (!t.CharIsSuccesfullyFeed(c))
        t_.getToken().push_back(Markov_IO::Token_New(c));





    }

    void popChars(std::size_t numberToBeRemoved)
    {


    }

    Markov_IO::Token_New popLast();
    std::deque<Markov_IO::Token_New> getTokens();

    std::string getString();

    bool append(const std::string s)
    {

    }

    std::vector<std::string> complete()const
    {

    }
    bool run();
    void clear();





  private:
    void assignVar();


    std::size_t getIndexTok(std::size_t indexChar)
    {
        auto lo= iChar_to_iTok.lower_bound(indexChar);
    }
    Markov_IO::Token_Stream t_;
    Markov_IO::ABC_Var* v_;
    Markov_CommandManagerVar *cm_;
    std::map<std::size_t,std::size_t> iChar_to_iTok;

    bool valid_;
    bool complete_;
    bool executed_;
    std::size_t vpos_;

  };

  class ExpressionView: public Markov_IO::Temporary
  {
  public:
    void virtual update()=0;
    void KeyEvent(Markov_IO::Key);
    void clear();

    void setModel(ExpressionParser* m){m_=m;}
    ExpressionParser* getModel(){ return m_;}
    ExpressionParser const* getModel()const {return m_;}
    ~ExpressionView(){
      delete m_;
    }


  protected:

    void move_Left()
    {
      if (pos_>0)
        --pos_;
      update();
    }

    void backErase()
    {
      if (pos_>0)
        {
          --pos_;
          removeTail();
          update();
        }
    }

    void removeTail()
    {
      std::size_t n=s_.size()-pos_;
      s_.erase(pos_);
      m_->popChars(n);
    }

    void move_Right()
    {
      if (pos_<s_.size())
        ++pos_;
      update();
    }

    void move_Home()
    {
      pos_=0;
      update();
    }

    void history_up()
    {

      removeTail();
      std::string tail=h_->up(s_);
      s_.append(tail);
      m_->append(tail);
      update();
    }

    void history_down()
    {
      removeTail();
      std::string tail=h_->down(s_);
      s_.append(tail);
      m_->append(tail);
      update();

    }

    std::string virtual chooseFromList(const std::vector<std::string> list)const=0;

    std::string virtual chooseFromSeveralLists(
        const std::map<std::string,std::vector<std::string>> list) const=0;

    void suggestCompletion()
    {
      removeTail();
      auto comp=m_->complete();
      std::string tail=chooseFromList(comp);
      s_.append(tail);
      m_->append(tail);
      update();
    }

    bool putReturn()
    {
      removeTail();
      s_.append("\n");
      m_->append("\n");
      bool r=m_->run();
      update();
      return r;
     }

    bool putText(char c)
    {
      removeTail();
      s_.push_back(c);
      m_->push_back(c);
      update();
    }


    ExpressionParser *m_;
    CommandHistory *h_;
    Markov_IO::Key previous_key;
    std::string s_;
    std::size_t pos_;
    std::size_t lastValidPos_;
    bool complete_;
    bool executed_;
 };




  class ExpressionManager
  {
  public:

    ExpressionManager(Markov_CommandManagerVar *cm):
      b_{},p_(0),previous_key(),categories_(),cm_(cm),v_(nullptr)
    {}


    const Markov_IO::Token_New& at(std::size_t i) const
    {
      return b_.at(i);
    }



    Markov_IO::Token_Stream tokens()
    {
      return Markov_IO::Token_Stream(b_);
    }

    Markov_IO::Token_New& at(std::size_t i)
    {
      return b_[i];
    }

    virtual void KeyEvent(Markov_IO::Key k);

    void clean();



  protected:
    void move_Left();

    void backErase();


    void move_Right();
    void move_Home();

    std::string currentLine() const;

    void history_up();

    void history_down();
    void suggestCompletion();

    //bool putSpace();




    bool putReturn();


    bool putText(char s);




    friend class ABC_CommandVar;
    void getStringandCleanFromCursor();
  private:
    /// Internals
    /// b_+currWord_ p_ is a
    std::deque<Markov_IO::Token_New>  b_;
    std::string currWord_;
    std::size_t p_;  // position of cursor on the line
    Markov_IO::Key previous_key;
    std::vector<std::vector<std::pair<std::string,bool>>> categories_;
    Markov_CommandManagerVar *cm_;
    Markov_IO::ABC_Value* v_;
  public:

  };



}
#endif // EXPRESSIONMANAGER

