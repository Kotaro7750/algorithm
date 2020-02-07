import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import rcParams

plt.rcParams["font.family"] = "IPAexGothic"

df = pd.read_csv('./bench.csv',header=0)

N = df[['n']].values
avg = df[['appendAVG']].values
build = df[['appendT']].values

plt.scatter(N, avg,label="計測値")

plt.grid(which='major',color='black',linestyle='-')
plt.grid(which='minor',color='black',linestyle='-')


plt.title("AVL木のノード挿入時間")
plt.xlabel("ノード数")
plt.ylabel("挿入にかかった時間[ns]")

plt.legend()
plt.show()

plt.scatter(N, build,label="計測値")

plt.grid(which='major',color='black',linestyle='-')
plt.grid(which='minor',color='black',linestyle='-')


plt.title("AVL木の構築時間")
plt.xlabel("ノード数")
plt.ylabel("構築にかかった時間[ms]")

plt.legend()
plt.show()

