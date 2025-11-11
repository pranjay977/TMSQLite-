#include<uomdao>
#include<uom>
#include<iostream>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurementDAO udao;
abc::IUnitOfMeasurement *m;
forward_list<abc::IUnitOfMeasurement *> *l;
forward_list<abc::IUnitOfMeasurement *>::iterator *i;
int code;
try
{
/*UnitOfMeasurement a(1,"a");
UnitOfMeasurement b(2,"b");
UnitOfMeasurement c(3,"c");
UnitOfMeasurement d(4,"d");
UnitOfMeasurement e(5,"e");
udao.add(&a);
udao.add(&b);
udao.add(&c);
udao.add(&d);
udao.add(&e);
*/
l=udao.getAll();
for(forward_list<abc::IUnitOfMeasurement *>::iterator i=l->begin();i!=l->end();i++)
{
cout<<(*i)->getCode()<<" , "<<(*i)->getTitle()<<endl;
}
cout<<"After updation"<<endl;
l=udao.getAll();
for(forward_list<abc::IUnitOfMeasurement *>::iterator i=l->begin();i!=l->end();i++)
{
cout<<(*i)->getCode()<<" , "<<(*i)->getTitle()<<endl;
}
cout<<"Enter code to remove:";
cin>>code;
for(forward_list<abc::IUnitOfMeasurement *>::iterator i=l->begin();i!=l->end();i++)
{
cout<<(*i)->getCode()<<" , "<<(*i)->getTitle()<<endl;
}
}catch(DAOException daoexp)
{
cout<<daoexp.what();
}
return 0;
}