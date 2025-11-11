#include<stdio.h>
#include<iostream>
using namespace std;

template<typename T>
class pranjay
{
private:
T *ptr;
int size;
public:
class Iter
{
T *ptr;
public:
Iter();
Iter(T *ptr);
void operator=(Iter &it);
void operator++(int);
int operator!=(Iter it);
T &operator *();
Iter(const T &ptr);
const Iter operator+(int val);
};
pranjay();
Iter begin();
Iter end();
pranjay(T *ptr,int size);
void sort(Iter ,Iter );
};
template<typename T>
pranjay<T>::Iter::Iter()
{
this->ptr=NULL;
}
template<typename T>
pranjay<T>::Iter::Iter(T *ptr)
{
this->ptr=ptr;
}
template<typename T>
void  pranjay<T>::Iter::operator=(typename pranjay<T>::Iter &it)
{
this->ptr=it.ptr;
}
template<typename T>
void pranjay<T>::Iter::operator++(int)
{
this->ptr=this->ptr+1;
}
template<typename T>
int pranjay<T>::Iter::operator!=(Iter it)
{
return this->ptr!=it.ptr;
}
template<typename T>
pranjay<T>::pranjay() {}
template<typename T>
typename pranjay<T>::Iter pranjay<T>::begin()
{
return Iter(this->ptr);
}
template<typename T>
typename pranjay<T>::Iter pranjay<T>::end()
{
return Iter(this->ptr+this->size);
}
template<typename T>
pranjay<T>::pranjay(T *ptr,int size)
{
this->ptr=ptr;
this->size=size;
}
template<typename T>
T &pranjay<T>::Iter::operator *()
{
return *(this->ptr);
}
template<typename T>
const typename pranjay<T>::Iter pranjay<T>::Iter::operator+(int val)
{
return Iter(this->ptr+val);
}
template<typename T>
void pranjay<T>::sort(Iter start,Iter end)
{
for(Iter i=start;i!=end;i++)
{
for(Iter j=start;j!=end;j++)
{
Iter i1=j;
Iter i2=j+1;
if(*i1>*i2) 
{
T g=*i1;
*i1=*i2;
*i2=g;
}
}
}
return;
}

int main()
{
int arr[10]={10,9,8,7,6,5,4,3,2,1};
pranjay<int> p(arr,sizeof(arr)/sizeof(arr[0]));
p.sort(p.begin(),p.end());
for(pranjay<int>::Iter i=p.begin();i!=p.end();i++)
{
cout<<*i<<endl;
}
return 0;
}
