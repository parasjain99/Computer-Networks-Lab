//Client Side Code
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    int clientSocket;
    char Send_buffer[1024], Rec_buffer[1024];
    struct sockaddr_in ipOfServer;
    //Creating the socket, arguments are: Internet domain, Stream socket, Default protocol (TCP)
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    //Configure settings of the server address struct
    ipOfServer.sin_family = AF_INET;
    //Set port number, using htons function to use proper byte order
    ipOfServer.sin_port = htons(2017);
    //Set IP address to localhost
    ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    //Set all bits of the padding field to 0
    memset(ipOfServer.sin_zero, '\0', sizeof ipOfServer.sin_zero);
    //Connect the socket to the server using the address struct
    if (connect(clientSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer)) < 0){
        //connecting to server, -ve value implies unsuccessful
        printf("Connection failed due to port and ip problems\n");
        return 1;
    }
    printf("Enter msg\n");
    gets(Send_buffer);
    // scanf("%s",Send_buffer);
    send(clientSocket, Send_buffer, 1024, 0);
    //Read the message from the server into the buffer
    recv(clientSocket, Rec_buffer, 1024, 0);
    //Print the received message
    printf("Msg from server:\n");
    puts(Rec_buffer);
    return 0;
} 