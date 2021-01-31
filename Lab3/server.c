//Server Side Code
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h> // It defines in_addr structure
#include <sys/socket.h> // It is for socket creation
#include <netinet/in.h> //It contains constants and structures needed for internet domain addresses

int main(){
    int mySocket, clintConnt;
    char Send_buffer[1024], Rec_buffer[1024];
    struct sockaddr_in ipOfServer;
    //Creating the socket, arguments are: Internet domain, Stream socket, Default protocol (TCP)
    mySocket = socket(AF_INET, SOCK_STREAM, 0);
    //Configure settings of the server address struct
    ipOfServer.sin_family = AF_INET;
    // Set port number, using htons function to use proper byte order
    ipOfServer.sin_port = htons(2017);
    ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY); //bind to any local address
    // Set all bits of the padding field to 0
    memset(ipOfServer.sin_zero, '\0', sizeof ipOfServer.sin_zero);
    // Bind the address struct to the socket
    bind(mySocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer));
    //Listen on the socket, with 20 max connection requests queued
    listen(mySocket, 20);
    while (1){
        //Accept call creates a new socket for the incoming connection
        clintConnt = accept(mySocket, (struct sockaddr *)NULL, NULL);
        //Recieve message from the socket of the incoming connection
        recv(clintConnt, Rec_buffer, 1024, 0);
        //Printing recieved message
        printf("Msg recieved from client: %s\n", Rec_buffer);
        //Generating msg for sending
        strcpy(Send_buffer, "This is eco msg from server:\n");
        //Concatinating the recieved msg to the sending buffer
        strcat(Send_buffer, Rec_buffer);
        //Sending message to the socket of the incoming connection
        send(clintConnt, Send_buffer, 1024, 0);
    }
    return 0;
}