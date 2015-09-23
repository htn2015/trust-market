#include "headers/Database.h"

Database::Database( const char* db_name ) : _db(nullptr), _stmt(nullptr), _connected(false) {
    _connected = sqlite3_open( db_name, &_db ) == SQLITE_OK;
    _generate();
}

Database::~Database() {
    if ( _db ) {
        sqlite3_close_v2( _db );
        _db = nullptr;
    }

    #ifdef DEV
        string log_str;
        cout << "DATABASE LOG: " << endl;
        while(getline(_log, log_str))
            cout << "\t" << log_str << endl << endl;
    #endif
}

void Database::_generate() {
    execute(
        "create table if not exists graph_nodes ("
            "_id integer primary key,"
            "pub_key text,"
            "address text,"
            "my_belief real,"
            "my_disbelief real,"
            "my_uncertainty real"
        ");"
        "create table if not exists graph_edges ("
            "_id integer primary key,"
            "from_node integer,"
            "to_node integer,"
            "belief real,"
            "disbelief real,"
            "uncertainty real"
        ");"
        "create table if not exists neighbours ("
            "_id integer primary key,"
            "connected_since datetime,"
            "address text,"
            "my_belief real,"
            "my_disbelief real,"
            "my_uncertainty real,"
            "is_vendor boolean"
        ");"
    );
}

void Database::execute(const char* sql, int (*callback)(void*,int,char**,char**), void* param ){
    if(strlen(sql) == 0)
        sql = _current_request.str().c_str();

    // Log each query (if multiple, they are separated by ;)
    stringstream sql_stream(sql);
    string segment;
    while(getline(sql_stream, segment, ';')) {
        _log << segment << endl;
    }

    if( sqlite3_exec( _db, sql, callback, param, &_error_message) != SQLITE_OK ) {
        throw_error(_error_message);
    }
}

void Database::execute(const string& sql, int (*callback)(void*,int,char**,char**), void* param ){
    execute(sql.c_str(), callback, param);
}

sqlite3_int64 Database::inserted_id() const {
    return sqlite3_last_insert_rowid( _db );
}

void Database::throw_error() {
    throw runtime_error( sqlite3_errmsg( _db ) );
}

void Database::throw_error( const char* msg ) {
    throw runtime_error( msg );
}

Database& operator<<( Database& db, const char* sql ) {
    db._current_request << sql;

    if( sql[ strlen(sql) - 1 ] == ';' ) {
        db.execute();
        db._current_request.str("");
        db._current_request.clear();
    }

    return db;
}

template <typename T>
Database& operator<<( Database& db, const T token ) {
    db._current_request << token;

    return db;
}

template Database& operator<<<int>( Database&, const int);
template Database& operator<<<long>( Database&, const long);
template Database& operator<<<float>( Database&, const float);
template Database& operator<<<double>( Database&, const double);

Database::operator bool() const {
    return _connected;
}