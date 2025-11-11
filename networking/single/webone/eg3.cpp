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
void addStud(Request &request,Response &response)
{
string name=request.get("nm");
string rollNumber=request.get("rl");
cout<<"NAME :: "<<name<<endl;
cout<<"ROLLNO:: "<<rollNumber<<endl;

_Info st;
strcpy(st.name,name.c_str());
strcpy(st.rollNo,rollNumber.c_str());
printf("FILE OPENED\n");
printf("FILE OPENED\n");
ofstream f("abc.dat",ios::app|ios::binary);
if(f.fail()) 
{
fstream dataFile("abc.dat",ios::out|ios::in|ios::binary);
dataFile.write((char *)&st,sizeof(_Info));
dataFile.close();
}
else{
f.write((char *)&st,sizeof(_Info));
f.close();
}
printf("FILE CLOSED\n");
response.write("<DOCKTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>");
response.write("great website");
response.write("</title>");
response.write("</head>");
response.write("<body>");
response.write("<style>");
response.write("body{background-color:green;color:black;}");
response.write("</style>");
response.write("<h1>CONGRATS YOUR DATA SUCCESSFULLY REGISTERED</h1>");
response.write("</body>");
response.write("</html>");
response.close();
}
void getStudent(Request &request,Response &response)
{
printf("BOOM BOOM FUNCTION\n");
printf("BOOM BOOM FUNCTION\n");
printf("FILE OPEND FUNCTION\n");
_Info st;
response.write("<DOCKTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>");
response.write("great website");
response.write("</title>");
response.write("</head>");
response.write("<body>");
response.write("<style>");
response.write("body{background-color:black;color:yellow;}");
response.write("</style>");
//response.write("table{ width: 50%;border-collapse: collapse;}");
//response.write("th, td {border:1px solid black;padding: 8px;text-align: left;}th{background-color:#f2f2f2;}");
response.write("</style></head><body><table><thead><tr><th>ROLL NO</th><th>NAME</th></tr>");
response.write("</thead><tbody>");
string str;
fstream f("abc.dat",ios::in | ios::out |ios::binary);
if(f.fail()) printf("SORRY NO FILE EXISTS\n");
string a,b,name,rollNo;
while(1)
{
f.read((char *)&st,sizeof(_Info));
if(f.fail()) break;
rollNo=st.rollNo;
name=st.name;
str+="<tr><td>"+rollNo+"</td><td>"+name+"</td></tr>";
} 
printf("OM OOM FUNCTION\n");
response.write(str);
response.write("</tbody></table>");
response.write("</body>");
response.write("</html>");
printf("OM OOM FUNCTION\n");
f.close();
response.close();
return;
}

void sendSuccessPage(Response &response,string rollNumber,string name)
{
response.write("<DOCKTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>");
response.write("ABC SCHOOL");
response.write("</title>");
response.write("</head>");
response.write("<body>");
response.write("ROLL NO:");
response.write(rollNumber);
response.write("  PREV NAME UPDATED BY NEW NAME :");
response.write("<h1>");
response.write(name);
response.write("</h1>");
response.write("</body>");
response.write("</html>");
response.close();

}


void sendPage(Response &response,string rollNumber,string name)
{
cout<<"ROLL NO IS is si si sis :("<<rollNumber<<")"<<endl;
response.write("<DOCKTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>");
response.write("ABC SCHOOL");
response.write("</title>");
response.write("</head>");
response.write("<body>");
response.write("Student (Edit Module)");
response.write("<form method='get' action='updateStudent'>ROLL NUMBER: ");
response.write(rollNumber);
response.write("<input type='hidden' id='rl' name='rl' value='");
response.write(rollNumber);
response.write("'><br>");
response.write("Name<input type='text' id='nm' name='nm' value='");
response.write(name);
response.write("'><br>");
response.write("<button type='submit'>Update</button>");
response.write("</form>");
response.write("<a href='index2.html'>HOME</a></body></html>");
response.close();
}
void sendNotFoundPage(Response &response)
{
response.write("<DOCKTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>");
response.write("ABC SCHOOL");
response.write("</title>");
response.write("</head>");
response.write("<body>");
response.write("SORRY ROLLNO NOT FOUND");
response.write("</body>");
response.write("</html>");
response.close();
}
void sendStudentEditForm(Request &request,Response &response)
{
string rollNumber=request.get("rl");
_Info st;
ifstream f("abc.dat");
if(f.fail()) cout<<"NO DATA TO SHOW"<<endl;
while(1)
{
f.read((char *)&st,sizeof(_Info));
if(f.fail()) break;
if(rollNumber==st.rollNo)
{
cout<<"PAGE FOUND\n";
sendPage(response,rollNumber,st.name);
return;
}
}
sendNotFoundPage(response);
}
void updateStudent(Request &request,Response &response)
{
string name=request.get("nm");
string rollNumber=request.get("rl");
_Info st;
fstream f("abc.dat",ios::out|ios::in|ios::binary);
if(f.fail()) cout<<"NO DATA TO SHOW"<<endl;
int pt;
while(1)
{
pt=f.tellg();
f.read((char *)&st,sizeof(_Info));
if(f.fail()) break;
if(rollNumber==st.rollNo)
{
_Info sd;
strcpy(sd.name,name.c_str());
strcpy(sd.rollNo,rollNumber.c_str());
f.seekg(pt,ios::cur);
f.write((char *)&sd,sizeof(_Info));
cout<<"***************DATA UPDATED************************\n";
sendSuccessPage(response,rollNumber,sd.name);
return;
}
}
sendNotFoundPage(response);

}
int main()
{
//DONE DONE 
TMWebProjector server(5050);
server.onRequest("/addStudent",addStud);
server.onRequest("/getStudents",getStudent);
server.onRequest("/editStudent",sendStudentEditForm);
server.onRequest("/updateStudent",updateStudent);
server.start();   
return 0;
}