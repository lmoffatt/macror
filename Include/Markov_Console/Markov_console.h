
#ifndef MARKOV_CONSOLE_H_INCLUDED
#define MARKOV_CONSOLE_H_INCLUDED


#include "Markov_CommandManager.h"
#include "Markov_IO/ABC_IO.h"
#include <iostream>
#include <string>


namespace Markov_Console_New
{

/**
    @brief Display a console wich execute the commands entered
    in stdin

  */
class Markov_Console :public Markov_IO_New::ABC_IO
{
protected:
    Markov_IO_New::Markov_CommandManagerVar* cm;
    std::string currentLine_;


public:
    Markov_Console(Markov_IO_New::Markov_CommandManagerVar* c);

      /// put a string to the output source
    virtual void put(const std::string& s) override;

    virtual void putNewLine() override;

    void freshLine()override;

    virtual void hideMessage()override;

    virtual bool isLineBegin()const override;

    virtual bool isLineEnd()const override;
    virtual std::string currentLine()const override;
    virtual char pop_next_char()override;

    virtual void erase_from_cursor_forward(std::string s) override;
    virtual void erase_from_cursor_backward(std::string s)override;



    virtual char backErase()override;

    virtual void move_end()override;
    virtual void move_home()override;

    virtual void cleanToEndLine()override;


    virtual void putTail(const std::string& text)override;


    virtual std::string getTail()override;

    virtual std::string spacer()const override;


    void putError(const std::string &s) override;

    virtual std::string getItemFromList(const std::string &title,
                                        const std::vector<std::string> &list,
                                        bool &ok,
                                        std::size_t pos) override ;


    virtual std::string
    getItemFromSeveralLists(const std::string& title,
                            const std::map<std::string,std::vector<std::string> >& list,
                            bool &ok,
                            std::size_t current) override;



    Markov_IO_New::Key getKey();

    virtual std::string move_cursor(int n) override;

    virtual void erase_from_cursor_forward(int n);

    virtual void showMessage(const std::string &m) override;


    int exec();
    int exec(const std::string fileCommandName);


  };

}
#endif // MARKOV_CONSOLE_H_INCLUDED



