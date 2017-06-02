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
if(argc!=3){
printf("Usage : %s <server> <port>\n", argv[0]);
exit(0);
}


servername=argv[1];
port=atoi(argv[2]);
printf("Servername = %s, port=%d", servername,port);
sockfd= socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		perror("not valid");
		exit(1);

	}

struct hostent *server_he;
if((server_he = gethostbyname(servername)) == NULL){
	perror("error in gethostbyname");
	return 2;
	}

struct sockaddr_in serveraddr;//store the server address

bzero((char *) &serveraddr, sizeof(serveraddr));

serveraddr.sin_family = AF_INET;
bcopy((char *)server_he->h_addr,
	(char *)&serveraddr.sin_addr.s_addr,
	server_he->h_length);
serveraddr.sin_port=htons(port);

if(connect(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr))< 0){
	perror("Cannot connect to the server");
	exit(0);

}
else
	printf("Connected to the server");

//for sending the data
char *msg="GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n";
int bytes_sent;
bytes_sent=send(sockfd, msg, strlen(msg),0);


//constructing a HTTP Request(the telnet thing we did in lab1)

char request[255];
sprintf(request, "GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n",path,host);








return 0;
}
