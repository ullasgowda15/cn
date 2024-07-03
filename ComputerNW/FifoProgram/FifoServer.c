#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

int main() {
    char fname[25]="";
    char fileContent[100]="";
    int fd, fd1, fd2;

    mkfifo("fifo1", 0600);
    mkfifo("fifo2", 0600);
    printf("Server is online!");
    fd1=open("fifo2", O_WRONLY);
    read(fd, fname, 25);
    fd2=open(fname, O_RDONLY);
    while(read(fd2, fileContent, 100)!=0) {
        write(fd1, fileContent, strlen(fileContent));
        if(fd2 < 0) {
            write(fd1, "File not found", 15);
            exit(1);
        }
    }
    printf("Server: Transfer completed.");
    close(fd);
    close(fd1);
    close(fd2);
}