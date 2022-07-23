import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


def func(x, a, b, c, d, e, f):
    return a + b*x + c*x**2 + d*x**3 + e*x**4 + f*x**5
# Define the data to be fit with some noise:


xi = -np.exp(1)
xf = 0

x_cmp = np.linspace(xi, xf, 1000)
y_cmp = np.exp(x_cmp)
xdata = np.linspace(xi, xf, 10000)
y = func(xdata, 1, 1, 1/2, 1/6, 1/24, 1/120)
ydata = np.exp(xdata)
plt.plot(x_cmp, y_cmp, 'b-', label='data')
#plt.plot(xdata, ydata, 'b-', label='data')
# Fit for the parameters a, b, c of the function func:

popt, pcov = curve_fit(
    func, xdata, ydata, bounds=(-1, [1., 1., 1., 1., 1., 1.]))
print(popt)

maxerror = max(ydata-func(xdata, *popt))

print(maxerror)

plt.plot(xdata, func(xdata, *popt), 'r-', label='fit')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.show()

plt.plot(xdata, abs(ydata-func(xdata, *popt))/ydata, 'r-', label='rel error')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.show()
