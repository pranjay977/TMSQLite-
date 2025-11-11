#include<iostream>
#include<abbm>
#include<string.h>
#include<wrapper>
using namespace abbm;
using namespace std;
void one(Request &request,Response &response)
{
cout<<"###### HURRY function one got called"<<endl;
request.forward("xyz.html");
}
void two(Request &request,Response &response)
{
cout<<"###### HURRY function two got called"<<endl;
request.forward("/three"); 
}
void three(Request &request,Response &response)
{
cout<<"###### HURRY function THREE got called"<<endl;
//DISPLAYS COOL by response.write();
}
int main()
{
TMWebProjector server(5050);
server.onRequest("/one",one);
server.onRequest("/two",two);
server.onRequest("/three",three);
server.start();
}