#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
string title;
UnitOfMeasurementManager manager;
cout<<"Enter title:";
cin>>title;
int flag=manager.unitOfMeasurementTitleExists(title);
cout<<"Title exists :"<<flag<<endl;
return 0;
}