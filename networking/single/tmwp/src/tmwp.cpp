//THIS CODE IS FOR LECTURE 101 (date 12.10.24)
//ASSIGNMENT REGARDING THAT IMAGE ON WEBSITE
//READING LOOP CHANGED FROM fgetc TO fread
//NEW MIME TYPE ALSO ADDED 
#include<tmwp>
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<iostream>
using namespace std;
using namespace tmwp;
typedef struct _request
{
char *mimeType;
char isClientSideTechnologyResource;
char *method;
char *data;
int cnt;
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
return *left==*right;
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
int i;
for(i=0;resource[i]!='\0' && resource[i]!='.';i++);
if(resource[i]=='\0') return 'N';
return 'Y';
}
REQUEST *parseRequest(char *bytes)
{
//DONE DONE DONE DONE 
char method[11];
char resource[100];
char data[200];
int i,j;
for(i=0;bytes[i]!=' ';i++) method[i]=bytes[i];
method[i]='\0';
i+=2;
for(j=0;bytes[i]!=' ' && bytes[i]!='?';j++,i++) resource[j]=bytes[i];
resource[j]='\0';
for(;bytes[i]!=' ' && bytes[i]!='=';i++);
i++;
for(j=0;bytes[i]<123 && bytes[i]>64;j++,i++) data[j]=bytes[i];
if(bytes[i]=='+')
{
data[j++]=' ';
i++;
for(;bytes[i]<123 && bytes[i]>64;j++,i++) data[j]=bytes[i];
}
data[j++]=',';
for(;bytes[i]!=' ' && bytes[i]!='=';i++);
i++;
for(;bytes[i]<123 && bytes[i]>64;j++,i++) data[j]=bytes[i];
data[j]='\0';
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
request->data=(char *)malloc(sizeof(char)*strlen(data)+1);
strcpy(request->data,data);
request->cnt=2;
request->isClientSideTechnologyResource=isClientSideTechnology(resource);
request->mimeType=getMIMEType(resource);
}
return request;
}
TMWebProjector::TMWebProjector(int portNumber)
{
this->portNumber=portNumber;
this->url=NULL;
this->ptrOnRequest=NULL;
}
TMWebProjector::~TMWebProjector()
{
if(this->url) delete [] this->url;
}
void TMWebProjector::onRequest(const char *url,void (*ptrOnRequest)(const char *data,int cnt))
{
printf("    On Request called successfully  url:%s\n",url);
if(this->url) delete [] this->url;
this->url=NULL;
this->ptrOnRequest=NULL;
if(url==NULL || ptrOnRequest==NULL) return;
this->url=new char[strlen(url)+1];
strcpy(this->url,url);
this->ptrOnRequest=ptrOnRequest;
}

void TMWebProjector::start()
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
string str;
char message[100];
char responseBufferLength[11];
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
return;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(this->portNumber);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
result=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(struct sockaddr));
if(result<0)
{
sprintf(message,"Unable to bind socket with port %d",this->portNumber);
printf("%s\n",message);
WSACleanup();
}
listen(serverSocketDescriptor,100);
len=sizeof(struct sockaddr);
while(1)
{
sprintf(message,"Server is ready to accept request at port %d",this->portNumber);
printf("%s\n",message);
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
REQUEST *request=parseRequest(requestBuffer);
if(request->isClientSideTechnologyResource=='Y')
{
printf("IS CLIENSIDE TECHNOLOG RESOURCE ENTERED\n");
/*is request->resource=NULL look for index.html and serve
else look for index.htm and serve
else send error 404
*/
 if(request->resource==NULL)
{
printf("######################################## Resource is NULL\n");
f=fopen("index.html","rb");
if(f==NULL)
{
f=fopen("index.htm","rb");
if(f!=NULL) printf("Sending index.htm\n");
}									//THIS BRACES INTRODUCE 
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
printf("(index.html) RESPONSE DATA SENDED\n");
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
//IF FILE NAME IS PRESENT
f=fopen(request->resource,"rb");
char temp[400];
if(f==NULL)
{
//###################################################### SOLUTION OF BUG
sprintf(temp,"<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body><style>body{background-color:'purple'}</style><h1>FILE NOT FOUND FOR %s</h1></body></html>",request->resource);
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
sprintf(temp,"HTTP/1.1 200 OK\nContent-Type:%s\nContent-Length:%d\nkeep-Alive: timeout=5, max=1000\n\n",request->mimeType,length);
strcpy(responseBuffer,temp);
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
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
}
}
}
else 
{
printf("IS NOT NOT CLIENT SIDE RESOURCE\n"); 
if(this->url==NULL || this->ptrOnRequest==NULL) 
{
printf(" URL BHI NULL PTR REQUEST BHI NULL\n");
char temp[500];
sprintf(temp,"<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body><style>body{background-color:red;color:black;}</style><h1>RESPONSE NOT FOUND FOR %s</h1></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\n\n",strlen(temp));
strcat(responseBuffer,temp);
printf("LENGTH OF RESPONSE BUFFER :%d\n",strlen(responseBuffer));
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
}
else
{
int ii=0;
if(this->url[0]=='/') ii=1;
if(strcmp(this->url+ii,request->resource)==0)
{
this->ptrOnRequest(request->data,request->cnt);
printf("sending processed page");
char temp[500];
sprintf(temp,"<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body><style>body{background-color:green;color:white;}</style>RESPONSE PROCESSED %s</body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\n\n",strlen(temp));
strcat(responseBuffer,temp);
printf("LENGTH OF RESPONSE BUFFER :%d\n",strlen(responseBuffer));
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
}
else 
{
//SOMETHING TO DO 
}
}
}
}
}
closesocket(serverSocketDescriptor);
WSACleanup();
return;
}