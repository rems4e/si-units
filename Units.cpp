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
//  Units.cpp
//
//  Created by Rémi on 04/05/2015.
//

#include "Units.h"
#include <iostream>

#ifdef UNITS_HEADER_ONLY
#define UNITS_CONDIIONAL_INLINE inline
#else
#define UNITS_CONDIIONAL_INLINE
#endif

namespace Units {

    UNITS_CONDIIONAL_INLINE std::ostream &operator<<(std::ostream &s, Length const &d) {
        if(std::abs(d._val) >= 1)
            s << d._val << " m";
        else if(std::abs(d._val) >= 1e-2)
            s << d._val * 1e2 << " cm";
        else
            s << d._val * 1e3 << " mm";

        return s;
    }

    UNITS_CONDIIONAL_INLINE std::ostream &operator<<(std::ostream &s, Speed const &v) {
        if(std::abs(v._val) >= 1)
            s << v._val << " m/s";
        else if(std::abs(v._val) >= 1e-2)
            s << v._val * 1e2 << " cm/s";
        else
            s << v._val * 1e3 << " mm/s";

        return s;
    }

    UNITS_CONDIIONAL_INLINE std::ostream &operator<<(std::ostream &s, AngularSpeed const &v) {
        return s << v._val << " s⁻¹";
    }

    UNITS_CONDIIONAL_INLINE std::ostream &operator<<(std::ostream &stream, Surface const &s) {
        return stream << s._val << " m²";
    }

    UNITS_CONDIIONAL_INLINE std::ostream &operator<<(std::ostream &stream, Mass const &m) {
        return stream << m._val << " kg";
    }

    UNITS_CONDIIONAL_INLINE std::ostream &operator<<(std::ostream &s, Time const &d) {
        if(std::abs(d._val) >= 3600)
            s << d._val / 3600 << " h";
        else if(std::abs(d._val) >= 60)
            s << d._val / 60 << " min";
        else if(std::abs(d._val) >= 1)
            s << d._val << " s";
        else if(std::abs(d._val) >= 1e-3)
            s << d._val * 1e3 << " ms";
        else if(std::abs(d._val) >= 1e-6)
            s << d._val * 1e6 << " us";
        else
            s << d._val * 1e9 << " ns";

        return s;
    }

    UNITS_CONDIIONAL_INLINE std::ostream &operator<<(std::ostream &s, Angle const &v) {
        return s << v._val;
    }
}
