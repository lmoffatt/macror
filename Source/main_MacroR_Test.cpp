#include "Markov_GUI/MacrorMainWindow.h"
#include "Markov_Console/Markov_CommandManagerTest.h"

#include <QApplication>
#include <qdebug.h>

#include <memory>
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
  Markov_Object::Environment env=Markov_Object::Environment();
  Markov_Object::Environment* e=&env;

 /*
  Markov_Object::QuantityExpression qe({{"L",1},{"M",-2}});
  Markov_Object::QuantityExpression qe2({{"L",-1},{"MN",2}});
  std::cout<<qe.ToString();std::cout<<q.ToString();
  Markov_Test::Markov_Object_Test::QuantityExpression_Test test1({&qe,&qe2});
  std::cout<<test1.classInvariant().VerboseLevel(false);

*/

  using Markov_Object::Quantity;

  std::shared_ptr<Quantity> L=std::make_shared<Quantity>(e,"L","L","longitude","dimension of distance and length");
  std::shared_ptr<Quantity> T=std::make_shared<Quantity>(e,"T","T","time","dimension of time");
  std::shared_ptr<Quantity> M=std::make_shared<Quantity>(e,"M","M","mass","dimension of mass");
  std::shared_ptr<Quantity> V=std::make_shared<Quantity>(e,"VELOCITY","L*T^-1","velocity","derivative of space over time");
  std::shared_ptr<Quantity> A=std::make_shared<Quantity>(e,"ASCELERATION","VELOCITY*T^-1","asceleration","second derivative of space over time");
  std::shared_ptr<Quantity> F=std::make_shared<Quantity>(e,"FORCE","M*ASCELERATION","asceleration","second derivative of space over time");
 std::shared_ptr<Markov_Object::Measurement_Unit> kg=
     std::make_shared<Markov_Object::Measurement_Unit>
     (e,"kg",1.0,"kg","M","kilogram","standard Unit of mass");
 std::shared_ptr<Markov_Object::Measurement_Unit> second=
     std::make_shared<Markov_Object::Measurement_Unit>
     (e,"s",1.0,"s","T","second","standard Unit of time");
 std::shared_ptr<Markov_Object::Measurement_Unit> newton=
     std::make_shared< Markov_Object::Measurement_Unit >
     (e,"N",1.0,"kg*m*s^-2","FORCE","Newton","derived standard Unit of Force");
 std::shared_ptr<Markov_Object::Measurement_Unit> meter=
     std::make_shared<Markov_Object::Measurement_Unit>
     (e,"m",1.0,"m","L","meter","standard Unit of distance");




  e->add(L);  e->add(T);  e->add(V); e->add(A); e->add(F); e->add(M);
  e->addDef(L);e->addDef(T);  e->addDef(V); e->addDef(A); e->addDef(F); e->addDef(M);

  e->add(kg); e->add(meter);  e->add(second); e->add(newton);
  e->addDef(kg); e->addDef(meter);  e->addDef(second); e->addDef(newton);

  Markov_Object::ScaledExpression a(e,1.0,"pm*Ms^-1*us^-1*N^-1");
  std::cout<<a.ToString()<<"\n";

  std::cout<<kg->ToString();
 //Markov_Test::Markov_Object_Test::Quantity_Test test({L,T,V,A,F,M});
 //std::cout<<test.classInvariant().VerboseLevel(true);
// std::cout<<test.classInvariant().VerboseLevel(false);

// Markov_Test::Markov_Object_Test::Measurement_Unit_Test test2({kg,meter,second,newton});
//std::cout<<test.classInvariant().VerboseLevel(true);
//std::cout<<test2.classInvariant().VerboseLevel(false);



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
