#include<dl/daoexception>
#include<string.h>
#include<fstream>
#include<common/stringutils>
#include<dl/iuomdao>
#include<dl/uomdao>
using namespace std;
using namespace stringutils;
using namespace inventory;
using namespace data_layer;
void UnitOfMeasurementDAO::add(abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false) 
{
const string vTitle=unitOfMeasurement->getTitle();
string title=trimmed(vTitle);
if(title.length()==0) throw DAOException("Title required length is zero");
if(title.length()>50) throw DAOException("Title length can'nt exceed 50");
Header header;
_UnitOfMeasurement _unitOfMeasurement;
fstream dataFile(FILE_NAME,ios::in | ios::out |ios::binary);
if(dataFile.fail()) //FILE NOT PRESENT
{
ofstream dfile(FILE_NAME,ios::app | ios::binary);
header.lastGeneratedCode=1;
header.numberOfRecords=1;
dfile.write((char *)&header,sizeof(Header));
_unitOfMeasurement.code=1;
strcpy(_unitOfMeasurement.title,title.c_str());
dfile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
dfile.close();
unitOfMeasurement->setCode(1);
return;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) //FILE EXISTS BUT OF ZERO BYTES
{
dataFile.clear();
dataFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);
header.lastGeneratedCode=1;
header.numberOfRecords=1;
dataFile.write((char *)&header,sizeof(Header));
_unitOfMeasurement.code=1;
strcpy(_unitOfMeasurement.title,title.c_str());
dataFile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
dataFile.close();
unitOfMeasurement->setCode(1);
return;
}
while(true)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_unitOfMeasurement.title,title.c_str())==0)
{
dataFile.close();
throw DAOException(title+string("exist"));
}
}
dataFile.clear();
header.lastGeneratedCode++;
header.numberOfRecords++;
_unitOfMeasurement.code=header.lastGeneratedCode;
UnitOfMeasurement m;
strcpy(_unitOfMeasurement.title,title.c_str());
dataFile.seekg(0,ios::end);
dataFile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
dataFile.seekp(0,ios::beg);
dataFile.write((char *)&header,sizeof(Header));
dataFile.close();
unitOfMeasurement->setCode(_unitOfMeasurement.code);
}

//DONE DONE
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementDAO::getAll() noexcept(false)
{
fstream dataFile(FILE_NAME,ios::in | ios::out |ios::binary);
if(dataFile.fail()) //FILE NOT PRESENT
{
throw DAOException("No data to read");
}
Header header;
dataFile.read((char *)&header,sizeof(Header));
_UnitOfMeasurement _unitOfMeasurement;
forward_list<abc::IUnitOfMeasurement *> *list=new forward_list<abc::IUnitOfMeasurement *>();
forward_list<abc::IUnitOfMeasurement *>::iterator i;
i=list->before_begin();
while(true)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
i=list->insert_after(i,new UnitOfMeasurement(_unitOfMeasurement.code,_unitOfMeasurement.title));
}
dataFile.close();
return list;
}




