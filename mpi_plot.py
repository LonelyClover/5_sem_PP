import matplotlib.pyplot as plt
import numpy as np

x = [2, 4, 8, 16]
y = [100000, 200000, 400000, 800000, 1600000, 3200000]

xx = x * len(y)
yy = [yi for yi in y for _ in range(len(x))]

zz = [ 
 1.500699,	 1.306497,	0.556406,	0.082194,
 3.157029,	 2.612390,	1.117016,	0.152502,
 9.497937,	 5.202948,	2.231242,	0.269884,
13.423271,	10.421332,	4.404296,	0.594860,
24.402896,	20.816346,	2.238879,	1.177378,
40.770107,	41.699605,	4.545853,	2.156015]

plt.figure(figsize=(15,15))
ax = plt.axes(projection='3d')
plt.title('MPI')
ax.set_xlabel('# cores')
ax.set_ylabel('# points')
ax.set_zlabel('time')
ax.plot_trisurf(xx, yy, zz, cmap='viridis', edgecolor='none')

plt.show()
