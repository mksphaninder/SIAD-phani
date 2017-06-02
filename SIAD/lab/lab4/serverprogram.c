#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
int main(int argc, char *argv[])
{

//declaring the variables
char *servername;
int port;
int serversockfd;


printf("Client program\n");
if(argc!=2){
printf("Usage : %s  <port>\n", argv[0]);
exit(0);
}


//assigning the ports
port=atoi(argv[1]);

//creation of socket: socket()
serversockfd= socket(AF_INET, SOCK_STREAM, 0);
	if(serversockfd < 0){
		perror("not valid");
		exit(1);

	}


//store the server address
struct sockaddr_in serveraddr;

bzero((char *) &serveraddr, sizeof(serveraddr));

//this is an internet address
serveraddr.sin_family = AF_INET;

//let the system figure out our IP Address
serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

//this is the port we will listen on
serveraddr.sin_port=htons(port);

int optval =1;
setsockopt(serversockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));

//binding with the server,socket
if(bind(serversockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0){
	perror("Error in binding");
        exit(3);
}

//listen to the request
int listen(int serversockfd, int backlog);

if(listen(serversockfd, 5) < 0){
	perror("Eroor on listen");
}
printf("SErver is listening ion port  %d \n",port);


//accepting a client

int childfd;
while(1){

	//client address
	struct sockaddr_in clientaddr;
	//wait to accept a connection from client
	int clientlen = sizeof(clientaddr);
	childfd = accept(serversockfd, (struct sockaddr *) &clientaddr, (socklen_t *) &clientlen);

	if(childfd <0){
		perror("Error on accept");
		exit(2);
	}
	printf("Server established connection with the %s\n",inet_ntoa(clientaddr.sin_addr));
	//create a process or thread to handle the coomunication with this new socket,continue listen on server socket for new connections



	
//recieving the data
int byte_received; //declaration part
char buffer[1024];  //declaration part
bzero(buffer, 1024); //to make sure that the buffer is empty, buffer is just a space to store th message and 1024 ois the size of it
byte_received= recv(childfd,buffer,1024,0);
if(byte_received<0){
	perror("ERROR reading from the socket");}
printf("Message recieved : %s", buffer);




//for sending the data


char *msg="Hello from server";
int bytes_sent;
bytes_sent=send(childfd, msg, strlen(msg),0);

//get inline message from user
/*char buffer[1024];
printf("Enter your message");
bzero(buffer,1024);
fgets(buffer,1024,stdin);
bytes_sent=send(childfd, msg, strlen(msg),0);


*/


}

return 0;
}
