#pragma once

#include <iostream>

#include <string>
#include <functional>
#include <stdexcept>
#include <ctime>

#include "_.h"
#include <sqlite3.h>

using namespace std;

typedef function<void(void)> void_function;

class Database {
protected:
    sqlite3* _db;
    sqlite3_stmt* _stmt;
    int _current_param;

    bool _connected;

    void _prepare( const string& );
    void _extract( void_function, bool );
    void _extract_single( void_function );

public:
    Database(const char* db_name = DATABSE_FILE);
    ~Database();

    void throw_error();
    void throw_error( const char* );

    void bind( const string& );
    void bind( const int );
    void bind( const float& );

    operator bool() const;
    friend istream& operator>>( istream&, Database& );

    sqlite3_int64 inserted_id() const;
};