void UnitOfMeasurementDAO::remove(int code) noexcept(false)
{
if(code<0) throw DAOException("No records are present");
fstream dataFile(FILE_NAME,ios::in| ios::out | ios::binary);
if(dataFile.fail()) //FILE NOT PRESENT
{
throw DAOException("No records are present");
}
Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) 
{
dataFile.close();
throw DAOException("No data to read");
}
if(header.numberOfRecords==0) 
{
dataFile.close();
throw DAOException("No data to read");
}
int found=false;
_UnitOfMeasurement _unitOfMeasurement;
while(true)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code)
{
found=true;
break;
}
}
if(found==false) 
{
dataFile.close();
throw DAOException("Record not found");
}
dataFile.clear();
dataFile.seekg(0,ios::beg);
fstream tempFile("abc.dat",ios::in | ios::out | ios::binary);
dataFile.read((char *)&header,sizeof(Header));
tempFile.write((char *)&header,sizeof(Header));
while(true)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code) 
{
continue;
}
else 
{
tempFile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
}
}
fstream f(FILE_NAME,ios::out | ios::trunc);
f.close();
fstream dtF(FILE_NAME,ios::app | ios::in | ios::binary);
tempFile.clear();
tempFile.seekp(0,ios::beg);
tempFile.read((char *)&header,sizeof(Header));
header.numberOfRecords--;
if(header.numberOfRecords==0)
{
header.lastGeneratedCode=0;
header.numberOfRecords=0;
dtF.write((char *)&header,sizeof(Header));
tempFile.close();
tempFile.clear();
dtF.close();
return;
}
dtF.write((char *)&header,sizeof(Header));
while(true)
{
tempFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(tempFile.fail()) break;
dtF.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
}
tempFile.close();
tempFile.clear();
fstream f2("abc.dat",ios::out | ios::trunc);
f2.close();
dtF.close();
return;
}
void UnitOfMeasurementDAO::update(abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false)
{
const string vTitle=unitOfMeasurement->getTitle();
string title=trimmed(vTitle);
if(title.length()==0) throw DAOException("Title required length is zero");
if(title.length()>50) throw DAOException("Title length can'nt exceed 50");
int code=unitOfMeasurement->getCode();
if(code<0) throw DAOException("Invalid code");
fstream dataFile(FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail()) throw DAOException("No data to read");
Header header;
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) 
{
dataFile.close();
throw DAOException("No data to read");
}
if(header.numberOfRecords==0) 
{
dataFile.close();
throw DAOException("No data to read");
}
int found=false;
_UnitOfMeasurement _unitOfMeasurement;
int pos;
while(true)
{
pos=dataFile.tellg();
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code)
{
found=true;
break;
}
}
if(found==false) 
{
dataFile.close();
throw DAOException("Record not found");
}
dataFile.clear();
dataFile.seekg(sizeof(Header),ios::beg);
found=false;
while(true)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_unitOfMeasurement.title,title.c_str())==0)
{
found=true;
break;
}
}
if(found==true && _unitOfMeasurement.code!=code)
{
dataFile.close();
throw DAOException(title+string("exist"));
}
dataFile.clear();
_unitOfMeasurement.code=code;
strcpy(_unitOfMeasurement.title,title.c_str());
dataFile.seekp(pos,ios::beg);
dataFile.write((char *)&_unitOfMeasurement,sizeof(_unitOfMeasurement));
dataFile.close();
return;
}
int UnitOfMeasurementDAO::getCount() noexcept(false)
{
fstream dataFile(FILE_NAME,ios::in | ios::out |ios::binary);
if(dataFile.fail())  throw DAOException("unit of measurement does not exists");
Header header;
dataFile.read((char *)&header,sizeof(Header));
return header.numberOfRecords;
}
int UnitOfMeasurementDAO::codeExists(int code) noexcept(false)
{
if(code<0) throw DAOException("Invalid code");
fstream dataFile(FILE_NAME,ios::in | ios::out |ios::binary);
if(dataFile.fail())  throw DAOException("Code does'nt exist");
_UnitOfMeasurement _unitOfMeasurement;
Header header;
dataFile.read((char *)&header,sizeof(Header));
while(true)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code) return 1;
}
return 0;
}
int UnitOfMeasurementDAO::titleExists(string title) noexcept(false)
{
if(title.length()==0 || title.length()>50) throw DAOException("Invalid title");
fstream dataFile(FILE_NAME,ios::in | ios::out |ios::binary);
if(dataFile.fail())  throw DAOException("Title does'nt exist");
Header header;
dataFile.read((char *)&header,sizeof(Header));
_UnitOfMeasurement _unitOfMeasurement;
while(true)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.title==title) return 1;
}
return 0;
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByCode(int code) noexcept(false)
{
if(code<0) throw DAOException("Invalid code");
fstream dataFile(FILE_NAME,ios::in | ios::out |ios::binary);
if(dataFile.fail())  throw DAOException("Code does'nt exist");
Header header;
dataFile.read((char *)&header,sizeof(Header));
_UnitOfMeasurement _unitOfMeasurement;
while(true)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code)
{
UnitOfMeasurement *m=new UnitOfMeasurement();
m->setTitle(_unitOfMeasurement.title);
m->setCode(_unitOfMeasurement.code);
return m;
}
}
throw DAOException("Code does'nt exist");
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByTitle(string title) noexcept(false)
{
if(title.length()==0 || title.length()>50) throw DAOException("Invalid title");
fstream dataFile(FILE_NAME,ios::in | ios::out |ios::binary);
if(dataFile.fail())  throw DAOException("Title does'nt exist");
Header header;
dataFile.read((char *)&header,sizeof(Header));
_UnitOfMeasurement _unitOfMeasurement;
while(true)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.title==title)
{
UnitOfMeasurement *m=new UnitOfMeasurement();
m->setTitle(_unitOfMeasurement.title);
m->setCode(_unitOfMeasurement.code);
return m;
}
}
throw DAOException("Title does'nt exist");
}
