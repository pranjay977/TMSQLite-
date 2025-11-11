
//DATE 1.11.24
#include<abbm>
#include<fstream>
#include<studInfo>
#include<string.h>
#include<wrapper>
#include<iostream>
using namespace abbm;
using namespace std;
void one(Request &request,Response &response)
{
cout<<"gInt(ONE) :("<<request.gInt()<<")"<<endl;
cout<<"###### HURRY function one got called"<<endl;
response.write("<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body><style>body{background-color:'red'}</style><h1>PROCESSSING SUCCESSFULL</h1></body></html>");
//response.close();
request.set("error","INVALID ERROR");
request.isForward=0;
request.forward("/error.tpl"); 
} 

void two(Request &request,Response &response)
{
cout<<"###### HURRY function two got called"<<endl;
string a="abcd";
string b="pankaj";
request.set(a,b);
cout<<"BEFORE SENDING"<<endl;
response.write("<DOCKTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Good website</title></head><body><style>body{background-color:red;color:black;}</style><h1>TWO FUNCTION</h1></body></html>");
response.close();
cout<<"AFTERE SENDING"<<endl;
request.isForward=0;
//request.forward("three"); 
}
void three(Request &request,Response &response)
{
string k="abcd";
string jk=request.Get(k);
cout<<"AFTER GET ###!@@!#@#@#@#@ ("<<jk<<")"<<endl;
cout<<"###### HURRY function THREE got called"<<endl;
cout<<"gInt(THREE) :("<<request.gInt()<<")"<<endl;
request.isForward=0;
//request.forward("one"); 
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