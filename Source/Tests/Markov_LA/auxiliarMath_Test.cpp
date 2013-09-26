#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/auxiliarMath.h"

#include "Markov_IO/auxiliarIO.h"
#include "Markov_LA/ContinuedFraction.h"

#include "Tests/AssertPlain.h"
#include "Tests/ElementaryTest.h"


namespace Markov_Test
{

namespace Markov_LA_Test
{
using namespace Markov_LA;
using namespace Markov_IO;

template<typename T>
MultipleTests Markov_LA_Test<T>::AuxiliarMath_Test()
{
    MultipleTests result("header auxiliarMath.h",
                         "header functions invariants");

    MultipleTests pNum("NaN and infinite",
                       "function invariants");

    pNum.push_back(ElementaryTest(
                       "function infinity()",
                       "returns infinity from numeric limits",
                       infinity()==std::numeric_limits<double>::infinity()));


    pNum.push_back(ElementaryTest(
                       "function NaN",
                       "isNaN(NaN()) is true",
                       isNaN(NaN())));

    pNum.push_back(ElementaryTest(
                       "function isNaN(quiet_NaN)",
                       "isNaN(std::numeric_limits<double>::quiet_NaN() is true",
                       isNaN(std::numeric_limits<double>::quiet_NaN())));

    pNum.push_back(ElementaryTest(
                       "function isNaN(signaling_NaN)",
                       "isNaN(std::numeric_limits<double>::signaling_NaN() is true",
                       isNaN(std::numeric_limits<double>::signaling_NaN())));


    pNum.push_back(ElementaryTest(
                       "function isFinite(quiet_NaN)",
                       "isfinite(std::numeric_limits<double>::quiet_NaN() is false",
                       !isFinite(std::numeric_limits<double>::quiet_NaN())));


    pNum.push_back(ElementaryTest(
                       "function isFinite(signaling_NaN)",
                       "isfinite(std::numeric_limits<double>::signaling_NaN() is false",
                       !isFinite(std::numeric_limits<double>::signaling_NaN())));


    pNum.push_back(ElementaryTest(
                       "function isFinite()",
                       "isFinite(std::numeric_limits<double>::infinity() is false",
                       !isFinite(std::numeric_limits<double>::infinity())));

    pNum.push_back(ElementaryTest(
                       "function isFinite()",
                       "isFinite(1./0.0) is false",
                       !isFinite(1./0.)));

    pNum.push_back(ElementaryTest(
                       "function isFinite()",
                       "isFinite(0./0.0) is false",
                       !isFinite(0./0.)));

    pNum.push_back(ElementaryTest(
                       "function isFinite()",
                       "isFinite(regular number) is true",
                       isFinite(3256.976)));

    result.push_back(pNum);


    MultipleTests perfinv("function erfinv",
                          "function invariants");


    double x_val[]={0, 1e-4,1e-3,
                    1e-2,1e-1,
                    0.2,0.3,
                    0.4,0.5,
                    0.6,0.7,
                    0.8,0.9,
                    0.99,0.999,
                    0.9999};

    double erfinv_x_val[]={0,0.000088622692777,0.000886227157467,
                           0.008862501280951,0.088855990494258,
                           0.179143454621292,0.272462714726754,
                           0.370807158593558,   0.476936276204470,
                           0.595116081449995,   0.732869077959217,
                           0.906193802436823,   1.163087153676674,
                           1.821386367718449,  2.326753765513521,
                           2.751063905711999};


    perfinv.push_back(ElementaryTest(
                          "erfinv(1)",
                          "\nExpected infinity\t"
                          "\nFound \t"+ToString(erfinv(1))+"\n",
                          erfinv(1)==infinity()));


    perfinv.push_back(ElementaryTest(
                          "erfinv(-1)",
                          "\nExpected -infinity\t"
                          "\nFound \t"+ToString(erfinv(-1))+"\n",
                          erfinv(-1)==-infinity()));


    for (std::size_t i=16; i>0; i--)
        perfinv.push_back(ElementaryTest(
                              "erfinv("+ToString(-x_val[i-1])+")",
                              "\nExpected \t"+ToString(-erfinv_x_val[i-1])+
                              "\nFound \t"+ToString(erfinv(-x_val[i-1]))+"\n"
                              "\ndifference \t"+
                              ToString(erfinv(-x_val[i-1])+erfinv_x_val[i-1])+"\n",
                              std::abs(erfinv(-x_val[i-1])+erfinv_x_val[i-1])<1e-6));
    for (std::size_t i=0; i<16; i++)
        perfinv.push_back(ElementaryTest(
                              "erfinv("+ToString(x_val[i])+")",
                              "\nExpected \t"+ToString(erfinv_x_val[i])+
                              "\nFound \t"+ToString(erfinv(x_val[i]))+"\n"
                              "\ndifference \t"+
                              ToString(erfinv(x_val[i])-erfinv_x_val[i])+"\n",
                              std::abs(erfinv(x_val[i])-erfinv_x_val[i])<1e-6));


    result.push_back(perfinv);



    MultipleTests pChiSqrCdf("function ChiSqrCdf",
                             "function invariants");


    double x_chi[]={0,0.1,
                    0.5,1,
                    1.5,2,
                    3,4,
                    5,10,
                    12,15,
                    20,30};

    double ChiSqrCdf_x_1[]={ 0,   0.248170365954151 ,
                             0.520499877813047 ,0.682689492137086,
                             0.779328638080153,  0.842700792949715,
                             0.916735483336446, 0.954499736103642,
                             0.974652681322532, 0.998434597741998,
                             0.999467994494861,0.999892488823271,
                             0.999992255783569,0.999999956795369};



   for (std::size_t i=0; i<14; i++)
        pChiSqrCdf.push_back(ElementaryTest(
                                 "ChiSqrCdf("+ToString(x_chi[i])+",1)",
                                 "\nExpected \t"+ToString(ChiSqrCdf_x_1[i])+
                                 "\nFound \t"+ToString(ChiSqrCdf(x_chi[i],1))+"\n"
                                 "\ndifference \t"+
                                 ToString(ChiSqrCdf(x_chi[i],1)-ChiSqrCdf_x_1[i])+"\n",
                                 std::abs(ChiSqrCdf(x_chi[i],1)-ChiSqrCdf_x_1[i])<1e-6));



    double ChiSqrCdf_x_2[]={  0,                   0.048770575499286,
                              0.221199216928595,   0.393469340287367,
                              0.527633447258985,   0.632120558828558,
                              0.776869839851570,   0.864664716763387,
                              0.917915001376101,   0.993262053000915,
                              0.997521247823334,   0.999446915629852,
                              0.999954600070238,   0.999999694097680};


    for (std::size_t i=0; i<14; i++)
        pChiSqrCdf.push_back(ElementaryTest(
                                 "ChiSqrCdf("+ToString(x_chi[i])+",2)",
                                 "\nExpected \t"+ToString(ChiSqrCdf_x_2[i])+
                                 "\nFound \t"+ToString(ChiSqrCdf(x_chi[i],2))+"\n"
                                 "\ndifference \t"+
                                 ToString(ChiSqrCdf(x_chi[i],2)-ChiSqrCdf_x_2[i])+"\n",
                                 std::abs(ChiSqrCdf(x_chi[i],2)-ChiSqrCdf_x_2[i])<1e-6));



    double x_chi_200[]={50,100,
                        150,180,
                        190,200,
                        210,220,
                        250,300,
                        400,800};

    double ChiSqrCdf_x_200[]={ 0.000000000000000,   0.000000000320007,
                               0.003352441498187,   0.158220989186433,
                               0.317356811169810,   0.513298798279165,
                               0.700245342391161,   0.841721329939903,
                               0.990620868331173,   0.999994075459665,
                               0.999999999999998,   1.000000000000000};





   for (std::size_t i=0; i<12; i++)
        pChiSqrCdf.push_back(ElementaryTest(
                                 "ChiSqrCdf("+ToString(x_chi_200[i])+",200)",
                                 "\nExpected \t"+ToString(ChiSqrCdf_x_200[i])+
                                 "\nFound \t"+ToString(ChiSqrCdf(x_chi_200[i],200))+"\n"
                                 "\ndifference \t"+
                                 ToString(ChiSqrCdf(x_chi_200[i],200)-ChiSqrCdf_x_200[i])+"\n",
                                 std::abs(ChiSqrCdf(x_chi_200[i],200)-ChiSqrCdf_x_200[i])<1e-6));










    result.push_back(pChiSqrCdf);







    MultipleTests pLogGammaFunction("function LogGammaFunction",
                          "function invariants");


    double x_val_g[]={0.5,1,
                    1.5,2,
                    3,4,
                    5,10,
                    12,15,
                    20,30};


    double LogGammaFunction_x_val[]={0.572364942924700,                   0,
                                     -0.120782237635245,                   0,
                                     0.693147180559945,   1.791759469228055,
                                     3.178053830347945,  12.801827480081469,
                                     17.502307845873887,  25.191221182738680,
                                    39.339884187199488,  71.257038967168000};




    for (std::size_t i=0; i<12; i++)
        pLogGammaFunction.push_back(ElementaryTest(
                              "LogGammaFunction("+ToString(x_val_g[i])+")",
                              "\nExpected \t"+ToString(LogGammaFunction_x_val[i])+
                              "\nFound \t"+ToString(LogGammaFunction(x_val_g[i]))+"\n"
                              "\ndifference \t"+
                              ToString(LogGammaFunction(x_val_g[i])-LogGammaFunction_x_val[i])+"\n",
                              std::abs(LogGammaFunction(x_val_g[i])-LogGammaFunction_x_val[i])<1e-6));


    result.push_back(pLogGammaFunction);





    MultipleTests pContinuedFraction("ContinuedFractions",
                                     "calculation");

    for (std::size_t n=16; n<50; n+=4)
    {
    std::vector<double> a(n);

    std::vector<double> b(n);


    for (std::size_t i=0;i<n;i++)
    {
        b[i]=1;
        a[i]=1;
     }
    double golden_ap= Markov_LA::ContinuedFraction(a,b)();
    double golden=0.5+std::sqrt(5)/2;

    ElementaryTest tg(
                "ContinuedFraction(a=[1,1...]; b=[1,1..], n="+ToString(n)+ ")",
                "\nExpected \t"+ToString(golden)+
                "\nFound \t"+ToString(golden_ap)+"\n"
                "\ndifference \t"+
                ToString(golden_ap-golden)+"\n",
                std::abs(golden_ap-golden)<1e-6);
    pContinuedFraction.push_back(tg);


    }








    result.push_back(pContinuedFraction);









    return result;




}

template MultipleTests Markov_LA_Test<double>::AuxiliarMath_Test();

}
}
