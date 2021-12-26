#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

void handler1(int sig){
    FILE* fd;
    FILE* fd2;
    int proc_pid;
    char buffer[256];
    char ch;
    int i = 0;
    int tmp;
    int init_size;
    char delim[] =  "\n";
    char *ptr;
    int arr[4];
    int k = 0;
    pid_t pid;
    FILE* fp1;
    int result;

    printf("Hello from the server handler: \n");
    signal(SIGUSR1, handler1);
    printf("pid=%d receives a signal %d\n",getpid(),sig);
    /////////////////////////////////////////////////////////////////////////////////////////////
    pid = fork();
    if (pid < 0){
        printf("Fork Error\n");
        exit(0);
    }
    else{
        if (pid == 0){
            fd = fopen("output.txt", "r"); //read the arguments sended by the client in "output.txt" file
            if (fd == NULL)
            {
                perror("Error while opening the file.\n");
                exit(EXIT_FAILURE);
            }
            while((ch = fgetc(fd)) != EOF){
                buffer[i] = ch;
                i++;
            }
            printf("file is ok!\n");
            /////////////////////////////////////////////////////////////////////////////////////////////
            init_size = strlen(buffer);
            ptr = strtok(buffer, delim);
            while(ptr != NULL)
            {
                arr[k] = atoi(ptr);
                ptr = strtok(NULL, delim);
                k++;
            }
            proc_pid = arr[0];
            printf("client pid = %d\n", proc_pid);
            /////////////////////////////////////////////////////////////////////////////////////////////
            //arr[0] = client pid 
            //arr[1] = num1
            //arr[2] = func -> 1 | 2 | 3 | 4
            //arr[3] = num2
            if(arr[2] == 1){ 
                result = arr[1] + arr[3];
            }
            if(arr[2] == 2){ 
                result = arr[1] - arr[3];
            }

            if(arr[2] == 3){
                if(arr[3] == 0){
                    fd2= fopen("solution.txt","w");
                    if(fd2<0){
                        perror("cant open: com_file");
                        exit(0);
                    }
                    fprintf(fd2,"%s", "Cannot-divide-by-zero");
                    kill(proc_pid,SIGUSR1);
                    exit(0);
                }
                else{
                    result = arr[1] / arr[3];
                }
            }
            if(arr[2] == 4){
                result = arr[1] * arr[3];
            }
            printf("result = %d\n",result);
            fp1 = fopen("solution.txt","w");
            if( fp1<0 ){ 
                perror("cant open: com_file"); 
                exit(0);
            }
            fprintf(fp1,"%d\n",result);            
            /////////////////////////////////////////////////////////////////////////////////////////////
            fclose(fp1);
            kill(proc_pid,SIGUSR1);
            printf("Printed the result and kill to client\n");
            exit(0);
        }
    } 
}


 int main(int argc, char* argv[]){
    signal(SIGUSR1, handler1);
    printf("Getting to sleep: \n");
    printf("Server pid: %d\n", getpid());
    sleep(9999);
    return 0;
}
