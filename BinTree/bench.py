import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rcParams

plt.rcParams["font.family"] = "IPAexGothic"

N = np.array([1000,10000,100000,1000000,10000000])
time = np.array([1,5,54,944,16821])

plt.scatter(N, time,label="計測値")

plt.grid(which='major',color='black',linestyle='-')
plt.grid(which='minor',color='black',linestyle='-')

plt.title("")
plt.xlabel("")
plt.ylabel("")

plt.legend()
plt.show()

