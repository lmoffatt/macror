#ifndef AVERAGEEXPERIMENT_H
#define AVERAGEEXPERIMENT_H
#include "Markov_IO/ExperimentAverage.h"
#include "Experiment.h"
#include "Markov_IO/ABC_Operator.h"
#include "Markov_IO/Options.h"

namespace Markov_IO
{

class AverageExperiment: public ABC_Operator
{
    public:
        ///virtual copy constructors
        virtual AverageExperiment* clone()const;

         virtual AverageExperiment* create()const;

        virtual ~AverageExperiment();

        virtual Experiment run(const ABC_Experiment &x);

        static  std::string ClassName();
        virtual std::string id()const;
        virtual std::string myClass()const;

        virtual bool amIAbstract()const;


        AverageExperiment(const std::string& name, double max_f,
               double min_dt,
               double min_y,
               double min_y_dt);


        AverageExperiment();

        virtual ClassDescription GetDescription()const;

        virtual bool LoadFromDescription(const ClassDescription& classDes);

        class Options: public Markov_IO::BaseOptions
        {
        public:
        Options();
        Options(const std::string& name, double max_freq,
                double min_dt,
                double min_y,
                double min_y_dt);
        Options(const Markov_IO::ABC_Options& options);
        virtual std::string myClass()const;
        static std::string ClassName();


        };
        AverageExperiment(const std::string name, Options op);

private:
        bool valid_step(const ABC_measure_step& xs);
        std::string name_;
        double max_f_;
        double min_dt_;
        double min_y_;
        double min_y_dt_;

       };


}
#endif // AVERAGEEXPERIMENT_H
