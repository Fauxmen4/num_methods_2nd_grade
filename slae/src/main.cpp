#include "matrix_t.h"

Matrix_t test5A(int n, double eps) {
    Matrix_t A1(E(n));
    for (int i = 0; i < A1.lines; i++) {
        for (int j = 0; j < A1.lines; j++) {
            if (j > i) {
                A1.matrix[i][j] = -1;
            }
        }
    }
    Matrix_t A2(E(n));
    for (int i = 0; i < A1.lines; i++) {
        for (int j = 0; j < A1.lines; j++) {
            if (j > i) {
                A1.matrix[i][j] = -1;
            } else {
                A1.matrix[i][j] = 1;
            }
        }
    }
    return A1+eps*7*A2;
}

Matrix_t test5b(int n) {
    Matrix_t b(n, 1);
    for (int i = 0; i < b.lines-1; i++) {
        b.matrix[i][0] = -1;
    }
    b.matrix[b.lines-1][0] = 1;
    return b;
}

void PrintAnswer(Matrix_t x) {
    std::cout << '[';
    std::cout << x.matrix[0][0];
    for (int i = 1; i < x.lines; i++) {
        std::cout << ", " << x.matrix[i][0];
    }
    std::cout << "]\n";
}

void PrintDifference(Matrix_t accur, Matrix_t close) {
    std::cout << '[';
    std::cout << abs(accur.matrix[0][0]-close.matrix[0][0]);
    for (int i = 1; i < accur.lines; i++) {
    std::cout << ", " << abs(accur.matrix[i][0]-close.matrix[i][0]);
    }
    std::cout << "] ";
}

const std::string testDir = "/home/parz1val/Documents/amcp/num_methods/tests/";

int main() {
    Matrix_t A(5, 5);
    Matrix_t b(5, 1);
    A.Enter();
    b.Enter();
    SimpleIterMethod(A, b, pow(10, -4)).first.Print();
    Solution(A,b).Print();
}

// int main() {
//     std::string testPath = testDir+"i.txt";
//     for (int eps = -3; eps > -6; eps--) {
//         std::cout << "Gauss Seidel method with accuracy: " << pow(10,eps) << "\n";
//         for (int i = 0; i < 5; i++) {
//             testPath[testDir.length()] = toascii(i+48);
//             std::pair<Matrix_t, Matrix_t> test = EnterSLAE(3, testPath);
//             std::cout << i << ": ";
//             std::pair<Matrix_t, int> answer = SeidelMethod(test.first, test.second, pow(10,eps));
//             std::cout << "k = " << answer.second << ' ';
//             PrintDifference(Solution(test.first, test.second), answer.first);
//             PrintAnswer(answer.first);
//         }    
//     }    
//     for (int eps = -3; eps > -6; eps--) {
//         std::cout << "Simple iteration method with accuracy: " << pow(10,eps) << "\n";
//         for (int i = 0; i < 5; i++) {
//             testPath[testDir.length()] = toascii(i+48);
//             std::pair<Matrix_t, Matrix_t> test = EnterSLAE(3, testPath);
//             std::cout << i << ": ";
//             std::pair<Matrix_t, int> answer = SimpleIterMethod(test.first, test.second, pow(10,eps));
//             std::cout << "k = " << answer.second << ' ';
//             PrintDifference(Solution(test.first, test.second), answer.first);
//             PrintAnswer(answer.first);
//         }    
//     }
//     std::cout << "LU decomposition\n";
//     for (int i = 0; i < 5; i++) {
//         testPath[testDir.length()] = toascii(i+48);
//         std::pair<Matrix_t, Matrix_t> test = EnterSLAE(3, testPath);
//         std::cout << i << ": ";
//         PrintAnswer(LU(test.first, test.second));
//     } 
//     std::cout << "QR decomposition\n";
//     for (int i = 0; i < 5; i++) {
//         testPath[testDir.length()] = toascii(i+48);
//         std::pair<Matrix_t, Matrix_t> test = EnterSLAE(3, testPath);
//         std::cout << i << ": ";
//         PrintAnswer(SimpleIterMethod(test.first, test.second, pow(10,-4)).first);
//     } 


    // std::cout << "Test 5:\n";
    

    // std::cout << "LU decomposition\n";
    // for (int i = 4; i < 7; i++) {
    //     Matrix_t A1(test5A(i, pow(10, -3)));
    //     Matrix_t b1(test5b(i));
    //     std::cout << "n = " << i << "\tEps = " << pow(10, -3) << ": ";
    //     Matrix_t ans1 = LU(A1, b1);
    //     PrintDifference(Solution(A1, b1), ans1);
    //     PrintAnswer(ans1);

    //     Matrix_t A2(test5A(i, pow(10, -6)));
    //     Matrix_t b2(test5b(i));
    //     std::cout << "n = " << i << "\tEps = " << pow(10, -6) << ": ";
    //     Matrix_t ans2 = LU(A2, b2);
    //     PrintDifference(Solution(A2, b2), ans2);
    //     PrintAnswer(ans2);



    //     // test5A(i, pow(10, -3)).Print();
    //     // test5b(i).Print();
    //     // test5A(i, pow(10, -6)).Print();
    //     // test5b(i).Print();
    // }




//}
