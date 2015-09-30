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

#endif
