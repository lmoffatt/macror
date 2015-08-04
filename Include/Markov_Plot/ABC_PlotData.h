#ifndef ABC_PLOTDATA_H
#define ABC_PLOTDATA_H

#include <string>
#include "Markov_LA/Matrix.h"


/*!
* @namespace Markov_Plot
* @brief  Library of graphical representations of kinetic models, Experiments
 and Bayesian statistical results.
*
*/

/**
 * @file Plot.h Produces plots of the concentration of the agonist and of the
  measured or simulated current.

 */

/**
 * @file Plot.h Produces plots of the concentration of the agonist and of the
  measured or simulated current.

 */


namespace Markov_Plot
{

class ABC_PlotData
{
public:
    virtual std::string type()=0;

    virtual const Markov_LA::M_Matrix<double>& x()const=0;
    virtual const Markov_LA::M_Matrix<double>& y()const=0;




};

}

#endif // ABC_PLOTDATA_H
