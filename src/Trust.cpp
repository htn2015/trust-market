#include "Trust.h"


Trust Trust::recommendation(Trust AB, Trust BC){
    return Trust(AB.b*BC.b, AB.b*BC.d, AB.d+AB.u+AB.b*BC.u);
}

Trust Trust::consensus(Trust Ap, Trust Bp){
    return Trust((Ap.b*Bp.u+Bp.b*Ap.u)/(Ap.u+Bp.u-Ap.u*Bp.u),(Ap.d*Bp.u+Bp.d*Ap.u)/(Ap.u+Bp.u-Ap.u*Bp.u),Ap.u*Bp.u/(Ap.u+Bp.u-Ap.u*Bp.u));
}