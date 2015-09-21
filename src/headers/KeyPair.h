#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool is_file(const char*);

struct KeyPair {
    string pub;
    string sec;

    KeyPair();

    void gen();
    string encrypt(string msg);
    string decrypt(string msg, string sec);

};