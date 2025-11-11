#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
int code;
string title;
try
{
UnitOfMeasurement uom;
UnitOfMeasurementManager manager;
cout<<"Enter title:";
cin>>title;
uom.setTitle(title);
uom.setCode(10);
manager.addUnitOfMeasurement(&uom);
cout<<"code:"<<uom.getCode()<<", Title:"<<title<<endl;
cout<<"Added"<<endl;
}catch(BLException &blexception)
{
if(blexception.hasGenericException())
{
cout<<blexception.getGenericException()<<endl;
}
if(blexception.hasPropertyException("code"))
{
cout<<blexception.getPropertyException("code")<<endl;
}
if(blexception.hasPropertyException("title"))
{
cout<<blexception.getPropertyException("title")<<endl;
}
}
return 0;
}


/*void addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false);
void updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false);
void removeUnitOfMeasurementByCode(int code) noexcept(false);
void removeUnitOfMeasurementByTitle(string &title) noexcept(false);
abc::IUnitOfMeasurement *getUnitOfMeasurementByCode(int code) noexcept(false);
abc::IUnitOfMeasurement *getUnitOfMeasurementByTitle(string &title) noexcept(false);
forward_list<abc::IUnitOfMeasurement *> * getUnitOfMeasurements() noexcept(false);
int unitOfMeasurementCodeExists(int code) noexcept(false);
int unitOfMeasurementTitleExists(string &title) noexcept(false);
int getUnitOfMeasurementCount() noexcept(false);
*/
