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
    }
}

#endif

#endif /* UnitTests_h */
