# Introduction #

A. Primer etapa.
A1. Ampliación de la funcionalidad de MarkolMol.
Se diseñará una clase abstracta que represente a un modelo cinético generalizado, del cuál se podrá extraer una realización particular del mismo, tanto sea aleatoriamente como a partir de la especificación del conjunto de parámetros. Se construirá una clase concreta que la implementa a través de una distribución normal multivariada de los parámetros cinéticos.

A2. Optimización de la interfase gráfica de modo aumentar la comodidad del  usuario. Diseño del servicio web.


B. Segunda etapa.
B1 Ampliación de la funcionalidad de MarkovMol 2
Se re-definirá la clase base de los modelos cinéticos de forma que incorpore las perturbaciones experimentales normalmente encontradas en la literatura: múltiples agonistas y antagonistas, bloqueantes, potencial de membrana, tensión de la membrana y temperatura.
B2. Implementación de cálculos en la nube.


C. Tercera etapa
C1 Construcción del módulo MarkovAllosteric
Se construirá MarkovAllosteric, un modulo que describe e implementa los mecanismos moleculares alostéricos. Estará compuesto por clases que describan los movimientos moleculares y el acoplamiento entre los mismos.
C2 Lanzamiento de Macro-R 0.2 beta
Macro-R 0.2 incluira las nuevas funcionalidades de MarkovMol


D. Cuarta etapa
D1. Diseño de MarkovChannelLibrary
Se diseñará un a biblioteca actualizada de los modelos cinéticos publicados en la literatura. Para ello se desarrollarán herramientas que faciliten la extracción de información.

E. Quinta etapa
E1 Lanzamiento de Macro-R 0.2 release.
Se trabajará en todas las fallas detectadas en Macro-R beta.
E2 Ampliación de MarkovBay
Se ampliarán la funcionalidad del módulo MarkovBay de forma que pueda calcular la evidencia Bayesiana de un modelo estadístico aplicado a un set de datos experimentales. También se incorporará una función que busque entre todos los modelos cinéticos aquel que tenga la mayor evidencia Bayesiana.

F. Sexta etapa
F1 Lanzamiento de Macro-R 0.3 beta, el cual incluye todas las funcionalidades anteriormente descriptas.
F2 Lanzamiento de Macro-R 0.3 release concluye el proyecto.