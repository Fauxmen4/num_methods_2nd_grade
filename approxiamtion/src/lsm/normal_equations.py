from typing import Callable

import numpy as np
import numpy.linalg as la


def normal_equations(x: list[float], f: Callable, pow: int):
    """
    Count coefficient of approximation ploynomial using normal equations
    """
    n = pow
    m = len(x)
    E = np.array([[0] * (n + 1)] * m, dtype=float)
    vals = np.array([ f(x_i) for x_i in x], dtype=float)
    # calculating E matrix
    for i in range(m):
        for j in range(n + 1):
            E[i][j] = x[i] ** j
    # Polynomial is calcualted in equation: E.T*E*a=E.T*f
    a = la.solve(E.T @ E, E.T @ vals)      # coefficients of approximation polynomial
    return a
