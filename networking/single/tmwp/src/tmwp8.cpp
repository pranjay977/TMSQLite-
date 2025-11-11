
//THIS CODE I START IMPLEMENTING CHANGES ON 3.1.2025(After that long gap)

//Try to implement multithreading and sir concept

#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<iostream>
#include<abbm>
using namespace std;
using namespace abbm;
int isHTML(string rsrc) 
{
int i=rsrc.find(".");
int cmp=strcmp("html",rsrc.c_str()+(i+1));
if(cmp==0) return 1;
return 0;
}
void sendHTML(string rsrc,Response &rs)
{
FILE *f;
f=fopen(rsrc.c_str(),"r");
if(f==NULL) return;
char *temp;
temp=new char[1000];
char c;
string str;
int j=0;
while(1)
{
c=fgetc(f);
if(feof(f)) break;
temp[j++]=c;
}
temp[j]='\0';
fclose(f);
str=temp;
delete []temp;
rs.write(str);
rs.close();
return;
}
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
char *getMIMEType(const char *resource)
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
char isClientSideTechnology(const char *resource)
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
if(data==NULL) 
{
return NULL;
}
int *pc=(int *)malloc(sizeof(int)*dataCnt);
if(pc==NULL) 
{
return NULL;
}
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
if(pc!=NULL) free(pc);
}
}
Request *rq=new Request;
if(dataCnt!=0) rq->setData(data,dataCnt);
if(method[0]!='\0') rq->setMethod(method);
if(resource[0]!='\0')
{
rq->setResource(resource);
char iCT=isClientSideTechnology(resource);
rq->setClientSideTechnology(iCT);
char *mimeType=getMIMEType(resource);
if(mimeType) rq->setMimeType(mimeType);
}
for(int k=0;k<dataCnt;k++) free(data[k]);
free(data);
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
void TMWebProjector::onRequest(const char *url,void (*ptrOnRequest)(Request &request,Response &response))
{
if(url==NULL || ptrOnRequest==NULL) return;
mp.insert(pair<string *,void (*)(Request &,Response &)>(new string(url),ptrOnRequest));
return;
}
/*
void TMWebProjector::onRequest(const char *url,void (*ptrOnRequest)(Request &request,Response &response))
{
if(this->url) delete [] this->url;
this->url=NULL;
this->ptrOnRequest=NULL;
if(url==NULL || ptrOnRequest==NULL) return;
this->url=new char[strlen(url)+1];
strcpy(this->url,url);
this->ptrOnRequest=ptrOnRequest;
mp.insert(pair<string *,void (*)(Request &,Response &)>(new string(url),ptrOnRequest));
return;
}
*/
int TMWebProjector::ResourceCheck(string &resource)
{
printf("Resource check\n");
cout<<"Resource:("<<resource<<")"<<endl;
map<string *,void (*)(Request &,Response &),stringComparator>::iterator i;
i=mp.find(&resource);
if(i!=mp.end())
{
if(this->url) delete []this->url;
string str=*(i->first);
this->url=new char[str.size()+1];
strcpy(this->url,str.c_str());
this->ptrOnRequest=i->second;
return 1;
}
return 0;
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
cout<<"$$$ TMWP6 $$$"<<endl;
int fl=0;
while(1)
{
sprintf(message,"Server is ready to accept request at port %d",this->portNumber);
if(fl==0) 
{
printf("%s\n",message);
fl=1;
}
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
Request rqs(rq);
delete rq;
while(1)
{
fl=0;
string str=rqs.getResource();
if(str!="") rsc=str;
if(rqs.getClientSideTechnologyResource()=='Y')
{
if(str[0]=='\0')
{
f=fopen("index3.html","rb");
if(f==NULL)
{
f=fopen("index.htm","rb");
if(f!=NULL) printf("sending index.htm\n");
}									//THIS BRACES INTRODUCE 
if(f==NULL) 
{
strcpy(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:189\nConnection: close\n\n<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Whatever</title></head><body>RESPONSE NOT FOUND</body></html>");
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
break;
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
break;
}  //else block
}
else 
{
//IF FILE NAME IS PRESENT
f=fopen(rsc.c_str(),"rb");
char temp[400];
if(f==NULL)
{
sprintf(temp,"<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body><style>body{background-color:'purple'}</style><h1>FILE NOT FOUND FOR %s</h1></body></html>",rsc.c_str());
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\nConnection: close\n\n",strlen(temp));
strcat(responseBuffer,temp);
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
break;
}
else 
{
fseek(f,0,2); 							//MOVE POINTER TO THE END OF FILE
length=ftell(f);
fseek(f,0,0);							//MOVE POINTER TO THE START OF FILE
char temp[500];
string mimeType=rqs.getMT();
sprintf(temp,"HTTP/1.1 200 OK\nContent-Type:%s\nContent-Length:%d\nConnection: closed\n\n",mimeType.c_str(),length);
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
break;
}
}
}
else 
{
string sc=rsc;
if(sc[0]!='/') sc=string("/")+sc;
int flag=0;
flag=ResourceCheck(sc);
if(!flag) 
{
i=sc.find(".tpl");
if(i==sc.size()-4)
{
cout<<"Header sended for tpl\n";
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\n\n",200);
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
f=fopen("error.tpl","rb");
if(f!=NULL) cout<<"grand opening"<<endl; 
fseek(f,0,2); 							//MOVE POINTER TO THE END OF FILE
length=ftell(f); 						//index.htm
fseek(f,0,0);			
cout<<"Length:"<<length<<endl;
int j;
i=0;
while(i<length)
{
j=0;
rc=length-i;
if(rc>1024) rc=1024;
fread(&responseBuffer,rc,1,f);
str=responseBuffer;
while(j!=-1)
{
j=str.find("{{{error}}}");
cout<<"j :"<<j<<endl;
if(j!=-1) str.replace(j,11,rqs.Get("error"));
}
strcpy(responseBuffer,str.c_str());
send(clientSocketDescriptor,responseBuffer,rc,0);
i+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
break;
}
else
{
char temp[500];
sprintf(temp,"<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body><style>body{background-color:red;color:black;}</style><h1>RESPONSE NOT FOUND FOR %s</h1></body></html>",rsc.c_str());
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\nConnection: close\n\n",strlen(temp));
strcat(responseBuffer,temp);
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
break;
}
}
else
{
Response rs;
rs.setPtrToF(send);
rs.setClientSocketDescriptor(clientSocketDescriptor);
string gm=rqs.get("rl");
this->ptrOnRequest(rqs,rs);
if(rqs.isForward)
{
string sc=rqs.forwardedResourceName;
if(sc[0]!='/') sc=string("/")+sc;
cout<<"forwaded resource:("<<sc<<")"<<endl;
this->ResourceCheck(sc);
char c=isClientSideTechnology(rsc.c_str());
rqs.setResource(sc.c_str());
rqs.setClientSideTechnology(c);
char *mimeType=getMIMEType(rsc.c_str());
if(mimeType) rqs.setMimeType(mimeType);
continue;
}
else
{
rqs.freeData();
break;
}
}
}
}
}
}
closesocket(serverSocketDescriptor);
WSACleanup();
return;
}