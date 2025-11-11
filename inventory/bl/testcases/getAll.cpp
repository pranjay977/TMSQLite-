#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
forward_list<abc::IUnitOfMeasurement *> *list;
forward_list<abc::IUnitOfMeasurement *>::iterator i;
UnitOfMeasurementManager um;
try
{
list=um.getUnitOfMeasurements();
for(i=list->begin();i!=list->end();i++)
{
cout<<(*i)->getTitle()<<" , "<<(*i)->getCode()<<endl;
}
}catch(BLException &blexception)
{
if(blexception.hasGenericException())
{
cout<<blexception.getGenericException()<<endl;
}
}
return 0;
}
