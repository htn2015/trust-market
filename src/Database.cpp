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
    _current_param = 1;
}

void Database::bind( const string& param ) {
    if( sqlite3_bind_text( _stmt, _current_param, param.c_str(), -1, SQLITE_TRANSIENT ) != SQLITE_OK ) {
        throw_error( "Binding error" );
    }

    _current_param++;
}

void Database::bind( const int param ) {
    if( sqlite3_bind_int( _stmt, _current_param, param ) != SQLITE_OK ) {
        throw_error( "Binding error" );
    }

    _current_param++;
}

void Database::bind( const float& param ) {
    if( sqlite3_bind_double( _stmt, _current_param, double(param) ) != SQLITE_OK ) {
        throw_error( "Binding error" );
    }

    _current_param++;
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

istream& operator>>( istream& is, Database& db ) {
    string sql;
    is >> sql;
    db._prepare( sql );
    return is;
}


sqlite3_int64 Database::inserted_id() const {
    return sqlite3_last_insert_rowid( _db );
}