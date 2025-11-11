#ifndef __STRING_$$ 1232
#define __STRING_$$ 1232
#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
class TMString
{
private:
int size;
char *str;
public:
TMString();
void operator=(char const *str);
void getStr(char *);
int getSize();
void operator=(const TMString &other);
int operator>(TMString &other);
int operator<(TMString &other);
int operator>=(TMString &other);
int operator<=(TMString &other);
int operator==(TMString &other);
int operator!=(TMString &other);
TMString operator+(TMString &other) const;
TMString operator+(char const *str);
void insert(int i,TMString &other);
void insert(int i,TMString &other,int j,int k);
void insert(int i,char const *str,int j,int k);
void insert(int i,char const *str);
void insert(int i,int times,char c);
TMString operator*(int multiply);
friend ostream &operator<<(ostream &c,TMString &s);
void operator+=(const TMString &other);
~TMString();
};
TMString TMString::operator*(const char *str,int multiply)
{
char *tempStr=new char[strlen(str)*multiply];
int i,k,j=0;
k=0;
while(k<multiply)
{
i=0;
while(i<this->size) 
{
tempStr[j]=str[i]; 
i++;
j++;
}
k++;
}
TMString other;
other=tempStr;
delete []tempStr;
return other;
}
void TMString::operator+=(const TMString &other)
{
char *tempStr=new char[this->size+other.size];
strcpy(tempStr,this->str);
strcat(tempStr,other.str);
TMString k;
*this=tempStr;
delete []tempStr;
return;
}

TMString TMString::operator*(int multiply)
{
char *tempStr=new char[this->size*multiply];
for(int k=0;k<multiply;k++) strcat(tempStr,this->str);
TMString other;
other=tempStr;
delete []tempStr;
return other;
}

TMString TMString::operator+(char const *str)
{
if(str==NULL || this->str==NULL) return *this;
char *tempStr=new char[this->size+strlen(str)];
strcpy(tempStr,this->str);
strcat(tempStr,str);
TMString k;
k=tempStr;
delete []tempStr;
return k;
}

int TMString::getSize()
{
return this->size;
}
TMString::TMString()
{
this->str=NULL;
this->size=0;
}
void TMString::operator=(char const *str)
{ 
if(str==NULL) return;
this->str==NULL;
this->size=0;
this->size=strlen(str);
this->str=new char[this->size];
strcpy(this->str,str);
}
void TMString::getStr(char *temp)
{
strcpy(temp,this->str);
}
ostream &operator<<(ostream &c,TMString &s)
{
char *temp=new char[s.getSize()];
s.getStr(temp);
c<<temp;
delete []temp;
return c;
}

/*ostream &operator<<(ostream &oo,TMString &st)            //Sir ka banvaya hua 
{
oo<<st.str;
return oo;
}
*/
void TMString::operator=(const TMString &other)
{
if(other.str==NULL) return;
this->str==NULL;
this->size=0;
this->size=other.size;
this->str=new char[this->size];
strcpy(this->str,other.str);
}
TMString::~TMString()
{
if(!this->str) delete []this->str;
}
int TMString::operator>(TMString &other)
{
if(other.str==NULL && this->str==NULL) return 0;
if(other.str==NULL) return 1;
if(this->str==NULL) return 0;
int k=strcmp(this->str,other.str);
if(k<0) return 0;
return 1; 
}
int TMString::operator<(TMString &other)
{
if(other.str==NULL && this->str==NULL) return 0;
if(other.str==NULL) return 0;
if(this->str==NULL) return 1;
int k=strcmp(this->str,other.str);
if(k<0) return 1;
return 0; 
}

