#include "matrix_t.h"

std::pair<Matrix_t, Matrix_t> EnterSLAE(int n, std::string testPath) {
    std::ifstream fin;
    fin.open(testPath);
    Matrix_t A(n, n);
    Matrix_t b(n, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> A.matrix[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        fin >> b.matrix[i][0];
    }
    fin.close();
    return std::pair<Matrix_t, Matrix_t>(A, b);
}

std::pair<Matrix_t, int> SeidelMethod(Matrix_t A, Matrix_t b, double eps) {
    // Matrix_t transA(A.Transpose());
    // A = transA * A;
    // b = transA * b;
    if (!A.IsPositiveDefined() && !A.IsDiagonallyDominant()) {
        Matrix_t T(A.Transpose());
        A = T * A;
        b = T * b;
    }
    int n = b.lines;
    Matrix_t d(n, 1);
    for (int i = 0; i < n; i++) {
        d.matrix[i][0] = b.matrix[i][0] / A.matrix[i][i];
    }
    Matrix_t C(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                C.matrix[i][j] = 0;
            else 
                C.matrix[i][j] = (-1)*A.matrix[i][j]/A.matrix[i][i];
        }
    }
    Matrix_t x0(d);
    Matrix_t x1(n, 1);
    int count = 0;
    while ((A*x1-b).FirstNorm() > eps) {
        if (count != 0) {
            x0 = x1;
        }
        int zeroIndex = 0;
        x1.Clear();
        for (int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if (j < zeroIndex)
                    x1.matrix[i][0] += C.matrix[i][j]*x1.matrix[j][0];
                else if (j == zeroIndex)
                    continue;
                else 
                    x1.matrix[i][0] += C.matrix[i][j]*x0.matrix[j][0];
            }
            x1.matrix[i][0] += d.matrix[i][0];
            zeroIndex++;
        }
        count++;
    } 
    return std::pair<Matrix_t, int>{x1, count};
}

// std::pair<Matrix_t, int> SimpleIterMethod(Matrix_t A, Matrix_t b, double eps) {
//     Matrix_t T(A.Transpose());
//     A = T*A;
//     b = T*b;
//     double mu = 1 / A.FirstNorm();
//     Matrix_t B = E(A.lines)-A*mu;

//     Matrix_t c(b*mu);
//     Matrix_t x0(c);
//     Matrix_t x1(c);
//     int count = 0;
//     while (true) {
//         x1 = B*x0+c;
//         count++;
//         if ((A*x1-b).FirstNorm() < eps) {
//             return std::pair<Matrix_t, int>{x1, count};
//         }
//         x0 = x1;
//     }
// }

std::pair<Matrix_t, int> SimpleIterMethod(Matrix_t A, Matrix_t b, double eps) {
    double mu = 1 / A.FirstNorm();
    Matrix_t B = E(A.lines)-A*mu;

    if (B.FirstNorm() >= 1) {
        Matrix_t T(A.Transpose());
        A = T*A;
        b = T*b;
        mu = 1 / A.FirstNorm();
        B = E(A.lines)-A*mu;
    }
    
    // Matrix_t c(b*mu);
    // Matrix_t x0(c);
    // Matrix_t x1(c);
    // int count = 0; 


    // while (true) {
    //     x1 = B*x0+c;
    //     count++;

    //     if (B.FirstNorm() >= 1) {
    //         if ((A*x1-b).FirstNorm() < eps) 
    //             return std::pair<Matrix_t, int>{x1, count};
    //     } else {
    //         if (B.FirstNorm()/(1-B.FirstNorm())*(x1-x0).FirstNorm() < eps) 
    //             return std::pair<Matrix_t, int>{x1, count};
    //     }
        
    //     // if ((A*x1-b).FirstNorm() < eps) {
    //     //     return std::pair<Matrix_t, int>{x1, count};
    //     // }
    //     x0 = x1;
    // }

    Matrix_t hehehe(3,3);
    return std::pair<Matrix_t, int>{hehehe, 666};
}

