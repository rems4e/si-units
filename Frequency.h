//
//  AngularSpeed.h
//
//  Created by Rémi on 17/01/2015.
//

#ifndef Units_AngularSpeed_h
#define Units_AngularSpeed_h

#include "Unit.h"

namespace Units {

    using AngularSpeed = Unit<0, 0, -1, true>;
    using Frequency = Unit<0, 0, -1, true>;

    /**
     * Class representing a physical quatity in s⁻¹. It happens to be able to represent an angular speed (angle per
     * second) and frequency, hence its specialized methods.
     */
    template <>
    class Unit<0, 0, -1, true> : public Unit<0, 0, -1, false> {
        friend class Unit<0, 0, -1, false>;

    public:
        using Unit<0, 0, -1, false>::ValueType;
        using Type = Unit<0, 0, -1, true>;

        friend std::ostream &operator<<(std::ostream &s, Type const &v);

        /**
         * Returns a new angular speed from the value specified in radians per second.
         */
        static constexpr Type makeFromRad_s(long double rad_s) {
            return Type(rad_s);
        }

        /**
         * Returns a new angular speed from the value specified in degrees per second.
         */
        static constexpr Type makeFromDeg_s(long double deg_s) {
            return Type(deg_s * M_PI / 180);
        }

        /**
         * Returns a new angular speed from the value specified in milliradians per second.
         */
        static constexpr Type makeFromMilliRad_s(long double millirad_s) {
            return Type(millirad_s / 1000);
        }

        /**
         * Returns a new frequency from the value specified in Hertz.
         */
        static constexpr Type makeFromHz(long double Hertz) {
            return Type(Hertz * 2 * M_PI);
        }

        /**
         * Returns the value of the angular speed in radians per second.
         */
        template <typename Rep = ValueType>
        constexpr Rep toRad_s() const {
            return (*this).value<Rep>();
        }

        /**
         * Returns the value of the fraquency in Hertz.
         */
        template <typename Rep = ValueType>
        constexpr Rep toHz() const {
            return (*this / (2 * M_PI)).value<Rep>();
        }

        /**
         * Returns the value of the angular speed in milliradians per second.
         */
        template <typename Rep = ValueType>
        constexpr Rep toMilliRad_s() const {
            return (*this * 1000).value<Rep>();
        }

        /**
         * Returns the value of the angular speed in degrees per second.
         */
        template <typename Rep = ValueType>
        constexpr Rep toDeg_s() const {
            return (*this * 180 / M_PI).value<Rep>();
        }

    private:
        using Unit<0, 0, -1, false>::Unit;
    };

    namespace UnitsLiterals {
        /**
         * Creates an angular speed quantity from a value expressed in multiples of π radians per second : 1_PI_s,
         * 2_PI_s, 0.5_PI_s…
         */
        inline constexpr AngularSpeed operator"" _PI_s(long double val) {
            return AngularSpeed::makeFromRad_s(val * M_PI);
        }
        inline constexpr AngularSpeed operator"" _PI_s(unsigned long long val) {
            return AngularSpeed::makeFromRad_s(val * M_PI);
        }

        /**
         * Creates an angular speed quantity from a value expressed in radians per second : 1_rad_s, 2_rad_s, 0.5_rad_s…
         */
        inline constexpr AngularSpeed operator"" _rad_s(long double v) {
            return AngularSpeed::makeFromRad_s(v);
        }
        inline constexpr AngularSpeed operator"" _rad_s(unsigned long long v) {
            return AngularSpeed::makeFromRad_s(v);
        }

        /**
         * Creates an angular speed quantity from a value expressed in milliradians per second : 1_mrad_s, 2_mrad_s,
         * 0.5_mrad_s…
         */
        inline constexpr AngularSpeed operator"" _mrad_s(long double v) {
            return AngularSpeed::makeFromRad_s(v / 1000);
        }
        inline constexpr AngularSpeed operator"" _mrad_s(unsigned long long v) {
            return AngularSpeed::makeFromRad_s(v / 1000.0);
        }

        /**
         * Creates an angular speed quantity from a value expressed in degrees per second : 1_deg_s, 2_deg_s, 0.5_deg_s…
         */
        inline constexpr AngularSpeed operator"" _deg_s(long double v) {
            return AngularSpeed::makeFromDeg_s(v);
        }
        inline constexpr AngularSpeed operator"" _deg_s(unsigned long long v) {
            return AngularSpeed::makeFromDeg_s(v);
        }

        /**
         * Creates a frequency quantity from a value expressed in Hert : 1_Hz, 2_Hz, 0.5_Hz…
         */
        inline constexpr Frequency operator"" _Hz(long double f) {
            return Frequency::makeFromHz(f);
        }
        inline constexpr Frequency operator"" _Hz(unsigned long long f) {
            return Frequency::makeFromHz(f);
        }
    }
}

#endif
