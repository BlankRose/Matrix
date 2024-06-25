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

#include <cmath>
#include <vector>
#include <iostream>
#include "general.hpp"

// Forward declaration...
template < class K >
class Vector;

#include "Vector.hpp"

/**
 * Represents a mathematical matrix, with various utilities functions
 * and overloads to simplify its usage and calculus
 *
 * @tparam K    Matrix inner working type
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
     * @exception std::out_of_range Given array is missing values
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
     * @exception std::out_of_range Given matrix is missing values
     * @exception std::bad_alloc    Allocation failure
     */
    explicit Matrix(const std::vector<std::vector<K>>& data):
        _max_m(data.size()),
        _max_n(data.empty() ? 0 : data[0].size()),
        _data(new value_type[_max_m * (data.empty() ? 0 : data[0].size())])
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
     * Move semantic implementation for Matrix
     *
     * @param other                 Matrix to move
     */
    Matrix(Matrix&& other) noexcept:
        _max_m(other._max_m), _max_n(other._max_n), _data(std::move(other._data))
        { other._data = nullptr; }

    /**
     * Constructs a new matrix by copying an existing vector
     *
     * @param other                 Vector to copy
     */
    template <typename = typename
        std::enable_if<std::is_same<Vector<value_type>, Vector<value_type>>::value>::type>
    explicit Matrix(const Vector<value_type>& other):
        Matrix(other._matrix) {}

    /**
     * Move semantic implementation for Matrix, by Vector
     *
     * @param other                 Vector to move
     */
    template <typename = typename
        std::enable_if<std::is_same<Vector<value_type>, Vector<value_type>>::value>::type>
    explicit Matrix(Vector<value_type>&& other) noexcept:
        Matrix(std::move(other._matrix)) {}

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
        this->_max_m = rhs._max_m;
        this->_max_n = rhs._max_n;
        rhs._data = nullptr;
        return *this;
    }

    /**
     * Calculates the addition of 2 matrix and assign result
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
     * Calculates the subtraction of 2 matrix and assign result
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
     * Calculates the multiplication of 2 matrix and assign result
     * to the current matrix
     *
     * @param rhs                   Matrix to multiplicative
     * @return                      This matrix
     *
     * @exception std::logic_error  Given matrix doesn't match requirements
     */
    Matrix& operator*=(const Matrix& rhs)
    {
        if (this->_max_n != rhs._max_m)
            throw std::logic_error("incompatible for multiplication");

        Matrix result(this->_max_m, rhs._max_n);
        for (size_type m = 0; m < this->_max_m; ++m)
            for (size_type n = 0; n < rhs._max_n; ++n)
            {
                value_type tmp = value_type();
                for (size_type p = 0; p < this->_max_n; ++p)
                    tmp = maths::fma((*this)[{m, p}], rhs[{p, n}], tmp);
                result[{m, n}] = tmp;
            }

        *this = std::move(result);
        return *this;
    }

    /**
     * Calculates the multiplication of a matrix with a vector and assign result
     * to the current matrix
     *
     * @param rhs                   Vector to multiplicative
     * @return                      This matrix
     *
     * @exception std::logic_error  Given vector doesn't match requirements
     */
    Matrix& operator*=(const Vector<value_type>& rhs)
    {
        if (this->_max_n != rhs.size())
            throw std::logic_error("incompatible for multiplication");

        Matrix result(this->_max_n, 1);
        for (size_type m = 0; m < this->_max_m; ++m)
            for (size_type n = 0; n < this->_max_n; ++n)
                result[{m, 0}] = maths::fma((*this)[{m, n}], rhs[n], result[{m, 0}]);
        *this = std::move(result);
        return *this;
    }

    /**
     * Calculates the addition of 2 matrix and returns a new matrix
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
     * Calculates the subtraction of 2 matrix and returns a new matrix
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
     * Calculates the multiplication of 2 matrix and returns a new matrix
     * containing the result
     *
     * @param rhs                   Matrix to multiplicative
     * @return                      New matrix containing result
     *
     * @exception std::logic_error  Given matrix doesn't match requirements
     */
    Matrix operator*(const Matrix& rhs) const
    {
        Matrix tmp = *this;
        tmp *= rhs;
        return tmp;
    }

    /**
     * Calculates the multiplication of a matrix with a vector and returns a new matrix
     * containing the result
     *
     * @param rhs                   Vector to multiplicative
     * @return                      New matrix containing result
     *
     * @exception std::logic_error  Given vector doesn't match requirements
     */
    Vector<value_type> operator*(const Vector<value_type>& rhs) const
    {
        Matrix tmp = *this;
        tmp *= rhs;
        return Vector<value_type>(std::move(tmp));
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
     * (Caution: does not check for bounds)
     *
     * @param pos                   Position of element to retrieve at
     * @return                      Reference to value at given coordinates
     */
    value_type& operator[](const shape_type& pos)
        { return this->_data[pos.first * this->_max_n + pos.second]; }

    /**
     * Retrieves the element at the given coordinates
     * (Caution: does not check for bounds)
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
     * @return                      Matrix height
     */
    constexpr size_type height() const noexcept
        { return this->_max_m; }

    /**
     * Retrieves the width of the matrix
     *
     * @return                      Matrix width
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
     * Checks if the matrix shape is square
     *
     * @return                      TRUE if shape is square, otherwise FALSE
     */
    constexpr bool square() const
        { return this->_max_m == this->_max_n; }

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
     * @param height                New matrix height
     * @param width                 New matrix width
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
     * Creates a copy of the matrix and transposes it
     *
     * @return                      Transposed copy of the matrix
     */
    Matrix transpose() const
    {
        Matrix result(this->_max_n, this->_max_m);
        for (size_type m = 0; m < this->_max_m; ++m)
            for (size_type n = 0; n < this->_max_n; ++n)
                result[{n, m}] = (*this)[{m, n}];
        return result;
    }

    /**
     * Calculates the trace of a square matrix, denoted "tr(A)"
     * --> Sum of elements in main diagonal
     *
     * @return                      Trace value of matrix
     *
     * @exception std::logic_error  Matrix needs is not square
     */
    value_type trace() const
    {
        if (!this->square())
            throw std::logic_error("trace can only be calculated on square matrix");
        value_type value = value_type();
        for (size_type n = 0; n < this->_max_n; ++n)
            value += (*this)[{n, n}];
        return value;
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
     * throws a logic error exception
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
     * Resolves the matrix with absolute values
     *
     * @return                      New matrix with only absolutes values
     */
    Matrix absolute() const
    {
        Matrix tmp = *this;
        for (size_type i = 0; i < this->size(); ++i)
            if (tmp[i] < value_type())
                tmp[i] = -tmp[i];
        return tmp;
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
        return Vector<value_type>(*this);
    }

    /**
     * Calculates the Reduced Row Echelon Form
     * and applies on the current matrix
     */
    void row_echelon_inplace()
    {
        size_type n = 0;
        for (size_type m = 0; m < this->_max_m; ++m)
        {
            if (n >= this->_max_n)
                return;
            size_type i = m;
            while (this->at(i, n) == 0)
                if (++i >= this->_max_m)
                {
                    i = m;
                    if (++n >= this->_max_n)
                        return;
                }
            this->swap_rows(i, m);
            this->divide_row(m, this->at(m, n));
            for (i = 0; i < this->_max_m; ++i)
                if (i != m)
                    this->fma_row(i, m, -this->at(i, n));
        }
    }

    /**
     * Calculates the Reduced Row Echelon Form
     * and returns it as a new matrix
     *
     * @return                      Result of Row echelon
     */
    Matrix row_echelon() const
    {
        Matrix tmp = *this;
        tmp.row_echelon_inplace();
        return tmp;
    }

    /**
     * Calculates the determinant of the given matrix, denoted `det(A)`.
     * If result is 0, it means it's a singular matrix (and has no inverse matrix).
     * Used for solving systems of linear equations
     *
     * @return                      Determinant of given matrix
     *
     * @exception std::logic_error  Matrix needs is not square
     */
    value_type determinant() const
    {
        // Required by properties of determinants
        if (!this->_max_n || !this->_max_m)
            return 1;

        if (!this->square())
            throw std::logic_error("determinant can only be calculated on square matrix");
        switch (this->_max_n)
        {
        case 0:
            return 1;
        case 1:
            return this->at(0, 0);
        case 2:
            return this->_det2x2();
        case 3:
            return this->_det3x3();
        default:
            return this->_detHigh();
        }
    }

    /**
     * Calculates the rank of a matrix, representing the amount
     * of independent rows / columns (or used dimension in vector space)
     *
     * @return                      Rank of current matrix
     */
    size_type rank() const
    {
        Matrix tmp = this->row_echelon();
        size_type rank = 0;
        for (size_type m = 0; m < this->_max_m; ++m)
            for (size_type n = 0; n < this->_max_n; ++n)
                if (tmp.at(m, n) != 0)
                {
                    ++rank;
                    break;
                }
        return rank;
    }

    /**
     * Swaps two rows, by swapping their contents
     *
     * @param a                     Index of first row
     * @param b                     Index of second row
     */
    void swap_rows(const size_type& a, const size_type& b)
    {
        for (size_type n = 0; n < this->_max_n; ++n)
            std::swap(this->at(a, n), this->at(b, n));
    }

    /**
     * Swaps two columns, by swapping their contents
     *
     * @param a                     Index of first column
     * @param b                     Index of second column
     */
    void swap_columns(const size_type& a, const size_type& b)
    {
        for (size_type m = 0; m < this->_max_m; ++m)
            std::swap(this->at(m, a), this->at(m, b));
    }

    /**
     * Divides an entire row by a given value
     *
     * @param m                     Index of row
     * @param rhs                   Value to divide by
     *
     * @exception std::logic_error  Division by 0
     */
    void divide_row(const size_type& m, const value_type rhs)
    {
        for (size_type n = 0; n < this->_max_n; ++n)
            this->at(m, n) /= rhs;
    }

    /**
     * Divides an entire column by a given value
     *
     * @param n                     Index of column
     * @param rhs                   Value to divide by
     *
     * @exception std::logic_error  Division by 0
     */
    void divide_column(const size_type& n, const value_type rhs)
    {
        for (size_type m = 0; m < this->_max_m; ++m)
            this->at(m, n) /= rhs;
    }

    /**
     * Calculates the fused multiply-add between
     * two rows and a given multiplier
     *
     * @param a                     Index of first row
     * @param b                     Index of second row
     * @param value                 Value to multiply by
     */
    void fma_row(const size_type& a, const size_type& b, const value_type value)
    {
        for (size_type n = 0; n < this->_max_n; ++n)
            // this->at(a, n) = maths::fma(value, this->at(b, n), this->at(a, n));
            this->at(a, n) += value * this->at(b, n);
    }

    /**
     * Calculates the fused multiply-add between
     * two columns and a given multiplier
     *
     * @param a                     Index of first column
     * @param b                     Index of second column
     * @param value                 Value to multiply by
     */
    void fma_column(const size_type& a, const size_type& b, const value_type value)
    {
        for (size_type m = 0; m < this->_max_m; ++m)
            // this->at(m, a) = maths::fma(value, this->at(m, b), this->at(m, a));
            this->at(m, a) += value * this->at(m, b);
    }

private:
    /**
     * Calculates the determinant of a 2x2 matrix
     * (Used by Matrix.determinant() and Matrix._det3x3)
     *
     * @return                      Determinant of given matrix
     */
    value_type _det2x2() const
    {
        return maths::cross_product(this->at(0, 0), this->at(0, 1), this->at(1, 0), this->at(1, 1));
    }

    /**
     * Calculates the determinant of a 3x3 matrix
     * (Used by Matrix.determinant() and Matrix._detHigh)
     *
     * @return                      Determinant of given matrix
     */
    value_type _det3x3() const
    {
        return this->at(0, 0) * maths::cross_product(this->at(1, 1), this->at(1, 2), this->at(2, 1), this->at(2, 2))
             - this->at(1, 0) * maths::cross_product(this->at(0, 1), this->at(0, 2), this->at(2, 1), this->at(2, 2))
             + this->at(2, 0) * maths::cross_product(this->at(0, 1), this->at(0, 2), this->at(1, 1), this->at(1, 2));
    }

    /**
     * Calculates the determinant of a higher matrix
     * (Used by Matrix.determinant())
     *
     * @return                      Determinant of given matrix
     */
    value_type _detHigh() const
    {
        const size_type LEN = this->_max_n;
        value_type result = value_type();
        Matrix sub_matrix(LEN - 1, LEN - 1);

        for (size_type i = 0; i < LEN; ++i)
        {
            size_type sub_n = 0;
            for (size_type n = 0; n < LEN; ++n)
            {
                if (n == i)
                    continue;
                for (size_type m = 1; m < LEN; ++m)
                    sub_matrix.at(m - 1, sub_n) = this->at(m, n);
                ++sub_n;
            }
            value_type sub_result = (i % 2 ? -1 : 1) * sub_matrix.determinant();
            result = maths::fma(sub_result, this->at(0, i), result);
        }
        return result;
    }

protected:
    friend Vector<value_type>;

    size_type       _max_m; // Matrix height (amount of rows)
    size_type       _max_n; // Matrix width (amount of columns)
    value_type *    _data;  // Matrix content
};

/**
 * Calculates the multiplication of a given scalar and returns a new matrix
 * containing the result
 *
 * @tparam K        Matrix inner working type
 * @param lhs       Scalar value
 * @param rhs       Matrix to compute
 * @return          New matrix containing result
 */
template < class K >
Matrix<K> operator*(const typename Matrix<K>::value_type& lhs, const Matrix<K>& rhs) noexcept
    { return rhs.operator*(lhs); }

/**
 * Writes the matrix internal structure on the given output stream
 *
 * @tparam K        Matrix inner working type
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
using i32Matrix = Matrix<int>;                  // Helper type for integer Matrix
using u32Matrix = Matrix<unsigned int>;         // Helper type for unsigned Matrix

#endif //MATRIX_HPP