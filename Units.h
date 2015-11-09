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
#include "Frequency.h"

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
}

#ifdef UNITS_HEADER_ONLY
#include "Units.cpp"
#endif

#include "UnitsTests.h"

#endif
