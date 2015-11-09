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
//  Angle.h
//
//  Created by Rémi on 17/01/2015.
//

#ifndef Units_Angle_h
#define Units_Angle_h

#include "Unit.h"

namespace Units {

    using Angle = Unit<0, 0, 0, true>;
    using PhysicalQuantity = Unit<0, 0, 0, true>;

    /**
     * Class representing a dimentionless quantity. It happens to be also able to represent an angle, hence its
     * specialized member functions.
     */
    template <>
    class Unit<0, 0, 0, true> : public Unit<0, 0, 0, false> {
        friend class Unit<0, 0, 0, false>;

    public:
        using Unit<0, 0, 0, false>::ValueType;
        using Type = Unit<0, 0, 0, true>;

        friend std::ostream &operator<<(std::ostream &s, Type const &v);

        /**
         * Returns a new angle from the value specified in radians.
         */
        static inline constexpr Type makeFromRad(long double rad) {
            return Type(rad / (2 * M_PI));
        }

        /**
         * Returns a new angle from the value specified in milliradians.
         */
        static inline constexpr Type makeFromMilliRad(long double millirad) {
            return Type(millirad / 1000 / (2 * M_PI));
        }

        /**
         * Returns a new angle from the value specified in degrees.
         */
        static inline constexpr Type makeFromDeg(long double deg) {
            return Type(deg / 360);
        }

        /**
         * Returns the value of the angle in radians.
         */
        template <typename Rep = ValueType>
        constexpr Rep toRad() const {
            return (*this * (2 * M_PI)).value<Rep>();
        }

        /**
         * Returns the value of the angle in degrees.
         */
        template <typename Rep = ValueType>
        constexpr Rep toDeg() const {
            return (*this * 360).value<Rep>();
        }

        /**
         * Returns the value of the angle in milliradians.
         */
        template <typename Rep = ValueType>
        constexpr Rep toMilliRad() const {
            return (*this * 1000 * (2 * M_PI)).value<Rep>();
        }

        /**
         * Returns a copy of the current instance, but converted to be in the interval [0, 2π[.
         */
        constexpr Type toMod2Pi() const {
            return ((*this % Type::makeFromRad(2 * M_PI)) + Type::makeFromRad(4 * M_PI)) % Type::makeFromRad(2 * M_PI);
        }

        /**
         * Returns a copy of the current instance, but converted to be in the interval [-π, π[.
         */
        constexpr Type toMinusPiPi() const {
            auto mod2Pi = this->toMod2Pi();

            if(mod2Pi >= Type::makeFromRad(M_PI))
                mod2Pi -= Type::makeFromRad(2 * M_PI);
            else if(mod2Pi < Type::makeFromRad(-M_PI))
                mod2Pi += Type::makeFromRad(2 * M_PI);

            return mod2Pi;
        }

        // Allows for conversion from a dimensionless value to its scalar counterpart
        operator UnitBase::ValueType() const {
            return this->value();
        }

    private:
        using Unit<0, 0, 0, false>::Unit;
    };

    namespace UnitsLiterals {
        /**
         * Creates an angular quantity from a value expressed in multiples of π radians : 1_PI, 2_PI, 0.5_PI…
         */
        inline constexpr Angle operator"" _PI(long double val) {
            return Angle::makeFromRad(val * M_PI);
        }
        inline constexpr Angle operator"" _PI(unsigned long long val) {
            return Angle::makeFromRad(val * M_PI);
        }

        /**
         * Creates an angular quantity from a value expressed in degrees : 1_deg, 2_deg, 0.5_deg…
         */
        inline constexpr Angle operator"" _deg(long double deg) {
            return Angle::makeFromDeg(deg);
        }
        inline constexpr Angle operator"" _deg(unsigned long long deg) {
            return Angle::makeFromDeg(deg);
        }

        /**
         * Creates an angular quantity from a value expressed in radians : 1_rad, 2_rad, 0.5_rad…
         */
        inline constexpr Angle operator"" _rad(long double rad) {
            return Angle::makeFromRad(rad);
        }
        inline constexpr Angle operator"" _rad(unsigned long long rad) {
            return Angle::makeFromRad(rad);
        }

        /**
         * Creates an angular quantity from a value expressed in milliradians : 1_mrad, 2_mrad, 0.5_mrad…
         */
        inline constexpr Angle operator"" _mrad(long double rad) {
            return Angle::makeFromMilliRad(rad);
        }
        inline constexpr Angle operator"" _mrad(unsigned long long rad) {
            return Angle::makeFromMilliRad(rad);
        }
    }
}

#endif
