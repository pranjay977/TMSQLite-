//lc107-108 
//THIS IS MY SOLUTION date(14.10.24)
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<iostream>
#include<twpm>
using namespace std;
using namespace twpm;


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
printf("HELLO THIS IS CORRECT VERSION NOT THEN WRONG ONE\n");
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
cout<<"BYTES["<<i<<"]:("<<bytes<<")"<<endl;
for(j=0;bytes[i]!=' ';i++,j++) 
{
if(bytes[i]=='?') break;
resource[j]=bytes[i];
}
printf("PRINVE PRINVE PRINVE\n");
resource[j]='\0';
if(bytes[i]=='?')
{
i++;
printf("PRAFULL PRAFULL\n");
int si=i;
while(bytes[i]!=' ')
{
if(bytes[i]=='&') dataCnt++;
i++;
}
printf("AD AD AD AD : %d resource: %s method:%s\n",dataCnt,resource,method);
dataCnt++;
printf("JD JD JD AD : %d resource: %s method:%s\n",dataCnt,resource,method);
data=(char **)malloc(sizeof(char *)*dataCnt);
if(data==NULL) 
{
printf("UNABLE TO ALLOCATE MEMEORY BY DATA\n");
return NULL;
}
printf("KD KD KD AD  : %d resource: %s method:%s\n",dataCnt,resource,method);
int *pc=(int *)malloc(sizeof(int)*dataCnt);
if(pc==NULL) 
{
printf("UNABLE TO ALLOCATE MEMEORY BY PC\n");
return NULL;
}
printf("LD LD LD AD : %d resource: %s method:%s\n",dataCnt,resource,method);
i=si;
int j=0;
printf("MD MD MD AD : %d resource: %s method:%s\n",dataCnt,resource,method);
while(bytes[i]!=' ')
{
if(bytes[i]=='&')
{
pc[j]=i;
j++;
}
i++;
printf("GD GD GD AD : %d resource: %s method:%s\n",dataCnt,resource,method);
}
pc[j]=i;
i=si;
j=0;
int howManyToPick;
printf("SD SD SD AD : %d resource: %s method:%s\n",dataCnt,resource,method);
while(j<dataCnt)
{
printf("PD PD PD AD : %d resource: %s method:%s\n",dataCnt,resource,method);
howManyToPick=pc[j]-i;
data[j]=(char *)malloc(sizeof(char)*(howManyToPick+1));
strncpy(data[j],bytes+i,howManyToPick);
data[j][howManyToPick]='\0';
i=pc[j]+1;
j++;
printf("QD QD QD AD : %d resource: %s method:%s\n",dataCnt,resource,method);
}
if(pc!=NULL) free(pc);
}
}
printf("AD3 AD3 AD3 AD3 \n");
Request *rq=new Request;
if(dataCnt!=0) rq->setData(data,dataCnt);
cout<<"AFTER SETTING DATA CONTROL GETTING BACK"<<endl;
if(method[0]!='\0') rq->setMethod(method);
cout<<"AFETER SETTING VALUE AND KEY"<<endl;
if(resource[0]!='\0')
{
rq->setResource(resource);
char iCT=isClientSideTechnology(resource);
rq->setClientSideTechnology(iCT);
char *mimeType=getMIMEType(resource);
if(mimeType) rq->setMimeType(mimeType);
}
cout<<"JUST BEFORE FREEING ALL DATA"<<endl;
for(int k=0;k<dataCnt;k++) free(data[k]);
cout<<"AFER FREEING DATA"<<endl;
free(data);
cout<<"JUST BEFORE RETURNING rq"<<endl;
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
if(this->url) delete [] this->url;
this->url=NULL;
this->ptrOnRequest=NULL;
if(url==NULL || ptrOnRequest==NULL) return;
this->url=new char[strlen(url)+1];
strcpy(this->url,url);
printf("URL :%s\n",url);
this->ptrOnRequest=ptrOnRequest;
mp.insert(pair<string *,void (*)(Request &,Response &)>(new string(url),ptrOnRequest));
return;
}
void TMWebProjector::ResourceCheck(string &resource)
{
map<string *,void (*)(Request &,Response &),stringComparator>::iterator i;
i=mp.find(&resource);
for(map<string *,void (*)(Request &,Response &),stringComparator>::iterator j=mp.begin();j!=mp.end();++j) 
{
cout<<"FIRST :"<<*(j->first)<<endl;
}
if(i!=mp.end())
{
string str=*(i->first);
strcpy(this->url,str.c_str());
this->ptrOnRequest=i->second;
printf("MIL GAYAY MIL GAYA\n");
}
printf("NAHI MILA\n");
return;
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
Request rqs(rq);
char **d;
int dataCnt;
d=NULL;
rqs.getData(&d,&dataCnt);
cout<<"DATA PUSHHHKJSJSJKDSDJS"<<endl;
cout<<"DATA CNT ::"<<dataCnt<<endl;
for(int j=0;j<dataCnt;j++) printf("%s\n",d[j]);
cout<<"SIMKJHHDKDJKSDJSJ"<<endl;
delete rq;
string str=rqs.getResource();
cout<<"RQS RESOURCE:"<<str<<endl;  
if(str!="") rsc=str;
if(rqs.getClientSideTechnologyResource()=='Y')
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
//OLDER ONE strcpy(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:189\nConnection: close\n\n<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Whatever</title></head><body>RESPONSE NOT FOUND</body></html>");
strcpy(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\n\n<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Whatever</title></head><body>RESPONSE NOT FOUND</body></html>");
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
}
else
{
fseek(f,0,2); 							//MOVE POINTER TO THE END OF FILE
length=ftell(f); 						//index.htm
fseek(f,0,0);			
char temp[500];				//MOVE POINTER TO THE START OF FILE
//OLDER ONE sprintf(temp,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nconnection:closed\n\n",length);
sprintf(temp,"HTTP/1.1 %d OK\nContent-Type:text/html\n\n",200);
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
//OLDER ONE sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\nConnection: close\n\n",strlen(temp));
sprintf(responseBuffer,"HTTP/1.1 %d OK\nContent-Type: text/html\n\n",200);
strcat(responseBuffer,temp);
printf("LENGTH OF RESPONSE BUFFER :%d\n",strlen(responseBuffer));
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
}
else 
{
printf("TMWP 333333333333333333333333 VERSION \n");
fseek(f,0,2); 							//MOVE POINTER TO THE END OF FILE
length=ftell(f);
fseek(f,0,0);							//MOVE POINTER TO THE START OF FILE
char temp[500];
string mimeType=rqs.getMT();
//OLDER ONE sprintf(temp,"HTTP/1.1 200 OK\nContent-Type:%s\nContent-Length:%d\nConnection: closed\n\n",mimeType.c_str(),length);
sprintf(temp,"HTTP/1.1 200 OK\nContent-Type:%s\n\n",mimeType.c_str());
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
sprintf(temp,"<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body><style>body{background-color:red;color:black;}</style><h1>RESPONSE NOT FOUND FOR %s</h1></body></html>",rsc.c_str());
//OLDER ONE sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\nConnection: close\n\n",strlen(temp));
sprintf(responseBuffer,"HTTP/1.1 %d OK\nContent-Type: text/html\n\n",200);
strcat(responseBuffer,temp);
printf("LENGTH OF RESPONSE BUFFER :%d\n",strlen(responseBuffer));
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
}
else
{
int ii=0;
if(this->url[0]=='/') ii=1;
printf("STRCMP TAK CONTROL:: rsc:(%s) , url:(%s)\n",rsc.c_str(),this->url+ii);
string str=string("/")+rsc;
this->ResourceCheck(str);
if(strcmp(this->url+ii,rsc.c_str())==0)
{
printf("Resource and STRCMP.SAME\n");
Response rs;
rs.setPtrToF(send);
rs.setClientSocketDescriptor(clientSocketDescriptor);
printf("BeFORE PTRONREQUEST\n");
string gm=rqs.get("rl");
cout<<"GAME CHANGER :::::: ("<<gm<<")"<<endl;
this->ptrOnRequest(rqs,rs);
printf("AFTER PTRONREQUEST\n");
}
else 
{
char temp[500];
sprintf(temp,"<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body><style>body{background-color:black;color:white;}</style><h1>CHINKU MINKU %s</h1></body></html>",rsc.c_str());
//OLDER ONE sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\nConnection: close\n\n",strlen(temp));
sprintf(responseBuffer,"HTTP/1.1 %d OK\nContent-Type: text/html\n\n",200);
strcat(responseBuffer,temp);
printf("LENGTH OF RESPONSE BUFFER :%d\n",strlen(responseBuffer));
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
}
}
//delete this->url;
}
}
}
closesocket(serverSocketDescriptor);
WSACleanup();
return;
}