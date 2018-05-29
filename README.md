#Tarea2-SO
Se solicita generar un proceso padre, en el lenguaje C, que realice las siguientes acciones:

1) Creará cuatro hijos: Cada uno de ellos implementa una función de ordenamiento Quick Sort a un conjunto
de datos aleatorios. Luego debe esperar un tiempo aleatorio entre 30 y 60 segundos antes de terminar.

2) El padre luego espera a que cada hijo termine y recién obtendrá de salida de cada hijo los datos para
desplegarlos por consola.

3) Los datos serán 15 enteros aleatorios entre 1 y 1000.

4) La comunicación entre padre e hijos se debe implementar de dos formas: mediante *pipes* y mediante *memoria*
*compartida*.

#Sobre la compilación y ejecución de la tarea

Para compilar los archivos se debe escribir en consola *make*, el cual generará dos archivos ejecutables:
*elo322_tarea2_pipes.out* y *elo322_tarea2_shm.out* los cuales corresponden a ambas implementaciones pedidas.
