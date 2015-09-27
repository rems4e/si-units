//
//  Unit.h
//
//  Created by Rémi on 17/01/2015.
//

#ifndef Units_Unit_h
#define Units_Unit_h

#include <cmath>
#include <limits>

#include <iosfwd>

#ifndef UNITS_NO_OVERFLOW_CHECK
#include <iostream>
#endif

namespace Units {

    class UnitBase {
    public:
        using ValueType = double;
    };

    template <int Kg, int M, int S, bool Specialized>
    class Unit : public UnitBase {};

    /**
     * This class is meant to represent a physical quantity in a type-safe manner.
     * It is the base class of a hierarchy of specialized types.
     *
     * @param Kg the integral power of the kilogrammes component.
     * @param M the integral power of the metres component.
     * @param S the integral power of the seconds component.
     */
    template <int Kg, int M, int S>
    class Unit<Kg, M, S, false> : public UnitBase {
        template <int Kg1, int M1, int S1>
        using DerivedType = Unit<Kg1, M1, S1, true>;

    public:
        using ValueType = UnitBase::ValueType;

        /**
         * Create a physical quantity from a raw numerical value.
         * As an example, a length quantity created with a numerical value of 1 will represent a long of 1 metre.

         * @param v The numerical value to assign to the newly created quantity.
         * @return A physical quantiy wrapping the given numerical value.
         */
        static constexpr DerivedType<Kg, M, S> makeFromValue(ValueType v) {
            return DerivedType<Kg, M, S>{ v };
        }

        /**
         * Returns the maximal value (i.e. the magnitude) of the quantity. Depends only on the underlying type.
         */
        static constexpr DerivedType<Kg, M, S> max() {
            return DerivedType<Kg, M, S>(std::numeric_limits<ValueType>::max());
        }

        /**
         * Swaps the value of two instances of the physical quantity.
         */
        constexpr friend void swap(DerivedType<Kg, M, S> &v1, DerivedType<Kg, M, S> const &v2) {
            using std::swap;
            swap(v1._val, v2._val);
        }

        /**
         * Assignment operator.
         */
        constexpr DerivedType<Kg, M, S> &operator=(DerivedType<Kg, M, S> v) {
            std::swap(static_cast<DerivedType<Kg, M, S> &>(*this), v);
            return static_cast<DerivedType<Kg, M, S> &>(*this);
        }

        /**
         * Unary negation operator.
         * @return A new instance with same magnitude but opposite sign of *this.
         */
        constexpr DerivedType<Kg, M, S> operator-() const {
            return makeFromValue(-_val);
        }

        /**
         * Unary plus.
         * @return A copy of *this.
         */
        constexpr DerivedType<Kg, M, S> operator+() const {
            return makeFromValue(_val);
        }

        /**
         * Adds the parameter, a quantity of same dimension, to the current instance.
         */
        constexpr DerivedType<Kg, M, S> &operator+=(DerivedType<Kg, M, S> const &val) {
            _val += val._val;
            return static_cast<DerivedType<Kg, M, S> &>(*this);
        }
        /**
         * Adds two same-dimension instances of physical quantity and returns the result as a new instance.
         */
        constexpr friend DerivedType<Kg, M, S> operator+(DerivedType<Kg, M, S> const &v1, DerivedType<Kg, M, S> const &v2) {
            return makeFromValue(v1._val + v2._val);
        }

        /**
         * Substracts the parameter, a quantity of same dimension, to the current instance.
         */
        constexpr DerivedType<Kg, M, S> &operator-=(DerivedType<Kg, M, S> const &val) {
            _val -= val._val;
            return static_cast<DerivedType<Kg, M, S> &>(*this);
        }

        /**
         * Returns the difference of two physical quantities as a new instance.
         */
        constexpr friend DerivedType<Kg, M, S> operator-(DerivedType<Kg, M, S> const &v1, DerivedType<Kg, M, S> const &v2) {
            return makeFromValue(v1._val - v2._val);
        }

