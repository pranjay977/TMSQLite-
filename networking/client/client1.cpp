#include<stdio.h>
#include<string.h>
#include<windows.h>
int main()
{
WSADATA wsaData;
WORD ver;
struct sockaddr_in clientSocketInformation;
struct sockaddr_in serverSocketInformation;
int serverSocketDescriptor;
int clientSocketDescriptor;
int result;
char responseData[1000],requestData[1000];
int len;

ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(clientSocketDescriptor<0)
{
printf("Unable to create socket\n");
return 0;
}
clientSocketInformation.sin_family=AF_INET;
clientSocketInformation.sin_port=htons(5050);
clientSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(clientSocketDescriptor,(struct sockaddr *)&clientSocketInformation,sizeof(struct sockaddr));
strcpy(requestData,"HEY ! THINKING MACHINES");
result=send(clientSocketDescriptor,requestData,strlen(requestData)+1,0);
result=recv(clientSocketDescriptor,responseData,sizeof(responseData),0);
printf("Response data received:\n");
printf("%s\n",responseData);
closesocket(clientSocketDescriptor);
WSACleanup();
return 0;
}

