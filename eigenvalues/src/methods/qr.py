import numpy as np
import numpy.linalg as la


EPS = 1e-8  # tolerance


def to_hessenberg_form(a: np.ndarray) -> np.ndarray:
    """
    Bring matrix a to Hessenberg form by using Hausholder method (reflection method)
    """
    res = a.copy()      # by the end of this function there would be matrix a in hessenberg form
    n = a.shape[0]                    # size of input matrix a
    for i in range(1, n-1):
        # for one iteration sub-diagonal elements in column i-1 become zeroes
        tmp = np.array([0]*n, dtype=float)
        for j in range(i, n):
            tmp[j] = res[j][i-1]
        s1 = la.norm(tmp, ord=2)
        if tmp[i] < 0:
            s1 *= -1
        mu1 = 1/np.sqrt(2*s1*(s1-tmp[i]))
        tmp[i] -= s1
        v = mu1*tmp
        h = np.eye(a.shape[0]) - 2 * (v.reshape(-1, 1) @ v.reshape(-1, 1).T)
        res = h @ res @ h
    # all elements in res which are smaller than tolerance should become zeroes 
    return round_to_diagonal(res)


def round_to_diagonal(a: np.ndarray) -> np.ndarray:
    """
    all elements in matrix a which are smaller than tolerance should become zeroes
    """
    res = a.copy()
    for i in range(res.shape[0]):
        for j in range(res.shape[1]):
            if abs(res[i][j]) < EPS:
                res[i][j] = 0
    return res


def is_diagonal(a: np.ndarray) -> bool:
    """
    check if matrix b is diagonal
    """
    for i in range(0, a.shape[0]):
        for j in range(i+1, a.shape[0]):
            # elements of a smaller size than EPS modulo are considered to be null
            if abs(a[j][i]) >= EPS:
                return False
    return True


def qr(a: np.ndarray) -> list[float]:
    """
    method of finding all matrix eigenvalues by using QR decomposition
    """
    b = to_hessenberg_form(a)
    eigvals = []
    while True:
        n = b.shape[0]          # size of matrix b
        # iteration with a shift
        q, r = la.qr(b - b[n-1][n-1] * np.eye(n))
        b = (r @ q + b[n-1][n-1] * np.eye(n))
        # decrease matrix size to increase speed of algorithm
        if abs(b[n-1][n-2]) < EPS:
            eigvals.append(b[n-1][n-1])
            b = b[0:n-1, 0:n-1]
            if b.shape[0] == 1:
                eigvals.append(b[0][0])
                return eigvals
    