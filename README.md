#Taller práctico II - Secuencia de señales
marcel diaz granados robayo   
universidad del magdalena

El proceso consiste en un conjunto de operaciones que por su complejidad se han decidido implementar en procesos hijos independientes. Cada proceso debe ser aplicado en un orden especifico, por lo que, en su conjunto, la secuencia es:


![Captura de pantalla 2023-10-17 a la(s) 12 10 05 a m](https://github.com/marceldgr/ejercicio-de-se-ales/assets/100010339/705e7cc2-d7f4-48b5-a809-8b1663409d44)


El programa deberá imprimir la cadena
“Proceso %d padre [%d]” (%d es estimado con getpid() y con getppid()), como resultado de la emulación del procesamiento de los datos que debe realizar cada proceso.
El orden de impresión de la salida debe ser:
a-d-g-d-c-f-h-i-h-f-c-b-e-b-a
