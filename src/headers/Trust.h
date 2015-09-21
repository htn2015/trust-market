#pragma once

struct Trust {
    float b,d,u;
    Trust(float x, float y, float z) : b(x), d(y), u(z) {};

    static Trust recommendation(Trust AB, Trust BC);
    static Trust consensus(Trust Ap, Trust Bp);
};
