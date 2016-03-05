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
//  UnitsTests.h
//
//  Created by Rémi on 03/10/2015.
//
//

#ifndef UnitsTests_h
#define UnitsTests_h

/**
 * Define UNITS_TESTS this before including the "Units.h" to run basic compile-time unit tests (no pun intended).
 */
#ifdef UNITS_TESTS

namespace Units {
    namespace UnitsTests {
        using namespace UnitsLiterals;

        static_assert(sin_constexpr(1_PI) < 1e-15, "");
        static_assert(cos_constexpr(0.5_PI) < 1e-15, "");

        static_assert(sin_constexpr(0.5_PI) > (1 - 1e-15), "");
        static_assert(cos_constexpr(1_PI) < -(1 - 1e-15), "");

        static_assert(1 / 1_s == 1_Hz, "");
        static_assert(1 / (2 * M_PI) / 1_s == 1_rad_s, "");

        static_assert(1_rad / 1_s == 1_rad_s, "");
        static_assert(1_rad_s * 1_s == 1_rad, "");
        static_assert(1_rad_s * 2 * M_PI == 1_Hz, "");

        static_assert((1_rad).toRad() == 1, "");
        static_assert((1_rad_s).toRad_s() == 1, "");
        static_assert((1_Hz).toHz() == 1, "");

        static_assert((1_Hz).toRad_s() == 2 * M_PI, "");

        static_assert((1_km).toM() - 1000 < 1e-15, "");
        static_assert((1_cm).toMm() - 10 < 1e-15, "");
    }
}

#endif

#endif /* UnitTests_h */
