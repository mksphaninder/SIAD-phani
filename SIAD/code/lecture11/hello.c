#include <stdio.h>
int main(void){
printf("content-Type: text/plain; charset = utf-8\n\n");
printf("hello world\n");
char username[100] ="";
char password[100] ="";
char *data = getenv("QUERY_STRING");// username
//char *data1 = getnv
sscanf(data,"name = %[^&]&password = %s",username,password);
//printf("%s",data);
if((username == "") || (password == "")){
printf("Invalid username or password");
}
else
printf("username is %s  password is %s",username,password);
return 0;
}
