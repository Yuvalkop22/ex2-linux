#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int proc_pid;
int result2;

void handler1(int sig){
    int init_size;
    char delim[] =  "\n";
    char *ptr;
    int arr[4];
    int k = 0;
    pid_t pid;
    char buffer[256];
    signal(SIGUSR1, handler1);
   FILE *fp;
   FILE* fpServer;
   int i=0;
   char ch;
   fpServer = fopen("solution.txt", "r"); // read the result from "to_client" file  
   while((ch = fgetc(fpServer)) != EOF){
       buffer[i] = ch;
       i++;
   }
//    init_size = strlen(buffer);
//     ptr = strtok(buffer, delim);
//       while(ptr != NULL)
//       {
//         printf("%s", ptr);
//         arr[k] = atoi(ptr);
//         ptr = strtok(NULL, delim);
//         k++;
//       }
    fclose(fpServer);
   //printf("The result is: %d\n",arr[1]);
   //result2 = atoi(ptr);
}

int main(int argc, char* argv[]){
   
   char buffer[256];
   printf("client asking\n");
   signal(SIGUSR1, handler1);
   FILE *fp;
   FILE* fpServer;
   int i=0;
   char ch;
   
   //////////////////////////////////////////////////////////////////////////////////
   //Open output file and prints the arguments (client pid, var1, signal number, var2)
   proc_pid = atoi(argv[1]);
   printf("client pid is= %d\n",getpid());
   fp = fopen ("output.txt","w");
   fprintf(fp,"%d\n%s\n%s\n%s\n",getpid(), argv[2], argv[3], argv[4]);
   fclose(fp);
   kill(proc_pid,SIGUSR1);
   fpServer = fopen("solution.txt", "r"); // read the result from "to_client" file  
   while((ch = fgetc(fpServer)) != EOF){
       buffer[i] = ch;
       i++;
   }
   printf("Result = %s\n", buffer);
   sleep(1);
   //////////////////////////////////////////////////////////////////////////////////
   exit (0);

}