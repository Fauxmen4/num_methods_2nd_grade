from typing import Tuple

import numpy.linalg as la
import numpy as np


DELTA = 1e-8    # absolute tolerance below which the coordinate is considered to be zero
RTOL = 1e-6     # relative error for computing eigenvalues in power_method


def power_method(a: np.ndarray) -> Tuple[np.ndarray, float]:
    """
    Power method implementation  
    """
    y = np.ones(a.shape[0])         # initial vector y^(0)
    z = y / la.norm(y)                                # normalized y^(0)
    lambda_new = np.zeros(len(y))

    for _ in range(2000):
        # main calculation on iteration
        y = a @ z                                     # y^(k)
        # counting lambda^(k) for calculation the papproximation of target eigenvalue
        lambda_prev = lambda_new.copy()
        lambda_new = np.zeros(len(y))
        cnt = 0                                       # amount of non-null coordinates in lambda_new
        for i, z_i in enumerate(z):
            if abs(z_i) > DELTA:
                lambda_new[i] = y[i] / z_i
                cnt += 1
        z = y / la.norm(y)                             # normalized y^(k)
        # check for convergence condition
        if la.norm(lambda_new - lambda_prev, ord=np.inf) <= RTOL * max(
                la.norm(lambda_prev, ord=np.inf),
                la.norm(lambda_new, ord=np.inf)
            ):
            eigval = sum(lambda_new) / cnt
            return z, eigval

    return np.array([]), float('inf')
