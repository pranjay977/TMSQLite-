#include<tmsqlite>
#include<iostream>
#include<sqliteException> 
using namespace std;
using namespace sqlite;
int main()
{
sqliteDB sqliteDB;
int e_id;
string sql2;
try
{
sqliteDB.open("emp.db");
cout<<"Enter employee id:";
cin>>e_id;
char sql[1001];
sprintf(sql,"delete from employee where e_id=%d;",e_id);
sql2=sql;
sqliteDB.executeDelete(sql2);
cout<<"Record with id "<<e_id<<" removed succesfully"<<endl;
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
sqliteDB.close();
return 0;
}