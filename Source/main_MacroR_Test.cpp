#include "Markov_GUI/MacrorMainWindow.h"
#include "Markov_Console/Markov_CommandManagerTest.h"

#include <QApplication>
#include <qdebug.h>

#include "Markov_IO/ABFFile.h"
#include "Markov_IO/PulsesProgram.h"

#include "Markov_Object/Abstract_Object.h"
#include "Markov_Object/Environment.h"
#include "Markov_Object/Measurement_Unit.h"
#include "Markov_Object/SimpleVariableValue.h"

#include "Markov_Object/SimpleVariable.h"
#include "Markov_Object/Quantity.h"


/*
int main(int argc, char **argv)
{
 QApplication app(argc, argv);
   Markov_Console::Markov_CommandManagerTest* cm=new Markov_Console::Markov_CommandManagerTest();
   MacrorMainWindow mainWin(0,cm);
   mainWin.resize(800, 608);
    mainWin.show();
    return app.exec();
}

*/

int main()
{
  Markov_Object::Environment e;
 /*
  Markov_Object::QuantityExpression qe({{"L",1},{"M",-2}});
  Markov_Object::QuantityExpression qe2({{"L",-1},{"MN",2}});
  std::cout<<qe.ToString();std::cout<<q.ToString();
  Markov_Test::Markov_Object_Test::QuantityExpression_Test test1({&qe,&qe2});
  std::cout<<test1.classInvariant().VerboseLevel(false);

*/

  using Markov_Object::Quantity;
  Quantity* L=new Quantity(&e,"L","L","longitude","dimension of distance and length");
  Quantity* T=new Quantity(&e,"T","T","time","dimension of time");
  Quantity* M=new Quantity(&e,"M","M","mass","dimension of mass");
  Quantity* V=new Quantity(&e,"VELOCITY","L*T^-1","velocity","derivative of space over time");
  Quantity* A=new Quantity(&e,"ASCELERATION","VELOCITY*T^-1","asceleration","second derivative of space over time");
  Quantity* F=new Quantity(&e,"FORCE","M*ASCELERATION","asceleration","second derivative of space over time");


  e.add(L);  e.add(T);  e.add(V); e.add(A); e.add(F); e.add(M);

  Markov_Test::Markov_Object_Test::Quantity_Test test({L,T,V,A,F,M});
  std::cout<<test.classInvariant().VerboseLevel(true);
  std::cout<<test.classInvariant().VerboseLevel(false);

  /*Markov_Object::Measurement_Unit* u=new Markov_Object::Measurement_Unit("ms","milisecond",&e,"time","scale of time");
  std::cout<<u->ToString();
  Markov_Object::Measurement_Unit* u2=new Markov_Object::Measurement_Unit(&e);
  std::size_t n=0;
  u2->ToObject(&e,u->ToString(),n);
  std::cout<<u2->ToString();


  e.addUnit(u);

  Markov_Object::SimpleVariable<std::size_t> c("milisecond_number",10.0,"ms",&e,"delay","time to reach maximum");
  Markov_Object::SimpleVariable<std::size_t>*c2=new Markov_Object::SimpleVariable<std::size_t>(&e);
  n=0;
  c2->ToObject(&e,c.ToString(),n);

  std::cout<<c.ToString();
  std::cout<<c2->ToString();
  std::cout<<c2->myUnit()->ToString();



  Markov_Object::SimpleVariable<double> *d=
      new Markov_Object::SimpleVariable<double> ("milisecond_number_real",0.0,"ms",&e,
                                                 "delay","time to reach maximum");
  e.add(d);
  Markov_Object::SimpleVariable<double> * d2= new Markov_Object::SimpleVariable<double>;
  n=0;
  c2->ToObject(&e,d->ToString(),n);

  std::cout<<c2->ToString();
  std::cout<<c.defaultValue()->ToString();

  std::cout<<c.unKnownValue()->ToString();


  Markov_Object::SimpleVariableValue<double> dd("milisecond_number_real",9.345,"ms",&e);
  Markov_Object::SimpleVariableValue<double> d3("milisecond_number_real",9.345,"ms",&e);

  std::cout << dd.ToString();
  std::cout << "context \n"<<dd.contextToString();



  Markov_Test::Markov_Object_Test::Abstract_Value_Test test(&dd);
  std::cout<<test.classInvariant().VerboseLevel(false);


  Markov_Test::Markov_Object_Test::Abstract_Named_Object_Test test2(d);

  std::cout<<test2.classInvariant().VerboseLevel(false);

  auto cp=&c;

  Markov_Test::Markov_Object_Test::Abstract_Named_Object_Test test3(cp);
  std::cout<<test3.classInvariant().VerboseLevel(false);

  Markov_Test::Markov_Object_Test::Abstract_Named_Object_Test test4(d2);
  std::cout<<test4.classInvariant().VerboseLevel(false);


  //  Markov_Object::Composite_Variable m(&e,"model","un modelo1","la puta digo");
  //  m.push_back("Q",&d);
  //  m.push_back("g",&d);


  //std::cout<<m.ToString();
  //std::cout<<m.defaultValue()->ToString();



*/
  // std::cout<<dd.ToString();
}
