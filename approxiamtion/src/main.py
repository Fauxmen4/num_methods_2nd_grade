from typing import Callable
from tabulate import tabulate
import random

import numpy as np
import numpy.linalg as la
import matplotlib
import matplotlib.pyplot as plt

from lsm import *


lower, upper = -1, 1
m = 30
max_pow = 5
table_headers = ["Степень полинома (n)", "Сумма квадратов ошибок для МНК (нормальные уравнения)", "Сумма квадратов ошибок для МНК (ортогональные полиномы)"]

def f(x):
    """
    function I gonna approxiamte
    """
    return 3 * x - np.cos(x + 1)


x, y = generate_points(lower, upper, m, f)
# test_x = [0, 0.25, 0.0833, 0.75, 1]
# test_y = [1.0,2,1,0,1]
# def test_f(x):
#     match x:
#         case 0:
#             return 1
#         case 0.25:
#             return 2
#         case 0.0833:
#             return 1
#         case 0.75:
#             return 0
#         case 1:
#             return 1

# norm = normal_equations(test_x, test_y, 4)
# orth = orthogonal_polynomials(test_x, test_f, 4)
# print(norm, orth, sep="\n")

table = []
for n in range(1, max_pow+1):
    a1 = normal_equations(x, f, n)
    a2 = orthogonal_polynomials(x, f, n)
    x_a = np.linspace(lower, upper, 1000)
    y_a1 = [poly_val(a1, i) for i in x_a]
    y_a2 = [poly_val(a2, i) for i in x_a]
    # plotting
    plt.subplot(1, max_pow, n)
    plt.plot(x_a, y_a1, "#FFA500")
    plt.plot(x_a, y_a2, "#008000")
    plt.legend(['normal', 'orthogonal'])
    plt.plot(x, y, "b.")
    plt.grid()

    table.append([n, lsm_error(x, y, a1), lsm_error(x, y, a2)])

# Print results in form of table and graphics
print(tabulate(table, headers=table_headers, tablefmt="mixed_grid"))

plt.show()
