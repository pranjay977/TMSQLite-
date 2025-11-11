#include<sqliteException>
SQLiteException::SQLiteException()
{
this->message="";
}
SQLiteException::SQLiteException(const SQLiteException &other) 
{
this->message=other.message;
}
SQLiteException::SQLiteException(string message) 
{
this->message=message;
}
SQLiteException::~SQLiteException() 
{
}
SQLiteException & SQLiteException::operator=(const SQLiteException &other) 
{
this->message=other.message;
return *this;
}
const char * SQLiteException::what() const throw() 
{
return this->message.c_str();
}
