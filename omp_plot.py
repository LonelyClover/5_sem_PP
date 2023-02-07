import matplotlib.pyplot as plt
import numpy as np

x = [2, 4, 8, 16]
y = [100000, 200000, 400000, 800000, 1600000, 3200000]

xx = x * len(y)
yy = [yi for yi in y for _ in range(len(x))]

zz = [ 
 1.388094,	 0.703819,	0.362753,	0.084720,
 2.931458,	 1.407739,	0.246913,	0.186645,
 5.526732,	 2.803745,	0.593160,	0.367467,
10.618050,	 5.602037,	1.412887,	0.673172,
21.071662,	11.194190,	2.320875,	1.289701,
43.844119,	17.765051,	4.010813,	2.470688]

plt.figure(figsize=(15,15))
ax = plt.axes(projection='3d')
plt.title('OpenMP')
ax.set_xlabel('# cores')
ax.set_ylabel('# points')
ax.set_zlabel('time')
ax.plot_trisurf(xx, yy, zz, cmap='viridis', edgecolor='none')

plt.show()
