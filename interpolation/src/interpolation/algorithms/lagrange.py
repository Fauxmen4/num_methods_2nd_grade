from typing import Callable
import numpy as np
import math


def lagrange_polynomial(points: np.array, f: Callable[[float], float]) -> np.poly:
    res = 0*np.poly([])
    for i in range(len(points)):
        x_s = points[0:i] + points[i+1:len(points)]
        tmp_res = np.poly(x_s)
        tmp_res *= f(points[i])
        for x in x_s:
            tmp_res /= (points[i] - x)
        res += tmp_res
    return np.array(res)