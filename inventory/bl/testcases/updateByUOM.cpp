#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
UnitOfMeasurementManager manager;
UnitOfMeasurement unitOfMeasurement;
string title;
int code;
try
{
cout<<"Enter title:";
cin>>title;
cout<<"Enter code :";
cin>>code;
unitOfMeasurement.setCode(code);
unitOfMeasurement.setTitle(title);
manager.updateUnitOfMeasurement(&unitOfMeasurement);
cout<<"UnitOfMeasurement with Code:"<<unitOfMeasurement.getCode()<<" is succesfully updated"<<endl;
}catch(BLException &blexception)
{
if(blexception.hasGenericException())
{
cout<<blexception.getGenericException()<<endl;
}
if(blexception.hasPropertyException("title"))
{
cout<<blexception.getPropertyException("title")<<endl;
}
}
return 0;
}