        /**
         * Multiplies the current instance by the parameter.
         * The parameter is a scalar value.
         */
        template <typename U>
        constexpr std::enable_if_t<!std::is_base_of<UnitBase, U>::value, DerivedType<Kg, M, S> &> operator*=(U const &val) {
            _val *= val;
            return static_cast<DerivedType<Kg, M, S> &>(*this);
        }

        /**
         * Multiplies the two instance together.
         * The 2nd parameter is a scalar value.
         */
        template <typename U, int Kg1, int M1, int S1>
        constexpr friend std::enable_if_t<!std::is_base_of<UnitBase, U>::value, Unit<Kg1, M1, S1, true>>
        operator*(Unit<Kg1, M1, S1, true> const &v1, U const &v2);


        /**
         * Multiplies the two instance together.
         * The 1st parameter is a scalar value.
         */
        template <typename U, int Kg1, int M1, int S1>
        constexpr friend Unit<Kg1, M1, S1, true> operator*(U const &v1, Unit<Kg1, M1, S1, true> const &v2);

        /**
         * Divides *this by the argument.
         * The parameter is a scalar value.
         */
        template <typename U>
        constexpr std::enable_if_t<std::is_arithmetic<U>::value, DerivedType<Kg, M, S> &> operator/=(DerivedType<Kg, M, S> val) {
            _val /= val;
            return static_cast<DerivedType<Kg, M, S> &>(*this);
        }
        /**
         * Returns a physical quantity divided by a scalar.
         */
        template <typename U>
        constexpr friend std::enable_if_t<std::is_arithmetic<U>::value, DerivedType<Kg, M, S>>
        operator/(DerivedType<Kg, M, S> const &v1, U v2) {
            return makeFromValue(v1._val / v2);
        }

        /**
         * Sets the value of the quantity to the remainder of the division of the instance by the parameter.
         * @param val The divisor.
         * @return The current instance, after it has been assigned by the remainder of the division.
         */
        constexpr DerivedType<Kg, M, S> &operator%=(ValueType val) {
            _val = std::fmod(_val, val);
            return static_cast<DerivedType<Kg, M, S> &>(*this);
        }

        /**
         * Returns the remainder of the division of the two parameters. E.g., 14_m % 4 returns 2_m, as 14_m - 4 * 3_m =
         * 2_m.
         * @param v1 The dividend of the division.
         * @param v2 The divisor of the division.
         * @return The remainder f the division.
         */
        constexpr friend DerivedType<Kg, M, S> operator%(DerivedType<Kg, M, S> const &v1, DerivedType<Kg, M, S> v2) {
            return makeFromValue(std::fmod(v1._val, v2._val));
        }

        /**
         * Tests for strict equality between the values.
         * Be careful that if the underlying type is floating point, a comparison with a delta may be better suitable.
         */
        constexpr friend bool operator==(DerivedType<Kg, M, S> const &val1, DerivedType<Kg, M, S> const &val2) {
            return val1._val == val2._val;
        }

        /**
         * Tests for strict inequality between the values.
         * Be careful that if the underlying type is floating point, a comparison with a delta may be better suitable.
         */
        constexpr friend bool operator!=(DerivedType<Kg, M, S> const &val1, DerivedType<Kg, M, S> const &val2) {
            return !(val1 == val2);
        }

        /**
         * Compares two physical quantities.
         */
        constexpr friend bool operator<(DerivedType<Kg, M, S> const &val1, DerivedType<Kg, M, S> const &val2) {
            return val1._val < val2._val;
        }

        /**
         * Compares two physical quantities.
         */
        constexpr friend bool operator>(DerivedType<Kg, M, S> const &val1, DerivedType<Kg, M, S> const &val2) {
            return val2._val < val1._val;
        }

