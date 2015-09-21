#ifndef HTN2015_DB_H
#define HTN2015_DB_H

#include <iostream>
#include <sqlite3.h>

using namespace std;

class DB {
private:
    static DB* instance;

    DB();
    ~DB();

    static bool connect();

public:
    static DB* get_instance();
};


#endif //HTN2015_DB_H
