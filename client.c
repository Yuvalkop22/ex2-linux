#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

void handler1(int sig){
    int init_size;
    char delim[] =  "\n";
    char *ptr;
    int arr[4];
    int k = 0;
    pid_t pid;
    char buffer[256];
    signal(SIGUSR1, handler1);
    //sleep(1);
   FILE *fp;
   FILE* fpServer;
   int i=0;
   char ch;
   fpServer = fopen("to_client.txt", "r"); // read the result from "to_client" file  
   while((ch = fgetc(fpServer)) != EOF){
       buffer[i] = ch;
       i++;
   }
   init_size = strlen(buffer);
    ptr = strtok(buffer, delim);
      while(ptr != NULL)
      {
        arr[k] = atoi(ptr);
        ptr = strtok(NULL, delim);
        k++;
      }
   printf("The result is: %s\n",arr[2]);
   kill(arr[1],SIGUSR1);
}
  // kill()

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
   exit (0);

}