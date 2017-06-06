/*decleration of libraries*/
#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>

int main(int argc, char *argv[]){ 
	//arg c stores the number of arguments.
	//parse the hostname and path from input - URL format:
	//constructing a string from substrings.
	char host_name[1000],path_name[1000],dtm[1000];
	int port=80;
	int sockfd;
	int byte_received;
	int remaining_bytes;
	//int total_len = 0;
	strcpy(dtm,argv[1]);
	
	//checking if the argument 2 is URL or not.
	if(argc!=2){
		printf("Usage : %s <url>\n", argv[1]);
		exit(0);
	}
	sscanf(dtm,"http://%[^/]/%s",host_name,path_name);//Spliting ths string into hostname and path name.
	printf("\n\nhostname from the given URLis %s\n", host_name);
	printf("\n\nand pathname is %s\n", path_name);
	printf("Client program\n");
	printf("\nServername = %s, port=%d", host_name,port);
	//creating socket
	sockfd= socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		perror("not valid");
		exit(1);
	}
	//To get socket address of server.
	struct hostent *server_he;
	if((server_he = gethostbyname(host_name)) == NULL){
	//Returns pointer if sucess else, sends null.
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
		printf("Connected to the server\n");
	//HTTP Request
	char request[255];
	sprintf(request,"GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n",path_name,host_name); 
	char str[80];
	char *host=path_name;
	sprintf(str, "Host: %s\r\n\r\n",host);
	//for sending the data
	int bytes_sent;
	bytes_sent=send(sockfd, request, strlen(request),0);
	//recieving the data
	
	char buffer[10000];//increalsed the size to store large data.
	bzero(buffer, 10000); //Clearing the garbage data.
	byte_received= recv(sockfd,buffer,10000,0);
	
	if(byte_received<0){
		error("ERROR reading from the socket");
	}
		//calculating the index of 200 ok to ensure that the status is 200 OK
	
	char *ret;// To store the address of end of header.
	//Since we don't need the header in the file.
	ret = strstr(buffer,"\r\n\r\n");// used for searching for first occurence of the substring in haystack
	char *search;
	search = strstr(buffer,"200 OK");
	printf("%s",search);
	
	if(search){
		  	//printing only the data part in buffer
		  printf("\nThe data part of the message recieved is:\n%s\n", ret+4);// excluding the \r\n\r\n part.
		  	//getting the filename for the text file. from the path name.
		  const char search1 = '/';// as it starts from '/'
		  char *filename;//storing the name of file
		  filename = strrchr(path_name, search1);
		  //remaining bytes has the size of the size of the data part.
		  const char* getFileNameFromPath(char* fl)
		  {
		  //int i;
		  	for(size_t i = strlen(fl) - 1; i>=0; i-- )
		  		{
		  			if(fl[i] == '/')
		  			{
		  				return &path_name[i+1];
		  			}
		  		}
		  		printf("%s",fl);
		  if(filename != NULL){
		  	  
			  byte_received= recv(sockfd,buffer,10000,0);
			  FILE *fptr = fopen(filename+1, "w+");//excluding the the first '/'
			  if(fptr == NULL)
			  {
			        printf("\nfile opening error\n");
			        exit(1);
		  	  }
		  	  remaining_bytes = byte_received-((ret-buffer)+4);
			  fwrite(ret+4, remaining_bytes,1,fptr);// Excluding \r\n\r part.
			  
		  		while(byte_received = recv(sockfd,buffer,10000,0) != 0) {
			   		fwrite(buffer,byte_received,1,fptr);
		 	 }
		  fclose(fptr);
	  	  }
	  	  
	  	  else{
		  	//writing the contents into the file with filename as index.html
		  FILE *fptr1; 
		 fptr1 =fopen("index.html", "w+");
		  //int remaining_bytes = byte_received-((ret-buffer)+4);
		  if(fptr1 == NULL)
			  {
			        printf("\nfile opening error\n");
			        exit(1);
		  }
		  	
		  fwrite(ret+4, remaining_bytes,1,fptr1);
		  while(byte_received = recv(sockfd,buffer,10000,0) != 0) {

			   fwrite(buffer,byte_received,1,fptr1);
		  	}
		  fclose(fptr1);
		  }
	}
	}
	else{
			//printing the entire buffer as the status is not 200 OK
		printf("\nThe message recieved is: %s", buffer);
		printf("\n\n\n\nThe status is not 200 OK, Bye!!! =)\n\n");
		exit(1);
		
	}
	return 0;
}
