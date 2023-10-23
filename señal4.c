#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void sigusr1_handler(int signum) {
   //printf("Recibida la señal[%d] en el proceso con PID %d\n", getpid(),getppid());
}

int main() {
    pid_t hijo[3], root;
    int i, j;

    // Establecer controlador de señal personalizado para SIGUSR1
    signal(SIGUSR1, sigusr1_handler);
       
    root = getpid();// Esta es la sección del proceso padre "A"
    for (i = 0; i < 3; i++) {
        hijo[i] = fork();
        if (!hijo[i]) break;
       
    }
    
    if (root == getpid()) {
        printf("Soy Padre 'A' con PID %d\n", getpid());
        usleep(1000);
        kill(hijo[i], SIGUSR1);
        for (j = 0; j < 3; j++) wait(NULL);
    }
    else {// Esta es la sección de los procesos hijos.

        if (i == 2) {// Esta sección pertenece al tercer hijo (i == 2).
                pid_t nietoG = fork();
                if (nietoG == 0) { // crear nieto G
                    printf("soy G  [%d] [%d], padre->[%d]\n", i, getpid(), getppid());
                    kill(getppid(), SIGUSR1); // enviar señal  
                } 
                else {
                    printf("soy D1 [%d] [%d], padre->[%d]\n", i, getpid(), getppid());
                    usleep(1000);// esperar 1 segundo
                    kill(nietoG, SIGUSR1);// enviar señal
                    wait(NULL);// esperar a que el nieto termine
                    printf("soy D2 [%d] [%d], padre->[%d]\n", i, getpid(), getppid());
                    kill(getppid(), SIGUSR1);// enviar señal
                    kill(hijo[1],SIGUSR1);// enviar señal al hermano del proceso actual
                    wait(NULL);// esperar a que el hermano termine
                    usleep(1000);//
                }
         
            
        }else  if(i==1){   // Esta sección pertenece al segundo hijo (i == 1).
             usleep(1000);   //      
            pid_t nietoF = fork();   
            if(nietoF==0){// crear nieto F
                kill(getppid(), SIGUSR1);   
                    pid_t bisnietoH = fork();
                    if(bisnietoH==0){// crear bisnieto H
                        kill(getppid(), SIGUSR1);
                            pid_t tataranietoI = fork();
                            if(tataranietoI==0){// crear tataranieto I
                                printf("soy I  [%d] [%d], padre->[%d]\n", i, getpid(), getppid());
                                kill(getppid(), SIGUSR1);// enviar señal
                            }
                            else{ 
                                printf("soy H1 [%d] [%d], padre->[%d]\n", i, getpid(), getppid());
                                    usleep(1000);// esperar 1 segundo
                                    kill(tataranietoI, SIGUSR1);// enviar señal
                                    wait(NULL);// esperar a que el tataranieto termine
                                    printf("soy H2 [%d] [%d], padre->[%d]\n", i, getpid(), getppid());
                                    kill(getppid(), SIGUSR1);// enviar señal
                                    wait(NULL);// esperar a que el padre termine

                            }//cerro tataranietoI
                    }
                    else{
                         printf("soy F1 [%d] [%d], padre->[%d]\n", i, getpid(), getppid());
                         usleep(1000);// esperar 1 segundo
                         kill(bisnietoH, SIGUSR1);// enviar señal
                         wait(NULL);// esperar a que el bisnieto termine
                         printf("soy F2 [%d] [%d], padre->[%d]\n", i, getpid(), getppid());
                         kill(getppid(), SIGUSR1);// enviar señal
                        wait(NULL);//
                        usleep(1000);//
                    }//cerro bisnietoH
            }
            else{
                printf("soy C1 [%d] [%d], padre->[%d]\n", i, getpid(), getppid());
                usleep(1000);// esperar 1 segundo
                kill(nietoF, SIGUSR1);// enviar señal
                wait(NULL);// esperar a que el nieto termine
                printf("soy C2 [%d] [%d], padre->[%d]\n", i, getpid(), getppid());
                usleep(1000);//
                kill(hijo[0], SIGUSR1);// enviar señal al hermano del proceso actual
                wait(NULL);// esperar a que el hermano termine
               
            }//cerro nietoF
            
        }
        else if(i==0){// Esta sección pertenece al primer hijo (i == 0).
         usleep(10000);// esperar 1 segundo
            pid_t nietoE = fork();
            if(nietoE==0){// crear nieto E
                printf("soy E  [%d] [%d], padre->[%d]\n", i, getpid(), getppid());
               usleep(100000);// esperar 1 segundo
                kill(getppid(), SIGUSR1);// enviar señal
                wait(NULL);// esperar a que el padre termine
            }
            else{
                printf("soy B1 [%d] [%d], padre->[%d]\n", i, getpid(), getppid());
                usleep(1000);// esperar 1 segundo
                kill(nietoE, SIGUSR1);// enviar señal
                wait(NULL);// esperar a que el nieto termine
                printf("soy B2 [%d] [%d], padre->[%d]\n", i, getpid(), getppid());
                usleep(10000);// esperar 1 segundo
                kill(getppid(), SIGUSR1);// enviar señal
                wait(NULL);// esperar a que el padre termine
                usleep(1000);// esperar 1 segundo
                                           
            }
        } 
    }
    return EXIT_SUCCESS;// terminar el proceso
}