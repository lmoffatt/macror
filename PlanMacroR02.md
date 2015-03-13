# Plan para MacroR 0.2 y 0.3 #


## A ##
Ampliación de la funcionalidad del Modulo MarkovMol  de forma que puedan describir la mayoría de los modelos cinéticos descriptos en la literatura científica. Las funcionalidades extra son tres: i) incluir la distribución a priori de los parámetros que definen los modelos cinéticos,  ii) ampliar el rango de perturbaciones experimentales como la acción de múltiples drogas, del potencial de membrana, de la temperatura y de la tensión de la membrana y iii) modelar las interacciones alostéricas entre subunidades.

## B ##
Construcción de una librería pública de modelos cinéticos de canales a partir de la bibliografía existente.  Se implementará para ello una funcionalidad que permita ingresar con facilidad modelos cinéticos de la literatura.

## C ##
Comparación entre modelos cinéticos alternativos. Se extenderán la funcionalidades de módulos  MarkovBay de manera de  dado un modelo cinético y un conjunto de experimentos, calcule la evidencia del modelo. Esta funcionalidad aplicada a una  librería de modelos cinéticos, permitiría determinar el modelo cinético que mejor describe los resultados experimentales con mínima intervención del operador.

## D ##
Construcción de una página web que implemente un sistema de servicios que puedan ser usados por nuestros clientes. Estos servicios consistirán en análisis cinéticos de datos experimentales brindados por los clientes, de acuerdo a las necesidades de los mismos.