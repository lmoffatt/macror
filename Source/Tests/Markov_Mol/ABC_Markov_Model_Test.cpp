#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixInit.h"

#include "Markov_IO/auxiliarIO.h"
#include "Markov_IO/x_dt.h"
#include "Markov_IO/x_step.h"

#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixExp.h"
#include "Markov_LA/matrixMaxMin.h"

#include "Markov_Bay/G_Test.h"

#include "Tests/Markov_Mol/MarkovTransitionStep_Test.h"
#include "Tests/Markov_Mol/MarkovTransitionRate_Test.h"
#include "Tests/Markov_Mol/MarkovState_Test.h"

#include "Tests/Markov_Mol/ABC_Markov_Model_Test.h"

#include "Tests/ElementaryTest.h"


namespace Markov_Test
{
namespace Markov_Mol_Test
{
using namespace Markov_LA;


MultipleTests ABC_Markov_Model_Test::classInvariant()const
{
    MultipleTests results("ABC_Markov_Model",
                          "Class Invariant");

    results.push_back(ABC_Parametrizable_Test::classInvariant());

    {
        MultipleTests pModel("Model description",
                             "Q(), n_bound_agonists() and g() invariants");
        {
            MultipleTests pSizes("Size of matrices",
                                 "Check all the sizes");

            pSizes.push_back(ElementaryTest(
                                 "k()",
                                 "equals to Q() size",
                                 (nrows(model_->Q())==model_->k())));

            pSizes.push_back(ElementaryTest(
                                 "Q()",
                                 "is square",
                                 (nrows(model_->Q())==ncols(model_->Q()))));

            pSizes.push_back(ElementaryTest(
                                 "g()",
                                 "k x 1",
                                 (nrows(model_->g())==model_->k())&&
                                 (ncols(model_->g())==1)));

            pSizes.push_back(ElementaryTest(
                                 "n_bound_agonists()",
                                 "1 x k",
                                 (ncols(model_->n_bound_agonists())==model_->k())&&
                                 (nrows(model_->n_bound_agonists())==1)));

            pModel.push_back(pSizes);
        };
        {
            MultipleTests pQ("Q()",
                             "invariants");
            pQ.push_back(ElementaryTest(
                             "zero diag",
                             "diag(Q())==0",
                             diag(model_->Q())==0.0));
            pQ.push_back(ElementaryTest(
                             "non negative",
                             " Q>=0.0",
                             model_->Q()>=0.0));
            {


                MultipleTests pQ1("connected back and forth ",
                                  "Q(i,J)>=0 and if Q(i,j)>0 ->Q(j,i)>0");

                MultipleTests pQ2("no isolated states ",
                                  "Q(i,:)>0");
                for (std::size_t i=0; i<model_->k()-1;++i)
                {
                    bool isConnected=false;
                    for (std::size_t j=i+1;j<model_->k();++j)
                    {
                        if (model_->Q()(i,j)>0)
                        {
                            pQ1.push_back(ElementaryTest(
                                              Markov_IO::ToString(i)+" "+ Markov_IO::ToString(j),
                                              "positive both ways",
                                              model_->Q()(j,i)>0));
                            isConnected=true;
                        }
                        else
                            pQ1.push_back(ElementaryTest(
                                              Markov_IO::ToString(i)+" "+ Markov_IO::ToString(j),
                                              "also zero",
                                              model_->Q()(j,i)==0.0));

                    }
                    pQ2.push_back(ElementaryTest(
                                      Markov_IO::ToString(i),
                                      "is connected",
                                      isConnected));
                }
                pQ.push_back(pQ1);
                pQ.push_back(pQ2);
            }

            pModel.push_back(pQ);
        }
        {
            MultipleTests pa("n_bound_agonists()",
                             "invariants");

            MultipleTests pa0("no more than one agonist is gain or lost at a time",
                              "Q(i,j)>0 -> abs(a(i)-a(j))<=1");


            MultipleTests pa1("only rates with nonincreasing agonists are in Q0",
                              "if Q0(i,j)>0 -> a(j)<=a(i)");

            MultipleTests pa2("only rates with increasing agonist are in Q1",
                              "if Q1(i,j)>0 then a(j)=a(i)+1");

            MultipleTests pQ0("Q0()/ Q1()",
                              "invariants");
            MultipleTests pQ00("rates are in Q0 or Q1",
                               "if Q()(i,j)>0 ->Q0(i,j)==Q(i,j) xor Q1(i,j)==Q(i,j)");





            for (std::size_t i=0; i<model_->k();++i)
            {
                for (std::size_t j=0;j<model_->k();++j)
                {
                    if (model_->Q()(i,j)>0)
                    {
                        long int  ai=model_->n_bound_agonists()[i];
                        long int  aj=model_->n_bound_agonists()[j];


                        pa0.push_back(ElementaryTest(
                                          Markov_IO::ToString(i)+" "+
                                          Markov_IO::ToString(j),
                                          "Q(i,j)>0 -> abs(a(i)-a(j))<=1",
                                          std::abs(ai-aj)<=1));
                        pQ00.push_back(ElementaryTest(
                                           Markov_IO::ToString(i)+" "+
                                           Markov_IO::ToString(j),
                                           "if Q()(i,j)>0 ->Q0(i,j)==Q()(i,j) xor"
                                           "Q1(i,j)==Q()(i,j)",
                                           ((model_->Q0()(i,j)>0)&&
                                            (model_->Q0()(i,j)==model_->Q()(i,j)))^
                                           ((model_->Q1()(i,j)>0)&&
                                            (model_->Q1()(i,j)==model_->Q()(i,j)))));
                    }
                    if (model_->Q0()(i,j)>0)
                    {
                        pa1.push_back(ElementaryTest(
                                          Markov_IO::ToString(i)+" "+
                                          Markov_IO::ToString(j),
                                          "if Q0(i,j)>0 -> a(j)<=a(i)",
                                          model_->n_bound_agonists()[i]>=
                                          model_->n_bound_agonists()[j]));
                    }
                    if (model_->Q1()(i,j)>0)
                    {
                        pa2.push_back(ElementaryTest(
                                          Markov_IO::ToString(i)+" "+
                                          Markov_IO::ToString(j),
                                          "if Q1(i,j)>0 -> a(j)==a(i)+1",
                                          model_->n_bound_agonists()[i]==
                                          model_->n_bound_agonists()[j]-1));
                    }

                }
            }

            pa.push_back(pa0);
            pa.push_back(pa1);
            pa.push_back(pa2);

            pModel.push_back(pa);

            pQ0.push_back(pQ00);


            pQ0.push_back(ElementaryTest(
                              "Q0",
                              "all rows sum up zero",
                              sum(model_->Q0(),true)==0.0));
            pQ0.push_back(ElementaryTest(
                              "Q1",
                              "all rows sum up zero",
                              sum(model_->Q1(),true)==0.0));

            pModel.push_back(pQ0);
        }
        results.push_back(pModel);
    }

    return results;
}




MultipleTests ABC_Markov_Model_Test::
startInvariant(double agonist_concentration,
               std::size_t Nchannels,
               Borrowed::MersenneTwister::MTRand& sto)const
{
    MultipleTests results("ABC_Markov_Model::start(double,"
                          "std::size_t,"
                          "Borrowed::MersenneTwister::MTRand&)const",
                          "invariants");


    Markov_state St=model_->start(agonist_concentration,Nchannels,sto);

    results.push_back(Markov_state_Test(St).classInvariant());

    results.push_back(ElementaryTest(
                          "ymean",
                          "equals N*g",
                          St.ymean()==(St.N()*model_->g())[0]));


    Markov_Bay::G_Test G(St.N(),St.P());
    double G0=G.G();
    std::size_t df0=G.df();
    std::size_t n0=1;
    double dG=std::abs(G0-df0);
    double sG0=std::sqrt(df0);
    double sG1=sG0;
    double sumG0=G0;
    double sumdf=df0;

    while (dG>2.0*sG0 && dG<5.0*sG1)
    {
        Markov_state St2=model_->start(agonist_concentration,Nchannels,sto);
        Markov_Bay::G_Test G2(St2.N(),St2.P());
        n0++;
        sumG0+=G2.G();
        sumdf+=G2.df();
        dG=std::abs(sumG0/n0-sumdf/n0);
        sG0=std::sqrt(df0/n0);
        sG1=sG0/std::sqrt(n0);
    }

    results.push_back(ElementaryTest(
                          "Multinomial distribution",
                          "G_Test: mean G value within two standard deviations",
                          dG<=2.0*sG0));

    results.push_back(ElementaryTest(
                          "P",
                          "Equals Peq() at x",
                          St.P()==model_->Peq(agonist_concentration)));

    results.push_back(ElementaryTest(
                          "N",
                          "sum up Nchannels",
                          totalsum(St.N())==Nchannels));


    return results;



}


MultipleTests ABC_Markov_Model_Test::
PeqInvariant(double agonist_concentration)const
{

    MultipleTests results("ABC_Markov_Model::Peq(double)const",
                          "invariants");

    M_Matrix<double> Peq=model_->Peq(agonist_concentration);

    results.push_back(ElementaryTest(
                          "size",
                          "size(Peq)==k()",
                          (ncols(Peq)==model_->k())&&
                          (nrows(Peq)==1)));

    Markov_Transition_rate Qx_avg=model_->Q_x(agonist_concentration,true);


    results.push_back(ElementaryTest(
                          "Equilibrium equation",
                          "Peq*Qx(x)==0 \n"+
                          Markov_IO::ToString(1.0+Peq*Qx_avg.Qrun)+"==0\n",
                          1000.0+Peq*Qx_avg.Qrun==1000.0)
                      );
    return results;
}



MultipleTests ABC_Markov_Model_Test::
Q_xInvariant (double agonist_concentrarion,
              bool isavergaing)
{
    MultipleTests results("ABC_Markov_Model::"
                          "Q_x (double,"
                          "bool)const",
                          "method Invariant");

    Markov_Transition_rate Qx=model_->Q_x(agonist_concentrarion,isavergaing);
    results.push_back(Markov_Transition_rate_Test(Qx).classInvariant());

    MultipleTests pQrun("Qrun",
                        "invariants");
    pQrun.push_back(ElementaryTest(
                        "Calculation",
                        "Qrun=Q0+Q1*x",
                        Qx.Qrun==model_->Q0()+
                        model_->Q1()*agonist_concentrarion));
    results.push_back(pQrun);

    MultipleTests pAverage("IsAveraging",
                           "invariants");
    if (isavergaing)
    {
        pAverage.push_back(ElementaryTest(
                               "Calculate averaging values",
                               "check dimension",
                               size(Qx.Wg)>0));
        pAverage.push_back(ElementaryTest(
                               "Wg",
                               "recover value",
                               Qx.Wg==Qx.W*model_->g()));
        pAverage.push_back(ElementaryTest(
                               "WgV",
                               "recover value",
                               Qx.WgV==Qx.W*diag(model_->g())*Qx.V));



    }
    else
    {
        pAverage.push_back(ElementaryTest(
                               "Calculate averaging values",
                               "check dimension",
                               size(Qx.Wg)==0));
        pAverage.push_back(ElementaryTest(
                               "WgV",
                               "empty",
                               size(Qx.WgV)==0));

    }
    results.push_back(pAverage);

    return results;
}



MultipleTests ABC_Markov_Model_Test::
Q_dtInvariant (const Markov_IO::ABC_measure_point& xdt,
               bool is_averaging,
               bool varyingx,
               bool two_anchor,
               std::size_t nsteps)
{
    MultipleTests results("ABC_Markov_Model::Q_dt("
                          "const Markov_IO::ABC_measure_point&,"
                          "bool,bool,bool)",
                          "method Invariant");

    Markov_Transition_step Qdt=model_->
            Q_dt(xdt,is_averaging,varyingx,two_anchor);
    results.push_back(Markov_Transition_step_Test(Qdt).classInvariant());

    MultipleTests pP("P",
                     "invariants");

    Markov_Transition_rate Qx=model_->Q_x(xdt.x(),is_averaging);
    results.push_back(Q_xInvariant(xdt.x(),is_averaging));

    pP.push_back(ElementaryTest(
                     "P calculation",
                     "P==expm(Qrun*dt)",
                     Qdt.P==expm(Qx.Qrun*xdt.dt())));
    results.push_back(pP);
    MultipleTests pg;
    if (!is_averaging)
    {
        pg=MultipleTests("Not averaging",
                         "No time averaging: returns only gmean");
        pg.push_back(ElementaryTest("gmean",
                                    "Equal to g()",
                                    Qdt.gmean_i==model_->g()));
    }
    else
    {
        if (!varyingx)
        {
            pg=MultipleTests ("Averaging, not varying x",
                              "Time averaging, no variations in x");
        }
        else
        {
            if (!two_anchor)
                pg=MultipleTests ("Averaging, single achor",
                                  "Time averaging, varying x, single anchor");
            else
                pg=MultipleTests("Averaging, double achor",
                                 "Time averaging, varying x, double anchor");
        }
        Markov_Transition_step QdtAprox=Q_dtRun(xdt,nsteps);
        Markov_Transition_step QdtAprox2=Q_dtRun(xdt,nsteps/2);

        pg.push_back(ElementaryTest("gmean_i",
                                    "close to approximation",
                                    norm(QdtAprox.gmean_i-Qdt.gmean_i)
                                    <1.2*norm(QdtAprox.gmean_i-QdtAprox2.gmean_i)));


        pg.push_back(ElementaryTest("gsqr_i",
                                    "close to approximation",
                                    norm(QdtAprox.gsqr_i-Qdt.gsqr_i)
                                    <1.2*norm(QdtAprox.gsqr_i-QdtAprox2.gsqr_i)));

        pg.push_back(ElementaryTest("gvar_i",
                                    "close to approximation \n"
                                    "Qdt.gvar_i\n"+
                                    Markov_IO::ToString(Qdt.gvar_i)+"\n"
                                    "QdtAprox.gvar_i\n"+
                                    Markov_IO::ToString(QdtAprox.gvar_i)+"\n"
                                    "QdtAprox2.gvar_i\n"+
                                    Markov_IO::ToString(QdtAprox2.gvar_i)+"\n"
                                    "norm(Qdt,QdtApprox) \t"+
                                    Markov_IO::ToString(norm(QdtAprox.gvar_i-Qdt.gvar_i))+
                                    "\n norm(Qdt,QdtApprox) \t"+
                                    Markov_IO::ToString(
                                        norm(QdtAprox.gvar_i-QdtAprox2.gvar_i))+"\n",
                                    norm(QdtAprox.gvar_i-Qdt.gvar_i)
                                    <1.2*norm(QdtAprox.gvar_i-QdtAprox2.gvar_i)));

        if (varyingx)
        {
            pg.push_back(ElementaryTest("gtotal_ij",
                                        "close to approximation",
                                        norm(QdtAprox.gtotal_ij-Qdt.gtotal_ij)
                                        <1.2*norm(QdtAprox.gtotal_ij-QdtAprox2.gtotal_ij)));

            if (two_anchor)
            {
                pg.push_back(ElementaryTest("gtotal_sqr_ij",
                                            "close to approximation",
                                            norm(QdtAprox.gtotal_sqr_ij-Qdt.gtotal_sqr_ij)
                                            <1.2*norm(QdtAprox.gtotal_sqr_ij-QdtAprox2.gtotal_sqr_ij)));

                pg.push_back(ElementaryTest(
                                 "gtotal_var_ij",
                                 "\nclose to approximation"
                                 "\nQdt.gtotal_var_ij\n"+
                                 Markov_IO::ToString(Qdt.gtotal_var_ij)+
                                 "QdtAprox.gtotal_var_ij\n"+
                                 Markov_IO::ToString(QdtAprox.gtotal_var_ij)+
                                 "norm(QdtAprox.gtotal_var_ij-Qdt.gtotal_var_ij)\t"+
                                 Markov_IO::ToString(
                                     norm(QdtAprox.gtotal_var_ij-Qdt.gtotal_var_ij))+
                                 "norm(QdtAprox.gtotal_var_ij-QdtAprox2.gtotal_var_ij)\t"+
                                 Markov_IO::ToString(
                                     norm(QdtAprox.gtotal_var_ij-QdtAprox2.gtotal_var_ij))+
                                 "\n",
                                 norm(QdtAprox.gtotal_var_ij-Qdt.gtotal_var_ij)
                                 <1.2*norm(QdtAprox.gtotal_var_ij-QdtAprox2.gtotal_var_ij)));

                pg.push_back(ElementaryTest("gtotal_var_i",
                                            "close to approximation",
                                            norm(QdtAprox.gtotal_var_i-Qdt.gtotal_var_i)
                                            <1.2*norm(QdtAprox.gtotal_var_i-QdtAprox2.gtotal_var_i)));
                pg.push_back(ElementaryTest("gvar_ij",
                                            "close to approximation",
                                            norm(QdtAprox.gvar_ij-Qdt.gvar_ij)
                                            <1.2*norm(QdtAprox.gvar_ij-QdtAprox2.gvar_ij)));
                pg.push_back(ElementaryTest("gmean_ij",
                                            "close to approximation",
                                            norm(QdtAprox.gmean_ij-Qdt.gmean_ij)
                                            <1.2*norm(QdtAprox.gmean_ij-QdtAprox2.gmean_ij)));

            }
        }

    }

    results.push_back(pg);
    return results;

}





MultipleTests ABC_Markov_Model_Test::
Q_stepInvariant(const Markov_IO::ABC_measure_step& xstep,
                bool is_averaging,
                bool two_anchor,
                std::size_t nsteps)const

{
    std::string name="Q_step(step,";
    name.append(is_averaging ? "averaging," : "notaveraging,");
    name.append(two_anchor ? "two_anchor)" : " one_anchor)");

    const Markov_IO::ABC_Put& p=xstep;
    name=name+"\n step= \n"+Markov_IO::ToString(p)+"\n";

    MultipleTests results(name,
                          "invariant");


    Markov_Transition_step Qst=model_->
            Q_step(xstep,is_averaging,two_anchor);
    results.push_back(Markov_Transition_step_Test(Qst).classInvariant());




    MultipleTests pg;
    Markov_Transition_step QstAprox=Q_stepRun(xstep,nsteps);
    Markov_Transition_step QstAprox2=Q_stepRun(xstep,nsteps/2);

    if (!is_averaging)
    {
        pg=MultipleTests("Not averaging",
                         "No time averaging: returns only gmean");
        pg.push_back(ElementaryTest("gmean",
                                    "Equal to g()",
                                    Qst.gmean_i==model_->g()));
    }
    else
    {
        if (!two_anchor)
            pg=MultipleTests ("Averaging, single achor",
                              "Time averaging, varying x, single anchor");
        else
            pg=MultipleTests("Averaging, double achor",
                             "Time averaging, varying x, double anchor");
    }



    if (is_averaging)
    {
        pg.push_back(ElementaryTest("gmean_i",
                                    "close to approximation",
                                    norm(QstAprox.gmean_i-Qst.gmean_i)
                                    <1.2*norm(QstAprox.gmean_i-QstAprox2.gmean_i)));
        pg.push_back(ElementaryTest("gsqr_i",
                                    "close to approximation",
                                    norm(QstAprox.gsqr_i-Qst.gsqr_i)
                                    <1.2*norm(QstAprox.gsqr_i-QstAprox2.gsqr_i)));

        pg.push_back(ElementaryTest("gvar_i",
                                    "close to approximation",
                                    norm(QstAprox.gvar_i-Qst.gvar_i)
                                    <1.2*norm(QstAprox.gvar_i-QstAprox2.gvar_i)));


        if (two_anchor)
        {
            pg.push_back(ElementaryTest("gtotal_ij",
                                        "close to approximation",
                                        norm(QstAprox.gtotal_ij-Qst.gtotal_ij)
                                        <1.2*norm(QstAprox.gtotal_ij-QstAprox2.gtotal_ij)));

            pg.push_back(ElementaryTest("gtotal_sqr_ij",
                                        "close to approximation",
                                        norm(QstAprox.gtotal_sqr_ij-Qst.gtotal_sqr_ij)
                                        <1.2*norm(QstAprox.gtotal_sqr_ij-QstAprox2.gtotal_sqr_ij)));

            pg.push_back(ElementaryTest("gtotal_var_ij",
                                        "close to approximation"
                                        "\nQdt.gtotal_var_ij\n"+
                                        Markov_IO::ToString(Qst.gtotal_var_ij)+
                                        "QdtAprox.gtotal_var_ij\n"+
                                        Markov_IO::ToString(QstAprox.gtotal_var_ij)+
                                        "norm(QdtAprox.gtotal_var_ij-Qdt.gtotal_var_ij)\t"+
                                        Markov_IO::ToString(
                                            norm(QstAprox.gtotal_var_ij-Qst.gtotal_var_ij))+
                                        "\nnorm(QdtAprox.gtotal_var_ij-QdtAprox2.gtotal_var_ij)\t"+
                                        Markov_IO::ToString(
                                            norm(QstAprox.gtotal_var_ij-QstAprox2.gtotal_var_ij))+
                                        "\n",
                                        norm(QstAprox.gtotal_var_ij-Qst.gtotal_var_ij)
                                        <1.2*norm(QstAprox.gtotal_var_ij-QstAprox2.gtotal_var_ij)));






            pg.push_back(ElementaryTest("gtotal_var_i",
                                        "close to approximation",
                                        norm(QstAprox.gtotal_var_i-Qst.gtotal_var_i)
                                        <1.2*norm(QstAprox.gtotal_var_i-QstAprox2.gtotal_var_i)));
            pg.push_back(ElementaryTest("gvar_ij",
                                        "close to approximation",
                                        norm(QstAprox.gvar_ij-Qst.gvar_ij)
                                        <1.2*norm(QstAprox.gvar_ij-QstAprox2.gvar_ij)));
            pg.push_back(ElementaryTest("gmean_ij",
                                        "close to approximation",
                                        norm(QstAprox.gmean_ij-Qst.gmean_ij)
                                        <1.2*norm(QstAprox.gmean_ij-QstAprox2.gmean_ij)));

        }

    }
    results.push_back(pg);
    return results;

}











Markov_Transition_step ABC_Markov_Model_Test::
Q_dtRun(const Markov_IO::ABC_measure_point& xdt,
        std::size_t numSteps)
{
    Markov_Transition_step res(model_->k(),true,true,true);
    double ddt=xdt.dt()/numSteps;
    Markov_IO::x_dt xddt(ddt,xdt.x());
    Markov_Transition_step Qdt=model_->Q_dt(xddt,false,false,false);
    M_Matrix<double> PPn=eye<double>(model_->k());
    M_Matrix<double> PG_n=PPn*diag(model_->g())*ddt;
    M_Matrix<double> PGG_n=PG_n*diag(model_->g())*ddt;
    double dtrun=ddt;
    for (std::size_t i=0; i<numSteps; i++)
    {
        PGG_n=(PGG_n*Qdt.P) +
                (PG_n*diag(model_->g()))*ddt+
                (PPn*diag(model_->g())*diag(model_->g()))*(ddt*ddt);
        PG_n= (PG_n*Qdt.P) + (PPn*diag(model_->g()))*ddt;
        PPn=PPn*Qdt.P;
        dtrun+=ddt;
    };

    res.P=PPn;

    res.gtotal_sqr_ij=PGG_n/(dtrun*dtrun*0.5);
    res.gtotal_ij=PG_n/dtrun;
    M_Matrix<double> u=Markov_LA::ones<double>(model_->k(),1);

    res.gmean_i=res.gtotal_ij*u;
    res.gsqr_i=res.gtotal_sqr_ij*u;
    res.gvar_i=res.gsqr_i-elemMult(res.gmean_i,res.gmean_i);;

    res.gmean_ij=M_Matrix<double>(model_->k(),model_->k());
    res.gvar_ij=M_Matrix<double>(model_->k(),model_->k());
    for (std::size_t i=0; i<model_->k(); i++)
        for (std::size_t j=0; j<model_->k(); j++)
            if (res.P(i,j)>1e-9)
            {
                res.gmean_ij(i,j)=res.gtotal_ij(i,j)/res.P(i,j);
                res.gvar_ij(i,j)=res.gtotal_sqr_ij(i,j)/res.P(i,j)-
                        res.gmean_ij(i,j)*res.gmean_ij(i,j);
            }
            else
            {
                res.gmean_ij(i,j)=0;
                res.gvar_ij(i,j)=0;
            }

    res.gtotal_var_ij=elemMult(res.gvar_ij,res.P);
    res.gtotal_var_i=res.gtotal_var_ij*u;
    return res;
}



Markov_Transition_step ABC_Markov_Model_Test::
Q_stepRun(const Markov_IO::ABC_measure_step& xdt,
          std::size_t numSteps)const

{
    Markov_Transition_step res(model_->k(),true,true,true);
    double ddt0=xdt.dt()/numSteps;

    M_Matrix<double> PPn=eye<double>(model_->k());
    M_Matrix<double> PG_n=zeros<double>(model_->k(),model_->k());
    M_Matrix<double> PGG_n=PG_n;
    double dtrun=0;
    for (std::size_t ii=0; ii<xdt.num_steps();++ii)
    {
        Markov_IO::x_dt xdt_i=xdt.sub_step(ii);
        std::size_t numStepsrun=std::ceil(xdt_i.dt()/ddt0);
        double ddt=xdt_i.dt()/numStepsrun;
        Markov_IO::x_dt xddt(ddt,xdt_i.x());
        Markov_Transition_step Qdt=model_->Q_dt(xddt,false,false,false);
        for (std::size_t i=0; i<numStepsrun; i++)
        {

            PGG_n=(PGG_n*Qdt.P) +
                    (PG_n*diag(model_->g()))*ddt+
                    (PPn*diag(model_->g())*diag(model_->g()))*(ddt*ddt);
            PG_n= (PG_n*Qdt.P) + (PPn*diag(model_->g()))*ddt;
            PPn=PPn*Qdt.P;
            dtrun+=ddt;
        };
    }
    res.P=PPn;

    res.gtotal_sqr_ij=PGG_n/(dtrun*dtrun*0.5);
    res.gtotal_ij=PG_n/dtrun;
    M_Matrix<double> u=Markov_LA::ones<double>(model_->k(),1);

    res.gmean_i=res.gtotal_ij*u;
    res.gsqr_i=res.gtotal_sqr_ij*u;
    res.gvar_i=res.gsqr_i-elemMult(res.gmean_i,res.gmean_i);;

    res.gmean_ij=M_Matrix<double>(model_->k(),model_->k());
    res.gvar_ij=M_Matrix<double>(model_->k(),model_->k());
    for (std::size_t i=0; i<model_->k(); i++)
        for (std::size_t j=0; j<model_->k(); j++)
            if (res.P(i,j)>1e-9)
            {
                res.gmean_ij(i,j)=res.gtotal_ij(i,j)/res.P(i,j);
                res.gvar_ij(i,j)=res.gtotal_sqr_ij(i,j)/res.P(i,j)-
                        res.gmean_ij(i,j)*res.gmean_ij(i,j);
            }
            else
            {
                res.gmean_ij(i,j)=0;
                res.gvar_ij(i,j)=0;
            }

    res.gtotal_var_ij=elemMult(res.gvar_ij,res.P);
    res.gtotal_var_i=res.gtotal_var_ij*u;
    return res;
}










MultipleTests ABC_Markov_Model_Test::
runInvariant(const Markov_IO::ABC_measure_point& xdt,
             Markov_state& markovState,
             std::size_t n_steps,
             Borrowed::MersenneTwister::MTRand& sto)
{

    MultipleTests results("ABC_Markov_Model::run("
                          "const Markov_IO::ABC_measure_point&,"
                          "Markov_state&,"
                          "std::size_t,"
                          "Borrowed::MersenneTwister::MTRand&)",
                          "method Invariant");

    Markov_state st=model_->run(xdt,markovState,n_steps,sto);

    results.push_back(Markov_state_Test(st).classInvariant());

    return results;


}



ABC_Markov_Model_Test::ABC_Markov_Model_Test(const ABC_Markov_Model& model):
    ABC_Parametrizable_Test(model),
    model_(dynamic_cast<const ABC_Markov_Model*>(sample_))
{

}

ABC_Markov_Model_Test::~ABC_Markov_Model_Test()
{

}

MultipleTests ABC_Markov_Model_Test::AllTests()
{

    MultipleTests result("class ABC_Markov_Model",
                         "All tests");

    result.push_back(classInvariant());

    double agonist_concentration=1;
    std::size_t Nchannels=100;
    std::size_t numSteps=100000;
    Borrowed::MersenneTwister::MTRand sto(Borrowed::MersenneTwister::seedinit(0));

    result.push_back(startInvariant(agonist_concentration,
                                    Nchannels,
                                    sto));


    result.push_back(PeqInvariant(agonist_concentration));
    double dt=1e-2;

    Markov_IO::x_dt xdt(dt,agonist_concentration);

    Markov_state markovState=model_->start(agonist_concentration,Nchannels,sto);
    std::size_t n_steps=100;

    result.push_back(runInvariant(xdt,markovState,n_steps,sto));

    result.push_back(Q_dtInvariant(xdt,false,false,false,numSteps));

    result.push_back(Q_dtInvariant(xdt,true,false,false,numSteps));

    result.push_back(Q_dtInvariant(xdt,true,true,false,numSteps));

    result.push_back(Q_dtInvariant(xdt,true,true,true,numSteps));

    result.push_back(Q_xInvariant (agonist_concentration,false));

    result.push_back(Q_xInvariant (agonist_concentration,true));

    Markov_IO::x_step xst;
    std::size_t n=1;
    for (std::size_t i=0; i<n; i++)
      xst.push_back(dt/n,agonist_concentration*0,0.0).
              push_back(dt/n,agonist_concentration*(i),0.0);

    result.push_back(Q_stepInvariant(xst ,false,false,numSteps));
    result.push_back(Q_stepInvariant(xst ,true,false,numSteps));
    result.push_back(Q_stepInvariant(xst ,true,true,numSteps));
    return result;


}



}
}




