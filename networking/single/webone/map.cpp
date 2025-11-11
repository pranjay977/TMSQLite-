#include<iostream>
#include<map>
using namespace std;
class Rq
{
public:
map<string,void *> mp;
void setInt(string st,int i)
{
mp.insert(pair<string ,void *>(st,(void *)&i));
}
void setFloat(string st,float f)
{
mp.insert(pair<string,void *>(st,(void *)&f));
}
void setChar(string st,char c)
{
mp.insert(pair<string,void *>(st,(void *)&c));
}
int getInt(string str)
{
map<string,void *>::iterator i;
i=mp.find(str);
if(i!=mp.end()) 
{
void *st=i->second;
int *ij=(int *)(st);
cout<<"DKLJFF:"<<*ij<<endl;
return *ij;
}
return 0;
}
};
int main()
{
Rq r;
r.setInt("ii",1);
r.setFloat("ff",2.3);
r.setChar("cc",'c');
cout<<"INT STORED:"<<r.getInt("ii")<<endl;
//cout<<"FLOAT STORED:"<<r.getfloat("ff")<<endl;
//cout<<"CHAR STORED:"<<r.getChar("cc")<<endl;
return 0;
}
