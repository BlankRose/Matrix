/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - Matrix.hpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: May 24, 2024 [11:11 AM]
//     ||  '-'
/* ************************************************************************** */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>

// Forward declaration..
template < class K >
class Vector;

#include "Vector.hpp"

/**
 * Represents a mathematical matrix, with various utilities functions
 * and overloads to simplify its usage and calculus
 *
 * @tparam K    Matrix' inner working type
 */
template < class K >
class Matrix
{
public:
    using value_type = K;
    using size_type = size_t;
    using shape_type = std::pair<size_type, size_type>;

    Matrix() = delete;
    ~Matrix() { delete[] this->_data; }

    /**
     * Constructs a new matrix of given size and value
     *
     * @param height                Height of the matrix (usually denoted `m`)
     * @param width                 Width of the matrix (usually denoted `n`)
     * @param value                 Default value to fill the matrix with
     *
     * @exception std::bad_alloc    Allocation failure
     */
    Matrix(const size_type& height, const size_type& width, const value_type& value = value_type()):
        _max_m(height), _max_n(width), _data(new value_type[height * width])
    {
        for (size_type i = 0; i < this->size(); ++i)
            this->_data[i] = value;
    }

    /**
     * Constructs a new matrix of given size and values
     *
     * @param height                Height of the matrix (usually denoted `m`)
     * @param width                 Width of the matrix (usually denoted `n`)
     * @param data                  Array of values to fill the matrix with
     *
     * @exception std::out_of_range Given array is too short
     * @exception std::bad_alloc    Allocation failure
     */
    Matrix(const size_type& height, const size_type& width, const std::vector<value_type>& data):
        _max_m(height), _max_n(width), _data(new value_type[_max_m * _max_n])
    {
        for (size_type i = 0; i < this->size(); ++i)
            this->_data[i] = data.at(i);
    }

    /**
     * Constructs a new matrix of given values
     *
     * @param data                  Matrix of values to fill the matrix with
     *
     * @exception std::out_of_range Given matrix is not properly shaped
     * @exception std::bad_alloc    Allocation failure
     */
    explicit Matrix(const std::vector<std::vector<K>>& data):
        _max_m(data.size()), _max_n(data.empty() ? 0 : data[0].size()), _data(new value_type[_max_m * _max_n])
    {
        for (size_type m = 0; m < data.size(); ++m)
            for (size_type n = 0; n < data[m].size(); ++n)
                this->at(m, n) = data.at(m).at(n);
    }

    /**
     * Constructs a new matrix by copy
     *
     * @param other                 Matrix to copy
     *
     * @exception std::bad_alloc    Allocation failure
     */
    Matrix(const Matrix& other):
        _max_m(other._max_m), _max_n(other._max_n), _data(new value_type[_max_m * _max_n])
    {
        for (size_type i = 0; i < this->size(); ++i)
            this->_data[i] = other._data[i];
    }

    /**
     * Move sementic implementation for Matrix
     *
     * @param other                 Matrix to move
     */
    Matrix(Matrix&& other) noexcept:
        _max_m(std::move(other._max_m)), _max_n(std::move(other._max_n)), _data(std::move(other._data))
        { other._data = nullptr; }

    /**
     * Copies the given matrix into this current one
     *
     * @param rhs                   Matrix to copy
     * @return                      This matrix
     *
     * @exception std::bad_alloc    Allocation failed
     */
    Matrix& operator=(const Matrix& rhs)
    {
        if (this == &rhs)
            return *this;
        delete[] this->_data;

        this->_data = new value_type[rhs._max_m * rhs._max_n];
        for (size_type i = 0; i < rhs.size(); ++i)
            this->_data[i] = rhs._data[i];

        this->_max_m = rhs._max_m;
        this->_max_n = rhs._max_n;
        return *this;
    }

    /**
     * Moves the given matrix into this current one
     *
     * @param rhs                   Matrix to move
     * @return                      This matrix
     */
    Matrix& operator=(Matrix&& rhs) noexcept
    {
        if (this == &rhs)
            return *this;
        delete[] this->_data;

        this->_data = std::move(rhs._data);
        this->_max_m = std::move(rhs._max_m);
        this->_max_n = std::move(rhs._max_n);
        rhs._data = nullptr;
        return *this;
    }

    /**
     * Calculates the addition of 2 matrixes and assign result
     * to the current matrix
     *
     * @param rhs                   Matrix to add
     * @return                      This matrix
     *
     * @exception std::logic_error  Given matrix is of different shape
     */
    Matrix& operator+=(const Matrix& rhs)
    {
        this->check_sizes(rhs);
        for (size_type i = 0; i < this->size(); ++i)
            this->_data[i] += rhs._data[i];
        return *this;
    }

