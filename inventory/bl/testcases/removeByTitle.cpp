#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace inventory;
using namespace business_layer;
int main()
{
string title;
cout<<"Enter title to remove uom:";
cin>>title;
UnitOfMeasurementManager manager;
try
{
manager.removeUnitOfMeasurementByTitle(title);
cout<<"UnitOfMeasurement with title:"<<title<<" removed"<<endl;
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