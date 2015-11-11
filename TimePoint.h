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
//  TimePoint.h
//
//  Created by Rémi on 24/12/2015.
//

#ifndef Units_TimePoint_h
#define Units_TimePoint_h

#include <iostream>
#include <thread>
#include "Time.h"

namespace Units {

    /**
     * A convenience function that mimics the <unistd.h> macro usage, but is type safe and allows specification of a
     * precise delay.
     */
    inline void sleep(Duration const &delay) {
        std::this_thread::sleep_for(delay.toSystemDelay());
    }

    /**
     * Instances of this class represent a particular point in the time.
     */
    class TimePoint {
    public:
        using TimePointClock = std::chrono::high_resolution_clock;
        using TimePointType = std::chrono::time_point<TimePointClock>;

        TimePoint() : _value(TimePointClock::now()) {}
        TimePoint(TimePointType d) : _value(d) {}
        TimePoint(TimePoint const &d) : _value(d.value()) {}

        TimePoint &operator=(TimePoint d) {
            swap(*this, d);
            return *this;
        }

        friend void swap(TimePoint &d1, TimePoint &d2) {
            using std::swap;
            swap(d1._value, d2._value);
        }

        static TimePoint now() {
            return TimePoint(TimePointClock::now());
        }

        /**
         * A TimePoint set relativey far away from now in the past.
         * Does not change accross invocations in a same program execution, so that results of two calls of this
         * function will always be positively compared for equality.
         */
        static TimePoint distantPast() {
            static TimePointType const distantPast = TimePointClock::now() - std::chrono::hours(24) * 365 * 100;
            return distantPast;
        }

        /**
         * A TimePoint set relativey far away from now in the future.
         * Does not change accross invocations in a same program execution, so that results of two calls of this
         * function will always be positively compared for equality.
         */
        static TimePoint distantFuture() {
            static TimePointType const distantFuture = TimePointClock::now() + std::chrono::hours(24) * 365 * 100;
            return distantFuture;
        }

        TimePoint &operator-=(Units::Duration const &d);
        TimePoint &operator+=(Units::Duration const &d);

        /**
         * Accesses the underlying std::chrono::time_point.
         */
        TimePointType value() const {
            return _value;
        }

    private:
        TimePointType _value;
    };

    inline bool operator<(TimePoint const &t1, TimePoint const &t2) {
        return t1.value() < t2.value();
    }

    inline bool operator==(TimePoint const &t1, TimePoint const &t2) {
        return t1.value() == t2.value();
    }

    inline bool operator>(TimePoint const &t1, TimePoint const &t2) {
        return t2 < t1;
    }

    inline bool operator!=(TimePoint const &t1, TimePoint const &t2) {
        return !(t1 == t2);
    }

    inline bool operator<=(TimePoint const &t1, TimePoint const &t2) {
        return !(t1 > t2);
    }

    inline bool operator>=(TimePoint const &t1, TimePoint const &t2) {
        return !(t1 < t2);
    }

    inline Units::Duration operator-(TimePoint const &t1, TimePoint const &t2) {
        auto delta = std::chrono::duration_cast<std::chrono::nanoseconds>(t1.value() - t2.value());
        return Units::Duration::makeFromNs(delta.count());
    }

    inline TimePoint operator-(TimePoint const &t1, Units::Duration const &d2) {
        return TimePoint{t1.value() - d2.toSystemDelay()};
    }

    inline TimePoint operator+(TimePoint const &t1, Units::Duration const &d2) {
        return TimePoint{t1.value() + d2.toSystemDelay()};
    }

    inline TimePoint &TimePoint::operator-=(Units::Duration const &d) {
        *this = *this - d;
        return *this;
    }

    inline TimePoint &TimePoint::operator+=(Units::Duration const &d) {
        *this = *this + d;
        return *this;
    }
}

#endif
