//
//  Mass.h
//
//  Created by Rémi on 17/01/2015.
//

#ifndef Units_Mass_h
#define Units_Mass_h

#include "Unit.h"

namespace Units {

    using Mass = Unit<1, 0, 0, true>;

    /**
     * Class representing a mass quantity.
     */
    template <>
    class Unit<1, 0, 0, true> : public Unit<1, 0, 0, false> {
        friend class Unit<1, 0, 0, false>;

    public:
        using Unit<1, 0, 0, false>::ValueType;
        using Type = Unit<1, 0, 0, true>;

        friend std::ostream &operator<<(std::ostream &stream, Type const &v);

        /**
         * Returns a new mass from the value specified in grammes.
         */
        static constexpr Type makeFromG(long double g) {
            return Type(g / 1000);
        }

        /**
         * Returns a new mass from the value specified in kilogrammes.
         */
        static constexpr Type makeFromKg(long double kg) {
            return Type(kg);
        }

        /**
         * Returns the value of the mass in kilogrammes.
         */
        template <typename Rep = ValueType>
        constexpr Rep toKg() const {
            return (*this).value<Rep>();
        }

    private:
        using Unit<1, 0, 0, false>::Unit;
    };

    namespace UnitsLiterals {
        /**
         * Creates an mass quantity from a value expressed in grammes : 1_g, 2_g, 0.5_g…
         */
        inline constexpr Mass operator"" _g(long double g) {
            return Mass::makeFromG(g);
        }
        inline constexpr Mass operator"" _g(unsigned long long g) {
            return Mass::makeFromG(g);
        }

        /**
         * Creates an mass quantity from a value expressed in kilogrammes : 1_kg, 2_kg, 0.5_kg…
         */
        inline constexpr Mass operator"" _kg(long double kg) {
            return Mass::makeFromKg(kg);
        }
        inline constexpr Mass operator"" _kg(unsigned long long kg) {
            return Mass::makeFromKg(kg);
        }
    }
}

#endif
