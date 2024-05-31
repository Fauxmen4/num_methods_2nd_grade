#include "matrix_t.h"

Matrix_t::Matrix_t(int lines, int columns) {
    matrix = new double*[lines];
    for (int i = 0; i < lines; i++) {
        matrix[i] = new double[columns]; 
    }
    this->lines = lines;
    this->columns = columns;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = 0;
        }
    }
}

Matrix_t::Matrix_t(const Matrix_t &other) {
    this->lines = other.lines;
    this->columns = other.columns;
    this->matrix = new double*[lines];
    for(int i = 0; i < this->lines; i++) {
        matrix[i] = new double[columns];
    }
    for (int i = 0; i < this->lines; i++) {
        for (int j = 0; j < this->columns; j++) {
            this->matrix[i][j] = other.matrix[i][j];
        }
    }
}

// Matrix_t::Matrix_t(int n) {
//     this->lines = n;
//     this->columns = n;
//     this->matrix = new double*[lines];
//     for(int i = 0; i < this->lines; i++) {
//         matrix[i] = new double[columns];
//     }
//     for (int i = 0; i < lines; i++) {
//         this->matrix[i][i] = 1;
//     }
// }


Matrix_t::Matrix_t(int n) {
    this->lines = n;
    this->columns = n;
    this->matrix = new double*[lines];
    for(int i = 0; i < this->lines; i++) {
        matrix[i] = new double[columns];
    }
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            if (i == j)
                this->matrix[i][j] = 1;
            else 
                this->matrix[i][j] = 0;
        }
    }
}

Matrix_t::~Matrix_t() {
    for (int i = 0; i < this->lines; i++) {
        delete [] this->matrix[i];
    }
    delete [] this->matrix;
}

void Matrix_t::Print() {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void Matrix_t::Enter() {
    this->matrix = new double*[lines];
    for (int i = 0; i < this->lines; i++) {
        this->matrix[i] = new double[columns];
    }
    for (int i = 0; i < this->lines; i++) {
        for (int j = 0; j < this->columns; j++) {
            int tmp; std::cin >> tmp; 
            this->matrix[i][j] = tmp;
        }
    }
}

bool Matrix_t::operator == (const Matrix_t& other) {
    if (this->lines != other.lines || this->columns != other.columns) {
        return false;
    }
    for (int i = 0; i < this->lines; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->matrix[i][j] != other.matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix_t::operator != (const Matrix_t& other) {
    if (this->lines != other.lines || this->columns != other.columns) {
        return true;
    }
    for (int i = 0; i < this->lines; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->matrix[i][j] != other.matrix[i][j]) {
                return true;
            }
        }
    }
    return false;
}

Matrix_t& Matrix_t::operator = (const Matrix_t& other) {
    for (int i = 0; i < this->lines; i++) {
        delete [] this->matrix[i];
    }
    delete [] this->matrix;
    this->lines = other.lines;
    this->columns = other.columns;
    this->matrix = new double*[other.lines];
    for(int i = 0; i < other.lines; i++) {
        this->matrix[i] = new double[other.columns];
    }
    for(int i = 0; i < this->lines; i++) {
        for (int j = 0; j < other.lines; j++) {
            this->matrix[i][j] = other.matrix[i][j];
        }
    }
    return *this;
}

Matrix_t Matrix_t::operator + (const Matrix_t& other) {
    Matrix_t tmp(this->lines, this->columns);
    for (int i = 0; i < tmp.lines; i++) {
        for (int j = 0; j < tmp.columns; j++) {
            tmp.matrix[i][j] = other.matrix[i][j] + this->matrix[i][j];
        }
    }
    return tmp;
}

Matrix_t Matrix_t::operator - (const Matrix_t& other) {
    Matrix_t tmp(this->lines, this->columns);
    for (int i = 0; i < tmp.lines; i++) {
        for (int j = 0; j < tmp.columns; j++) {
            tmp.matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];
        }
    }
    return tmp;
}

Matrix_t Matrix_t::operator * (double s) {
    Matrix_t tmp(this->lines, this->columns);
    for (int i = 0; i < this->lines; i++) {
        for (int j = 0; j < this->columns; j++) {
            tmp.matrix[i][j] = this->matrix[i][j]*s;
        }
    }
    return tmp;
}

Matrix_t operator * (double s, const Matrix_t& other) {
    Matrix_t tmp(other.lines, other.columns);
    for (int i = 0; i < other.lines; i++) {
        for (int j = 0; j < other.columns; j++) {
            tmp.matrix[i][j] = other.matrix[i][j]*s;
        }
    }
    return tmp;
}

Matrix_t Matrix_t::operator * (const Matrix_t& other) {
    Matrix_t tmp(this->lines, other.columns);
    for (int i = 0; i < tmp.lines; i++) {
        for (int j = 0; j < tmp.columns; j++) {
            for (int k = 0; k < this->columns; k++) {
                tmp.matrix[i][j] += this->matrix[i][k]*other.matrix[k][j];
            }
        }
    }
    return tmp;
}

Matrix_t Matrix_t::Transpose() {
    Matrix_t tmp(this->columns, this->lines);
    for (int i = 0; i < this->lines; i++) {
        for (int j = 0; j < this->columns; j++) {
            tmp.matrix[j][i] = this->matrix[i][j];
        }
    }
    return tmp;
}



