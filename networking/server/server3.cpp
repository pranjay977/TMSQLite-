#include<stdio.h>
#include<string.h>
#include<windows.h>
int main()
{
WORD ver;
WSADATA wsaData;
int serverSocketDescriptor,clientSocketDescriptor;
struct sockaddr_in serverSocketInformation,clientSocketInformation;
int len,successCode;
ver=MAKEWORD(1,1);
WSAStarup(ver,&wsaData);
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
serverSocketInformation.sin_port=htonl(5050);
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(struct sockaddr));
if(successCode<0)
{
printf("Unable to bind socket 5050\n");
WSACleanup();
closesocket(serverSocketDescriptor);
return 0;
}


return 0;
}