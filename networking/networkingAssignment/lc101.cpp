//THIS CODE IS FOR LECTURE 101 (date 12.10.24)
//ASSIGNMENT REGARDING THAT IMAGE ON WEBSITE
//READING LOOP CHANGED FROM fgetc TO fread
//NEW MIME TYPE ALSO ADDED 
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
if(extensionEquals(resource+lastIndexOfDot+1,"jpg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpeg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"png"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"image/png");
}
if(extensionEquals(resource+lastIndexOfDot+1,"ico"))
{
mimeType=(char *)malloc(sizeof(char)*13);
strcpy(mimeType,"image/x-icon");
}
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
for(j=0;bytes[i]!=' ';j++,i++) resource[j]=bytes[i];
resource[j]='\0';
printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! resource :%s\n",resource);
REQUEST *request=(REQUEST *)malloc(sizeof(REQUEST));
request->method=(char *)malloc(sizeof(char)*strlen(method)+1);
strcpy(request->method,method);
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
int rc;                                                         //THIS IS CHANGE 2
char g,responseBuffer[1024],requestBuffer[8192];               //DECREASE BOTH BUFFER SIZE BY 1 THIS IS CHANGE 3
int clientSocketDescriptor;
int serverSocketDescriptor;
int len,length;
int i,j;
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
bytesExtracted=recv(clientSocketDescriptor,requestBuffer,8192,0);
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
f=fopen("index.html","rb");
if(f==NULL)
{
f=fopen("index.htm","rb");
if(f==NULL) 
{
strcpy(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:189\n\n<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Whatever</title></head><body>RESPONSE NOT FOUND</body></html>");
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
}
else
{
fseek(f,0,2); 							//MOVE POINTER TO THE END OF FILE
length=ftell(f); 						//index.htm
fseek(f,0,0);			
char temp[500];				//MOVE POINTER TO THE START OF FILE
sprintf(temp,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nkeep-Alive: timeout=5, max=1000\n\n",length);
strcpy(responseBuffer,temp);
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("(index.htm) RESPONSE DATA SENDED\n");
i=0;
while(i<length)
{
rc=length-i;
if(rc>1024) rc=1024;
fread(&responseBuffer,rc,1,f);
send(clientSocketDescriptor,responseBuffer,rc,0);
i+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
}  //else block
}
else
{
fseek(f,0,2); 							//MOVE POINTER TO THE END OF FILE
length=ftell(f);						//(INDEX.HTML)
fseek(f,0,0);		
char temp[500];					//MOVE POINTER TO THE START OF FILE
sprintf(temp,"HTTP/1.1 200 OK\nContent-Type:%s\nContent-Length: %d\nkeep-Alive: timeout=5, max=1000\n\n",request->mimeType,length);
strcpy(responseBuffer,temp);
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
i=0;
while(i<length)
{
rc=length-i;
if(rc>1024) rc=1024;
fread(&responseBuffer,rc,1,f);
send(clientSocketDescriptor,responseBuffer,rc,0);
i+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
}  // else block of index.html
}  // if block of resource==NULL
else 
{
//IF FILE NAME IS PRESENT
f=fopen(request->resource,"rb");
char temp[400];
if(f==NULL)
{
//###################################################### SOLUTION OF BUG
sprintf(temp,"<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body>RESPONSE NOT FOUND FOR %s</body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\n\n",strlen(temp));
strcat(responseBuffer,temp);
printf("LENGTH OF RESPONSE BUFFER :%d\n",strlen(responseBuffer));
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
}
else 
{
fseek(f,0,2); 							//MOVE POINTER TO THE END OF FILE
length=ftell(f);
fseek(f,0,0);							//MOVE POINTER TO THE START OF FILE
char temp[500];
sprintf(temp,"HTTP/1.1 200 OK\nContent-Type: %s\nContent-Length: %d\nkeep-Alive: timeout=5, max=1000\n\n",request->resource,length);
strcpy(responseBuffer,temp);
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
while(i<=length)
{
rc=length-i;
if(rc>1024) rc=1024;
fread(&responseBuffer,rc,1,f);
send(clientSocketDescriptor,responseBuffer,rc,0);
i+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
}
}

                                           //BIG ELSE BLOCK ENDS HERE
}                                        //else block ends here
}                                        //if(isClientSideResource) block ends here
}                                        //While(1) loop ends here
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}