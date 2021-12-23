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
    FILE* fpServer;
    pid_t pid;
    char buff[256];
    char buff2[256];
    int i=0;
    char ch;


    fp = fopen ("output.txt","w");
    
    fprintf(fp,"%s\n%s\n%s\n%s\n", argv[1], argv[2], argv[3], argv[4]);

     fpServer = fopen("to_client.txt", "r"); // read mode
    while((ch = fgetc(fpServer)) != EOF){
      buffer[i] = ch;
      i++;
   }
   printf("The result is: %s\n",buffer);
//    for(int j = 0; j < i; j++){
//        printf("%c", buffer[j]);
//    }
   
    return 0;

}