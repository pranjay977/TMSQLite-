#include<stdio.h>
int main()
{
FILE *f;
f=fopen("index.html","a");
fputs("<!DOCKTYPE HTML>",f);
fputs("<html lang='en'>",f);
fputs("<head>",f);
fputs("<meta charset='utf-8'>",f);
fputs("<title>Whatever</title>",f);
fputs("</head>",f);
fputs("<body>",f);
fputs("<h1>Welcome to Pranjay Zone</h1>",f);
fputs("</body>",f);
fputs("</html>",f);

fclose(f);
return 0;
}