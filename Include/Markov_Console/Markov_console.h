
#ifndef MARKOV_CONSOLE_H_INCLUDED
#define MARKOV_CONSOLE_H_INCLUDED


#include "Markov_CommandManager.h"
#include "Markov_IO/ABC_IO.h"
#include <iostream>
#include <string>


namespace Markov_Console
{

/**
    @brief Display a console wich execute the commands entered
    in stdin

  */
class Markov_Console :public Markov_IO::ABC_IO
{
protected:
    Markov_CommandManager* cm;

public:
    Markov_Console(Markov_CommandManager* c,const std::string& fileCommandName="");

      /// put a string to the output source
    virtual void put(const std::string& s)const;

    void putError(const std::string &s)const;

    virtual std::string getItemFromList(const std::string &title,
                                        const std::vector<std::string> &list,
                                        bool &ok,
                                        std::size_t pos) ;


    Markov_IO::Key getKey();

    virtual void move_cursor(int n);

    virtual void erase_from_cursor(int n);

    virtual void showMessage(const std::string &m);


    int exec();
    int exec(const std::string fileCommandName);

};

}
#endif // MARKOV_CONSOLE_H_INCLUDED



