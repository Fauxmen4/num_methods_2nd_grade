from typing import Tuple, Set

import numpy.linalg as la
import numpy as np


DELTA = 1e-8    # absolute tolerance below which the coordinate is considered to be zero
EPS = 1e-8      # permissible error


def find_with_shift(a: np.ndarray, shift: float) -> Tuple[np.ndarray, float]:
    """
    Inverse power method implementation for finding eigen values
    """
    y = np.ones(a.shape[0])     # initial vector y^(0)
    z = y / la.norm(y)                            # normalized y^(0)
    sigma = shift                          # initial shift

    while True:
        # main calculation on iteration
        y = la.solve(a - sigma * np.eye(a.shape[0]), z) # y^(k)
        # counting mu^(k) to calculate lambda_m averaged by my^(k) coordinates
        mu = []
        for i, y_i in enumerate(y):
            if abs(y_i) >= DELTA:
                mu.append(z[i] / y_i)
        z = y / la.norm(y)                                                      # normalized y^(k)
        if len(mu) != 0:
            new_sigma = sigma + sum(mu) / len(mu)
            # check for convergence
            if abs(new_sigma - sigma) <= EPS:
                return z, new_sigma
            sigma = new_sigma


# TODO: Fix issue with repetitive eigenvectors
def inverse_power_method(a: np.ndarray, step: float = 1) -> Tuple[Set[np.ndarray], Set[float]]:
    eigvectors = set()
    eigvals = set()
    for shift in np.arange(-la.norm(a), la.norm(a), step, dtype=float):     # changing shift for finding all eigen[values|vectors]
        try:
            eigvector, eigval = find_with_shift(a, shift)
            # Round vector and add it to set in order to avoid dublicates
            for i, v in enumerate(eigvector):
                eigvector[i] = round(v, 5)    
            eigvector = tuple(eigvector)
            eigvectors.add(eigvector)
            # The same as with vectors
            eigval = round(eigval, 11) 
            eigvals.add(eigval)
        except np.linalg.LinAlgError:   
            # Sometimes singular matrix appears in algorithm so we skip this iteration
            # We can afford it because step is too small so we would definitely find all eigen[values|vectors]
            continue
    return eigvectors, eigvals
