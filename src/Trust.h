#ifndef HTN2015_TRUST_H
#define HTN2015_TRUST_H


struct Trust {
    float b,d,u;
    Trust(float x, float y, float z) : b(x), d(y), u(z) {};

    static Trust recommendation(Trust AB, Trust BC);
    static Trust consensus(Trust Ap, Trust Bp);
};


#endif //HTN2015_TRUST_H
