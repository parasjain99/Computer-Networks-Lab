//Submitted By Paras Jain (2018KUCP1006)
//client side code
#include <stdio.h>
// It is standard input and output library
#include <stdlib.h>
// It includes functions regarding memory allocation
#include <string.h>
// It contains string functions
#include <errno.h>
//It defines macros for reporting and retrieving error conditions through error codes
#include <unistd.h>
//It contains various constants
#include <sys/types.h> 
//It contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h>
// It defines in_addr structure
#include <sys/socket.h>
// It is for socket creation
#include <netinet/in.h>
//It contains constants and structures needed for internet domain addresses

int main()
{
    char dataReceived[1024];
    // This is basically declaring data variable. This is called packet in Network Communication, which contain data and send through.
    memset(dataReceived, '\0', sizeof(dataReceived));
    //Initialising the character array with '\0' i.e null character;
    int CreateSocket = socket(AF_INET, SOCK_STREAM, 0);
    //Since this communication is through socket, here also, we created socket.
    // AF_INET is for IPV4 address, SOCK_STREAM is for connection-oriented,it confirms that we are using TCP as a protocol in this communication, which is reliable communication, 0 telling kernel to use default protocol
    if (CreateSocket < 0)
    { // Socket function returns -ve value if it is not created
        printf("Socket not created \n");
        return 1;
    }
    struct sockaddr_in ipOfServer;
    ipOfServer.sin_family = AF_INET;   //(AF_INET) i.e for IPV4 address.
    ipOfServer.sin_port = htons(2017); //  This is the port to connect with.
    ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    // loopback address return address of server
    if (connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer)) < 0)
    {
        //connecting to server, -ve value implies unsuccessful
        printf("Connection failed due to port and ip problems\n");
        return 1;
    }
    recv(CreateSocket, dataReceived, sizeof(dataReceived), 0); //Recieving data from the server
    printf("Data received: %s", dataReceived);                 //Printing recieved data
    return 0;
}