        /**
         * Compares two physical quantities.
         */
        constexpr friend bool operator<=(DerivedType<Kg, M, S> const &val1, DerivedType<Kg, M, S> const &val2) {
            return !(val1._val > val2._val);
        }

        /**
         * Compares two physical quantities.
         */
        constexpr friend bool operator>=(DerivedType<Kg, M, S> const &val1, DerivedType<Kg, M, S> const &val2) {
            return !(val1._val < val2._val);
        }

        /**
         * Returns the absolute value (magnitude) of the quantity.
         */
        constexpr friend DerivedType<Kg, M, S> abs(DerivedType<Kg, M, S> const &val) {
            return val >= DerivedType<Kg, M, S>() ? val : -val;
        }

        /**
         * Retourns the cosine of the quantity.
         */
        constexpr friend ValueType cos(DerivedType<Kg, M, S> const &val) {
            using std::cos;
            return cos(val._val);
        }
        /**
         * Retourns the sine of the quantity.
         */
        constexpr friend ValueType sin(DerivedType<Kg, M, S> const &val) {
            using std::sin;
            return sin(val._val);
        }

        /**
         * Accède à la valeur numérique stockée par l'instance.
         * Accessible uniquement aux classes filles.
         * Par défault, le type de la valeur retourné est ValueType, et donc capable de retourner directement la valeur
         * de l'instance.
         * En revanche, si le type de retour est spécifié, une vérification est effectuée pour être sûr que la
         * conversion
         * est sans overflow.
         * Si c'est le cas, on affiche une erreur, et la valeur retournée représente une valeur incohérente.
         * Ce test n'est pas effectué si la macro UNITS_NO_OVERFLOW_CHECK est définie, mais la valeur retournée sera
         *bien
         * sûr toujours incohérente.
         *
         * @return la valeur numérique de l'instance.
         */

    protected:
        /**
         * Value constructor.
         */
        constexpr Unit(ValueType val) : _val(val) {}

        /**
         * Default constructor, the numeric value of the quantity is value-initialized.
         */
        constexpr Unit() : _val(ValueType()) {}
        /**
         * Copy constructor.
         */
        Unit(DerivedType<Kg, M, S> const &v) : _val(v._val) {}

        /**
         * Gives access to the dimensionless numerical value of the instance.
         * It is to be used by the child classes (e.g. the Length class uses this method for the return value of its
         * toM() method.)
         * It allows for casting the value to any arithmetic type, and optionally printing a warning in case of
         * overflow, depending if the preprocessort define UNITS_NO_OVERFLOW_CHECK is set or not.
         */
        template <typename U = ValueType>
        constexpr U value() const {
#ifndef UNITS_NO_OVERFLOW_CHECK
            if(_val > std::numeric_limits<U>::max() || _val < std::numeric_limits<U>::lowest()) {
                std::cerr << "The physical quantity's magnitude can not be represented with the requested data type, "
                             "an incoherent value will be generated." << std::endl;
            }
#endif // UNITS_NO_OVERFLOW_CHECK
            return static_cast<U>(_val);
        }

        ValueType _val;
    };

    template <typename U, int Kg1, int M1, int S1>
    constexpr std::enable_if_t<!std::is_base_of<UnitBase, U>::value, Unit<Kg1, M1, S1, true>>
    operator*(Unit<Kg1, M1, S1, true> const &v1, U const &v2) {
        return Unit<Kg1, M1, S1, true>::makeFromValue(v1.value() * v2);
    }

    template <typename U, int Kg1, int M1, int S1>
    constexpr Unit<Kg1, M1, S1, true> operator*(U const &v1, Unit<Kg1, M1, S1, true> const &v2) {
        return v2 * v1;
    }

    template <int Kg, int M, int S>
    class Unit<Kg, M, S, true> : public Unit<Kg, M, S, false> {
        friend class Unit<Kg, M, S, false>;
        using Unit<Kg, M, S, false>::Unit;
    };
}

#endif
