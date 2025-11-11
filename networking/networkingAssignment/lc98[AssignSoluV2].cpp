//THIS IS SIR's SOLUTION OF LECTURE 98
//THIS IS VERSION2 IN THIS I DO LITTLE EXPERIMENT
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<iostream>
using namespace std;
typedef struct _request
{
char *mimeType;
char isClientSideTechnologyResource;
char *method;
char *resource;
}REQUEST;

int extensionEquals(const char *left,const char *right)
{
char a,b;
while(*left && *right)
{
a=*left;
b=*right;
if(a>=65 && a<=90) a+=32;
if(b>=65 && b<=90) b+=32;
if(a!=b) return 0;
left++;
right++;
}
return *left-*right;
}
char *getMIMEType(char *resource)
{
char *mimeType;
mimeType=NULL;
int len=strlen(resource);
int lastIndexOfDot=len-1;
while(lastIndexOfDot>0 && resource[lastIndexOfDot]!='.') lastIndexOfDot--;
if(lastIndexOfDot==0) return mimeType;
if(extensionEquals(resource+lastIndexOfDot+1,"html"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
if(extensionEquals(resource+lastIndexOfDot,"css"))
{
mimeType=(char *)malloc(sizeof(char)*9);
strcpy(mimeType,"text/css");
}
if(extensionEquals(resource+lastIndexOfDot,"js"))
{
mimeType=(char *)malloc(sizeof(char)*16);
strcpy(mimeType,"text/javascript");
}
return mimeType;
}
char isClientSideTechnology(char *resource)
{
return 'Y';
}
REQUEST *parseRequest(char *bytes)
{
char method[11];
char resource[100];
int i,j;
for(i=0;bytes[i]!=' ';i++) method[i]=bytes[i];
method[i]='\0';
i+=2;
printf("I: %d\n",i);
for(j=0;bytes[i]!=' ';j++,i++) resource[j]=bytes[i];
resource[j]='\0';
REQUEST *request=(REQUEST *)malloc(sizeof(REQUEST));
request->method=(char *)malloc(sizeof(char)*strlen(method)+1);
strcpy(request->method,method);
printf("METHOD :%s\n",method);
printf("RESOURCE:%s\n",resource);
if(resource[0]=='\0')
{
request->resource=NULL;
request->isClientSideTechnologyResource='Y';
request->mimeType=NULL;
}
else
{
request->resource=(char *)malloc(sizeof(char)*strlen(resource)+1);
strcpy(request->resource,resource);
request->isClientSideTechnologyResource=isClientSideTechnology(resource);
request->mimeType=getMIMEType(resource);
}
return request;
}
int main()
{
struct sockaddr_in clientSocketInformation;
struct sockaddr_in serverSocketInformation;
int result,bytesExtracted;
char g,responseBuffer[1025],requestBuffer[8193];
int clientSocketDescriptor;
int serverSocketDescriptor;
int len,length;
FILE *f;
WORD ver;
WSADATA wsaData;
string str;						//CHINKI
char responseBufferLength[11];



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
while(1)
{
printf("Server is ready to accept request at port 5050\n");
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
bytesExtracted=recv(clientSocketDescriptor,requestBuffer,8193,0);
if(bytesExtracted<0)
{

}
else  if(bytesExtracted==0)
{

}
else 
{
requestBuffer[bytesExtracted]='\0';
printf("REQUEST:%s\n\n",requestBuffer);
REQUEST *request=parseRequest(requestBuffer);
if(request->isClientSideTechnologyResource)
{
/*is request->resource=NULL look for index.html and serve
else look for index.htm and serve
else send error 404
*/
if(request->resource==NULL)
{
printf("##########RESOURCE==NULL BLOCK ENTERED##############\n"); 
f=fopen("index.html","rb");
if(f==NULL)
{
f=fopen("index.htm","rb");
if(f==NULL) 
{
char temp[500],responseBufferLength[11];
strcpy(temp,"<!DOCKTYPE HTML>");
strcat(temp,"<html lang='en'>");
strcat(temp,"<head>");
strcat(temp,"<meta charset='utf-8'>");
strcat(temp,"<title>Whatever</title>");
strcat(temp,"</head>");
strcat(temp,"<body>");
strcat(temp,"RESPONSE NOT FOUND");
strcat(temp,"</body>");
strcat(temp,"</html>");
strcpy(responseBuffer,"HTTP/1.1 200 OK\n");
strcat(responseBuffer,"Content-Type: text/html\n");
strcat(responseBuffer,"Content-Length: ");
sprintf(responseBufferLength,"%d\n",strlen(temp));
strcat(responseBuffer,responseBufferLength);
strcat(responseBuffer,"\n");
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("***RESPONSE DATA SENDED\n");
}
else
{
fseek(f,0,2); 							//MOVE POINTER TO THE END OF FILE
length=ftell(f); 						//index.htm
fseek(f,0,0);							//MOVE POINTER TO THE START OF FILE
strcpy(responseBuffer,"HTTP/1.1 200 OK\n");
strcat(responseBuffer,"Content-Type: text/html\n");
strcat(responseBuffer,"Content-Length: ");
sprintf(responseBufferLength,"%d\n",length);
strcat(responseBuffer,responseBufferLength);
strcat(responseBuffer,"keep-Alive: timeout=5, max=1000\n");
strcat(responseBuffer,"\n");
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("(index.htm) RESPONSE DATA SENDED\n");
int i=0;
while(1)
{
g=fgetc(f);
if(feof(f)) 
{
responseBuffer[i]='\0';
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("(index.htm) RESPONSE DATA SENDED\n");
break;
}
responseBuffer[i++]=g;
if(i==1024)
{
responseBuffer[i]='\0';
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("(index.htm) RESPONSE DATA SENDED\n");
i=0;
}
}
fclose(f);
}  //else block
}
else
{
fseek(f,0,2); 							//MOVE POINTER TO THE END OF FILE
length=ftell(f);						//(INDEX.HTML)
fseek(f,0,0);							//MOVE POINTER TO THE START OF FILE
strcpy(responseBuffer,"HTTP/1.1 200 OK\n");
strcat(responseBuffer,"Content-Type: text/html\n");
strcat(responseBuffer,"Content-Length: ");
char responseBufferLength[11];
sprintf(responseBufferLength,"%d\n",length);
strcat(responseBuffer,responseBufferLength);
strcat(responseBuffer,"keep-Alive: timeout=5, max=1000\n");
strcat(responseBuffer,"\n");
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
int i=0;
while(1)
{
g=fgetc(f);
if(feof(f)) 
{
responseBuffer[i]='\0';
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
break;
}
responseBuffer[i++]=g;
if(i==1024)
{
responseBuffer[i]='\0';
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
i=0;
}
}
fclose(f);
}  // else block of index.html
}  // if block of resource==NULL
else 
{
printf("RESOURCE NOT NULL#####################\n");
//IF FILE NAME IS PRESENT
f=fopen(request->resource,"rb");
char temp[400];
if(f==NULL)
{
char temp[500],responseBufferLength[11];
strcpy(temp,"<!DOCKTYPE HTML>");
strcat(temp,"<html lang='en'>");
strcat(temp,"<head>");
strcat(temp,"<meta charset='utf-8'>");
strcat(temp,"<title>Whatever</title>");
strcat(temp,"</head>");
strcat(temp,"<body>");
strcat(temp,"RESPONSE NOT FOUND");
strcat(temp,"</body>");
strcat(temp,"</html>");
strcpy(responseBuffer,"HTTP/1.1 200 OK\n");
strcat(responseBuffer,"Content-Type: text/html\n");
strcat(responseBuffer,"Content-Length: ");
sprintf(responseBufferLength,"%d\n",strlen(temp));
strcat(responseBuffer,responseBufferLength);
strcat(responseBuffer,"\n");
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("***RESPONSE DATA SENDED\n");
}
else 
{
printf("**********MENTIONED FILE FOUNDED\n");
fseek(f,0,2); 							//MOVE POINTER TO THE END OF FILE
length=ftell(f);
fseek(f,0,0);							//MOVE POINTER TO THE START OF FILE
strcpy(responseBuffer,"HTTP/1.1 200 OK\n");
strcat(responseBuffer,"Content-Type: text/html\n");
strcat(responseBuffer,"Content-Length: ");
char responseBufferLength[11];
sprintf(responseBufferLength,"%d\n",length);
strcat(responseBuffer,responseBufferLength);
strcat(responseBuffer,"keep-Alive:  timeout=5, max=1000\n");
strcat(responseBuffer,"\n");
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
int i=0;
while(1)
{
g=fgetc(f);
if(feof(f)) 
{
responseBuffer[i]='\0';
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
break;
}
responseBuffer[i++]=g;
if(i==1024)
{
responseBuffer[i]='\0';
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
i=0;
}
}
fclose(f);
}
}
}
}
}
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}