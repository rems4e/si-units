//
//  Units.h
//
//  Created by Rémi on 17/01/2015.
//

#ifndef Units_Units_h
#define Units_Units_h

#include "Unit.h"

#include "Angle.h"
#include "Length.h"
#include "Surface.h"
#include "Time.h"
#include "Mass.h"
#include "Speed.h"
#include "AngularSpeed.h"

namespace Units {

    /**
     * Returns the angle of the vector (x, y).
     */
    inline Angle atan2(Length const &y, Length const &x) {
        using std::atan2;
        return Angle::makeFromRad(atan2(y.toM(), x.toM()));
    }

    /**
     * Returs the square root of a surface/area, i.e. the edge length of a square of this surface.
     */
    inline Length sqrt(Surface const &s) {
        using std::sqrt;
        return Length::makeFromM(sqrt(s.toM2()));
    }

    /**
     * Returns the product of a physical quantity with another physical quantity.
     * The return type is coherent (e.g.: speed * time => length).
     */
    template <int Kg1, int M1, int S1, int Kg2, int M2, int S2>
    constexpr auto operator*(Unit<Kg1, M1, S1, true> const &t1,
                             Unit<Kg2, M2, S2, true> const &t2) -> Unit<Kg1 + Kg2, M1 + M2, S1 + S2, true> {
        return Unit<Kg1 + Kg2, M1 + M2, S1 + S2, true>::makeFromValue(t1.value() * t2.value());
    }

    /**
     * Returns the division of a physical quantity by another physical quantity.
     * The return type is coherent (e.g.: time / speed => length).
     */
    template <int Kg1, int M1, int S1, int Kg2, int M2, int S2>
    constexpr auto operator/(Unit<Kg1, M1, S1, true> const &t1,
                             Unit<Kg2, M2, S2, true> const &t2) -> Unit<Kg1 - Kg2, M1 - M2, S1 - S2, true> {
        return Unit<Kg1 - Kg2, M1 - M2, S1 - S2, true>::makeFromValue(t1.value() / t2.value());
    }

    template <int Kg1, int M1, int S1>
    constexpr auto operator/(Unit<Kg1, M1, S1, true> const &t1, Unit<Kg1, M1, S1, true> const &t2) -> UnitBase::ValueType {
        return t1.value() / t2.value();
    }
}

#endif
