//Server Side Code
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(){
    int mySocket, clintConnt, clintNum = 0;
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
    time_t clock; //for capturing timestamp
    while (1)
    {
        //Accept call creates a new socket for the incoming connection
        clintConnt = accept(mySocket, (struct sockaddr *)NULL, NULL);
        clock = time(NULL); //Capturing time when a client hits
        clintNum++;         //Incrementing client number
        if (fork() > 0)
        { // for parent process this code will execute to serve the current client
            char timStmp[100];
            snprintf(timStmp, sizeof(timStmp), "%.24s\r", ctime(&clock));
            printf("clint number %d hit at time: %s\n", clintNum, timStmp);
            //Recieve message from the socket of the incoming connection
            recv(clintConnt, Rec_buffer, 1024, 0);
            clock = time(NULL);
            snprintf(timStmp, sizeof(timStmp), "%.24s\r", ctime(&clock));
            //Printing recieved message
            printf("Msg recieved from client number %d at time: %s\n%s\n", clintNum, timStmp, Rec_buffer);
            //Generating msg for sending
            sprintf(Send_buffer, "Client number %d your msg recieved at time %s", clintNum, timStmp);
            //Sending message to the socket of the incoming connection
            send(clintConnt, Send_buffer, 1024, 0);
            break;
        }
        else
        {
            continue; // for child process we want the while loop to run again so that it can wait for a new client.
        }
    }
    return 0;
}
