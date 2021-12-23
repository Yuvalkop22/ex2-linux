#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int result = 0;
void handler1(int sig){
    FILE* fd;
    FILE* fd2;
    char buffer[256];
    char ch;
    int i = 0;
   // int pid; 
    int tmp;
    int init_size;
    char delim[] =  "\n";
    char *ptr;
    int arr[4];
    int k = 0;
    pid_t pid;
    signal(SIGUSR1, handler1);
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
            /////////////////////////////////////////////////////////////////////////////////////////////
            init_size = strlen(buffer);
            ptr = strtok(buffer, delim);
            while(ptr != NULL)
            {
                arr[k] = atoi(ptr);
                ptr = strtok(NULL, delim);
                k++;
            }
            /////////////////////////////////////////////////////////////////////////////////////////////
            if(arr[2] == 1){ 
                result = arr[1] + arr[3];
            }
            if(arr[2] == 2){ 
                result = arr[1] - arr[3];
            }

            if(arr[2] == 3){
                if(arr[3] == 0){
                    fd2= fopen("to_client.txt","w");
                    if(fd2<0){
                        perror("cant open: com_file");
                        exit(0);
                    }
                    fprintf(fd2,"%s", "Cannot divide by zero");
                    exit(-1);
                }else{
                    result = arr[1] / arr[3];
                }
            }
            if(arr[2] == 4){
                result = arr[1] * arr[3];
            }            
            /////////////////////////////////////////////////////////////////////////////////////////////
            kill(arr[0],SIGUSR1);
        }
    } 
}


 int main(int argc, char* argv[]){
    signal(SIGUSR1, handler1);
    printf("result = %d",result);
    FILE* fd2;
    fd2= fopen("to_client.txt","w");
        if( fd2<0 )
        { 
            perror("cant open: com_file"); 
            exit(0);
        }
    fprintf(fd2,"%s\n%d",argv[1],result);
    sleep(5);
    return 0;
}