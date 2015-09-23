#pragma once

#include <iostream>

#include <string>
#include <sstream>
#include <functional>
#include <stdexcept>
#include <ctime>

#include "_.h"
#include <sqlite3.h>

using namespace std;

typedef function<void(void)> void_function;

class Database {
protected:
    stringstream current_request;

    sqlite3* _db;
    sqlite3_stmt* _stmt;

    bool _connected;
    char* error_message;

public:
    Database(const char* db_name = DATABSE_FILE);
    ~Database();

    void execute( const string&, int (*callback)(void*,int,char**,char**) = nullptr, void* param = nullptr );

    void throw_error();
    void throw_error( const char* );

    operator bool() const;

    template <typename T>
    friend Database& operator<<( Database&, const T );
    friend Database& operator<<( Database&, const char* );

    sqlite3_int64 inserted_id() const;
};