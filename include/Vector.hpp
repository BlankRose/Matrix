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

#include "Matrix.hpp"

template < class K >
class Vector
{
public:
    using matrix_type = Matrix<K>;
    using value_type  = typename matrix_type::value_type;
    using size_type   = typename matrix_type::size_type;
    using shape_type  = typename matrix_type::shape_type;

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

    Vector operator+(const Vector& rhs)
        { this->_matrix + rhs._matrix; return *this; }

    Vector operator-(const Vector& rhs)
        { this->_matrix - rhs._matrix; return *this; }

    Vector operator*(const value_type& rhs)
        { this->_matrix * rhs; return *this; }

    value_type& at(const size_type& m)
        { return this->_matrix.at(m, 0); }

    const value_type& at(const size_type& m) const
        { return this->_matrix.at(m, 0); }

    constexpr shape_type shape() const noexcept
        { return { this->_matrix.shape().first, 1 }; }

    constexpr size_type size() const noexcept
        { return this->_matrix.shape().first; }

    constexpr bool has(const size_type& m) const noexcept
        { return this->_matrix.has(m, 0); }

    void resize(const size_type& height, const value_type& value = value_type())
        { this->_matrix.resize(height, 1, value); }

    matrix_type to_matrix() const
        { return _matrix; }

    static Vector from_matrix(const matrix_type& matrix)
    {
        Vector tmp(0);
        matrix.resize(matrix.shape().first, 1);
        return tmp._matrix = std::move(matrix);
    }

private:
    matrix_type     _matrix;
};

template < class K >
Vector<K> operator*(const typename Vector<K>::value_type& lhs, const Vector<K>& rhs)
    { return rhs.operator*(lhs); }

template < class K >
std::ostream& operator<<(std::ostream& out, const Vector<K>& value)
    { return out << value.to_matrix(); }

using f32Vector = Vector<float>;
using i32Vector = Vector<int>;
using u32Vector = Vector<unsigned>;

#endif //VECTOR_HPP