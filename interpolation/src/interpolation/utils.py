import math
import numpy as np


def fill_equally(a, b: float, n: int) -> list:
    return [a + i * (b - a) / (n - 1) for i in range(n)]


def fill_optimally(a, b: float, n: int) -> list:
    n -= 1
    points = []
    for i in range(n+1):
        points.append(((b - a) * math.cos((1 + 2 * i) / (2 + 2 * n) * math.pi) + (a + b))/2)
    points[0] = b 
    points[len(points)-1] = a 
    return points[::-1]
