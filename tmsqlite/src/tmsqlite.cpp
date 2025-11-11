#include<tmsqlite>
#include<sqlite3.h>
#include<string.h>
#include<sqliteException>
using namespace sqlite;
void sqliteDB::open(const string &fileName) noexcept(false)
{
this->resultCode=sqlite3_open(fileName.c_str(),&(this->db));
if(this->resultCode!=SQLITE_OK)
{
throw SQLiteException(string("Unable to connect,reason:"+string(sqlite3_errmsg(this->db))));
}
}
void sqliteDB::executeUpdate(const string &statementString) noexcept(false)
{
/*if(statementString==NULL)
{
throw SQLiteException("SQL Statement is NULL");
}
*/
//statementString=statementString.trim();
if(statementString.length()==0) 
{
throw SQLiteException(string("Invalid SQL statement"));
}
int i;
i=statementString.find("update");
if(i!=0) throw SQLiteException("Invalid syntax");
//VALIDATIONS PERFORM LATED
this->resultCode=sqlite3_exec(this->db,statementString.c_str(),0,0,&(this->errorMessage));
if(this->resultCode!=SQLITE_OK)
{
sqlite3_free(this->errorMessage);
sqlite3_close(this->db);
throw SQLiteException(string("Unable to update record ,reason:"+string(this->errorMessage)));
}
}

sqliteDB::sqliteDB()
{
this->resultCode=SQLITE_OK;
this->db=NULL;
this->errorMessage=NULL;
this->stmt=NULL;
}

void sqliteDB::executeInsert(const string &statementString) noexcept(false)
{
//statementString=statementString.trim();
if(statementString.length()==0) 
{
throw SQLiteException(string("Invalid SQL statement"));
}
if(statementString.length()==0) 
{
throw SQLiteException(string("Invalid SQL statement"));
}
int i;
i=statementString.find("insert into");
if(i!=0) throw SQLiteException("Invalid syntax");
//VALIDATIONS PERFORM LATED
this->resultCode=sqlite3_exec(this->db,statementString.c_str(),NULL,NULL,&(this->errorMessage));
if(this->resultCode!=SQLITE_OK)
{
sqlite3_free(this->errorMessage);
sqlite3_close(this->db);
throw SQLiteException(string("Unable to insert record ,reason:"+string(this->errorMessage)));
}
}




void sqliteDB::executeDelete(const string &statementString) noexcept(false)
{
//statementString=statementString.trim();
if(statementString.length()==0) 
{
throw SQLiteException(string("Invalid SQL statement"));
}
//VALIDATIONS PERFORM LATED
int i;
i=statementString.find("delete");
if(i!=0) throw SQLiteException("Invalid syntax");
this->resultCode=sqlite3_exec(this->db,statementString.c_str(),NULL,NULL,&(this->errorMessage));
if(this->resultCode!=SQLITE_OK)
{
sqlite3_free(this->errorMessage);
sqlite3_close(this->db);
throw SQLiteException(string("Unable to delete record ,reason:"+string(this->errorMessage)));
}
}


sqlite3_stmt * sqliteDB::selectRows(const string &statementString) noexcept(false)
{
int i;
i=statementString.find("select");
if(i!=0) throw SQLiteException("Invalid syntax");
this->resultCode=sqlite3_prepare_v2(this->db,statementString.c_str(),-1,&this->stmt,NULL);
cout<<"resultCode:"<<this->resultCode<<endl;
cout<<"SQLITE_OK:"<<SQLITE_OK<<endl;

if(this->resultCode!=SQLITE_OK)
{
throw SQLiteException(string("Unable to select Rows record"));
}
return this->stmt;
}
void sqliteDB::close() noexcept(false)
{
sqlite3_close(this->db);
}
//sqlite3_stmt *rowsStatement
Rows::Rows() noexcept(false)
{
this->rowsStatement=NULL;
this->columnCount=0;
}
Rows::Rows(sqlite3_stmt *stmt) noexcept(false)
{
this->rowsStatement=stmt;
this->columnCount=sqlite3_column_count(stmt);
}
void Rows::operator=(sqlite3_stmt *stmt) noexcept(false)
{
this->rowsStatement=stmt;
this->columnCount=sqlite3_column_count(stmt);
}
int Rows::hasMoreRows() noexcept(false)
{
return sqlite3_step(this->rowsStatement)==SQLITE_ROW;
}

map<string,void *> * Rows::getRow() noexcept(false)
{
this->mp.clear();
for(int i=0;i<this->columnCount;i++)
{
int type=sqlite3_column_type(rowsStatement, i);
const char *columnName=sqlite3_column_name(rowsStatement, i);
if(type==SQLITE_INTEGER)
{
int *val=new int(sqlite3_column_int(this->rowsStatement, i));
mp[columnName] = (void *)val;
}           
if(type==SQLITE_FLOAT)
{
double *val =new double(sqlite3_column_double(this->rowsStatement, i));
mp[columnName] =(void *)val;
}
if(type==SQLITE_TEXT)
{
const unsigned char **val =new const unsigned char *((sqlite3_column_text(this->rowsStatement, i)));
mp[columnName] = (void *)*val;
mp[columnName]=(void *)*val;
}
if(type==SQLITE_NULL)
{
mp[columnName]=NULL;
}
}
return &this->mp;
}
/*
void row::operator=() noexcept(false)
{
this->rowStatement=stmt;
}

*/
void  row::operator=(map<string ,void *> *mp) noexcept(false)
{
this->mp=*mp;
}
int sqliteDB::getLastGeneratedRowId() noexcept(false)
{
return sqlite3_last_insert_rowid(this->db);
}
int row::getInt(const string &name) noexcept(false)
{
if(this->mp.find(name)==mp.end()) throw SQLiteException("No such field :"+name+" exists");
return *(int *)mp[name];
}
string row::getString(const string &name) noexcept(false)
{
if(this->mp.find(name)==mp.end()) throw SQLiteException("No such field :"+name+" exists");
const unsigned char *a=(const unsigned char *)mp[name];
return string((char const *)a);
}
double row::getDouble(const string &name) noexcept(false)
{
if(this->mp.find(name)==mp.end()) throw SQLiteException("No such field :"+name+" exists");
return *(double *)mp[name];
}
