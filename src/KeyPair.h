#ifndef HTN2015_KEYPAIR_H
#define HTN2015_KEYPAIR_H

struct KeyPair {
    long pub;
    long sec;

    KeyPair(long, long);
    KeyPair();

    void generate();
    long encrypt(long message);
    long decrypt(long message);
};


#endif //HTN2015_KEYPAIR_H
