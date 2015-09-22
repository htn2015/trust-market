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

void Database::_prepare( const string& sql ) {
    if( sqlite3_prepare_v2( _db, sql.c_str(), -1, &_stmt, nullptr ) != SQLITE_OK ) {
        throw_error();
    }
}

void Database::_extract( void_function callback, bool single = false ) {
    int result;

    while( (result = sqlite3_step(_stmt)) == SQLITE_ROW ) {
        callback();

        if(single) {
            if ( (result = sqlite3_step(_stmt)) == SQLITE_ROW )
                throw_error("Not all rows extracted");

            break;
        }
    }

    if( result != SQLITE_DONE )
        throw_error();

    if( sqlite3_finalize(_stmt) != SQLITE_OK )
        throw_error();

    _stmt = nullptr;
}

void Database::_extract_single( void_function callback ) {
    _extract( callback, true );
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

void Database::operator<<( const string& sql ) {
    _prepare( sql );
}

sqlite3_int64 Database::inserted_id() const {
    return sqlite3_last_insert_rowid( _db );
}