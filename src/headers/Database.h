#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <sqlite3.h>
#include <functional>

#include "_.h"

using namespace std;

class Database {
protected:
    stringstream current_request;

    sqlite3* _db;
    sqlite3_stmt* _stmt;

    bool _connected;
    char* _error_message;

    void _generate();

public:
    Database(const char* db_name = DATABSE_FILE);
    ~Database();

    void execute( const char* = "", int (*callback)(void*,int,char**,char**) = nullptr, void* param = nullptr );
    void execute( const string&, int (*callback)(void*,int,char**,char**) = nullptr, void* param = nullptr );

    sqlite3_int64 inserted_id() const;

    void throw_error();
    void throw_error( const char* );

    operator bool() const;

    template <typename T>
    friend Database& operator<<( Database&, const T );
    friend Database& operator<<( Database&, const char* );
};