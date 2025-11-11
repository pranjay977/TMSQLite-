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
string title;
try
{
cout<<"Enter title to get uom:";
cin>>title;
unitOfMeasurement=manager.getUnitOfMeasurementByTitle(title);
cout<<unitOfMeasurement->getTitle()<<" , "<<unitOfMeasurement->getCode()<<endl;
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