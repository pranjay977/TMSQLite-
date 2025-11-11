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
int result,cnt,i;
char requestData[1000];
char *accumalator;
char *responseData;
int len;
int busId;
char m,busName[30];
char locationName[30];
char passengerName[30];
char passCityName[30];
char str[131];
char header[11];
printf("Enter busId:");
scanf("%d",&busId);
while((m=getchar())!='\n');
printf("Enter busName:");
fgets(busName,30,stdin);
if(busName[strlen(busName)-1]!='\n')
{
while((m=getchar())!='\n');
}
busName[strlen(busName)-1]='\0';
printf("Enter locationName:");
fgets(locationName,30,stdin);
if(locationName[strlen(locationName)-1]!='\n')
{
while((m=getchar())!='\n');
}
locationName[strlen(locationName)-1]='\0';
printf("Enter passengerName:");
fgets(passengerName,30,stdin);
if(passengerName[strlen(passengerName)-1]!='\n')
{
while((m=getchar())!='\n');
}
passengerName[strlen(passengerName)-1]='\0';
printf("Enter passenger CityName:");
fgets(passCityName,30,stdin);
if(passCityName[strlen(passCityName)-1]!='\n')
{
while((m=getchar())!='\n');
}
passCityName[strlen(passCityName)-1]='\0';
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
sprintf(str,"%d,%s,%s,%s,%s",busId,busName,locationName,passengerName,passCityName);
printf("strlength of str :%d\n",strlen(str));
printf("(%s)\n",str);
sprintf(header,"%-10d",strlen(str));
result=send(clientSocketDescriptor,header,10,0);
result=send(clientSocketDescriptor,str,strlen(str)+1,0);
result=recv(clientSocketDescriptor,header,sizeof(header),0);
cnt=0;
for(i=0;header[i]!='\0' && header[i]!=' ';i++) cnt=cnt*10+(header[i]-48);
int z=0;
accumalator=(char *)malloc(sizeof(char)*cnt);
responseData=(char *)malloc(sizeof(char)*cnt);
responseData[0]='\0';
while(z<cnt)
{
printf("HELLO\n");
result=recv(clientSocketDescriptor,accumalator,cnt-z,0);
z=z+result;
strcat(responseData,accumalator);
accumalator[0]='\0';
}
free(accumalator);
responseData[z]='\0';
printf("Response data received:\n");
printf("%s\n",responseData);
closesocket(clientSocketDescriptor);
free(responseData);
WSACleanup();
return 0;
}

