from typing import Callable
import random

import numpy as np


EPS = 0.5  # half the length of the value corridor
MAX_VALUES_IN_POINT = 5


def generate_points(low: float, up: float, cnt: int, f: Callable):
    x, y = [], []  # input data
    points = np.linspace(low, up, cnt)
    for i in points:
        # add exact point with accurate measuring
        #! Uncomment in order to add accurately measured points to input data
        # x.append(i)
        # y.append(f(i))
        # generate additional points inside of the value corridor
        vals_cnt = random.randint(3, MAX_VALUES_IN_POINT)
        for _ in range(vals_cnt):
            val = f(i) - EPS + 2 * EPS * random.random()
            x.append(i)
            y.append(val)
    return x, y


def poly_val(coeffs, x):
    # in case degrees in coeffs in increasing order
    val = 0
    for i, v in enumerate(coeffs):
        val += v*x**i
    return val


def lsm_error(x: list[float], y: list[float], a: np.ndarray):
    """
    Sum of squared errors for LSM
    """
    err = 0
    for i, x_i in enumerate(x):
        err += (y[i] - poly_val(a, x_i))**2
    return err
