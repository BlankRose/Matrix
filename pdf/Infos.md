# Definition

Matrix are rectangular arrays containing values and various expressions.
Usually defined as `m` rows x `n` columns, they can be used in various domains
such as mathematics, physics, etc. to represent various elements.

__NOTE:__ *Vectors can be seen as `1 x n` matrix (or `m x 1` for column-based vectors).*

- Wikipedia: https://en.wikipedia.org/wiki/Matrix_(mathematics)
- Calculator: https://www.mathsisfun.com/algebra/matrix-calculator.html

--------------------------------------------------------------------------------

# Linear Interpolation (ex2)

Linear interpolation takes two bounds, a scalar between 0 and 1 representing the value's 
distance between the given bounds.
(e.g. `0.5` means the value is right in between `a` and `b`,
whereas `0.25` means the value is 25% away from `a` and 75% away from `b`)

__NOTE:__ `lerp(a, b, 0) = a` and `lerp(a, b , 1) = b`

--------------------------------------------------------------------------------

# Norms (ex4)

Various norms can be applied on any given Vector, which returns useful information
them, such as:

- Taxicab norm `l1(v)`: Retrieves the total length of all vector's individual components
- Euclidean norm `l2(v)`: Retrieves the length of the vector
- Supremum norm `loo(v)`: Retrieves the largest vector's component

--------------------------------------------------------------------------------

# Trace (ex8)

Matrix trace, denoted `tr(A)`, are calculated by adding all values containing within its diagonal.
Its result is used in graph theory, for generalizing some properties, and is also the sum
of the eigenvalues (important property for proving certain results), etc.

__REQUIREMENTS:__ Square Matrix

- Use cases: https://math.stackexchange.com/questions/4453933/why-is-the-trace-of-a-matrix-important

--------------------------------------------------------------------------------

# Transpose (ex9)

Matrix can be transposed, denoted `At`, where it simply shifts all of it's the content on its diagonal.
Despite the shift, they still shares many attributes.

__NOTE:__ `A = (At)t`

--------------------------------------------------------------------------------

# Row Echelon Form (ex10)

Matrix can be put into their row echelon form (or even its reduced version),
to help solving equations (e.g. finding its rank), by finding pivots and
applying elementary row operations, which are:

- Swapping two rows
- Scalar multiplications
- Row addition

At the end, the row echelon form has the characteristics of having their first
non-zero number from the left of a row to be `1`'s (called pivots) and values below
the pivots are entirely made of `0`'s and zeroed rows are always at the very
bottom of the matrix. They also usually form a staircase pattern.

- Calculus in-depth: https://www.wikihow.com/Reduce-a-Matrix-to-Row-Echelon-Form

--------------------------------------------------------------------------------

# Determinant (ex11)

Matrix determinants, denoted as `det(A)`, are used in finding the inverse of a matrix,
or solving systems of linear equations.

On a geometric perspective, it represents the size of the area enclosed by the matrix
in the vector space.

__NOTE:__ When `det(A) = 0`, the matrix is singular and thus has no inverse matrix\
__REQUIREMENTS:__ Square Matrix

- Calculus in-depth: https://www.mathsisfun.com/algebra/matrix-determinant.html
- Geometry representation explained: https://math.stackexchange.com/questions/250534/geometric-meaning-of-the-determinant-of-a-matrix

--------------------------------------------------------------------------------

# Rank (ex13)

Matrix rank, denoted `rank(A)` or `rk(A)`, determines how many rows / columns
are linearly independent. It can help by having some insight on solutions for
equations for exemple (e.g. whether it has one, multiple or no solutions)

__NOTE:__ Row rank is same as column rank

- Calculus and explanation: https://www.cuemath.com/algebra/rank-of-a-matrix/
- Importance explanation: https://math.stackexchange.com/questions/21100/importance-of-matrix-rank