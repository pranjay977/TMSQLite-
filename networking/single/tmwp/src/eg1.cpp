#include<iostream>
using namespace std;
int main()
{
long long unsigned int num;
cout<<"Enter a no:";
cin>>num;
num=123456789102;
char numArr[20];
sprintf(numArr,"%lu",num);
string str(numArr);
cout<<"STRING:"<<str<<endl;
return 0;
}