int TMString::operator>=(TMString &other)
{
if(other.str==NULL && this->str==NULL) return 0;
if(other.str==NULL) return 1;
if(this->str==NULL) return 0;
int k=strcmp(this->str,other.str);
if(k<=0) return 0;
return 1; 
}
int TMString::operator<=(TMString &other)
{
if(other.str==NULL && this->str==NULL) return 0;
if(other.str==NULL) return 0;
if(this->str==NULL) return 1;
int k=strcmp(this->str,other.str);
if(k<=0) return 1;
return 0; 
}
int TMString::operator==(TMString &other)
{
if(other.str==NULL && this->str==NULL) return 1;
if(other.str==NULL) return 0;
if(this->str==NULL) return 0;
int k=strcmp(this->str,other.str);
if(k==0) return 1;
return 0; 
}
int TMString::operator!=(TMString &other)
{
if(other.str==NULL && this->str==NULL) return 0;
if(other.str==NULL) return 0;
if(this->str==NULL) return 0;
int k=strcmp(this->str,other.str);
if(k==0) return 0;
return 1; 
}
TMString TMString::operator+(TMString &other) const
{
char *str=new char[this->size+other.size];
strcpy(str,this->str);
int j=this->size;
int i=0;
while(i<other.size) 
{
str[j]=other.str[i]; 
i++;
j++;
}
str[j]='\0';
TMString temp;
temp=str;
delete []str;
return temp;
}

void TMString::insert(int i,TMString &other)
{

}
void TMString::insert(int i,TMString &other,int j,int k)
{
char *str=new char[this->size+k];
int e=0;
while(e<i) 
{
str[e]=this->str[e];
e++;
}
cout<<"e val:"<<e<<endl;
cout<<str<<endl;
int s=0;
while(s<k) 
{
str[e]=other.str[j];
j++;
e++;
s++;
}
cout<<str<<endl;
cout<<"e val:"<<e<<endl;
while(this->str[i]!='\0') str[e++]=this->str[i++];
cout<<"e val:"<<e<<endl;
this->str=str;
delete []str;
return;
}
void TMString::insert(int i,char const *string,int j,int k)
{
char *str=new char[this->size+k];
int e=0;
while(e<i) 
{
str[e]=this->str[e];
e++;
}
cout<<"e val:"<<e<<endl;
cout<<str<<endl;
int s=0;
while(s<k) 
{
str[e]=string[j];
j++;
e++;
s++;
}
cout<<str<<endl;
cout<<"e val:"<<e<<endl;
while(this->str[i]!='\0') str[e++]=this->str[i++];
cout<<"e val:"<<e<<endl;
this->str=str;
delete []str;
return;
}
void TMString::insert(int i,char const *string)
{
char *str=new char[this->size+strlen(string)];
int e=0;
while(e<i) 
{
str[e]=this->str[e];
e++;
}
cout<<"e val:"<<e<<endl;
cout<<str<<endl;
int s=0;
while(s<strlen(str)) 
{
str[e]=string[s];
e++;
s++;
}
cout<<str<<endl;
cout<<"e val:"<<e<<endl;
while(this->str[i]!='\0') str[e++]=this->str[i++];
cout<<"e val:"<<e<<endl;
this->str=str;
delete []str;
return;
}
void TMString::insert(int i,int times,char c)
{
char *str=new char[this->size+times];
int e=0;
while(e<i) 
{
str[e]=this->str[e];
e++;
}
cout<<"e val:"<<e<<endl;
cout<<str<<endl;
int s=0;
while(s<times) 
{
str[e]=c;
e++;
s++;
}
cout<<str<<endl;
cout<<"e val:"<<e<<endl;
while(this->str[i]!='\0') str[e++]=this->str[i++];
cout<<"e val:"<<e<<endl;
this->str=str;
delete []str;
return;
}

int main()
{
TMString g,s;
g="MAHAKAL";
s="abcdefg";
g=s+"Indore";
cout<<g<<endl;
cout<<s<<endl;
g.insert(2,s,3,2);
cout<<g<<endl;
g.insert(2,"ramesh babu",3,2);
string k="THINKINGMACHINES";
cout<<k<<endl;
k.insert(3,"prafullKelkar");
cout<<k<<endl;
k="ThinkingMachines";
k.insert(3,10,'Q');
cout<<k<<endl;
cout<<g<<endl;
return 0;
}