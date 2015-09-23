#include "headers/Database.h"

Database::Database( const char* db_name ) : _db(nullptr), _stmt(nullptr), _connected(false) {
    _connected = sqlite3_open( db_name, &_db ) == SQLITE_OK;
}

Database::~Database() {
    if ( _db ) {
        sqlite3_close_v2( _db );
        _db = nullptr;
    }
}

void Database::execute(const string& sql, int (*callback)(void*,int,char**,char**), void* param ){
    if( sqlite3_exec( _db, sql.c_str(), callback, param, &error_message) != SQLITE_OK ) {
        throw_error();
    }
}

void Database::throw_error() {
    throw runtime_error( sqlite3_errmsg( _db ) );
}

void Database::throw_error( char const* msg ) {
    throw runtime_error( msg );
}

Database::operator bool() const {
    return _connected;
}


Database& operator<<( Database& db, const char* sql ) {
    db.current_request << sql;

    if( sql[ strlen(sql) - 1 ] == ';' ) {

        cout << "EXECUTING: " << db.current_request.str() << endl;

        db.execute( db.current_request.str() );
        db.current_request.str("");
        db.current_request.clear();
    }

    return db;
}

template <typename T>
Database& operator<<( Database& db, const T id ) {
    db.current_request << id;

    return db;
}

template Database& operator<<<int>( Database&, const int);
template Database& operator<<<long>( Database&, const long);
template Database& operator<<<float>( Database&, const float);
template Database& operator<<<double>( Database&, const double);


sqlite3_int64 Database::inserted_id() const {
    return sqlite3_last_insert_rowid( _db );
}