//Server side code
#include <stdio.h>
// It is standard input and output library 
#include <stdlib.h>
// It includes functions regarding memory allocation
#include <string.h>
// It contains string functions
#include <errno.h> 
//It defines macros for reporting and retrieving error conditions through error codes
#include <time.h>
// It contains various functions for manipulating date and time
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

int main(){
  // This is basically declaring data variable.
  //This is called packet in Network Communication, which contain data and send through.
  char buffer[1024];
  // Client connection for file descripter of the accepted socket
  int clintListn, clintConnt = 0; //these are sockets, client listen iswelcome door, and client connect is data transfer socket
  //Creating a variable of datatype struct sockaddr_in to Provide IP address of server
  struct sockaddr_in serverAddr; //ip of server
  //socket() function creates a new socket inside kernel and returns an integer which used as socket descriptor.
  //Create the socket. The three arguments are:
  // 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case)
  clintListn = socket(AF_INET, SOCK_STREAM, 0);
  // AF_INET is for IPV4 address, SOCK_STREAM is for connection-oriented,it confirms that we are using TCP as a protocol in this communication, which is reliable communication, 0 telling kernel to use default protocol
  //Initialising all the member variables of structure ipOfServer with '0'
  memset(&serverAddr, '0', sizeof(serverAddr));
  //Configure settings of the server address struct
  //Address family = Internet, same as socket call (AF_INET) i.e for IPV4 address.
  serverAddr.sin_family = AF_INET;
  //Set IP address to localhost
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); //bind to any local address
  // Set port number, using htons function to use proper byte order
  serverAddr.sin_port = htons(2017);
  // specify port to listen on, this is basically the port number of running server
  //  Network'order'is'big-endian'
  //  Host'order'can'be'big-'or'little-endian'
  //  conversion is done using htons(), htonl():'host'to'network'short/long'

  //Bind the address struct to the socket
  //to bind the created socket to structure ipOfServer, we are calling bind() function,
  //which includes port, ip addresses as arguments.
  bind(clintListn, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

  // Listen on the socket, with 20 max connection requests queued
  //Telling willingness to accept connections,
  //the 2nd argument 20 says that maximum 20 number of clients can connect to that server.
  //So maximum 20 queue process can be handled by server.
  if (listen(clintListn, 20) == 0)
    printf("Listening\n");
  else
    printf("Error\n");

  //Accept call creates a new socket for the incoming connection
  // addr_size = sizeof serverStorage; //Extra no use
  time_t clock; //  for storing time in seconds. It is a integral value.
  while(1){
    //Now the server has started.
    //Next server waits for client request by accept() function.
    clintConnt = accept(clintListn, (struct sockaddr *)NULL, NULL);
    //Whenever successfully complets (a client hits), accept() creates the connection socket
    //returns the non-negative file descriptor of the accepted socket
    printf("Hi,Iam running server.Some Client hit me\n");
    // whenever a request from client came. It will be processed here.
    clock = time(NULL);
    //This is basically used to get the current time i.e the time at which a clint hit the server.
    //This function returns the time since 00:00:00 UTC, January 1, 1970 in seconds
    snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&clock));
    // It is storing the time data in the character array datasending

    /*---- Send message to the socket of the incoming connection ----*/
    send(clintConnt, buffer, 1024, 0);
    sleep(1);
    // accept() runs infinite loop to keep server running always.
    //But it may eat up all CPU processing, to avoid that we have written sleep(1),
    //which server went to sleep for 1 sec.
  }

  return 0;
}
