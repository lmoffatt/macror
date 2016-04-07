#include "Markov_GUI/MacrorMainWindow.h"
#include "Markov_Console/Markov_CommandManagerTest.h"

#include <QApplication>
#include <qdebug.h>

#include "Markov_IO/ABFFile.h"
#include "Markov_IO/PulsesProgram.h"
#include "Markov_IO/ABC_Var.h"
#include "Markov_IO/Var.h"


//TODO: reduce the number of classes and separate semantics (analyse meaning of data) from algorithms (perform calculations)

int main(int argc, char **argv)
{
//  Markov_IO_New_Test::test();


 QApplication app(argc, argv);
   Markov_IO_New::Markov_CommandManagerVar* cm=new Markov_IO_New::Markov_CommandManagerVar();

   Markov_IO_New::MacrorMainWindow mainWin(0,cm);
   mainWin.resize(800, 608);
    mainWin.show();
    return app.exec();
}



/*int main()
{
  Markov_IO::Environment e;
  Markov_IO::Base_Unit* u=new Markov_IO::Base_Unit("ms","milisecond",&e,"time","scale of time");
  std::cout<<u->ToString();
  Markov_IO::Base_Unit* u2=new Markov_IO::Base_Unit("","",&e,"","");
  std::size_t n=0;
  u2->ToObject(u->ToString(),n);
  std::cout<<u2->ToString();


  e.addUnit(u);
  Markov_IO::SimpleVariable<std::size_t> c("milisecond_number",10.0,"ms",&e,"delay","time to reach maximum");
  Markov_IO::SimpleVariable<std::size_t> c2("",0,"",&e,"","");
  n=0;
  c2.ToObject(c.ToString(),n);

  std::cout<<c.ToString();
  std::cout<<c2.ToString();



  Markov_IO::SimpleVariable<double> d("milisecond_number_real",0.0,"ms",&e,"delay","time to reach maximum");
  Markov_IO::SimpleVariable<double> d2("",0.0,"",&e,"","");
  n=0;
  c2.ToObject(d.ToString(),n);

  std::cout<<d.ToString();
  std::cout<<c2.ToString();
  std::cout<<c.defaultSample()->ToString();

  Markov_IO::SimpleVariableValue<double> dd("milisecond_number_real",9.345,"ms",&e,"","","");
  Markov_IO::SimpleVariableValue<double> d3("milisecond_number_real",9.345,"ms",&e,"","","");

  Markov_IO::Complex_Variable m(&e,"model","un modelo1","la puta digo");
  m.push_back("Q",&d);
  m.push_back("g",&d);


  std::cout<<m.ToString();
  std::cout<<m.defaultSample()->ToString();




  std::cout<<dd.ToString();
}
*/