    /**
     * Calculates the subtraction of 2 matrixes and assign result
     * to the current matrix
     *
     * @param rhs                   Matrix to subtract
     * @return                      This matrix
     *
     * @exception std::logic_error  Given matrix is of different shape
     */
    Matrix& operator-=(const Matrix& rhs)
    {
        this->check_sizes(rhs);
        for (size_type i = 0; i < this->size(); ++i)
            this->_data[i] -= rhs._data[i];
        return *this;
    }

    /**
     * Calculates the multiplication of a given scalar and assign result
     * to the current matrix
     *
     * @param rhs                   Scalar value
     * @return                      This matrix
     */
    Matrix& operator*=(const value_type& rhs) noexcept
    {
        for (size_type i = 0; i < this->size(); ++i)
            this->_data[i] *= rhs;
        return *this;
    }

    /**
     * Calculates the addition of 2 matrixes and returns a new matrix
     * containing the result
     *
     * @param rhs                   Matrix to add
     * @return                      New matrix containing result
     *
     * @exception std::logic_error  Given matrix is of different shape
     */
    Matrix operator+(const Matrix& rhs) const
    {
        Matrix tmp = *this;
        tmp += rhs;
        return tmp;
    }

    /**
     * Calculates the subtraction of 2 matrixes and returns a new matrix
     * containing the result
     *
     * @param rhs                   Matrix to subtract
     * @return                      New matrix containing result
     *
     * @exception std::logic_error  Given matrix is of different shape
     */
    Matrix operator-(const Matrix& rhs) const
    {
        Matrix tmp = *this;
        tmp -= rhs;
        return tmp;
    }

    /**
     * Calculates the multiplication of a given scalar and returns a new matrix
     * containing the result
     *
     * @param rhs                   Scalar value
     * @return                      New matrix containing result
     */
    Matrix operator*(const value_type& rhs) const noexcept
    {
        Matrix tmp = *this;
        tmp *= rhs;
        return tmp;
    }

    /**
     * Retrieves the element at the given coordinates, with bounds checks
     *
     * @param m                     Height position (usually denoted `m`)
     * @param n                     Width position (usually denoted `n`)
     * @return                      Reference to value at given coordinates
     *
     * @exception std::out_of_range Given coordinates points out of the matrix
     */
    value_type& at(const size_type& m, const size_type& n)
    {
        const size_type pos = m * this->_max_n + n;
        if (pos > this->_max_m * this->_max_n)
            throw std::out_of_range("position is out of range");
        return this->_data[pos];
    }

    /**
     * Retrieves the element at the given coordinates
     *
     * @param m                     Height position (usually denoted `m`)
     * @param n                     Width position (usually denoted `n`)
     * @return                      Const reference to value at given coordinates
     *
     * @exception std::out_of_range Given coordinates points out of the matrix
     */
    const value_type& at(const size_type& m, const size_type& n) const
    {
        const size_type pos = m * this->_max_n + n;
        if (pos > this->_max_m * this->_max_n)
            throw std::out_of_range("position is out of range");
        return this->_data[pos];
    }

    /**
     * Retrieves the element at the given coordinates
     * (Caution: does not checks for bounds)
     *
     * @param pos                   Position of element to retrieve at
     * @return                      Reference to value at given coordinates
     */
    value_type& operator[](const shape_type& pos)
        { return this->_data[pos.first * this->_max_n + pos.second]; }

    /**
     * Retrieves the element at the given coordinates
     * (Caution: does not checks for bounds)
     *
     * @param pos                   Position of element to retrieve at
     * @return                      Const reference to value at given coordinates
     */
    const value_type& operator[](const shape_type& pos) const
        { return this->_data[pos.first * this->_max_n + pos.second]; }

    /**
     * Retrieves the shape of the matrix
     *
     * @return                      Height-width pair, representing the shape
     */
    constexpr shape_type shape() const noexcept
        { return {this->_max_m, this->_max_n}; }

    /**
     * Retrieves the height of the matrix
     *
     * @return                      Matrix' height
     */
    constexpr size_type height() const noexcept
        { return this->_max_m; }

    /**
     * Retrieves the width of the matrix
     *
     * @return                      Matrix' width
     */
    constexpr size_type width() const noexcept
        { return this->_max_n; }

    /**
     * Checks if the matrix contains no values, having 0-length rows or columns
     *
     * @return                      TRUE if empty, otherwise FALSE
     */
    constexpr bool empty() const
        { return !this->_max_m || !this->_max_n; }

