#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void handler1(int signal){
    printf("Print solution: ");
}

int main(int argc, char* argv[]){
    
   int fd;
   char buffer[256];


    signal(SIGUSR1, handler1);
    //sleep(1);
    FILE *fp;
    pid_t pid;
    char buff[256];
    char buff2[256];
    
    fp = fopen ("output.txt","w");
    
    fprintf(fp,"%s\n%s\n%s\n%s\n", argv[1], argv[2], argv[3], argv[4]);


    return 0;

}