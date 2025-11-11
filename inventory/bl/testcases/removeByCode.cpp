#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace inventory;
using namespace business_layer;
int main()
{
int code;
cout<<"Enter code to remove uom:";
cin>>code;
UnitOfMeasurementManager manager;
try
{
manager.removeUnitOfMeasurementByCode(code);
cout<<"UnitOfMeasurement with code:"<<code<<" removed"<<endl;
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