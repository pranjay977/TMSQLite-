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
#include <tmsqlite>

using namespace sqlite;

int main()
{
    sqliteDB db;

    try
    {
        db.open("mydatabase.db");

        db.executeInsert("insert into users (name, age) values ('Alice', 30)");

        sqlite3_stmt *stmt = db.selectRows("select name, age from users");
        Rows rows(stmt);

        while (rows.hasMoreRows())
        {
            row r;
            r = rows.getRow();

            std::cout << r.getString("name") << " is " << r.getInt("age") << " years old\n";
        }

        db.close();
    }
    catch (SQLiteException &e)
    {
        std::cerr << "Database error: " << e.what() << std::endl;
    }

    return 0;
}
```

## Requirements

- A C++ compiler with `noexcept` support (C++11 or later)
- [SQLite3](https://www.sqlite.org/download.html) development library (`sqlite3.h` and `libsqlite3`)

## Building

Link against the SQLite3 library when compiling, for example:

```bash
g++ -std=c++11 your_program.cpp sqliteDB.cpp -lsqlite3 -o your_program
```

## Project Status

This project is a work in progress. Known limitations in the current implementation include:

- SQL keyword checks (`insert into`, `update`, `delete`, `select`) are case-sensitive and only check the very start of the statement, so queries with leading whitespace or different casing will be rejected.
- Statement validation is minimal; more robust input validation is planned.
- Memory allocated for column values in `getRow()` is not currently freed, which can lead to memory leaks in long-running applications.

Contributions and improvements are welcome.

