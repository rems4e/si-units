//
//  Surface.h
//
//  Created by Rémi on 17/01/2015.
//

#ifndef Units_Surface_h
#define Units_Surface_h

#include "Unit.h"

namespace Units {
    using Surface = Unit<0, 2, 0, true>;

    /**
     * Class representing a surface/area quantity.
     */
    template <>
    class Unit<0, 2, 0, true> : public Unit<0, 2, 0, false> {
        friend class Unit<0, 2, 0, false>;

    public:
        using Unit<0, 2, 0, false>::ValueType;
        using Type = Unit<0, 2, 0, true>;

        friend std::ostream &operator<<(std::ostream &stream, Type const &v);

        /**
         * Returns a new surface/area from the value specified in squared millimetres.
         */
        static constexpr Type makeFromMm2(long double mm2) {
            return Type(mm2 / 1000000);
        }

        /**
         * Returns a new surface/area from the value specified in squared centimetres.
         */
        static constexpr Type makeFromCm2(long double cm2) {
            return Type(cm2 / 10000);
        }

        /**
         * Returns a new surface/area from the value specified in squared decimetres.
         */
        static constexpr Type makeFromDm2(long double dm2) {
            return Type(dm2 / 100);
        }

        /**
         * Returns a new surface/area from the value specified in squared metres.
         */
        static constexpr Type makeFromM2(long double m2) {
            return Type(m2);
        }

        /**
         * Returns the value of the surface/area in squared metres.
         */
        template <typename Rep = ValueType>
        constexpr Rep toM2() const {
            return (*this).value<Rep>();
        }

        /**
         * Returns the value of the surface/area in squared millimetres.
         */
        template <typename Rep = ValueType>
        constexpr Rep toMm2() const {
            return (*this * 1000000).value<Rep>();
        }

    private:
        using Unit<0, 2, 0, false>::Unit;
    };

    namespace UnitsLiterals {
        /**
         * Creates a surface/area quantity from a value expressed in squared millimetres : 1_mm2, 2_mm2, 0.5_mm2…
         */
        inline constexpr Surface operator"" _mm2(long double dist) {
            return Surface::makeFromMm2(dist);
        }
        inline constexpr Surface operator"" _mm2(unsigned long long dist) {
            return Surface::makeFromMm2(dist);
        }

        /**
         * Creates a surface/area quantity from a value expressed in squared metres : 1_m2, 2_m2, 0.5_m2…
         */
        inline constexpr Surface operator"" _m2(long double dist) {
            return Surface::makeFromM2(dist);
        }
        inline constexpr Surface operator"" _m2(unsigned long long dist) {
            return Surface::makeFromM2(dist);
        }
    }
}

#endif
