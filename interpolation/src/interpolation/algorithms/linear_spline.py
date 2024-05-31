from typing import Callable
import numpy as np
from ..poly import Poly


def linear_spline(points: np.array, f: Callable[[float], float]) -> list[list[float]]:
    n = len(points) - 1
    res = []
    for i in range(n):
        a = np.array([[points[i], 1], [points[i+1], 1]])
        b = np.array([[f(points[i])], [f(points[i+1])]])
        tmp = np.linalg.solve(a, b)
        res.append(tmp[::-1])
    return res