    /**
     * Retrieve the amount of values within the matrix
     *
     * @return                      Amount of values
     */
    constexpr size_type size() const noexcept
        { return this->_max_m * this->_max_n; }

    /**
     * Checks if the given coordinates is within the bounds of the matrix
    *
     * @param m                     Height position (usually denoted `m`)
     * @param n                     Width position (usually denoted `n`)
     * @return                      TRUE if within bounds, otherwise FALSE
     */
    constexpr bool has(const size_type& m, const size_type& n) const noexcept
        { return m < this->_max_m && n < this->_max_n; }

    /**
     * Resizes the matrix to the given coordinates, and uses the value
     * for newly created spots
     *
     * @param height                New matrix' height
     * @param width                 New matrix' width
     * @param value                 Value to inplace in case of new spots
     *
     * @exception std::bad_alloc    Allocation failure
     */
    void resize(const size_type& height, const size_type& width, const value_type& value = value_type())
    {
        Matrix tmp(height, width, value);
        for (size_type m = 0; m < height; ++m)
            for (size_type n = 0; n < width; ++n)
            {
                if (this->has(m, n))
                    tmp.at(m, n) = this->at(m, n);
                else
                    tmp.at(m, n) = value;
            }
        *this = std::move(tmp);
    }

    /**
     * Checks if the two matrix are same
     *
     * @param rhs                   Matrix to compare to
     * @return                      TRUE if same, otherwise FALSE
     */
    bool operator==(const Matrix& rhs) const
    {
        if (this->shape() != rhs.shape())
            return false;
        for (size_type i = 0; i < this->size(); ++i)
            if (this->_data[i] != rhs._data[i])
                return false;
        return true;
    }

    /**
     * Checks if the two matrix are different
     *
     * @param rhs                   Matrix to compare to
     * @return                      TRUE if different, otherwise FALSE
     */
    bool operator!=(const Matrix& rhs) const
        { return !(*this == rhs); }

    /**
     * Checks if given matrix has the same shape as the current one, otherwise
     * throws an logic error exception
     *
     * @param other                 Matrix to compare to
     *
     * @exception std::logic_error  Given matrix is of different shape
     */
    void check_sizes(const Matrix& other) const
    {
        if (this->shape() != other.shape())
            throw std::logic_error("cannot operate with different matrix sizes");
    }

    /**
     * Converts the matrix into a vector by copy, if possible,
     * otherwise throws an exception
     *
     * @return                      Ready to use vector
     *
     * @exception std::logic_error  Matrix is too wide to fit in a vector
     * @exception std::bad_alloc    Allocation failure
     */
    Vector<value_type> to_vector() const
    {
        if (this->_max_n != 1)
            throw std::logic_error("matrix is too wide to be converted into vector");
        Vector<K> tmp(0);
        tmp._matrix = *this;
        return tmp;
    }

private:
    friend Vector<value_type>;

    size_type       _max_m; // Matrix' height
    size_type       _max_n; // Matrix' width
    value_type *    _data;  // Matrix' content
};

/**
 * Calculates the multiplication of a given scalar and returns a new matrix
 * containing the result
 *
 * @tparam K        Matrix' inner working type
 * @param lhs       Scalar value
 * @param rhs       Matrix to compute
 * @return          New matrix containing result
 */
template < class K >
Matrix<K> operator*(const typename Matrix<K>::value_type& lhs, const Matrix<K>& rhs) noexcept
    { return rhs.operator*(lhs); }

/**
 * Writes the matrix' internal structure on the given output stream
 *
 * @tparam K        Matrix' inner working type
 * @param out       Output stream to write on
 * @param value     Matrix to write
 * @return          Returns output stream for chaining
 */
template < class K >
std::ostream& operator<<(std::ostream& out, const Matrix<K>& value)
{
    const size_t max_m = value.shape().first;
    const size_t max_n = value.shape().second;

    for (size_t m = 0; m < max_m; ++m)
    {
        out << (m != 0 ? ' ' : '[');
        for (size_t n = 0; n < max_n; ++n)
            out << value.at(m, n) << (n < max_n - 1 ? ", " : "");
        out << (m < max_m - 1 ? '\n' : ']');
    }
    return out;
}

using f64Matrix = Matrix<double>;               // Helper type for double Matrix
using i64Matrix = Matrix<long long>;            // Helper type for long Matrix
using u64Matrix = Matrix<unsigned long long>;   // Helper type for unsigned long Matrix

using f32Matrix = Matrix<float>;                // Helper type for float Matrix
using i32Matrix = Matrix<int>;                  // Helper type for integer Matrx
using u32Matrix = Matrix<unsigned int>;         // Helper type for unsigned Matrix

#endif //MATRIX_HPP