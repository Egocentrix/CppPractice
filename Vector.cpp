// Practice with templates by implementing a basic vector/matrix class
// Template aliasing wohoo!
#include <iostream>

// Matrix (vector) class that stores elements in column-major order
template <int R, int C, typename T>
class Matrix
{

public:
    T data[R * C] = {};
    // Public, so the {} initializer list works;
};

// Serialization
template <int R, int C, typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<R, C, T> M)
{
    for (size_t i = 0; i < R; i++)
    {
        for (size_t j = 0; j < C; j++)
        {
            os << M.data[i + j * R] << " ";
        }
        os << "\n";
    }
    return os;
}

// Transpose matrix/vector
template <int R, int C, typename T>
Matrix<C, R, T> transpose(const Matrix<R, C, T> &M)
{
    Matrix<C, R, T> N = {};
    for (size_t i = 0; i < R; i++)
    {
        for (size_t j = 0; j < C; j++)
        {
            N.data[i * C + j] = M.data[i + j * R];
        }
    }
    return N;
}

// Multiplication of R-by-CL with CL-by-CR matrix, result is R-by-CR
template <int R, int CL, int CR, typename T>
Matrix<R, CR, T> operator*(const Matrix<R, CL, T> &lhs, const Matrix<CL, CR, T> &rhs)
{
    Matrix<R, CR, T> result = {}; // zero-initialize

    for (size_t i = 0; i < CR; i++)
    {
        for (size_t j = 0; j < R; j++)
        {
            for (size_t k = 0; k < CL; k++) // CL is inner dimension
            {
                result.data[i * R + j] += lhs.data[j + R * k] * rhs.data[k + CL * i];
            }
        }
    }

    return result;
}

// Define Vector in terms of Matrix by template aliasing
template <int R, typename T>
using Vector = Matrix<R, 1, T>;

// Main function for testing
int main(int, char **)
{
    Matrix<3, 2, int> M = {1, 2, 3, 4, 5, 6};
    std::cout << M;
    std::cout << transpose(M);

    Vector<5, int> vec = {1, 2, 3, 4, 5};
    std::cout << vec;
    std::cout << transpose(vec);

    Matrix<2, 3, int> M2 = {3, 2, 1, 2, 1, 4};
    Matrix<3, 2, int> V2 = {4, 5, 6, 7, 2, 1};

    std::cout << "\n"
              << M2 << V2 << M2 * V2;

    std::cout << "Hello, world!\n";
}
