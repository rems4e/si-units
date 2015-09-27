//
//  Speed.h
//
//  Created by Rémi on 17/01/2015.
//

#ifndef Units_Speed_h
#define Units_Speed_h

#include "Unit.h"

namespace Units {

    using Speed = Unit<0, 1, -1, true>;

    /**
     * Class representing a speed quantity.
     */
    template <>
    class Unit<0, 1, -1, true> : public Unit<0, 1, -1, false> {
        friend class Unit<0, 1, -1, false>;

    public:
        using Unit<0, 1, -1, false>::ValueType;
        using Type = Unit<0, 1, -1, true>;

        friend std::ostream &operator<<(std::ostream &s, Type const &v);

        /**
         * Returns a new speed from the value specified in metres per second.
         */
        static constexpr Type makeFromM_s(long double m_s) {
            return Type(m_s);
        }

        /**
         * Returns a new speed from the value specified in decimetres per second.
         */
        static constexpr Type makeFromDm_s(long double dm_s) {
            return Type(dm_s / 10);
        }

        /**
         * Returns a new speed from the value specified in centimetres per second.
         */
        static constexpr Type makeFromCm_s(long double cm_s) {
            return Type(cm_s / 100);
        }

        /**
         * Returns a new speed from the value specified in millimetres per second.
         */
        static constexpr Type makeFromMm_s(long double mm_s) {
            return Type(mm_s / 1000);
        }

        /**
         * Returns the value of the speed in millimetres per second.
         */
        template <typename Rep = ValueType>
        constexpr Rep toMm_s() const {
            return (*this * 1000).value<Rep>();
        }

        /**
         * Returns the value of the speed in metres per second.
         */
        template <typename Rep = ValueType>
        constexpr Rep toM_s() const {
            return (*this).value<Rep>();
        }

        /**
         * Returns the value of the length in decimillimetres per second.
         */
        template <typename Rep = ValueType>
        constexpr Rep toDm_s() const {
            return (*this * 10).value<Rep>();
        }

    private:
        using Unit<0, 1, -1, false>::Unit;
    };

    namespace UnitsLiterals {
        /**
         * Creates an speed quantity from a value expressed in millimetres per second : 1_mm_s, 2_mm_s, 0.5_mm_s…
         */
        inline constexpr Speed operator"" _mm_s(long double v) {
            return Speed::makeFromMm_s(v);
        }
        inline constexpr Speed operator"" _mm_s(unsigned long long v) {
            return Speed::makeFromMm_s(v);
        }

        /**
         * Creates an speed quantity from a value expressed in centimetres per second : 1_cm_s, 2_cm_s, 0.5_cm_s…
         */
        inline constexpr Speed operator"" _cm_s(long double v) {
            return Speed::makeFromCm_s(v);
        }
        inline constexpr Speed operator"" _cm_s(unsigned long long v) {
            return Speed::makeFromCm_s(v);
        }

        /**
         * Creates an speed quantity from a value expressed in decimetres per second : 1_dm_s, 2_dm_s, 0.5_dm_s…
         */
        inline constexpr Speed operator"" _dm_s(long double v) {
            return Speed::makeFromDm_s(v);
        }
        inline constexpr Speed operator"" _dm_s(unsigned long long v) {
            return Speed::makeFromDm_s(v);
        }

        /**
         * Creates an speed quantity from a value expressed in metres per second : 1_m_s, 2_m_s, 0.5_m_s…
         */
        inline constexpr Speed operator"" _m_s(long double v) {
            return Speed::makeFromM_s(v);
        }
        inline constexpr Speed operator"" _m_s(unsigned long long v) {
            return Speed::makeFromM_s(v);
        }
    }
}

#endif
