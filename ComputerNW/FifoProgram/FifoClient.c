#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

int main() {
    char s[100]="";
    char s1[1000]="";
    int fd, fd1;
    printf("Waiting for server...\n");
    fd = open("fifo1", O_WRONLY);
    fd1 = open("fifo2", O_RDONLY);
    printf("Enter the file name :");
    gets(s);
    write(fd, s, strlen(s));
    while(read(fd1, s1, 1000)!=0) {
        printf("\nFile content : %s", s1);
    }
    printf("\nFile received!");
    close(fd);
    close(fd1);
}