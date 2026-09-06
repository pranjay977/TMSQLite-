# TMSQLite

A lightweight C++ object-oriented wrapper around the SQLite3 C API, designed to make working with SQLite databases in C++ simpler and more intuitive — without giving up direct access to the underlying `sqlite3` engine.

## Overview

TMSQLite wraps the raw `sqlite3` C API in a small set of C++ classes so you can open a database, run queries, and read results using clean, exception-based method calls instead of manual return-code checking and manual result parsing.

## Features

- **Simple connection management** — `open()` and `close()` methods for managing the database lifecycle.
- **Convenience methods for common operations** — dedicated `executeInsert()`, `executeUpdate()`, and `executeDelete()` methods for their respective SQL statement types.
- **Exception-based error handling** — all operations throw a `SQLiteException` on failure instead of relying on manual error-code checks, so calling code can use standard `try/catch` blocks.
- **Row iteration for SELECT queries** — `selectRows()` returns a prepared statement handle that can be wrapped in a `Rows` object to step through a result set with `hasMoreRows()`.
- **Typed column access** — results are exposed via a `row` object with `getInt()`, `getString()`, and `getDouble()` accessors, so you can read column values by name instead of by index.
- **Last-insert-ID lookup** — `getLastGeneratedRowId()` retrieves the row ID of the most recently inserted record.

## Example Usage

```cpp
#include<tmsqlite>
#include<string.h>
#include<sqlite3.h>
#include<iostream>
#include<sqliteException>
using namespace std;
using namespace sqlite;
int main()
{
sqliteDB sqliteDB;
char s_name[50],m;
int s_id;
string sql;
char sql1[100];
try
{
sqliteDB.open("school.db");
cout<<"Enter school id:";
cin>>s_id;
while((m=getchar())!='\n');
cout<<"Enter school name:";
fgets(s_name,50,stdin);
s_name[strlen(s_name)-1]='\0';
sprintf(sql1,"insert into school values(%d,'%s');",s_id,s_name);
sql=sql1;
sqliteDB.executeInsert(sql);
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
sqliteDB.close();
return 0;
}
```

## Requirements

- A C++ compiler with `noexcept` support (C++11 or later)
- [SQLite3](https://www.sqlite.org/download.html) development library (`sqlite3.h` and `libsqlite3`)

## Building

Link against the SQLite3 library when compiling, for example:

```bash
g++  your_program.cpp -o your_program.exe -I ..\include c:\sqlite3\include -L ..\lib -L c:\sqlite3\lib -ltmsqlite -lsqlite3  
```

## Project Status

This project is a work in progress. Known limitations in the current implementation include:

- SQL keyword checks (`insert into`, `update`, `delete`, `select`) are case-sensitive and only check the very start of the statement, so queries with leading whitespace or different casing will be rejected.
- Statement validation is minimal; more robust input validation is planned.
- Memory allocated for column values in `getRow()` is not currently freed, which can lead to memory leaks in long-running applications.

Contributions and improvements are welcome.

