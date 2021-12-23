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
   
   char buffer[256];
   signal(SIGUSR1, handler1);
   //sleep(1);
   FILE *fp;
   FILE* fpServer;
   int i=0;
   char ch;
   
   //////////////////////////////////////////////////////////////////////////////////
   //Open output file and prints the arguments (client pid, var1, signal number, var2)
   fp = fopen ("output.txt","w");
   fprintf(fp,"%s\n%s\n%s\n%s\n", argv[1], argv[2], argv[3], argv[4]);
   //////////////////////////////////////////////////////////////////////////////////
    fpServer = fopen("to_client.txt", "r"); // read the result from "to_client" file  
    while((ch = fgetc(fpServer)) != EOF){
      buffer[i] = ch;
      i++;
   }
   printf("The result is: %s\n",buffer); 
   //////////////////////////////////////////////////////////////////////////////////
   exit (0);

}