
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<iostream>
using namespace std;
void send404(string &str)
{
str="THIS SIDE IS NOT PRESENT";
return;

}
int main()
{
WSADATA wsaData;
WORD ver;
string errorMessage;
char g;
int clientSocketDescriptor,serverSocketDescriptor;
int len,successCode;
char response[1000],header[1000];
char request[1000];
string str;
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
serverSocketInformation.sin_port=htons(5050);
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(struct sockaddr));
if(successCode<0)
{
printf("Unable to bind to port 5050\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,100);
printf("Server is ready to accept request on port 5050\n");
len=sizeof(struct sockaddr);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketDescriptor,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept request\n");
closesocket(serverSocketDescriptor);
WSACleanup();
 return 0;
}
string Request;
//DONE DONE DONE 
successCode=recv(clientSocketDescriptor,(char *)Request.c_str(),1000,0);
if(successCode>0)
{
cout<<"Request Data:"<<Request<<endl;
//MAIN STORY STARTED FROM HERE
//REQUEST RECEIVE TIME VALIDATIONS VALA POINT I DON'T THINK
if(request[4]=='/')
{
printf("CHILLO\n");
FILE *f;
f=fopen("index.html","r");
if(f==NULL)
{
printf("loop enter\n");
f=fopen("index.htm","r");
if(f==NULL) 
{
printf("error message\n");
printf("SOCKKKKK\n");
//errorMessage="ERROR";
strcpy(response,"<!DOCKTYPE HTML>");
strcat(response,"<html lang='en'>");
strcat(response,"<head>");
strcat(response,"<meta charset='utf-8'>");
strcat(response,"<title>Whatever</title>");
strcat(response,"</head>");
strcat(response,"<body>");
printf("DSFSDFSDFSDFS\n");
strcat(response,"ERROR");
strcat(response,"</body>");
strcat(response,"</html>");
printf("RESPONSE FOR ERROR:\n");
printf("%s\n",response);
}
else
{
while(1)
{
printf("HEEEEE\n");
g=fgetc(f);
if(feof(f)) break;
str+=g;
while(1)
{
printf("HE\n");
g=fgetc(f);
if(feof(f)) break;
str+=g;
}
}
strcpy(response,str.c_str());
}
}
else
{
while(1)
{
printf("FDFDFFEEEEE\n");
g=fgetc(f);
printf("%c\n",g);
if(feof(f)) break;
str+=g;
while(1)
{
printf("sfdffs\n");
g=fgetc(f);
printf("%c\n",g);
if(feof(f)) break;
str+=g;
}
}
strcpy(response,str.c_str());
}
}
else 
{
//SOMETHING TO DO 
}
//HEADER TO SET
int k=0;
char mimeType[14];
strcpy(header,"HTTP/1.1 200 OK\n");
strcat(header,"Content-Type: ");
int i,si=Request.find("Accept: ");
for(i=si;Request[i]!=',';i++,k++)
{
mimeType[k]=Request[i];
}
strcat(header,mimeType);
strcat(header,"\n");
strcat(header,"Content-Length: ");
char responseLength[11];
printf(responseLength,"%d\n",strlen(response)+1);
strcat(header,responseLength);
strcat(header,"\n");

successCode=send(clientSocketDescriptor,header,strlen(header)+1,0);
successCode=send(clientSocketDescriptor,response,strlen(response)+1,0);
if(successCode>0)
{
printf("Response sended\n");
}
}
return 0;
}