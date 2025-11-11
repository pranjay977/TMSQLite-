#include<tmsqlite> 
#include<sqliteException>
using namespace std;
using namespace sqlite;
int main()
{
sqliteDB sqliteDB;
try
{
sqliteDB.open("mytable.db");
string sql="select * from my_table where age>25";
Rows rows;
rows=sqliteDB.selectRows(sql);
row row;
while(rows.hasMoreRows())
{
row=rows.getRow();
cout<<row.getInt("address")<<" , "<<row.getString("city")<<" , "<<row.getDouble("rating")<<endl;
}
}catch(SQLiteException sqliteException)
{
cout<<sqliteException.what()<<endl;
}
return  0;
}