#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H



namespace Markov_IO_New
{

  class Markov_CommandManagerVar;
  class ABC_Input;
  class ABC_Output;

  struct ScriptManager
   {

      bool run(Markov_CommandManagerVar* cm, ABC_Input* istream, ABC_Output *ostream, bool checkErrors);

  };
}


#endif // SCRIPTMANAGER_H
