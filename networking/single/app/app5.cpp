#include<twpm>
#include<fstream>
#include<studInfo>
#include<string.h>
#include<wrapper>
#include<iostream>
using namespace twpm;
using namespace std;
class _Info
{
public:
char name[50];
char rollNo[20];
};
void charishma(Request &request,Response &response)
{
string rl;
rl=request.get("rl");
if(rl=="101")
{
response.setMarks("physics",10);
response.setMarks("chemistry",20);
response.setMarks("Maths",50);
}
request.forward(marks.sct);
}
int main()
{
//DONE DONE 
TMWebProjector server(5050);
server.onRequest("/now",charishma);
server.start();   
return 0;
}