Matrix_t QR(Matrix_t A, Matrix_t b) {
    int n = A.lines;
    Matrix_t Q(n);
    Matrix_t R(A);
    
    for (int i = 0; i < n-1; i++) {
        Matrix_t z(Ort(n-i));
        Matrix_t y(R.Cut(i,n-1,i,i));
        double a = y.SecondVectorNorm();
        Matrix_t w = (y-a*z)*(1/(y-a*z).SecondVectorNorm());
        Matrix_t Q1(n);
        Q1.Insert(i,n-1,i,n-1,E(n-i)-2*w*w.Transpose());
        R.Insert(i,n-1,i,n-1,(Q1.Cut(i,n-1,i,n-1)*R.Cut(i,n-1,i,n-1)));
        Q = Q*Q1;
    }

    Matrix_t y(Q.Transpose()*b);
    Matrix_t x(n, 1);
    x.matrix[n-1][0] = y.matrix[n-1][0]/R.matrix[n-1][n-1];
    for (int i = n-1; i >= 0; i--) {
        x.matrix[i][0] = y.matrix[i][0];
        for (int j = n-1; j > i; j--) {
            x.matrix[i][0] -= R.matrix[i][j]*x.matrix[j][0];
        }
        x.matrix[i][0] /= R.matrix[i][i];
    }

    return x;
}

Matrix_t LU(Matrix_t A, Matrix_t b) {
    int n = A.lines;
    Matrix_t P(n);
    Matrix_t M(A);
    for (int i = 0; i < n-1; i++)
    {
        double max_el = 0;
        int lineToSwap = -1;
        for (int j = i; j < n; j++) {
            if (abs(M.matrix[j][i]) > abs(max_el)) {
                max_el = std::max(M.matrix[j][i], max_el);
                lineToSwap = j;
            }
        }
        M.SwapLines(i, lineToSwap);
        P.SwapLines(i, lineToSwap);
        //? Теперь преобразуем M:
            //? Сначала пройдемся по i-тому столбцу
            //? Потом по элементам справа от элементов под позицией [i][i]
        for(int j = i+1; j < n; j++) {
            M.matrix[j][i] = M.matrix[j][i]/M.matrix[i][i];
        }    
        for(int j = i+1; j < n; j++) {
            for (int k = i+1; k < n; k++) {
                M.matrix[j][k] = M.matrix[j][k] - M.matrix[j][i]*M.matrix[i][k];
            }
        }
    }
    Matrix_t U(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            //std::cout << M.matrix[i][j] << ' ';
            U.matrix[i][j] = M.matrix[i][j];
        }
    }
    Matrix_t L(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            L.matrix[i][j] = M.matrix[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        L.matrix[i][i] = 1;
    }
    //? L и U готовы
    //? Решение уравнения Ly = Pb
    Matrix_t b1(P*b);
    //b1.Print();
    Matrix_t y(n,1);
    y.matrix[0][0] = b1.matrix[0][0];
    for (int i = 1; i < n; i++) {
        y.matrix[i][0] = b1.matrix[i][0];
        for (int j = 0; j < i; j++) {
            y.matrix[i][0] -= L.matrix[i][j]*y.matrix[j][0];
        }
    }
    //? Решение уравнения Ux = y
    Matrix_t x(n, 1);
    x.matrix[n-1][0] = y.matrix[n-1][0]/U.matrix[n-1][n-1];
    for (int i = n-1; i >= 0; i--) {
        x.matrix[i][0] = y.matrix[i][0];
        for (int j = n-1; j > i; j--) {
            x.matrix[i][0] -= U.matrix[i][j]*x.matrix[j][0];
        }
        x.matrix[i][0] /= U.matrix[i][i];
    }
    return x;
}

Matrix_t Solution(Matrix_t A, Matrix_t b) {
    Eigen::MatrixXf newA(A.lines, A.columns);
    for (int i = 0; i < A.lines; i++) {
        for (int j = 0; j < A.columns; j++) {
            newA(i, j) = A.matrix[i][j];
        }
    }
    //std::cout << newA << '\n';
    Eigen::VectorXf newB(b.lines);
    for (int i = 0; i < b.lines; i++) {
        newB(i) = b.matrix[i][0];
    }
    //std::cout << newB << '\n';
    Eigen::VectorXf solution = newA.colPivHouseholderQr().solve(newB);
    Matrix_t x(b.lines, 1);    
    for (int i = 0; i < b.lines; i++) {
        x.matrix[i][0] = solution(i);
    }
    return x;
}

// Matrix_t Solution(Matrix_t A, Matrix_t b) {
//     int n = A.lines;
//     Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> newA(n, n);
//     Eigen::Vector<double,Eigen::Dynamic> newB(n);
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             newA << A.matrix[i][j];
//         }
//         newB << b.matrix[i][0];
//     }

//     Matrix_t e(3);
//     return e;
// }

// Matrix_t Solution(Matrix_t A, Matrix_t b) {
//     int n = A.lines;
//     Eigen::Matrix3f newA;
//     Eigen::Vector3f newB;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             newA << A.matrix[i][j];
//         }
//         newB << b.matrix[i][0];
//     }
//     Eigen::Vector3f x = newA.ldlt().solve(newB);
//     x[]
// }