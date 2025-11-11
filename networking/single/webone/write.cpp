#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class _Info
{
public:
char name[50];
char rollNo[20];
};
int main()
{
_Info a,b,c,d,e;
strcpy(a.name,"RAMESH");
strcpy(a.rollNo,"11111");
strcpy(b.name,"MAMESH");
strcpy(b.rollNo,"22222");
strcpy(c.name,"RAJ");
strcpy(c.rollNo,"33333");
strcpy(d.name,"BRIJESH");
strcpy(d.rollNo,"44444");
strcpy(e.name,"AMIT");
strcpy(e.rollNo,"55555");
ofstream f("abc.dat",ios::app|ios::binary);
if(f.fail())
{
fstream df("abc.dat",ios::out|ios::in|ios::binary);
df.write((char *)&a,sizeof(_Info));
df.close();
}
f.write((char *)&b,sizeof(_Info));
f.write((char *)&c,sizeof(_Info));
f.write((char *)&d,sizeof(_Info));
f.write((char *)&e,sizeof(_Info));
f.close();
return 0; 
}