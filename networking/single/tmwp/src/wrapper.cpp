//IN THIS CLASS I CAN ALSO GO WITH string CLASS OTHER THAN USING char *
#include<windows.h>
#include<string.h>
#include<wrapper>
#include<iostream>
using namespace std;
int compareStringIgnoreCase(const char *a,const char *b)
{
if(a==b) return 0;
if(a==NULL) return -1;
if(b==NULL) return 1; 
char c,d;
for(;*a!='\0' && *b!='\0';a++,b++) 
{
c=*a;
if(c>=97 && c<=122) c=c-32;
d=*b;
if(d>=97 && d<=122) d=d-32;
if(c!=d)  return c-d;
}
if(*a==*b) return 0;
c=*a;
if(c>=97 && c<=122) c=c-32;
d=*b;
if(d>=97 && d<=122) d=d-32;
return c-d;
}
void Request::Int(int a)
{
this->singu=a;
}
int Request::gInt()
{
return this->singu;
}
void Request::set(string k,string v)
{
string *a=new string(k);
string *b=new string(v);
this->resourceMap.insert(pair<string *,string *>(a,b));
return;
}
string Request::Get(string k)
{
map<string *,string *,stringComparator>::iterator i;
i=this->resourceMap.find(&k);
if(i!=this->resourceMap.end()) return *(i->second);
return "";
}

void Request::forward(string abc)
{
if(abc.size()==0) return;
this->isForward=1;
this->forwardedResourceName=abc;
}
int Request::forwardResourceSize()
{
return this->forwardedResourceName.size();
}
bool Request::stringComparator::operator()(string *left,string *right)
{
return compareStringIgnoreCase(left->c_str(),right->c_str())>0;
}
string Request::getKey(char *data,int *index)
{
string str;
int i,j;
char *temp=new char[strlen(data)+1];
for(i=0,j=0;data[j]!='\0' && data[j]!='=';j++,i++) temp[i]=data[j];
temp[i]='\0';
str=temp;
delete []temp;
*index=i+1;
return str;
}
string  Request:: getValue(char *data,int *index)
{
printf("$$$$$:(%s)\n",data);
string str;
char *temp=new char[strlen(data)+1];
int i,j;
for(i=0,j=*index;data[j]!='\0';j++,i++) 
{
if(data[j]=='+') temp[i]=' ';
else temp[i]=data[j];
}
temp[i]='\0';
str=temp;
delete []temp;
return str;
}
Request::Request(Request *rs)
{
this->data=rs->data;
this->dataCnt=rs->dataCnt;
this->mimeType=rs->mimeType;
this->isClientSideTechnologyResource=rs->isClientSideTechnologyResource;
this->method=rs->method;
this->resource=rs->resource;
this->m=rs->m;
this->resourceMap=rs->resourceMap;
this->isForward=rs->isForward;
this->forwardedResourceName=rs->forwardedResourceName;
}

Request::Request()
{
this->data=NULL;
this->dataCnt=0;
this->mimeType=NULL;
this->isClientSideTechnologyResource='Y';
this->method=NULL;
this->resource=NULL;
this->isForward=0;
this->forwardedResourceName="";
}
void Request::setData(char **data,int dataCnt)
{
this->data=data;
this->dataCnt=dataCnt;
map<string *,string *,stringComparator>::iterator s;
int index,j;
string key,value,*a,*b;
for(j=0;j<this->dataCnt;j++) 
{
key=this->getKey(data[j],&index);
value=this->getValue(data[j],&index);
a=new string(key);
b=new string(value);
this->m.insert(pair<string *,string *>(a,b));
}
return;
}
void Request::setMethod(char *method)
{
if(this->method) free(this->method);
this->method=(char *)malloc(sizeof(char)*strlen(method)+1);
strcpy(this->method,method);
}
void Request::setResource(const char *resource)
{
if(this->resource) free(this->resource);
this->resource=(char *)malloc(sizeof(char)*strlen(method)+1);
strcpy(this->resource,resource);
}
void Request::setClientSideTechnology(char flag)
{
this->isClientSideTechnologyResource=flag;
}
void Request::setMimeType(char *mimeType)
{
if(this->mimeType) free(this->mimeType);
this->mimeType=(char *)malloc(sizeof(char)*strlen(mimeType)+1);
strcpy(this->mimeType,mimeType);
}
Request::~Request()
{

}
string Request::getMT()
{
if(this->mimeType==NULL) return "";
string mimeType(this->mimeType);
return mimeType;
}
string Request::getResource()
{
string str;
if(this->resource==NULL) return "";
str=this->resource;
return str;
}
char Request::getClientSideTechnologyResource()
{
return this->isClientSideTechnologyResource;
}
void Request::getData(char ***data,int *cnt)
{
int j;
*data=this->data;
*cnt=this->dataCnt;
return;
}
string Request::get(string str)
{
//DONE DONE DONE
string sg;
map<string *,string *,stringComparator>::iterator i;
i=this->m.find(&str);
if(i!=this->m.end()) 
{
sg=*(i->second);
return sg;
}
return "";
}

void Request::freeData()
{
if(this->data)
{
for(int i=0;i<this->dataCnt;i++) free(this->data[i]);
free(this->data);
}
}

// RESPONSE METHODS STARTED FROM HERE
//PRANJAY
/*
printf("sending processed page");
char temp[500];
sprintf(temp,"<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body><style>body{background-color:green;color:white;}</style>RESPONSE PROCESSED %s</body></html>",rsc.c_str());
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\n\n",strlen(temp));
strcat(responseBuffer,temp);
printf("LENGTH OF RESPONSE BUFFER :%d\n",strlen(responseBuffer));
result=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("RESPONSE DATA SENDED\n");
*/
void Response::setPtrToF(int (*abc)(long long unsigned int,const char *,int,int))
{
this->ptrToF=abc;
}

Response::Response()
{
this->clientSocketDescriptor=0;
this->responseBuffer="";
this->temp="";
this->ptrToF=NULL;
this->isClosed=false;
this->headerCreated=false;
}
/*                                             
void Response::write(string str)                              THIS IS MY VERSION
{
if(str.c_str()==NULL) return;
if(this->temp.size()==0) this->temp=str;
else this->temp+=str;  
}
*/                                
void Response::write(string str)
{
if(str.c_str()==NULL)  return;
int len=str.size();
if(len==0) return;
if(!this->headerCreated) this->createHeader();
this->ptrToF(this->clientSocketDescriptor,str.c_str(),len,0);
}
/*void Response::close()                      THIS IS MY VERSION
{
int result=this->temp.size();
char numArr[20];
sprintf(numArr,"%d",result);
string s(numArr);
this->responseBuffer="HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: "+s+"\n\n";
this->responseBuffer+=temp;
result=this->ptrToF(this->clientSocketDescriptor,this->responseBuffer.c_str(),this->responseBuffer.size(),0);
}*/ 
void Response::close()
{
if(this->isClosed) return;
closesocket(this->clientSocketDescriptor);
this->isClosed=true;
}
void Response::setClientSocketDescriptor(int clsd)
{
this->clientSocketDescriptor=clsd;
}
void Response::createHeader()
{
char header[51];
strcpy(header,"HTTP/1.1 200 OK\nContent-Type:text/html\n\n");
this->ptrToF(this->clientSocketDescriptor,header,strlen(header),0);
this->headerCreated=true;
}
