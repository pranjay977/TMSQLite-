//lc107-108 
//THIS IS MY SOLUTION date(14.10.24)
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<iostream>
#include<twmp>
using namespace std;
using namespace twmp;

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
printf("left %c,right %c\n",*left,*right);
left++;
right++;
}
printf("%d\n",*left-*right);
return *left==*right;
}
char *getMIMEType(char *resource)
{
char *mimeType;
mimeType=NULL;
int len=strlen(resource);
printf("RESOURCE LENGTH:%d\n",len);
int lastIndexOfDot=len-1;
while(lastIndexOfDot>0 && resource[lastIndexOfDot]!='.') lastIndexOfDot--;
printf("ARPIT BALAL\n");
if(lastIndexOfDot==0) return mimeType;
printf("CHARRPIT BALAL\n");
printf("resource+laI+1: (%c)\n",resource[lastIndexOfDot+1]);
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
printf("ICO FILE ME ENTER\n");
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
Request *parseRequest(char *bytes)
{
//DONE DONE DONE DONE 
char method[11];
char resource[1001];
//char Data[200];
int i,j;
for(i=0;bytes[i]!=' ';i++) method[i]=bytes[i];
method[i]='\0';
i+=2;
char **data;
int dataCnt;
data=NULL;
dataCnt=0;
if(strcmp(method,"GET")==0)
{
printf("111\n");
for(j=0;bytes[i]!=' ';i++,j++) 
{
if(bytes[i]=='?') break;
resource[j]=bytes[i];
}
resource[j]='\0';
if(bytes[i]=='?')
{
i++;
int si=i;
while(bytes[i]!=' ')
{
if(bytes[i]=='&') dataCnt++;
i++;
}
dataCnt++;
data=(char **)malloc(sizeof(char *)*dataCnt);
int *pc=(int *)malloc(sizeof(int)*dataCnt);
i=si;
int j=0;
while(bytes[i]!=' ')
{
if(bytes[i]=='&')
{
pc[j]=i;
j++;
}
i++;
}
pc[j]=i;
i=si;
j=0;
int howManyToPick;
while(j<dataCnt)
{
howManyToPick=pc[j]-i;
data[j]=(char *)malloc(sizeof(char)*(howManyToPick+1));
strncpy(data[j],bytes+i,howManyToPick);
data[j][howManyToPick]='\0';
i=pc[j]+1;
j++;
}
//free(pc);
}
}
Request *rq=new Request;
rq->setData(data,dataCnt);
rq->setMethod(method);
if(resource[0]!='\0')
{
rq->setResource(resource);
char iCT=isClientSideTechnology(resource);
rq->setClientSideTechnology(iCT);
char *mimeType=getMIMEType(resource);
if(mimeType) rq->setMimeType(mimeType);
}
//free(data);
return rq;
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
void TMWebProjector::onRequest(const char *url,void (*ptrOnRequest)(Request *request,Response *response))
{
if(this->url) delete [] this->url;
this->url=NULL;
this->ptrOnRequest=NULL;
if(url==NULL || ptrOnRequest==NULL) return;
this->url=new char[strlen(url)+1];
strcpy(this->url,url);
printf("URL :%s\n",url);
this->ptrOnRequest=ptrOnRequest;
if(!ptrOnRequest) printf("CHIIIl\n");
}

void TMWebProjector::start()
{
struct sockaddr_in clientSocketInformation;
struct sockaddr_in serverSocketInformation;
int result,bytesExtracted;
int rc;                                                         //THIS IS CHANGE 2
string rsc;
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
Request *rq=parseRequest(requestBuffer);
char str[1001];
str[0]='\0';
rq->getResource(str);
if(str[0]!='\0') rsc=str;
if(rq->getClientSideTechnologyResource()=='Y')
{
/*is request->resource=NULL look for index.html and serve
else look for index.htm and serve
else send error 404
*/
if(str[0]=='\0')
{
f=fopen("index2.html","rb");
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
sprintf(temp,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nconnection:closed\n\n",length);
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
f=fopen(rsc.c_str(),"rb");
printf("RITU RITU RITU RITU RITU RiTU RITU RITU RITU \n");
char temp[400];
if(f==NULL)
{
//###################################################### SOLUTION OF BUG
sprintf(temp,"<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body><style>body{background-color:'purple'}</style><h1>FILE NOT FOUND FOR %s</h1></body></html>",rsc.c_str());
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\n\n",strlen(temp));
strcat(responseBuffer,temp);
printf("LENGTH OF RESPONSE BUFFER :%d\n",strlen(responseBuffer));
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
}
else 
{
printf("JITU JITU JITU JITU RITU RiTU RITU RITU JITU \n");
fseek(f,0,2); 							//MOVE POINTER TO THE END OF FILE
length=ftell(f);
fseek(f,0,0);							//MOVE POINTER TO THE START OF FILE
char temp[500];
string mimeType;
rq->getMT(mimeType);
sprintf(temp,"HTTP/1.1 200 OK\nContent-Type:%s\nContent-Length:%d\nconnection:closed\n\n",mimeType.c_str(),length);
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
char temp[500];
sprintf(temp,"<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body><style>body{background-color:red;color:black;}</style><h1>RESPONSE NOT FOUND FOR %s</h1></body></html>",rsc.c_str());sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\n\n",strlen(temp));
strcat(responseBuffer,temp);
printf("LENGTH OF RESPONSE BUFFER :%d\n",strlen(responseBuffer));
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
}
else
{
int ii=0;
if(this->url[0]=='/') ii=1;
printf("URL RESOURCE (%s)\n",rsc.c_str()); 
if(strcmp(this->url+ii,rsc.c_str())==0)
{
Response *rs=new Response;
rs->setPtrToF(send);
rs->setClientSocketDescriptor(clientSocketDescriptor);
printf("FUNCTION CALLED\n");
this->ptrOnRequest(rq,rs);
/*if(request->data!=NULL)
{
for(int k=0;k<rq->getDataCnt();k++) free(request->data[k]);
}
*/
/*
PRANJAY
printf("sending processed page");
char temp[500];
sprintf(temp,"<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body><style>body{background-color:green;color:white;}</style>RESPONSE PROCESSED %s</body></html>",rsc.c_str());
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\n\n",strlen(temp));
strcat(responseBuffer,temp);
printf("LENGTH OF RESPONSE BUFFER :%d\n",strlen(responseBuffer));
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
*/
}
}
delete this->url;
}
}
}
closesocket(serverSocketDescriptor);
WSACleanup();
return;
}