/*
 * Copyright (c) 2015 Rémi Saurel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
    constexpr T sin_constexpr(T const x) {
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
    constexpr T cos_constexpr(T const x) {
        return sin_constexpr(M_PI / 2 - x);
    }
}

#endif /* Math_h */
