#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
int code;
UnitOfMeasurementManager manager;
cout<<"Enter code:";
cin>>code;
int flag=manager.unitOfMeasurementCodeExists(code);
cout<<"code exists :"<<flag<<endl;
return 0;
}