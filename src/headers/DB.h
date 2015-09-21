#pragma once

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