#include "Markov_GUI/MacrorMainWindow.h"
#include "Markov_Console/Markov_CommandManagerTest.h"

#include <QApplication>
#include <qdebug.h>

#include "Markov_IO/ABFFile.h"
#include "Markov_IO/PulsesProgram.h"

int main(int argc, char **argv)
{
 //Markov_IO::ABFFile d(
  //  "/media/OS/Luciano/datos/FASTA/Protocols/Single Pulses II/01-24/C1 n ATP/2004_01_24_C1_0000.abf");

//Markov_IO::ABFFile d2(
 //    "/media/OS/Luciano/datos/FFIRCA 08/2008-07-26/K308R_T339S/A1/2008_07_26_K308R_T339S_A1_0022.abf");

  /*
  Markov_LA::M_Matrix<double> t_x("0 2e-3");
  Markov_LA::M_Matrix<double> x("0 1");


  Markov_IO::Pulses_trace trace("n",t_x,x,40e-3,500,0,1e-6,1);

  std::cout<<trace;

  Markov_IO::Pulses_program p("n",std::vector<Markov_IO::Pulses_trace>(1,trace),
                              Markov_LA::M_Matrix<std::size_t>("0"),
                              Markov_LA::M_Matrix<double>("1")
                              );

  std::cout<<p;
*/
QApplication app(argc, argv);
   Markov_Console::Markov_CommandManagerTest* cm=new Markov_Console::Markov_CommandManagerTest();
   MacrorMainWindow mainWin(0,cm);
   mainWin.resize(800, 608);
    mainWin.show();
    return app.exec();
}

