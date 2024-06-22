/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - Vector.hpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: May 24, 2024 [11:15 AM]
//     ||  '-'
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <vector>
#include <iostream>
#include "general.hpp"

// Forward declaration
template < class K >
class Matrix;

#include "Matrix.hpp"

/**
 * Represents a mathematical vector, acting as a wrapper for Matrix
 *
 * @tparam K    Vector's inner working type
 */
template < class K >
class Vector
{
public:
    using value_type  = typename Matrix<K>::value_type;
    using size_type   = typename Matrix<K>::size_type;
    using shape_type  = typename Matrix<K>::shape_type;

    Vector() = delete;
    ~Vector() = default;

    explicit Vector(const size_type& height, const value_type& value = value_type()):
        _matrix(height, 1, value) {}

    Vector(const size_type& height, const std::vector<value_type>& data):
        _matrix(height, 1, data) {}

    explicit Vector(const std::vector<value_type>& data):
        _matrix(data.size(), 1, value_type())
    {
        for (size_type i = 0; i < this->size(); ++i)
            this->_matrix.at(i, 0) = data.at(i);
    }

    Vector(const Vector& other):
        _matrix(other._matrix) {}

    Vector(Vector&& other) noexcept:
        _matrix(std::move(other._matrix)) {}

    template <typename = typename
        std::enable_if<std::is_same<Matrix<value_type>, Matrix<value_type>>::value>::type>
    explicit Vector(const Matrix<value_type>& other):
        _matrix(other) {}

    template <typename = typename
        std::enable_if<std::is_same<Matrix<value_type>, Matrix<value_type>>::value>::type>
    explicit Vector(Matrix<value_type>&& other) noexcept:
        _matrix(std::move(other)) {}

    Vector& operator=(const Vector& rhs)
        { this->_matrix = rhs._matrix; return *this; }

    Vector& operator=(Vector&& rhs) noexcept
        { this->_matrix = std::move(rhs._matrix); return *this; }

    Vector& operator+=(const Vector& rhs)
        { this->_matrix += rhs._matrix; return *this; }

    Vector& operator-=(const Vector& rhs)
        { this->_matrix -= rhs._matrix; return *this; }

    Vector& operator*=(const value_type& rhs)
        { this->_matrix *= rhs; return *this; }

    Vector operator+(const Vector& rhs) const
    {
        Vector tmp = *this;
        tmp += rhs;
        return tmp;
    }

    Vector operator-(const Vector& rhs) const
    {
        Vector tmp = *this;
        tmp -= rhs;
        return tmp;
    }

    Vector operator*(const value_type& rhs) const
    {
        Vector tmp = *this;
        tmp *= rhs;
        return tmp;
    }

    bool operator==(const Vector& rhs) const
        { return this->_matrix == rhs._matrix; }

    bool operator!=(const Vector& rhs) const
        { return this->_matrix != rhs._matrix; }

    bool operator==(const Matrix<K>& rhs) const
        { return this->_matrix == rhs; }

    bool operator!=(const Matrix<K>& rhs) const
        { return this->_matrix != rhs; }

    value_type& at(const size_type& m)
        { return this->_matrix.at(m, 0); }

    const value_type& at(const size_type& m) const
        { return this->_matrix.at(m, 0); }

    value_type& operator[](const size_type& m)
        { return this->_matrix[{m, 0}]; }

    const value_type& operator[](const size_type& m) const
        { return this->_matrix[{m, 0}]; }

    constexpr shape_type shape() const noexcept
        { return { this->_matrix.height(), 1 }; }

    constexpr size_type height() const noexcept
        { return this->_matrix.height(); }

    constexpr size_type width() const noexcept
        { return 1; }

    constexpr bool empty() const
        { return this->_matrix.empty(); }

    constexpr bool square() const
        { return this->_matrix.square(); }

    constexpr size_type size() const noexcept
        { return this->_matrix.height(); }

    constexpr bool has(const size_type& m) const noexcept
        { return this->_matrix.has(m, 0); }

    void resize(const size_type& height, const value_type& value = value_type())
        { this->_matrix.resize(height, 1, value); }

    void check_sizes(const Vector& other) const
        { return this->_matrix.check_sizes(other._matrix); }

    value_type dot(const Vector& other) const
    {
        this->check_sizes(other);
        value_type result = value_type();
        for (size_type i = 0; i < this->size(); ++i)
            result = maths::fma((*this)[i], other[i], result);
        return result;
    }

    /**
     * Calculate the 1-norm (Taxicab norm) for this vector
     * --> Retrieves: Absolute sum of vector's components
     *
     * @return                      Value of the norm
     */
    double norm_1() const
    {
        value_type tmp = 0;
        for (size_type i = 0; i < this->size(); ++i)
            tmp += std::max((*this)[i], -(*this)[i]);
        return static_cast<double>(tmp);
    }

    /**
     * Calculates the 2-norm (Euclidean norm) for this vector
     * --> Retrieves: Length of the vector
     *
     * @return                      Value of the norm
     */
    double norm_2() const
    {
        double tmp = 0;
        for (size_type i = 0; i < this->size(); ++i)
            tmp += std::pow(static_cast<double>((*this)[i]), 2.);
        return std::pow(tmp, .5);
    }

    /**
     * Calculates the inf-norm (Supremum norm) for this vector.
     * --> Retrieves: Highest absolute number
     *
     * @return                      Value of the norm
     */
    double norm_inf() const
    {
        value_type tmp = 0;
        for (size_type i = 0; i < this->size(); ++i)
            tmp = std::max(tmp, std::max((*this)[i], -(*this)[i]));
        return static_cast<double>(tmp);
    }

    /**
     * Converts the vector into a matrix by copy
     *
     * @return                      Ready to use matrix
     * @exception std::bad_alloc    Allocation failure
     */
    Matrix<value_type> to_matrix() const
        { return _matrix; }

private:
    friend Matrix<value_type>;

    Matrix<value_type>     _matrix; // Vector's inner matrix
};

template < class K >
Vector<K> operator*(const typename Vector<K>::value_type& lhs, const Vector<K>& rhs)
    { return rhs.operator*(lhs); }

template < class K >
bool operator==(const Matrix<K>& lhs, const Vector<K>& rhs)
    { return rhs == lhs; }

template < class K >
bool operator!=(const Matrix<K>& lhs, const Vector<K>& rhs)
    { return rhs != lhs; }

template < class K >
std::ostream& operator<<(std::ostream& out, const Vector<K>& value)
    { return out << value.to_matrix(); }

using f64Vector = Vector<double>;               // Helper type for double Vector
using i64Vector = Vector<long long>;            // Helper type for long Vector
using u64Vector = Vector<unsigned long long>;   // Helper type for unsigned long Vector

using f32Vector = Vector<float>;                // Helper type for float Vector
using i32Vector = Vector<int>;                  // Helper type for integer Vector
using u32Vector = Vector<unsigned>;             // Helper type for unsigned Vector

#endif //VECTOR_HPP