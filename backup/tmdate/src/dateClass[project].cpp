#include<tmdate>
#include<string.h>
#include<iostream>
using namespace std;
void TMDate::FromDaytoTMDate()
{
int y,d,m;
int x=this->dayNumber;
int daysInMonth,daysInYear;
y=1901;
while(1)
{
if(y%4==0) daysInYear=366;
else daysInYear=365;
if(x<daysInYear) break;
x=x-daysInYear;
y++;
}
int mht[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(y%4==0) mht[1]=29;
m=0;
while(1)
{
daysInMonth=mht[m];
if(x<daysInMonth) break;
x=x-daysInMonth;
m++;
}
m++;
this->date=x;
this->month=m;
this->year=y;
return;
}
TMDate::TMDate()
{
this->date=0;
this->month=0;
this->year=0;
this->dayNumber=0;
}
TMDate::TMDate(const TMDate &other)
{
this->date=other.date;
this->month=other.month;
this->year=other.month;
this->dayNumber=other.dayNumber;
}
void TMDate::DayNumber()
{
int x=0;
int j=1901;
while(j<this->year)
{
if(j%4==0) x=x+366;
else x=x+365;
j++;
}
int mht[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(this->year%4==0) mht[1]=29;
int ep=this->month-2;
j=0;
while(j<=ep)
{
x=x+mht[j];
j++;
}
x=x+this->date;
this->dayNumber=x;
this->FromDaytoTMDate();
return;
}
TMDate TMDate::operator=(const char *Date)
{
int tDate,month,i=0;
tDate=month=0;
if(strlen(Date)<8 || strlen(Date)>10) return *this;
i=0;
while(Date[i]>=48 && Date[i]<58)
{
tDate=(Date[i]-48)+tDate;
if(!(Date[i+1]>=48 && Date[i+1]<58)) 
{
i++;
break;
}
if(Date[i]>=48 && Date[i]<58) tDate=tDate*10;
i++;
}
if(tDate>31 || tDate<1) return *this;
i++;
while(Date[i]>=48 && Date[i]<58) 
{
month=(Date[i]-48)+month;
if(!(Date[i+1]>=48 && Date[i+1]<58)) 
{
i++;
break;
}
if(Date[i]>=48 && Date[i]<58) month=month*10;
i++;
}
if(month>12 || month<1) return *this;
i++;
int temp;
int year=0;
while(i<strlen(Date))
{
temp=Date[i]-48;
year=year+temp;
if(Date[i+1]=='\0') break;
year=year*10;
i++;
}
if(year<1901) return *this;
this->date=date;
this->month=month;
this->year=year;
this->DayNumber();
return *this;
}
TMDate TMDate::operator+=(int k)
{
this->dayNumber=this->dayNumber+k;
this->FromDaytoTMDate();
return *this;
}
TMDate TMDate::operator-=(int s)
{
this->dayNumber=this->dayNumber-s;
this->FromDaytoTMDate();
return *this;
}
TMDate TMDate::operator+(int dt2)
{
this->dayNumber=this->dayNumber+dt2;
this->FromDaytoTMDate();
return *this;
}int TMDate::operator==(const TMDate &other)
{
return this->dayNumber==other.dayNumber;
}
int TMDate::operator!=(const TMDate &other)
{
return this->dayNumber!=other.dayNumber;
}
int TMDate::operator<=(const TMDate &other)
{
return this->dayNumber<=other.dayNumber;
}
int TMDate::operator>=(const TMDate &other)
{
return this->dayNumber>=other.dayNumber;
}
int TMDate::getMonth()
{
return this->month;
}
int TMDate::isLeapYear()
{
if(this->year%4==0) return 1;
return 0;
}
int TMDate::getYear()
{
return this->year;
}
int TMDate::getTMDate()
{
return this->date;
}
void TMDate::getMonthName(char *name)
{
char Mname[12][12]={"Janauary","febraury","March","April","May","June","July","August","September","October","November","December"};
int Mindex=this->month;
strcpy(name,Mname[Mindex-1]);
return;
}
void TMDate::getMonthShortName(char *shtName)
{
char tempName[12];
this->getMonthName(tempName);
strcpy(shtName,tempName);
shtName[3]='\0';
return;
}
int TMDate::getDayOfWeek()
{
return this->dayNumber%7+1;
}
void TMDate::getDayOfWeekName(char *wkn)
{
int weekDay=this->dayNumber%7;
char week[7][10]={"Sunday","Monday","Tuesday","Wednesday","Thrusday","Friday","Saturday"};
if(weekDay==6) strcpy(wkn,week[0]);
else strcpy(wkn,week[weekDay+1]);
return;
}
void TMDate::getData()
{
cout<<this->date<<"/";
cout<<this->month<<"/";
cout<<this->year<<endl;
}
