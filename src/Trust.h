<<<<<<< HEAD
=======
//
// Created by Andrei on 15-09-19.
//

>>>>>>> 666deeff83547a9e6623ba3b1b78cf9471eaa6da
#ifndef HTN2015_TRUST_H
#define HTN2015_TRUST_H


struct Trust {
    int b,d,u;
    Trust(int x, int y, int z) : b(x), d(y), u(z) {};

    Trust recommendation(Trust AB, Trust BC);
    Trust consensus(Trust Ap, Trust Bp);
};


#endif //HTN2015_TRUST_H
