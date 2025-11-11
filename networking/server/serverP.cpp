#include<windows.h>
#include<stdio.h>
#include<string.h>
int main()
{
int serverSocketDescriptor;
int clientSocketDescriptor;
int len,successCode;
char request[100],response[100];
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
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
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
serverSocketInformation.sin_port=ntohs(5050);
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(struct sockaddr));
if(successCode<0)
{
printf("Unable to bind with socket 5050\n");
WSACleanup();
closesocket(serverSocketDescriptor);
return 0;
}
listen(serverSocketDescriptor,100);
printf("server is ready to accept request on port 5050\n");
len=sizeof(struct sockaddr);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
successCode=recv(clientSocketDescriptor,request,sizeof(request),0);
if(successCode>0)
{
printf("Request data as follows:\n");
printf("%s\n",request);
}
strcpy(response,"THANKYOU VISITING PRANJAY ZONE");
successCode=send(clientSocketDescriptor,response,strlen(response)+1,0);
if(successCode>0)
{
printf("Response data successfully sended\n");
}
closesocket(serverSocketDescriptor);
closesocket(clientSocketDescriptor);
WSACleanup();
return 0;
}