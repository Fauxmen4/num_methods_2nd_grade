import numpy as np
import numpy.linalg as la

from methods import qr


LOW, HIGH = -100, 100
N = 10

# random number generator initialization
rng = np.random.default_rng()

"""
Generating random matrix a for testing
"""
l = rng.integers(low=LOW, high=HIGH, size=N)
l_m = np.diag(l)
c_m = rng.integers(low=LOW, high=HIGH, size=N*N).reshape(N, N)
a = c_m @ l_m @ la.inv(c_m)
print(a)

res = qr(a)
print(res, la.eigvals(a), sep="\n")
