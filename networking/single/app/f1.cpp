#include<stdio.h>
struct student
{
int rollNumber;
int chm;
int phy;
int mth;
};
int main()
{
struct student st;
struct student *jd;
FILE *f;
f=fopen("marks.xyz","wb+");
st.rollNumber=1;
st.chm=10;
st.phy=20;
st.mth=30;
fwrite(&st,sizeof(student),1,f);
st.rollNumber=2;
st.chm=20;
st.phy=30;
st.mth=40;
fwrite(&st,sizeof(student),1,f);
st.rollNumber=3;
st.chm=50;
st.phy=60;
st.mth=70;
fwrite(&st,sizeof(student),1,f);
st.rollNumber=4;
st.chm=60;
st.phy=70;
st.mth=80;
fwrite(&st,sizeof(student),1,f);
fseek(f,SEEK_SET,0);
while(1)
{
fread(&st,sizeof(student),1,f);
if(feof(f)) break;
printf("rl: %d , ch :%d ,phy :%d ,mth :%d\n",st.rollNumber,st.chm,st.phy,st.mth);
}
fclose(f);
return 0;
}