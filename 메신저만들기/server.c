#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[]){
        int serv_sock;
        int clnt_sock;

        char message[]="Hello World!";
	

        struct sockaddr_in serv_addr;
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_size;

        char *servIP_ptr;
        char servIP_arr[20];
        int servPort;
        //declare variables to contain server ip and port numbers
        char *clntIP_ptr;
        char clntIP_arr[20];
        int clntPort;
        //declare variables to contain client ip and port numbers
        if(argc != 2){
                printf("Usage : %s <port>\n", argv[0]);
                exit(1);
        }

        serv_sock = socket(PF_INET, SOCK_STREAM, 0);
        if(serv_sock == -1)
                error_handling("socket() error");

        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(atoi(argv[1]));
        //serv_addr init

        servIP_ptr = inet_ntoa(serv_addr.sin_addr);
        strcpy(servIP_arr, servIP_ptr);
        //convert to a common ip address
        servPort = serv_addr.sin_port;
        //save port number

        if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
                error_handling("bind() error");
        //bind with client
        if(listen(serv_sock, 5) == -1)
                error_handling("listen() error");
        //listen with client
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        //clnt_addr_size, clnt_sock init
        if(clnt_sock == -1)
                error_handling("accept() error");

        clntIP_ptr = inet_ntoa(clnt_addr.sin_addr);
        strcpy(clntIP_arr, clntIP_ptr);
        //after connecting with the client, convert to a common ip address
        clntPort = clnt_addr.sin_port;
        //save port number
        printf("%s\n", servIP_arr);
        printf("%d\n", servPort);
        printf("%s\n", clntIP_arr);
        printf("%d\n", clntPort);
        //output process
        write(clnt_sock, message, sizeof(message));
        close(clnt_sock);
        close(serv_sock);
        //close socket
        return 0;
}
void error_handling(char *message){
        fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
        }

