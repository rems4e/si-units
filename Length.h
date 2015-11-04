//
//  Length.h
//
//  Created by Rémi on 17/01/2015.
//

#ifndef Units_Length_h
#define Units_Length_h

#include "Unit.h"

namespace Units {

    using Length = Unit<0, 1, 0, true>;
    using Distance = Unit<0, 1, 0, true>;

    /**
     * Class representing a length quantity.
     */
    template <>
    class Unit<0, 1, 0, true> : public Unit<0, 1, 0, false> {
        friend class Unit<0, 1, 0, false>;

    public:
        using Unit<0, 1, 0, false>::ValueType;
        using Type = Unit<0, 1, 0, true>;

        friend std::ostream &operator<<(std::ostream &s, Type const &d);

        /**
         * Returns a new length from the value specified in millimetres.
         */
        static constexpr Type makeFromMm(long double mm) {
            return Type(mm / 1000);
        }

        /**
         * Returns a new length from the value specified in centimetres.
         */
        static constexpr Type makeFromCm(long double cm) {
            return Type(cm / 100);
        }

        /**
         * Returns a new length from the value specified in decimetres.
         */
        static constexpr Type makeFromDm(long double dm) {
            return Type(dm / 10);
        }

        /**
         * Returns a new length from the value specified in metres.
         */
        static constexpr Type makeFromM(long double m) {
            return Type(m);
        }

        /**
         * Returns a new length from the value specified in kilometres.
         */
        static constexpr Type makeFromKm(long double km) {
            return Type(km * 1000);
        }

        /**
         * Returns the value of the length in millimetres.
         */
        template <typename Rep = ValueType>
        constexpr Rep toMm() const {
            return (*this * 1000).value<Rep>();
        }

        /**
         * Returns the value of the length in metres.
         */
        template <typename Rep = ValueType>
        constexpr Rep toM() const {
            return (*this).value<Rep>();
        }

        /**
         * Returns the value of the length in decimetres.
         */
        template <typename Rep = ValueType>
        constexpr Rep toDm() const {
            return (*this * 10).value<Rep>();
        }


    private:
        using Unit<0, 1, 0, false>::Unit;
    };

    namespace UnitsLiterals {
        /**
         * Creates an length quantity from a value expressed in millimetres : 1_mm, 2_mm, 0.5_mm…
         */
        inline constexpr Length operator"" _mm(long double dist) {
            return Length::makeFromMm(dist);
        }
        inline constexpr Length operator"" _mm(unsigned long long dist) {
            return Length::makeFromMm(dist);
        }

        /**
         * Creates an length quantity from a value expressed in centimetres : 1_cm, 2_cm, 0.5_cm…
         */
        inline constexpr Length operator"" _cm(long double dist) {
            return Length::makeFromCm(dist);
        }
        inline constexpr Length operator"" _cm(unsigned long long dist) {
            return Length::makeFromCm(dist);
        }

        /**
         * Creates an length quantity from a value expressed in decimetres : 1_dm, 2_dm, 0.5_dm…
         */
        inline constexpr Length operator"" _dm(long double dist) {
            return Length::makeFromDm(dist);
        }
        inline constexpr Length operator"" _dm(unsigned long long dist) {
            return Length::makeFromDm(dist);
        }

        /**
         * Creates an length quantity from a value expressed in metres : 1_m, 2_m, 0.5_m…
         */
        inline constexpr Length operator"" _m(long double dist) {
            return Length::makeFromM(dist);
        }
        inline constexpr Length operator"" _m(unsigned long long dist) {
            return Length::makeFromM(dist);
        }

        /**
         * Creates an length quantity from a value expressed in kilometres : 1_km, 2_km, 0.5_km…
         */
        inline constexpr Length operator"" _km(long double dist) {
            return Length::makeFromKm(dist);
        }
        inline constexpr Length operator"" _km(unsigned long long dist) {
            return Length::makeFromKm(dist);
        }
    }
}

#endif
