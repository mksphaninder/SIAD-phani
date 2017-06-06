#include <stdio.h>
int main(void){

	printf("Content-Type: text/plain; charset = utf-8\n\n");
	char *data = getenv("QUERY_STRING");// username
	//printf("data=%s\n",data );
	
	printf("hello world\n");
	char username[100] ="";
	char password[100] ="";
	char us[100] = "krishna";
	char ps[100] = "krishna";
	int ret;
	int ret2;
	sscanf(data,"name = %[^&]&password = %s",username,password);
	ret = strncmp(username,us,7);
	ret2 = strncmp(password,ps,7);
	if (ret==0 && ret2==0)
	{
		printf("\n hello %s",username);
	}
	else{
		printf("Acess denied");
	}
		
return 0;
}
