#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
class aaa
{
public:
int data;
char name[50];
};
void add()
{
string name;
int data;
cout<<"Enter data:";
cin>>data;
cout<<"Enter name:";
cin>>name;
aaa a;
a.data=data;
strcpy(a.name,name.c_str());
fstream f("pqr.s",ios::app|ios::binary);
if(f.fail()) 
{
fstream ft("pqr.s",ios::out|ios::in|ios::binary);
ft.write((char *)&a,sizeof(aaa));
ft.close();
return;
}
f.write((char *)&a,sizeof(aaa));
f.close();
printf("DATA SUCCESFULL\n");
}
void display()
{
aaa a;
fstream f("pqr.s",ios::out|ios::in|ios::binary);
if(f.fail()) return;
while(1)
{
f.read((char *)&a,sizeof(aaa));
if(f.fail()) break;
cout<<a.data<<" , "<<a.name<<endl;
}
f.close();
return;
}
int main()
{
int ch;
while(1)
{
cout<<"Enter your choice:";
cin>>ch;
if(ch==1) add();
if(ch==2) display();
if(ch==3) break;
}
return 0;
}
