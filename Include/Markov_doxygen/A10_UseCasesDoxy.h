#ifndef A10_USECASESDOXY_H
#define A10_USECASESDOXY_H

/**
  @page use_cases_page Use Cases

  Is MacroR usefull for me? This is the question we try to answer in this
section. We answer by analogy, by listing situations where MacroR is usefull
indeed.\n\n

The purpose of MacroR is to provide with statistically sound Molecular Kinetics
analysis.\n\n

The core of MacroR is its unique ability of obtaining a good approximation to
the Likelihood function of Kinetics Models on Real Electrophysiology
experimental data. The Likelihood function allow us to Optimize the Parameters
of a Kinetic Model and by using the Bayes Theorem we can estimate
the error rate of the parameters. Moreover,  We can even consider all the
possible values of those parameters and irrespective of the actual value of them
compare alternative models.\n\n

As other applications MacroR is able to simulate a random samples of an ion
channel preparation.\n\n

So, what are scenarios where MacroR might be usefull? \n\n

Here is a sample list:\n\n

- Use Case 1: model_simulation_use_case_page "Model Simulation". You want to
find out how a populations of channels that follow a specific kinetic model
 might behave after they are exposed to a given set of experimental conditions.

- Use Case 2: model_likelihood_use_case_page "Model Likelihood".
You have one or a series of experimental results, you suspect that the response
is due to a channel that follow strictely a given kinetic model. You want to
find out the likelihood that the experimental results were produced by exactly
the proposed kinetic model, fixing all kinetic parameters and fitting the number
of channels and the noise of the experimental measure.

- Use Case 3: model_optimization_use_case_page "Model Optimization".
You have one or a series of experimental results, you suspect that the response
is due to a channel that follow a given kinetic model, but you do not know the
exact parameters. You want to find out which are the kinetic
parameters that maximize the likelihood of the data, trusting that the kinetic
scheme is right.

- Use Case 4: model_comparison_use_case_page "Model Selection".
You have experimental results that come from an homogeneous population of ion
channels, but you are not sure which is the kinetic model that describe
adequately describe it. You want to find out among those several kinetic models,
 which one is more likely to describe the data.

- Use Case 5: model_adjustment_use_case_page "Model Adjustment".
You have experimental results from an homogeneous population of an ion channel
that is very similar to one that is well known. You do not have enough
information to a complete determination of all the parameters of the model but
you do know that its behavior differs from the established model. You want to
find out which is the most likely model that fits your data.

If you think of a use case that might be solved by MacroR, please describe it in
the following page.



*/



#endif // A10_USECASESDOXY_H
