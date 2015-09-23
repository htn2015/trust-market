#include "headers/Trust.h"

Trust operator*(const Trust& AB, const Trust &BC) {
    return Trust(
        AB.belief * BC.belief,
        AB.belief * BC.disbelief,
        AB.disbelief + AB.uncertainty + AB.belief * BC.uncertainty
    );
}

Trust operator+(const Trust& Ap, const Trust& Bp) {

    float quotient = Ap.uncertainty + Bp.uncertainty - Ap.uncertainty * Bp.uncertainty;

    return Trust(
        (Ap.belief * Bp.uncertainty + Bp.belief * Ap.uncertainty) / quotient,
        (Ap.disbelief * Bp.uncertainty + Bp.disbelief * Ap.uncertainty) / quotient,
        (Ap.uncertainty * Bp.uncertainty) / quotient
    );
}

Trust::operator float() {
    return (1-uncertainty) * pow((belief/(belief + disbelief)), 2);
}