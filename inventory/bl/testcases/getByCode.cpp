#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
UnitOfMeasurementManager manager;
abc::IUnitOfMeasurement *unitOfMeasurement;
int code;
try
{
cout<<"Enter code to get uom:";
cin>>code;
unitOfMeasurement=manager.getUnitOfMeasurementByCode(code);
cout<<unitOfMeasurement->getCode()<<" , "<<unitOfMeasurement->getTitle()<<endl;
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
}
return 0;
}