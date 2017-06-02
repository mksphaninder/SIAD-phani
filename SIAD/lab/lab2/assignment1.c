#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
int main(int argc, char *argv[])
{
char *servername;
int port;
int sockfd;
//struct hostent *gethostbyname(const char *name); //to get gethostbyname
printf("Client program\n");
//checking if the argumet 3 is port number or not
if(argc!=3){
printf("Usage : %s <server> <port>\n", argv[0]);
exit(0);
}
servername=argv[1]; //declaring the servername as the first argument
port=atoi(argv[2]); //declaring the port as the second argument
printf("Servername = %s, port=%d", servername,port);
//creating socket
sockfd= socket(AF_INET, SOCK_STREAM, 0);
if(sockfd < 0){
perror("not valid");
exit(1);
}
//a host address entry
struct hostent *server_he;
if((server_he = gethostbyname(servername)) == NULL){
perror("error in gethostbyname");
return 2;
}
//connection to server declaration
struct sockaddr_in serveraddr;//store the server address
//prepare to copy: clear sockaddr_in structure
bzero((char *) &serveraddr, sizeof(serveraddr));
//set the family to AF_NET(IPv4)
serveraddr.sin_family = AF_INET;
//copy the server’ address from gethostbyname(..),
//return in struct hostent (stored in *server_he)
bcopy((char *)server_he->h_addr,
(char *)&serveraddr.sin_addr.s_addr,
server_he->h_length);
//set the port number
serveraddr.sin_port=htons(port);
//connection to server
if(connect(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr))< 0){
perror("Cannot connect to the server");
exit(0);
}
else
printf("Connected to the server");
//for sending the data
char *msg="GET / HTTP/1.0\r\n\r\n";
int bytes_sent;
bytes_sent=send(sockfd, msg, strlen(msg),0);
//recieving the data
int byte_received;
char buffer[1024];
bzero(buffer, 1024); //to make sure that the buffer is empty, buffer is just a space to store the
message and 1024 is the size of it
byte_received= recv(sockfd,buffer,1024,0);
if(byte_received<0){
error("ERROR reading from the socket");}
printf("Message recieved : %s", buffer);
return 0;
}
