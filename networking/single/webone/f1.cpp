#include<iostream>
#include<fstream>
using namespace std;
int main()
{
FILE *f;
char sym[3]={'{','x','}'};
char c;
int chr;
int x,y,z;
x=11;
y=22;
z=33;
f=fopen("abc.xyz","rb");
while(1)
{
c=fgetc(f);
if(feof(f)) break;
if(c=='$')
{
int i=0;
while(i<3)
{
c=fgetc(f);
if(feof(f))
{
fclose(f);
return 0;
}
if(i==1 && (c!='x' && c!='y' && c!='z')) break;
else if(i==1) 
{
if(c=='x') chr=x;
if(c=='y') chr=y;
if(c=='z') chr=z;
}
if(i!=1 && c!=sym[i]) break;
i++;
}
if(i==3) printf("${%d}",chr);
continue;
}
printf("%c",c);
}
fclose(f);
return 0;
}