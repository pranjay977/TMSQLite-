#include<dl/iuom>
#include<dl/uom>
#include<dl/daoexception>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<bl/iuom>
#include<bl/uom>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<bl/blexception>
#include<common/stringutils>
#include<map>
#include<forward_list>
#include<string.h>
#include<fstream>
using namespace inventory;
using namespace business_layer;
//using namespace data_layer;
using namespace stringutils;
using namespace std;

bool UnitOfMeasurementTitleComparator::operator()(string *left,string *right)
{
return compareStringIgnoreCase(left->c_str(),right->c_str())<0;
}
UnitOfMeasurementManager::DataModel UnitOfMeasurementManager::dataModel;
UnitOfMeasurementManager::DataModel::DataModel()
{
populateDataStructure();
}
UnitOfMeasurementManager::DataModel::~DataModel()
{
/*
iterate any one map ,and release all bl UnitOfMeasurement objects clear both maps
*/
//map<int,abc::IUnitOfMeasurement *>::iterator i;
_UnitOfMeasurement *blUnitOfMeasurement;
map<string *,_UnitOfMeasurement *>::iterator i;
string *title;
for(i=dataModel.titleWiseMap.begin();i!=dataModel.titleWiseMap.end();i++)
{
title=i->first;
blUnitOfMeasurement=i->second;
delete blUnitOfMeasurement;
delete title;
}
dataModel.titleWiseMap.clear();
dataModel.codeWiseMap.clear();
}

//DONE DONE DONE DONE 
void UnitOfMeasurementManager::DataModel ::populateDataStructure()
{
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *dlUnitOfMeasurements;
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *>::iterator i;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
dlUnitOfMeasurements=unitOfMeasurementDAO.getAll();
inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
_UnitOfMeasurement *blUnitOfMeasurement;
int code;
string *title;
for(i=dlUnitOfMeasurements->begin();i!=dlUnitOfMeasurements->end();i++)
{
dlUnitOfMeasurement=*i;
code=dlUnitOfMeasurement->getCode();
title=new string(dlUnitOfMeasurement->getTitle());
blUnitOfMeasurement=new _UnitOfMeasurement;
blUnitOfMeasurement->code=code;
blUnitOfMeasurement->title=title;
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(code,blUnitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(title,blUnitOfMeasurement));
delete dlUnitOfMeasurement;
}
dlUnitOfMeasurements->clear();
delete dlUnitOfMeasurements;
}catch(inventory::data_layer::DAOException &daoException)
{
//NO NEED TO DO ANYTHING
}
}
UnitOfMeasurementManager::UnitOfMeasurementManager()
{

}
//CHING PONG
void UnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false)
{
BLException blException;
if(unitOfMeasurement==NULL)
{
blException.setGenericException("UnitOfMeasurement can'nt be NULL");
throw blException;
}
int code=unitOfMeasurement->getCode();
string title=unitOfMeasurement->getTitle();
if(code==0)
{
blException.addPropertyException("code","Code should not be zero"); 
}
if(title.length()==0)
{
blException.addPropertyException("title","Title required"); 
}
if(title.length()>50)
{
blException.addPropertyException("title","length should not exceed 50"); 
}
if(blException.hasExceptions())
{
throw blException;
}
map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparator>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i!=dataModel.titleWiseMap.end())
{
blException.addPropertyException("title","Given title exists");
throw blException;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
dlUnitOfMeasurement=new inventory::data_layer::UnitOfMeasurement;
dlUnitOfMeasurement->setCode(0);
dlUnitOfMeasurement->setTitle(title);
unitOfMeasurementDAO.add(dlUnitOfMeasurement);
unitOfMeasurement->setCode(dlUnitOfMeasurement->getCode());
delete dlUnitOfMeasurement;
string *t=new string(title);
_UnitOfMeasurement *blUnitOfMeasurement;
blUnitOfMeasurement=new _UnitOfMeasurement;
blUnitOfMeasurement->code=code;
blUnitOfMeasurement->title=t;
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(code,blUnitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(t,blUnitOfMeasurement));
}catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setGenericException(string(daoException.what()));
throw blException;
} 
return;
}


