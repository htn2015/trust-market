//
// Created by Andrei on 15-09-20.
//

#include "_.h"
#include "DB.h"

DB* DB::instance = nullptr;

DB::DB() {
    DB::connect();
}

DB::~DB() {
    //sqlite3_close(&(this->db));
    delete DB::instance;
};

DB* DB::get_instance() {

    if( !DB::instance )
        DB::instance = new DB;

    return DB::instance;
}

bool DB::connect() {

    //sqlite3* pSqlite3 = *(DB::db);
    //sqlite3_open(DATA_FILE, &pSqlite3);

    return true;
}