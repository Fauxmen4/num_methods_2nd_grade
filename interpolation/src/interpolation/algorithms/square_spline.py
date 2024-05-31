from typing import Callable
import numpy as np


def square_spline(points: np.array, f: Callable[[float], float]) -> list[list[float]]:
    n = len(points)
    a = np.array([[0]*(n-1)*3]*(n-1)*3, dtype=float)
    b = np.array([0]*(n-1)*3, dtype=float)
    for i in range(n-1):
        b[i*3] = f(points[i])
        b[i*3+1] = f(points[i+1])
        a[i*3][i*3] = points[i]**2
        a[i*3][i*3+1] = points[i]
        a[i*3+1][i*3] = points[i+1]**2
        a[i*3+1][i*3+1] = points[i+1]
        a[i*3+2][i*3] = 2 * points[i+1]
        a[i*3][i*3+2] = a[i*3+1][i*3+2] = a[i*3+2][i*3+1] = 1
        if i != n-2:
            a[i*3+2][i*3+3] = (-2) * points[i+1]
            a[i*3+2][i*3+4] = -1
    solution = np.linalg.solve(a, b)
    res = []
    for i in range(n-1):
        res.append([solution[i*3+2], solution[i*3+1], solution[i*3]])
    return res
