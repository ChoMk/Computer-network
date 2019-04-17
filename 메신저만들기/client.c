#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[]){
        int sock;


        struct sockaddr_in serv_addr;

        int recv_cnt;//Size of the string received from the socket
        char message[BUF_SIZE];//Declare strings for buffer
        FILE *fp;//Declare File Variables
        fp = fopen("12131605.txt","w");//file open
        if(fp == NULL){
                printf("fopen fail\n");
                exit(1);
        }//fopen error check

        if(argc != 3){
                printf("Usage : %s <IP> <port>\n", argv[0]);
                exit(1);
        }
        sock = socket(PF_INET, SOCK_STREAM, 0);//declare socket
        if(sock == -1)
                error_handling("socket() error");
        //socket erro check
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
        serv_addr.sin_port = htons(atoi(argv[2]));
        //Initialization for sockets

        if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
                error_handling("connect() error!");//connect error check

        while(1){
                recv_cnt = read(sock, message, BUF_SIZE-1);//Passing a string from the socket to the message

                if(recv_cnt == -1)
                        error_handling("read() erro!");//read error check
                if(recv_cnt == 0)//Escape the wile door if the size of the string from the socket is zero.
                        break;
                fprintf(fp,"%s", message);//Saving a read string to a text file because the size of the string from the socket is not zero


        }
        close(sock);//close socket
        return 0;
}

void error_handling(char *message){
        fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
}
