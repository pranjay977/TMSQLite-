#include<tmsqlite>
#include<string.h>
#include<sqlite3.h>
#include<iostream>
#include<sqliteException>
using namespace std;
using namespace sqlite;
int main()
{
sqliteDB sqliteDB;
char s_name[50],m;
int s_id;
string sql;
char sql1[100];
try
{
sqliteDB.open("school.db");
cout<<"Enter school id:";
cin>>s_id;
while((m=getchar())!='\n');
cout<<"Enter school name:";
fgets(s_name,50,stdin);
s_name[strlen(s_name)-1]='\0';
sprintf(sql1,"insert into school values(%d,'%s');",s_id,s_name);
sql=sql1;
sqliteDB.executeInsert(sql);
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
sqliteDB.close();
return 0;
}