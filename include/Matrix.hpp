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
     * @note                        Time Complexity: O(N)
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
     * @note                        Time Complexity: O(N)
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
     * @note                        Time Complexity: O(N)
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
     * @note                        Time Complexity: O(N)
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
     * @note                        Time Complexity: O(1)
     */
    Matrix(Matrix&& other) noexcept:
        _max_m(std::move(other._max_m)), _max_n(std::move(other._max_n)), _data(std::move(other._data))
        { other._data = nullptr; }

    /**
     * Copies the given matrix into this current one
     *
     * @param rhs                   Matrix to copy
     *
     * @return                      This matrix
     * @exception std::bad_alloc    Allocation failed
     * @note                        Time Complexity: O(N)
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
     *
     * @return                      This matrix
     * @note                        Time Complexity: O(1)
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
     * Calculates the addition of 2 matrixes and assign result to the current matrix
     *
     * @param rhs                   Matrix to add
     *
     * @return                      This matrix
     * @exception std::logic_error  Given matrix is of different shape
     * @note                        Time Complexity: O(N)
     */
    Matrix& operator+=(const Matrix& rhs)
    {
        this->check_sizes(rhs);
        for (size_type i = 0; i < this->size(); ++i)
            this->_data[i] += rhs._data[i];
        return *this;
    }

    /**
     * Calculates the subtraction of 2 matrixes and assign result to the current matrix
     *
     * @param rhs                   Matrix to subtract
     *
     * @return                      This matrix
     * @exception std::logic_error  Given matrix is of different shape
     * @note                        Time Complexity: O(N)
     */
    Matrix& operator-=(const Matrix& rhs)
    {
        this->check_sizes(rhs);
        for (size_type i = 0; i < this->size(); ++i)
            this->_data[i] -= rhs._data[i];
        return *this;
    }

    /**
     * Calculates the multiplication of a given scalar and assign result to the current matrix
     *
     * @param rhs                   Scalar value
     *
     * @return                      This matrix
     * @note                        Time Complexity: O(N)
     */
    Matrix& operator*=(const value_type& rhs) noexcept
    {
        for (size_type i = 0; i < this->size(); ++i)
            this->_data[i] *= rhs;
        return *this;
    }

    /**
     * Calculates the addition of 2 matrixes and returns a new matrix containing the result
     *
     * @param rhs                   Matrix to add
     *
     * @return                      New matrix containing result
     * @exception std::logic_error  Given matrix is of different shape
     * @note                        Time Complexity: O(N)
     */
    Matrix operator+(const Matrix& rhs) const
    {
        Matrix tmp = *this;
        tmp += rhs;
        return tmp;
    }

    /**
     * Calculates the subtraction of 2 matrixes and returns a new matrix containing the result
     *
     * @param rhs                   Matrix to subtract
     *
     * @return                      New matrix containing result
     * @exception std::logic_error  Given matrix is of different shape
     * @note                        Time Complexity: O(N)
     */
    Matrix operator-(const Matrix& rhs) const
    {
        Matrix tmp = *this;
        tmp -= rhs;
        return tmp;
    }

    /**
     * Calculates the multiplication of a given scalar and returns a new matrix containing the result
     *
     * @param rhs                   Scalar value
     *
     * @return                      New matrix containing result
     * @note                        Time Complexity: O(N)
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
     *
     * @return                      Reference to value at given coordinates
     * @exception std::out_of_range Given coordinates points out of the matrix
     * @note                        Time Complexity: O(1)
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
     *
     * @return                      Const reference to value at given coordinates
     * @exception std::out_of_range Given coordinates points out of the matrix
     * @note                        Time Complexity: O(1)
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
     *
     * @return                      Reference to value at given coordinates
     * @note                        Time Complexity: O(1)
     */
    value_type& operator[](const shape_type& pos)
        { return this->_data[pos.first * this->_max_n + pos.second]; }

    /**
     * Retrieves the element at the given coordinates
     * (Caution: does not checks for bounds)
     *
     * @param pos                   Position of element to retrieve at
     *
     * @return                      Const reference to value at given coordinates
     * @note                        Time Complexity: O(1)
     */
    const value_type& operator[](const shape_type& pos) const
        { return this->_data[pos.first * this->_max_n + pos.second]; }

    /**
     * Retrieves the shape of the matrix
     *
     * @return                      Height-width pair, representing the shape
     * @note                        Time Complexity: O(1)
     */
    constexpr shape_type shape() const noexcept
        { return {this->_max_m, this->_max_n}; }

    /**
     * Retrieve the amount of values within the matrix
     *
     * @return                      Amount of values
     * @note                        Time Complexity: O(1)
     */
    constexpr size_type size() const noexcept
        { return this->_max_m * this->_max_n; }

    /**
     * Checks if the given coordinates is within the bounds of the matrix
    *
     * @param m                     Height position (usually denoted `m`)
     * @param n                     Width position (usually denoted `n`)
     *
     * @return                      TRUE if within bounds, otherwise FALSE
     * @note                        Time Complexity: O(1)
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
     * @note                        Time Complexity: O(n)
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

    bool operator==(const Matrix& rhs) const
    {
        if (this->shape() != rhs.shape())
            return false;
        for (size_type i = 0; i < this->size(); ++i)
            if (this->_data[i] != rhs._data[i])
                return false;
        return true;
    }

    bool operator!=(const Matrix& rhs) const
        { return !(*this == rhs); }

    /**
     * Checks if given matrix has the same shape as the current one, otherwise
     * throws an logic error exception
     *
     * @param other                 Matrix to compare to
     *
     * @exception std::logic_error  Given matrix is of different shape
     * @note                        Time Complexity: O(1)
     */
    void check_sizes(const Matrix& other) const
    {
        if (this->shape() != other.shape())
            throw std::logic_error("cannot operate with different matrix sizes");
    }

private:
    size_type       _max_m; // Matrix' height
    size_type       _max_n; // Matrix' width
    value_type *    _data;  // Matrix' content
};

template < class K >
Matrix<K> operator*(const typename Matrix<K>::value_type& lhs, const Matrix<K>& rhs) noexcept
    { return rhs.operator*(lhs); }

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

using f32Matrix = Matrix<float>;
using i32Matrix = Matrix<int>;
using u32Matrix = Matrix<unsigned int>;

#endif //MATRIX_HPP