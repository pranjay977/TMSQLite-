#include<bl/blexception>
using namespace inventory; 
using namespace business_layer; 
BLException::BLException()
{
this->genericException="";
}
BLException::BLException(const BLException &other) 
{
this->genericException=other.genericException;
this->exceptions=other.exceptions;
}
BLException::BLException(string genericException) 
{
this->genericException=genericException;
}
BLException::~BLException() 
{
}
BLException & BLException::operator=(const BLException &other) 
{
this->genericException=other.genericException;
this->exceptions=other.exceptions;
return *this;
}
const char * BLException::what() const throw() 
{
return this->genericException.c_str();
}
void  BLException::setGenericException(string genericException)
{
this->genericException=genericException;
}
void BLException::addPropertyException(string property,string exception)
{
this->exceptions.insert(pair<string,string>(property,exception));
}
string BLException::getGenericException()
{
return this->genericException;
}
string BLException::getPropertyException(string property)
{
map<string,string>::iterator i=this->exceptions.find(property);
if(i==this->exceptions.end())
{
 return string("");
}
return i->second;
}
int BLException::hasPropertyException(string property)
{
return this->getPropertyException(property).length()>0;
}
int BLException::hasPropertyExceptions()
{
return getPropertyExceptionsCount()>0;
}
int BLException::hasExceptions()
{
int exceptionsCount=0;
if(this->genericException.length()>0) exceptionsCount++;
if(this->exceptions.size()>0) exceptionsCount++;
return exceptionsCount;
}
int BLException::hasGenericException()
{
return this->genericException.length()>0;
}
int BLException::getPropertyExceptionsCount()
{
return this->exceptions.size();
}
