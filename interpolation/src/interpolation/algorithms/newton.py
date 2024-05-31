from typing import Callable
import numpy as np
import math


def separated_differences(x_s: np.array, n: int, f: Callable[[float], float]) -> float:
    res = 0
    for i in range(n):
        g = 1
        for j in range(n):
            if i != j:
                g /= (x_s[i]-x_s[j]) 
        res += g*f(x_s[i])
    return res        
    

def newton_polynomial(points: np.array, f: Callable[[float], float]) -> np.poly:
    res = 0*np.poly([]) + f(points[0])
    for i in range(1, len(points)):
        res = np.polyadd(res, np.poly(points[:i])*separated_differences(points, i+1, f))
    return res