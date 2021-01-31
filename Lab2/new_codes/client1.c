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

int main(){
  char buffer[1024];
  // This is basically declaring data variable. This is called packet in Network Communication, which contain data and send through.
  int clientSocket;
  struct sockaddr_in serverAddr; //ip of server
  // socklen_t addr_size; //no need

  // Create the socket. The three arguments are: 
  //1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case)
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  //Since this communication is through socket, here also, we created socket.
  // AF_INET indicates that the underlying network is IPV4 address, SOCK_STREAM is for connection-oriented,it confirms that we are using TCP as a protocol in this communication, which is reliable communication, 0 telling kernel to use default protocol
  
  //Configure settings of the server address struct
  // Address family = Internet
  serverAddr.sin_family = AF_INET; //(AF_INET) i.e for IPV4 address.
  //Set port number, using htons function to use proper byte order
  serverAddr.sin_port = htons(2017); //  This is the port to connect with (of server)
  // Set IP address to localhost
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // loopback address return address of server
  //Set all bits of the padding field to 0
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
  //Connect the socket to the server using the address struct
  // addr_size = sizeof serverAddr; //no need
  if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof (serverAddr))<0){
    //Establishes TCP connection with the server, -ve value implies unsuccessful
    printf("Connection failed due to port and ip problems\n");
    return 1;
  } 

  //Read the message from the server into the buffer
  recv(clientSocket, buffer, 1024, 0);

  //Print the received message
  printf("Data received: %s",buffer);   

  return 0;
} 