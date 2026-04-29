#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
    int fd[2]; // 0-> read 1-> write
    int pid;
    char write_msg[] = "Hello from this side! ";
    char read_msg[1024] ;

    pipe(fd);
    pid = fork();

    if(pid < 0){
        perror("fork error!");
        return 1;
    }
    // parent -> write & Child -> read
    if(pid >0){
        printf("Parent process \n");
        printf("Sent : %s\n\n",write_msg);
        close(fd[0]);
        write(fd[1],write_msg,strlen(write_msg)+1);
        close(fd[1]);
    }else{
        printf("Child process \n");
        close(fd[1]);
        read(fd[0],read_msg,sizeof(read_msg));
        printf("child recieved : %s\n" ,read_msg);
        close(fd[0]);
    }
    return 0;
}
