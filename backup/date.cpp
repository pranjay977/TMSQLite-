#include<string.h>
#include<iostream>
using namespace std;
class Date
{
private:
int date;
int month;
int year;
int intNumber;
public:
Date();
//Date(const char *date);
Date(const Date &date);
Date operator=(const char *date);
/*Date operator+=(int k);
Date operator-=(int s);
Date operator+(int dt2);
Date operator==(const Date &date);
Date operator!=(const Date &date);
Date operator<=(const Date &date);
Date operator>=(const Date &date);
*/
void getData()
{
cout<<this->date<<" ";
cout<<this->month<<" ";
cout<<this->year<<endl;
}
};
Date::Date()
{
this->date=0;
this->month=0;
this->year=0;
this->intNumber=10;
}
Date::Date(const Date &other)
{
this->date=other.date;
this->month=other.month;
this->year=other.month;
this->intNumber=other.intNumber;
}
//Date Date::(const Date &date);
Date Date::operator=(const char *date)
{
int Date,month,year;
if(strlen(date)<8 || strlen(date)>11) return *this;
if(strlen(date)==9) 
{
printf("Hello\n");
Date=(date[0]-48)*10+date[1]-48;
month=(date[3]-48)*10+date[4]-48;
int temp;
int i=6;
int year=0;
while(i<10)
{
temp=date[i]-48;
year=year+temp;
year=year*10;
i++;
}
this->date=Date;
this->month=month;
this->year=year;
}
return *this;
}
/*
Date Date::operator+=(int k);
Date Date::operator-=(int s);
Date Date::operator+(int dt2);
Date Date::operator==(const Date &date);
Date Date::operator!=(const Date &date);
Date Date::operator<=(const Date &date);
Date Date::operator>=(const Date &date);
*/
int main()
{
Date date;
date="10/12/2024";
date.getData();
return 0;
 }