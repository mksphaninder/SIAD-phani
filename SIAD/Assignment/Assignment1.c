#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
int main(int argc, char *argv[])
{
char *servername;
int port=80;
int sockfd;
char path;
char url[100];
strcpy(url, argv[1]);
sscanf(url,"http://%[^/]/%s");

//struct hostent *gethostbyname(const char *name); //to get gethostbyname
printf("Client program\n");

if(argc!=2){
printf("Usage : %s <URL>\n", argv[0]);
exit(0);
}

servername=argv[1]; //declaring the servername as the first argument
path=argv[2]; //declaring the port as the second argument
printf("Servername = %s, port=%d", servername,port);

//creating socket
sockfd = socket(AF_INET, SOCK_STREAM, 0);
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

//HTTP Request

char request[255];

sprintf(request,"GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n",path,servername);
printf("request=%s\n",request);


char str[80];
char *host=path;
sprintf(str, "Host: %s\r\n\r\n",host);


//for sending the data

int bytes_sent;
bytes_sent=send(sockfd, request, strlen(request),0);

//recieving the data

int byte_received;
char buffer[10000];
bzero(buffer, 10000); 



byte_received= recv(sockfd,buffer,10000,0);
if(byte_received<0){
error("ERROR reading from the socket");}

//printing only the data part in buffer



char *e;
char *g;
int index;
int index1;
e = strchr(buffer, 'o');
g = strchr(buffer, 'k');
index = (int)(g - buffer);
index1 = (int)(e - buffer);
printf("index of o  %d", index);
printf("index of k %d",index1);

if((index == 13)&&(index1 == 14)){

char *ret;
ret = strstr(buffer,"\r\n\r\n");
//printf("\nThe data part of the message recieved is:\n%s\n", ret+4);

printf("Message recieved : %s", buffer);


   FILE *fptr;

   fptr = fopen("site.txt", "w");


   if(fptr == NULL)
   {
      printf("Error!");
      exit(1);
   }
   
  

   fprintf(fptr,"%s", buffer);
   fclose(fptr);

}

else{
  printf("\n The status is not 200 ok. \n");
  

}
return 0;
}

