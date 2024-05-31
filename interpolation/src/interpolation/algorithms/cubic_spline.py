from typing import Callable
import numpy as np
from ..poly import Poly


def cubic_spline(points: np.array, f: Callable[[float], float]) -> list[np.poly]:
    n = len(points)
    gamma = np.array([0]*(n-2), dtype=float)
    for i in range(n-2):
        gamma[i] = 6*((f(points[i+2]) - f(points[i+1])) / (points[i+2] - points[i+1]) -
                      (f(points[i+1]) - f(points[i])) / (points[i+1] - points[i]))
    h = np.array([[0]*(n-2)]*(n-2), dtype=float)
    h[0][0] = 2*(points[2] - points[0])
    for i in range(n-3):
        h[i+1][i+1] = 2*(points[i+3] - points[i+1]) 
        h[i+1][i] = points[i+2] - points[i+1]
        h[i][i+1] = points[i+2] - points[i+1]
    sol = np.linalg.solve(h, gamma)
    y2d = np.concatenate((np.array([0]), sol, np.array([0])), dtype=float)
    y1d = np.array([0]*(n-1), dtype=float)
    for i in range(n-1):
        y1d[i] = (
            (f(points[i+1]) - f(points[i])) / (points[i+1] - points[i]) - 
            y2d[i+1] * (points[i+1] - points[i]) / 6 - 
            y2d[i] * (points[i+1] - points[i]) / 3
                  )    
    res = []
    for i in range(n-1):
        tmp_poly = np.poly([])*0
        tmp_poly = np.polyadd( (y2d[i+1] - y2d[i])/(points[i+1]-points[i])/6*np.poly([points[i]]*3), tmp_poly )
        tmp_poly = np.polyadd( tmp_poly, y2d[i]/2*np.poly([points[i]]*2) )
        tmp_poly = np.polyadd( tmp_poly, y1d[i]*np.poly([points[i]]) )
        tmp_poly = np.polyadd( tmp_poly, f(points[i]) )
        res.append(tmp_poly[::-1])
    return res 
