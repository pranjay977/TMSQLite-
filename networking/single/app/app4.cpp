#include<abbm>
#include<fstream>
#include<windows.h>
#include<studInfo>
#include<string.h>
#include<wrapper>
#include<iostream>
using namespace abbm;
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
{_Info st;
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
response.write(str);
response.write("</tbody></table>");
response.write("</body>");
response.write("</html>");
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

void sendDeleteForm(Response &response)
{
response.write("<DOCKTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>");
response.write("DBCFILEE SCHOOL");
response.write("</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>STUDENT DELETED SUCCESSFULLY</h1>");
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
f.seekp(pt);
f.write((char *)&sd,sizeof(_Info));
sendSuccessPage(response,rollNumber,sd.name);
f.close();
return;
}
}

f.close();
sendNotFoundPage(response);
}
void removeStudent(Request &request,Response &response)
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
response.write("<DOCKTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>");
response.write("ABC SCHOOL");
response.write("</title>");
response.write("</head>");
response.write("<body>");
response.write("Student (delete Module)");
response.write("<form method='get' action='CDeleteSt'>ROLL NUMBER: ");
response.write(rollNumber);
response.write("<input type='hidden' id='rl' name='rl' value='");
response.write(rollNumber);
response.write("'><br>");
string pc=st.name;
response.write("NAME:");
response.write(pc);
response.write("<input type='hidden' id='nm' name='nm' value='");
response.write(pc);
response.write("'><br>");
response.write("<button type='submit'>delete</button>");
response.write("</form>");
response.write("<a href='index2.html'>HOME</a></body></html>");
response.close();
}
}
f.close();
return;
}

void DeleteSt(Request &request,Response &response)
{
string name=request.get("nm");
string rollNumber=request.get("rl");
_Info st;
fstream f("abc.dat",ios::out|ios::in|ios::binary);
if(f.fail()) cout<<"NO DATA TO SHOW"<<endl;
int flag=0;
while(1)
{
f.read((char *)&st,sizeof(_Info));
if(f.fail()) break;
if(rollNumber==st.rollNo) 
{
flag=1;
break;
}
}
if(flag==0) 
{
cout<<"ROLL NO NOT FOUND"<<endl;
f.close();
return;
}
ofstream tf("xyz.dat",ios::binary);
f.seekg(0,ios::cur);
while(1)
{
f.read((char *)&st,sizeof(_Info));
if(f.fail()) break;
tf.write((char *)&st,sizeof(_Info));
}
f.close();
tf.close();
ifstream cf("xyz.dat");
ofstream gf("abc.dat",ios::binary);
while(1)
{
cf.read((char *)&st,sizeof(_Info));
if(cf.fail()) break;
if(st.rollNo!=rollNumber) 
{
gf.write((char *)&st,sizeof(st));
}
}
cf.close();
gf.close();
ofstream cc("xyz.dat");
cc.close();
response.write("<DOCKTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>");
response.write("ABC SCHOOL");
response.write("</title>");
response.write("</head>");
response.write("<body>");
response.write("STUDENT DELELTED");
response.write("<a href='index2.html'>HOME</a></body></html>");
response.close();
return;
}




int main()
{
//DONE DONE 
TMWebProjector server(5050);
server.onRequest("/addStudent",addStud);
server.onRequest("/getStudents",getStudent);
server.onRequest("/editStudent",sendStudentEditForm);
server.onRequest("/updateStudent",updateStudent);
server.onRequest("/deleteStudent",removeStudent);
server.onRequest("/CDeleteSt",DeleteSt);
server.start();   
return 0;
}