// double Matrix_t::Det() {
//     Matrix_t M(this->lines, 2*this->lines-1);
//     for (int i = 0; i < this->lines; i++) {
//         for (int j = 0; j < M.columns; j++) {
//             M.matrix[i][j] = this->matrix[i][j%this->columns];
//         }
//     }
//     double det = 0;
//     for (int i = 0; i < this->lines; i++) {
//         int x = 0, y = i;
//         double current_sum = 1;
//         for(int count = 0; count < this->lines; count++) {
//             std::cout << x % this->lines << " " << y % this->lines << '\n';
//             current_sum *= this->matrix[x][y];
//             y++;
//             x++;
//         }
//         std::cout << current_sum << '\n';
//         det += current_sum;
//         current_sum = 1;
//     }

//     //M.Print();

//     return 0;
// }

double Matrix_t::Det() {
    double det = 0;
    for (int i = 0; i < this->lines; i++) {
        int x = 0, y = i;
        double current_sum = 1;
        for (int count = 0; count < this->lines; count++) {
            current_sum *= this->matrix[x][y];
            x++; x %= this->lines;
            y++; y %= this->lines;
        }
        det += current_sum;
    }

    for (int i = 0; i < this->lines; i++) {
        int x = this->lines-1, y = i;
        double current_sum = 1;
        for (int count = 0; count < this->lines; count++) {
            current_sum *= this->matrix[x][y];
            x--; x %= this->lines;
            y++; y %= this->lines;
        }
        det -= current_sum;
    }

    return det;
}

double Matrix_t::FirstNorm() {
    double res = 0;
    for (int i = 0; i < this->columns; i++) {
        double tmp = 0;
        for (int j = 0; j < this->lines; j++) {
            tmp += abs(this->matrix[j][i]);
        }
        res =std::max(tmp, res);
    }
    return res;   
}

// double Matrix_t::SecondNorm() {
//     int n = this->lines;
//     Matrix_t A = *this;
//     A = A.Transpose() * A;
//     //A.Print();
//     Eigen::MatrixXd ACopy(n, n);
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             ACopy(i, j) = A.matrix[i][j];
//         }
//     }
//     //std::cout << ACopy << '\n';
//     Eigen::VectorXcd eivals = ACopy.eigenvalues();
//     double maxEiVal = -1;
//     for (auto &i : eivals) {
        
//     }
//      Change sqrt to heron's formula
//     return sqrt(maxEiVal);
// }

double Matrix_t::SecondVectorNorm() {
    int n = this->lines;
    double num;
    for (int i = 0; i < n; i++) {
        num += (this->matrix[i][0])*(this->matrix[i][0]);
    }
    return sqrt(num);
}

double Matrix_t::InfNorm() {
    double res = -100000;
    for (int i = 0; i < this->lines; i++) {
        double tmp = 0;
        for (int j = 0; j < this->columns; j++) {
            tmp += abs(this->matrix[i][j]);
        }
        res =std::max(tmp, res);
    }
    return res;
}

bool Matrix_t::NotNull() {
    for (int i = 0; i < this->lines; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->matrix[i][j] == 0) 
                return false; 
        }
    }
    return true;
}

void Matrix_t::Clear() {
    for (int i = 0; i < this->lines; i++) {
        for (int j = 0; j < this->columns; j++) {
            this->matrix[i][j] = 0;
        }
    }
}

Matrix_t Matrix_t::Cut(int b1, int b2, int a1, int a2) {
    Matrix_t res(b2-b1+1, a2-a1+1);
    for (int i = b1; i < b2+1; i++) {
        for (int j = a1; j < a2+1; j++) {
            res.matrix[i-b1][j-a1] = this->matrix[i][j];
        }
    }
    return res;
}

Matrix_t Ort(int n) {
    Matrix_t res(n, 1);
    res.matrix[0][0] = 1;
    return res;
}

Matrix_t E(int n) {
    Matrix_t res(n, n);
    for (int i = 0; i < res.lines; i++) {
        for (int j = 0; j < res.columns; j++) {
            if (i == j)
                res.matrix[i][j] = 1;
            else
                res.matrix[i][j] = 0;
        }
    }
    return res;
}

void Matrix_t::Insert(int b1, int b2, int a1, int a2, const Matrix_t& other) {
    for (int i = b1; i < b2+1; i++) {
        for (int j = a1; j < a2+1; j++) {
            this->matrix[i][j] = other.matrix[i-b1][j-a1];
        }
    }
}

void Matrix_t::SwapLines(int l1, int l2) {
    for (int i = 0; i < this->columns; i++) {
        double tmp;
        tmp = this->matrix[l1][i];
        this->matrix[l1][i] = this->matrix[l2][i];
        this->matrix[l2][i] = tmp;
    }
}

// bool Matrix_t::IsPositiveDefined() {
//     Eigen::MatrixXd newA(this->lines, this->lines);
// 	for (int i = 0; i < this->lines; i++) {
// 		for (int j = 0; j < this->lines; j++) {
// 			newA(i, j) = this->matrix[i][j];
// 		}
// 	}
// 	Eigen::EigenSolver<Eigen::MatrixXd> solver(newA);
// 	for (int i = 0; i < this->lines; i++)
// 		if (solver.eigenvalues()[i].real() <= 0) return false;
// 	return true;
// }

bool Matrix_t::IsPositiveDefined() {
    for (int i = 0; i < this->lines; i++) {
        if (this->Cut(0,i,0,i).Det() <= 0) {
            return false;
        }
    }
    return true;
}

bool Matrix_t::IsDiagonallyDominant() {
    for (int i = 0; i < this->lines; i++) {
        double sum = 0;
        for (int j = 0; j < this->lines; j++) {
            if (j != i) sum += abs(this->matrix[i][j]);
        }
        if (abs(this->matrix[i][i]) < sum)
            return false;
    }
    return true;
}