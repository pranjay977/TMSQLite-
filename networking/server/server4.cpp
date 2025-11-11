#include<windows.h>
#include<stdio.h>
#include<string.h>
int main()
{
WSADATA wsaData;
WORD ver;
int clientSocketDescriptor,serverSocketDescriptor;
int len,successCode;
char request[1000],response[1000],header[100];
struct sockaddr_in serverSocketInformation,clientSocketInformation;
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
printf("Unable to bind socket 5050\n");
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,100);
len=sizeof(struct sockaddr);
printf("Server is ready to accept request on port 5050\n");
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept request on port 5050\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
successCode=recv(clientSocketDescriptor,request,sizeof(request),0);
if(successCode>0)
{
printf("Request arrive ....\n");
printf("%s\n",request);
printf("REQUEST SENDED\n");
}
strcpy(response,"<!DOCKTYPE HTML>");
strcat(response,"<html lang='en'>");
strcat(response,"<head>");
strcat(response,"<meta charset='utf-8'>");
strcat(response,"<title>Whatever</title>");
strcat(response,"</head>");
strcat(response,"<body>");
strcat(response,"<h1>Welcome to thinking machines</h1>");
strcat(response,"</body>");
strcat(response,"</html>");

strcpy(header,"HTTP/1.1 200 OK\n");
strcat(header,"Content-Type: text/html\n");
strcat(header,"Content-Length: ");
char responseLength[11];
sprintf(responseLength,"%d\n",strlen(response)+1);
strcat(header,responseLength);
strcat(header,"\n");
successCode=send(clientSocketDescriptor,header,strlen(header)+1,0);
successCode=send(clientSocketDescriptor,response,strlen(response)+1,0);
if(successCode<0)
{
printf("Unable to send response data\n");
WSACleanup();
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
return 0;
}
printf("\nResponse sended\n");
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}