//
// Created by Andrei on 15-09-19.
//

#ifndef HTN2015_TRUST_H
#define HTN2015_TRUST_H


struct Trust {
    int b,d,u;
    Trust(int x, int y, int z) : b(x), d(y), u(z) {};

    Trust recommendation(Trust AB, Trust BC);
    Trust consensus(Trust Ap, Trust Bp);
};


#endif //HTN2015_TRUST_H
