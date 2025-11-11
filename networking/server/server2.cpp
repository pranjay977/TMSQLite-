#include<stdio.h>
#include<windows.h>
#include<string.h>
int main()
{
struct sockaddr_in clientSocketInformation;
struct sockaddr_in serverSocketInformation;
int result;
char responseData[1000];
char *requestData,*accumalator;
int clientSocketDescriptor;
int serverSocketDescriptor;
int len,z,cnt,i;
char header[11];
WORD ver;
WSADATA wsaData;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
result=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(struct sockaddr));
if(result<0)
{
printf("Unable to bind socket with port 5050\n");
WSACleanup();
}
listen(serverSocketDescriptor,100);
len=sizeof(struct sockaddr);
printf("Server is ready to accept request at port 5050\n");
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept request at port 5050 \n");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
result=recv(clientSocketDescriptor,header,sizeof(header),0);
printf("Header received\n");
cnt=0;
for(i=0;header[i]!='\0' && header[i]!=' ';i++) cnt=cnt*10+(header[i]-48);
z=0;
printf("%d\n",cnt);
accumalator=(char *)malloc(sizeof(char)*cnt);
requestData=(char *)malloc(sizeof(char)*cnt);
requestData[0]='\0';
while(z<cnt)
{
printf("HELLO\n");
result=recv(clientSocketDescriptor,accumalator,cnt-z,0);
z=z+result;
strcat(requestData,accumalator);
accumalator[0]='\0';
}
requestData[z]='\0';
if(result>0)
{
printf("Request data arrive:\n");
printf("%s\n",requestData);
}
free(requestData);
free(accumalator);
strcpy(responseData,"WELCOME TO DURGA TRANSPORTATION THANKYOU FOR REGISTERING");
sprintf(header,"%-10d",strlen(responseData));
result=send(clientSocketDescriptor,header,10,0);
result=send(clientSocketDescriptor,responseData,strlen(responseData),0);
if(result>0)
{
printf("Response data sended\n");
}
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}