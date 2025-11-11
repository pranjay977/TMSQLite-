#include<twmp>
#include<wrapper>
#include<iostream>
using namespace twmp;
using namespace std;
/*void doSomething(Request &request,Response &response)
{
int j=0;
while(j<dataCnt)
{
cout<<data[j]<<endl;
j++;
}
}
*/
void doSomething(Request *request,Response *response)
{
string name;
name=request->get("nm");
string city=request->get("ct");
printf("\n\n");
cout<<"Name:"<<name<<endl;
cout<<"City:"<<city<<endl;
printf("\n\n");
response->write("<DOCKTYPE HTML>");
response->write("<html lang='en'>");
response->write("<head>");
response->write("<meta charset='utf-8'>");
response->write("<title>");
response->write("great website");
response->write("</title>");
response->write("</head>");
response->write("<body>");
response->write("<style>");
response->write("body{background-color:yellow;color:orange;}");
response->write("</style>");
response->write("<h1>HURRY YOUR SUCCEED</h1>");
response->write("<h2>Name:"+name+"</h2>");
response->write("<h2>City:"+city+"</h2>");
response->write("</body>");
response->write("</html>");
response->close();
}
int main()
{
TMWebProjector server(5050);
server.onRequest("/register",doSomething);
server.start();
return 0;
}