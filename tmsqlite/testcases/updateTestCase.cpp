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
cout<<"Enter school id to update:";
cin>>s_id;
while((m=getchar())!='\n');
cout<<"Enter new school name:";
fgets(s_name,50,stdin);
s_name[strlen(s_name)-1]='\0';
sprintf(sql1,"update school set name='%s' where id=%d",s_name,s_id);
sql=sql1;
sqliteDB.executeUpdate(sql);
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
sqliteDB.close();
return 0;
}