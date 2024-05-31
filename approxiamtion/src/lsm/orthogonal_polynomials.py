from typing import Callable

import numpy as np

from lsm.utils import poly_val


def orthogonal_polynomials(x: list[float], f: Callable, pow: int):
    """
    Count coefficient of approximation ploynomial using orthogonal polynomials
    """
    q_k = build_orth_polys(x, pow)
    a = []
    for i in range(pow+1):
        a.append(
            sum(
                [ poly_val(q_k[i], x_i)*f(x_i) for x_i in x ]
            ) / sum(
                [ poly_val(q_k[i], x_i)**2 for x_i in x ]
            )
        )
    q = np.array([0]*(pow+1), dtype=float)
    for i in range(pow+1):
        q += a[i]*q_k[i]
    return q


# pow must be >= 2
def build_orth_polys(x: list[float], pow: int):
    """
    build orthogonal polynomials up to specified degree in variable (pow)
    """
    m = len(x)
    q = []      # array with coeffs of orthogonal polynomials
    q.append(
        np.array([1])
    )
    q.append(
        np.array([-sum(x)/m, 1])
    )
    # next polynomials are calculate according to the formula:
    # q[j+1] = x*q[j] - alpha*q[j] - beta*q[j-1]
    for i in range(2, pow+1):
        alpha = sum(
            [ x_i*poly_val(q[i-1], x_i)**2 for x_i in x ]
        ) / sum(
            [ poly_val(q[i-1], x_i)**2 for x_i in x ]
        )
        beta = sum(
            [ x_i*poly_val(q[i-1], x_i)*poly_val(q[i-2], x_i) for x_i in x ]
        ) / sum(
            [ poly_val(q[i-2], x_i)**2 for x_i in x ]
        )

        new_q = np.insert(q[i-1], 0, 0) - alpha*np.append(q[i-1], 0) - beta*np.append(q[i-2], [0, 0])
        q.append(new_q)
    # add insignificant zeroes to simplify calcultions in future functions
    for i in range(pow+1):
        q[i] = np.append(q[i], np.array([0]*(pow-i)))
    return q
