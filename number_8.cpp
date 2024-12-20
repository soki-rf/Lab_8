#include <iostream>
#include <cstring> 

struct Matrix {
    int** data_ = nullptr;
    size_t n_ = 0u;        
    size_t m_ = 0u;       
};


void Construct(Matrix& out, size_t n, size_t m) {
    out.n_ = n;
    out.m_ = m;
    out.data_ = new int*[m];
    for (size_t i = 0; i < m; ++i) {
        out.data_[i] = new int[n];
        std::memset(out.data_[i], 0, n * sizeof(int));
    }
}


void Destruct(Matrix& in) {
    for (size_t i = 0; i < in.m_; ++i) {
        delete[] in.data_[i];
    }
    delete[] in.data_;
    in.data_ = nullptr;
    in.n_ = 0;
    in.m_ = 0;
}


Matrix Copy(const Matrix& matrix) {
    Matrix copy;
    Construct(copy, matrix.n_, matrix.m_);
    for (size_t i = 0; i < matrix.m_; ++i) {
        std::memcpy(copy.data_[i], matrix.data_[i], matrix.n_ * sizeof(int));
    }
    return copy;
}


Matrix Add(const Matrix& a, const Matrix& b) {
    if (a.m_ != b.m_ || a.n_ != b.n_) {
        return Matrix(); 
    }
    Matrix result;
    Construct(result, a.n_, a.m_);
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            result.data_[i][j] = a.data_[i][j] + b.data_[i][j];
        }
    }
    return result;
}


Matrix Sub(const Matrix& a, const Matrix& b) {
    if (a.m_ != b.m_ || a.n_ != b.n_) {
        return Matrix(); 
    }
    Matrix result;
    Construct(result, a.n_, a.m_);
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            result.data_[i][j] = a.data_[i][j] - b.data_[i][j];
        }
    }
    return result;
}


Matrix Mult(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.m_) {
        return Matrix();
    }
    Matrix result;
    Construct(result, b.n_, a.m_);
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < b.n_; ++j) {
            result.data_[i][j] = 0;
            for (size_t k = 0; k < a.n_; ++k) {
                result.data_[i][j] += a.data_[i][k] * b.data_[k][j];
            }
        }
    }
    return result;
}


void Transposition(Matrix& matrix) {
    Matrix transposed;
    Construct(transposed, matrix.m_, matrix.n_);
    for (size_t i = 0; i < matrix.m_; ++i) {
        for (size_t j = 0; j < matrix.n_; ++j) {
            transposed.data_[j][i] = matrix.data_[i][j];
        }
    }
    Destruct(matrix);
    matrix = transposed;
}


bool operator==(const Matrix& a, const Matrix& b) {
    if (a.m_ != b.m_ || a.n_ != b.n_) {
        return false;
    }
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            if (a.data_[i][j] != b.data_[i][j]) {
                return false;
            }
        }
    }
    return true;
}


int main() {
    Matrix a, b;
    Construct(a, 2, 2);
    Construct(b, 2, 2);

    a.data_[0][0] = 1; a.data_[0][1] = 2;
    a.data_[1][0] = 3; a.data_[1][1] = 4;

    b.data_[0][0] = 5; b.data_[0][1] = 6;
    b.data_[1][0] = 7; b.data_[1][1] = 8;

    Matrix sum = Add(a, b);
    Matrix diff = Sub(a, b);
    Matrix prod = Mult(a, b);

    std::cout << "Sum: " << sum.data_[0][0] << std::endl;

    Destruct(a);
    Destruct(b);
    Destruct(sum);
    Destruct(diff);
    Destruct(prod);

    return 0;
}
