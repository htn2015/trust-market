//
// Created by Andrei on 15-09-20.
//

#ifndef HTN2015_KEYGEN_H
#define HTN2015_KEYGEN_H

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


#endif //HTN2015_KEYGEN_H