void UnitOfMeasurementManager:: updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false)
{
BLException blException;
string title=unitOfMeasurement->getTitle();
int code=unitOfMeasurement->getCode();
if(code==0)
{
blException.addPropertyException("code","Code should not be zero"); 
}
if(title.length()==0)
{
blException.addPropertyException("title","Title required"); 
}
if(title.length()>50)
{
blException.addPropertyException("title","length should not exceed 50"); 
}
if(blException.hasExceptions())
{
throw blException;
}
//ALL VALIDATIONS


map<int,_UnitOfMeasurement *>:: iterator i;
i=dataModel.codeWiseMap.find(code);
inventory::data_layer::UnitOfMeasurement uom;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
_UnitOfMeasurement * _unitOfMeasurement;
if(i!=dataModel.codeWiseMap.end())
{
uom.setCode(code);
uom.setTitle(title);
try
{
unitOfMeasurementDAO.update(&uom);
}catch(inventory::data_layer::DAOException &daoexception)
{
blException.setGenericException(string(daoexception.what()));
throw blException;
}
}
}
void UnitOfMeasurementManager:: removeUnitOfMeasurementByCode(int code) noexcept(false)
{
BLException blException;
if(code==0)
{
blException.addPropertyException("code","Code should not be zero"); 
}
if(blException.hasExceptions())
{
throw blException;
}
//ALL VALIDATIONS


map<int,_UnitOfMeasurement *>:: iterator i;
i=dataModel.codeWiseMap.find(code);
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDao;
_UnitOfMeasurement * _unitOfMeasurement;
if(i!=dataModel.codeWiseMap.end())
{
int code;                                                //Only For Simplicity i use this technique
_unitOfMeasurement=i->second;
code=_unitOfMeasurement->code;
try
{
unitOfMeasurementDao.remove(code);
}catch(inventory::data_layer::DAOException &daoexception)
{
blException.setGenericException(string(daoexception.what()));
throw blException;
}
}
else
{
blException.addPropertyException("code","Given code does not exists");
throw blException;
}
return;
}
void UnitOfMeasurementManager:: removeUnitOfMeasurementByTitle(string &title) noexcept(false)
{
BLException blException;
if(title.length()==0)
{
blException.addPropertyException("title","Title required"); 
}
if(title.length()>50)
{
blException.addPropertyException("title","length should not exceed 50"); 
}
if(blException.hasExceptions())
{
throw blException;
}

map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparator>:: iterator i;
i=dataModel.titleWiseMap.find(&title);
_UnitOfMeasurement * _unitOfMeasurement;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDao;
if(i!=dataModel.titleWiseMap.end())
{
int code;                                                //Only For Simplicity i use this technique
_unitOfMeasurement=i->second;
code=_unitOfMeasurement->code;
try
{
unitOfMeasurementDao.remove(code);
}catch(inventory::data_layer::DAOException &daoexception)
{
blException.setGenericException(string(daoexception.what()));
throw blException;
}
}
else
{
blException.addPropertyException("title","Given title does not exists");
throw blException;
}
return;
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager:: getUnitOfMeasurementByCode(int code) noexcept(false)
{
BLException blException;
if(code==0)
{
blException.addPropertyException("code","Code should not be zero"); 
}
if(blException.hasExceptions())
{
throw blException;
}
//ALL VALIDATIONS


map<int,_UnitOfMeasurement *>:: iterator i;
i=dataModel.codeWiseMap.find(code);
abc::IUnitOfMeasurement *uom;
_UnitOfMeasurement * _unitOfMeasurement;
if(i!=dataModel.codeWiseMap.end())
{
int code;                                                //Only For Simplicity i use this technique
string title;
_unitOfMeasurement=i->second;
code=_unitOfMeasurement->code;
title=*(_unitOfMeasurement->title);
uom=new UnitOfMeasurement;
uom->setCode(code);
uom->setTitle(title);
}
else
{
blException.addPropertyException("code","Given code does not exists");
throw blException;
}
return uom;
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager:: getUnitOfMeasurementByTitle(string &title) noexcept(false)
{
BLException blException;
if(title.length()==0)
{
blException.addPropertyException("title","Title required"); 
}
if(title.length()>50)
{
blException.addPropertyException("title","length should not exceed 50"); 
}
if(blException.hasExceptions())
{
throw blException;
}
//ALL VALIDATIONS

abc::IUnitOfMeasurement *uom;
map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparator>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i!=dataModel.titleWiseMap.end())
{
string title;
int code;
_UnitOfMeasurement *_unitOfMeasurement;
_unitOfMeasurement=i->second;
title=*(_unitOfMeasurement->title);
code=_unitOfMeasurement->code;
uom=new UnitOfMeasurement;
uom->setCode(code);
uom->setTitle(title);
}
else 
{
blException.addPropertyException("title","Given title does not exists");
throw blException;
}
return uom;
}
//CONE DONE DONE 
forward_list<abc::IUnitOfMeasurement *>  * UnitOfMeasurementManager:: getUnitOfMeasurements() noexcept(false)
{
BLException blException;
int count=this->getUnitOfMeasurementCount();
if(count==0) 
{
blException.setGenericException("No records to display");
throw blException;
}
map<int,_UnitOfMeasurement *>::iterator i;
forward_list<abc::IUnitOfMeasurement *> *list=new forward_list<abc::IUnitOfMeasurement *>();
forward_list<abc::IUnitOfMeasurement *>::iterator j=list->before_begin();
string title;
int code;
_UnitOfMeasurement *_unitOfMeasurement;
abc::IUnitOfMeasurement *uom;
for(i=dataModel.codeWiseMap.begin();i!=dataModel.codeWiseMap.end();++i)
{
uom=new UnitOfMeasurement;
_unitOfMeasurement=i->second;
title=*(_unitOfMeasurement->title);
code=(_unitOfMeasurement->code);
uom->setCode(code);
uom->setTitle(title);
j=list->insert_after(j,uom);
}
return list;
}
int  UnitOfMeasurementManager::unitOfMeasurementCodeExists(int code) noexcept(false)
{
BLException blException;
if(code==0)
{
blException.addPropertyException("code","Code should not be zero"); 
}
if(blException.hasExceptions())
{
throw blException;
}
//ALL VALIDATIONS
map<int,_UnitOfMeasurement *>:: iterator i;
i=dataModel.codeWiseMap.find(code);
if(i!=dataModel.codeWiseMap.end()) return 1;
return 0;
}
int UnitOfMeasurementManager:: unitOfMeasurementTitleExists(string &title) noexcept(false)
{
BLException blException;      
//ALL VALIDATIONS
map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparator>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i==dataModel.titleWiseMap.end()) return 0;
return 1;
}
int UnitOfMeasurementManager:: getUnitOfMeasurementCount() noexcept(false)
{
inventory::data_layer::UnitOfMeasurementDAO uom;
int count;
try
{
count=uom.getCount();
}catch(inventory::data_layer::DAOException &daoException)
{
BLException blException;
blException.setGenericException(string(daoException.what()));
throw blException;
}
return count;
}