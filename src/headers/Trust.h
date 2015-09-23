#pragma once

#include <cmath>

struct Trust {
    float belief, disbelief, uncertainty;

    Trust( float x, float y, float z ) : belief(x), disbelief(y), uncertainty(z) {};

    // Recommendation
    friend Trust operator*( const Trust&, const Trust& );

    // Consensus
    friend Trust operator+( const Trust&, const Trust& );

    // To scalar
    operator float();
};
