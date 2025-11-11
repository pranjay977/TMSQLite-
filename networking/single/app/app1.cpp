#include<tmwp>
#include<iostream>
using namespace tmwp;
using namespace std;
void doSomething(const char *data,int cnt)
{
cout<<"Data:"<<data<<endl;
cout<<"cnt:"<<cnt<<endl;
}
int main()
{
TMWebProjector server(5050);
server.onRequest("/register",doSomething);
server.start();
return 0;
}