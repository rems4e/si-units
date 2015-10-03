//
//  Math.h
//
//  Created by Rémi on 03/10/2015.
//
//

#ifndef Units_Math_h
#define Units_Math_h

#include <cmath>

namespace Units {
    /**
     * These functions provide compile-time sine and cosine values with a relative error (compared to the std::sin/cos
     * results) less than 1e-10 in magnitude (tested for a subset of values, no warranty is given for the whole
     * range ]-∞, +∞[ !).
     */
    template <typename T>
    constexpr T sin_constexpr(const T x) {
        if(x < 0) {
            return sin_constexpr(M_PI - x);
        }
        if(x < 1e-6) {
            return x;
        }
        auto toCube = sin_constexpr(x / 3.0);
        return 3 * sin_constexpr(x / 3.0) - 4 * toCube * toCube * toCube;
    }

    template <typename T>
    constexpr T cos_constexpr(const T x) {
        return sin_constexpr(M_PI / 2 - x);
    }
}

#endif /* Math_h */