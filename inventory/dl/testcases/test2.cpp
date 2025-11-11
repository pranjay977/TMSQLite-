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
string title;
UnitOfMeasurement up;
cout<<"Enter code:";
cin>>code;
cout<<"Enter title";
cin>>title;
up.setCode(code);
up.setTitle(title);
try
{
/*
UnitOfMeasurement a(1,"a");
UnitOfMeasurement b(2,"b");
UnitOfMeasurement c(3,"c");
UnitOfMeasurement d(4,"d");
UnitOfMeasurement e(5,"e");
UnitOfMeasurement f(6,"f");
UnitOfMeasurement g(7,"g");
UnitOfMeasurement h(8,"h");
UnitOfMeasurement i(9,"i");
UnitOfMeasurement j(10,"j");
udao.add(&a);
udao.add(&b);
udao.add(&c);
udao.add(&d);
udao.add(&e);
udao.add(&f);
udao.add(&g);
udao.add(&h);
udao.add(&i);
udao.add(&j);
*/
l=udao.getAll();
for(forward_list<abc::IUnitOfMeasurement *>::iterator i=l->begin();i!=l->end();i++)
{
cout<<(*i)->getCode()<<" , "<<(*i)->getTitle()<<endl;
}
udao.update(&up);
cout<<"After updation"<<endl;
l=udao.getAll();
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