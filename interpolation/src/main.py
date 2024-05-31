import interpolation as intr 
import numpy as np
from tabulate import tabulate


# a, b = -10, 10
a, b = -5, 5
# a, b = 2, 12
k = 1000
def f(x: float) -> float:
    return 3 * x - np.cos(x) - 1
    # return x*np.log(x+1)


def main() -> None:
    x = np.arange(a, b, 0.01)
    
    
    """
    Linear spline
    """
    table = []
    for n in range(10, 41, 10):
        points = intr.fill_equally(a, b, n)
        ls1 = intr.linear_spline(points, f)
        p_y = []
        
        for i in x:
            j = 0
            while j < n-1 and points[j+1] <= i:
                j += 1
            if j == n-1: j -= 1
            p_y.append(ls1[j][1]*i + ls1[j][0])
        """
        Filling the table
        """
        max_deviation = -10000
        for i in range(k):
            max_deviation = max(max_deviation, abs(p_y[i] - f(x[i])))
        table.append([n, k, max_deviation])
    field_names = ["Количество узлов (n)", "Количество проверочных точек (k)", "Максимальное отклонение (RS^n_1,0)"]
    print(tabulate(table, headers=field_names, tablefmt="fancy_grid"))

    """
    Square spline
    """
    table = []
    for n in range(10, 40+1, 10):
        points = intr.fill_equally(a, b, n)
        ls1 = intr.square_spline(points, f)
        p_y = []
        
        for i in x:
            j = 0
            while j < n-1 and points[j+1] <= i:
                j += 1
            if j == n-1: j -= 1
            p_y.append(ls1[j][2]*i**2 + ls1[j][1]*i + ls1[j][0])
        # Filling the table
        max_deviation = -10000
        for i in range(k):
            max_deviation = max(max_deviation, abs(p_y[i] - f(x[i])))
        table.append([n, k, max_deviation])
    field_names = ["Количество узлов (n)", "Количество проверочных точек (k)", "Максимальное отклонение (RS^n_2,1)"]
    print(tabulate(table, headers=field_names, tablefmt="fancy_grid"))   
        
    
    """
    Cubic spline
    """
    table = []
    for n in range(10, 41, 10):
        points = intr.fill_optimally(a, b, n)
        ls1 = intr.cubic_spline(points, f)
        p_y = []
        
        for i in x:
            j = 0
            while j < n-1 and points[j+1] <= i:
                j += 1
            if j == n-1: j -= 1
            p_y.append(ls1[j][3]*i**3 + ls1[j][2]*i**2 + ls1[j][1]*i + ls1[j][0])
        """
        Filling the table
        """
        max_deviation = -10000
        for i in range(k):
            max_deviation = max(max_deviation, abs(p_y[i] - f(x[i])))
        table.append([n, k, max_deviation])
    field_names = ["Количество узлов (n)", "Количество проверочных точек (k)", "Максимальное отклонение (RS^n_3,2)"]
    print(tabulate(table, headers=field_names, tablefmt="fancy_grid"))     
    
    
    
    # y = f(x)
    # fig, ax = plt.subplots(2, 4)
    # """
    # Lagrange polynomial
    # """
    # table = []
    # s = 0
    # for i in range(10, 41, 10):
    #     eq_points = intr.fill_equally(a, b, i)
    #     opt_points = intr.fill_optimally(a, b, i)
    #     eq_lagrange = intr.lagrange_polynomial(eq_points, f)
    #     opt_lagrange = intr.lagrange_polynomial(opt_points, f)
    #     rl_n  = np.polyval(eq_lagrange, np.arange(a, b, 0.01))
    #     rl_opt_n = np.polyval(opt_lagrange, np.arange(a, b, 0.01))
    #     """
    #     Count deviation
    #     """
    #     max_eq_dev, max_opt_dev = 0, 0
    #     for m in range(k):
    #         max_eq_dev = max(max_eq_dev, abs(f(x[m])-rl_n[m]))
    #         max_opt_dev = max(max_opt_dev, abs(f(x[m])-rl_opt_n[m]))
    #     table.append([i, k, max_eq_dev, max_opt_dev])
    #     """
    #     Building graphics
    #     """
    #     ax[0, s].plot(x, y, label='f(x)')
    #     ax[0, s].plot(x, rl_n, label=f'L_{i}(x)')
    #     ax[0, s].plot(x, rl_opt_n, label=f'Lopt_{i}(x)')
    #     ax[0, s].legend()
    #     ax[0, s].grid()
    #     s += 1
    # field_names = ["Количество узлов (n)", "Количество проверочных точек (k)", "Максимальное отклонение RL_n", " Максимальное отклонение RLopt_n"]     
    # print(tabulate(table, headers=field_names, tablefmt="fancy_grid"))
    # """
    # Newton polynomial
    # """
    # table = []
    # s = 0
    # for i in range(10, 41, 10):
    #     eq_points = intr.fill_equally(a, b, i)
    #     opt_points = intr.fill_optimally(a, b, i)
    #     eq_newton = intr.newton_polynomial(eq_points, f)
    #     opt_newton = intr.newton_polynomial(opt_points, f)
    #     rl_n  = np.polyval(eq_newton, np.arange(a, b, 0.01))
    #     rl_opt_n = np.polyval(opt_newton, np.arange(a, b, 0.01))
    #     """
    #     Count deviation
    #     """
    #     max_eq_dev, max_opt_dev = 0, 0
    #     for m in range(k):
    #         max_eq_dev = max(max_eq_dev, abs(f(x[m])-rl_n[m]))
    #         max_opt_dev = max(max_opt_dev, abs(f(x[m])-rl_opt_n[m]))
    #     table.append([i, k, max_eq_dev, max_opt_dev])
    #     """
    #     Building graphics
    #     """
    #     ax[1, s].plot(x, y, label='f(x)')
    #     ax[1, s].plot(x, rl_n, label=f'N_{i}(x)')
    #     ax[1, s].plot(x, rl_opt_n, label=f'Nopt_{i}(x)')
    #     ax[1, s].legend()
    #     ax[1, s].grid()
    #     s += 1
    # field_names = ["Количество узлов (n)", "Количество проверочных точек (k)", "Максимальное отклонение RN_n", " Максимальное отклонение RNopt_n"]     
    # print(tabulate(table, headers=field_names, tablefmt="fancy_grid")) 

    # plt.show()
    
    # fig, ax = plt.subplots(2, 4)
    # """
    # By equal nodes
    # """
    # s = 0
    # for cnt in range(10, 41, 10):
    #     nodes = intr.fill_equally(a, b, cnt)
    #     lagrange = intr.newton_polynomial(nodes, f)
    #     lagrange_values  = np.polyval(lagrange, np.arange(a, b, 0.01))
    #     cub_spline = intr.cubic_spline(nodes, f)
    #     cub_spline_values = []
    #     for i in x:
    #         j = 0
    #         while j < n-1 and nodes[j+1] <= i:
    #             j += 1
    #         if j == n-1: j -= 1
    #         cub_spline_values.append(cub_spline[j][3]*i**3 + cub_spline[j][2]*i**2 + cub_spline[j][1]*i + cub_spline[j][0])
    #     diff_l = [abs(lagrange_values[i] - f(x[i])) for i in range(k)]
    #     diff_cs = [abs(cub_spline_values[i] - f(x[i])) for i in range(k)]
    #     ax[0, s].plot(x, diff_l, label=f'L_{cnt}')
    #     ax[0, s].plot(x, diff_cs, label=f'S_3,2_{cnt}')
    #     ax[0, s].legend()
    #     ax[0, s].grid()
    #     s += 1
    # """
    # By optimal nodes
    # """
    # s = 0
    # for cnt in range(10, 41, 10):
    #     nodes = intr.fill_optimally(a, b, cnt)
    #     lagrange = intr.newton_polynomial(nodes, f)
    #     lagrange_values  = np.polyval(lagrange, np.arange(a, b, 0.01))
    #     cub_spline = intr.cubic_spline(nodes, f)
    #     cub_spline_values = []
    #     for i in x:
    #         j = 0
    #         while j < n-1 and nodes[j+1] <= i:
    #             j += 1
    #         if j == n-1: j -= 1
    #         cub_spline_values.append(cub_spline[j][3]*i**3 + cub_spline[j][2]*i**2 + cub_spline[j][1]*i + cub_spline[j][0])
    #     diff_l = [abs(lagrange_values[i] - f(x[i])) for i in range(k)]
    #     diff_cs = [abs(cub_spline_values[i] - f(x[i])) for i in range(k)]
    #     ax[1, s].plot(x, diff_l, label=f'Lopt_{cnt}')
    #     ax[1, s].plot(x, diff_cs, label=f'S_3,2opt_{cnt}')
    #     ax[1, s].legend()
    #     ax[1, s].grid()
    #     s += 1
    # plt.show()

if __name__ == "__main__":
    main()
    
