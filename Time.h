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
//  Time.h
//
//  Created by Rémi on 17/01/2015.
//

#ifndef Units_Time_h
#define Units_Time_h

#include "Unit.h"
#include <chrono>

namespace Units {

    using Time = Unit<0, 0, 1, true>;
    using Duration = Time;

    /**
     * Class representing a time/duration quantity.
     */
    template <>
    class Unit<0, 0, 1, true> : public Unit<0, 0, 1, false> {
        friend class Unit<0, 0, 1, false>;

    public:
        using Unit<0, 0, 1, false>::ValueType;
        using Type = Unit<0, 0, 1, true>;

        friend std::ostream &operator<<(std::ostream &s, Type const &d);

        /**
         * Returns a new time/duration from the value specified in nanoseconds.
         */
        static constexpr Type makeFromNs(long double ns) {
            return Type(ns / 1e9);
        }

        /**
         * Returns a new time/duration from the value specified in microseconds.
         */
        static constexpr Type makeFromUs(long double us) {
            return Type(us / 1e6);
        }

        /**
         * Returns a new time/duration from the value specified in millimsecond.
         */
        static constexpr Type makeFromMs(long double ms) {
            return Type(ms / 1e3);
        }

        /**
         * Returns a new time/duration from the value specified in seconds.
         */
        static constexpr Type makeFromS(long double s) {
            return Type(s);
        }

        /**
         * Returns a new time/duration from the specified std::chrono::duration.
         */
        template <typename T>
        static constexpr Type makeFromSystemDelay(T const &delay) {
            return makeFromNs(std::chrono::duration_cast<std::chrono::nanoseconds>(delay).count());
        }

        /**
         * Returns the value of the time/duration in seconds.
         */
        template <typename Rep = ValueType>
        constexpr Rep toS() const {
            return (*this).value<Rep>();
        }

        /**
         * Returns the value of the time/duration as a std::chrono::nanoseconds object, for interoperability with the
         * std durations facilities.
         */
        std::chrono::nanoseconds toSystemDelay() const {
            return std::chrono::nanoseconds(static_cast<long long>(this->toS() * 1e9));
        }

        operator std::chrono::nanoseconds() const {
            return this->toSystemDelay();
        }

    private:
        using Unit<0, 0, 1, false>::Unit;
    };

    namespace UnitsLiterals {
        /**
         * Creates a time/duration quantity from a value expressed in nanoseconds : 1_ns, 2_ns, 0.5_ns…
         */
        inline constexpr Time operator"" _ns(long double duration) {
            return Time::makeFromNs(duration);
        }
        inline constexpr Time operator"" _ns(unsigned long long duration) {
            return Time::makeFromNs(duration);
        }

        /**
         * Creates a time/duration quantity from a value expressed in microseconds : 1_us, 2_us, 0.5_us…
         */
        inline constexpr Time operator"" _us(long double duration) {
            return Time::makeFromUs(duration);
        }
        inline constexpr Time operator"" _us(unsigned long long duration) {
            return Time::makeFromUs(duration);
        }

        /**
         * Creates a time/duration quantity from a value expressed in milliseconds : 1_ms, 2_ms, 0.5_ms…
         */
        inline constexpr Time operator"" _ms(long double duration) {
            return Time::makeFromMs(duration);
        }
        inline constexpr Time operator"" _ms(unsigned long long duration) {
            return Time::makeFromMs(duration);
        }

        /**
         * Creates a time/duration quantity from a value expressed in seconds : 1_s, 2_s, 0.5_s…
         */
        inline constexpr Time operator"" _s(long double duration) {
            return Time::makeFromS(duration);
        }
        inline constexpr Time operator"" _s(unsigned long long duration) {
            return Time::makeFromS(duration);
        }

        /**
         * Creates a time/duration quantity from a value expressed in minutes : 1_min, 2_min, 0.5_min…
         */
        inline constexpr Time operator"" _min(long double duration) {
            return Time::makeFromS(duration * 60);
        }
        inline constexpr Time operator"" _min(unsigned long long duration) {
            return Time::makeFromS(duration * 60);
        }

        /**
         * Creates a time/duration quantity from a value expressed in hours : 1_h, 2_h, 0.5_h…
         */
        inline constexpr Time operator"" _h(long double duration) {
            return Time::makeFromS(duration * 3600);
        }
        inline constexpr Time operator"" _h(unsigned long long duration) {
            return Time::makeFromS(duration * 3600);
        }
    }
}

#endif
